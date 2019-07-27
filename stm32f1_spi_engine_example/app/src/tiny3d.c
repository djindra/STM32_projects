#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "common.h"
#include "display.h"
#include "tiny3d.h"

//  This code is ported from:
//
//    Arduino - Tiny 3D Engine
//    by Themistokle "mrt-prodz" Benetatos
//    https://github.com/mrt-prodz/ATmega328-Tiny-3D-Engine/blob/master/tiny_3d_engine.ino


#define COLOR0 0
#define COLOR1 1
#define COLOR2 1

// ----------------------------------------------
// test meshes
// ----------------------------------------------

#include "mesh_test2.h"

#define EDGE(a, b) faces[a][b]
#define NODE(a, b) nodes[a][b]

const Matrix4 matrix_init={{
      {PRES,    0,    0,    0},
      {   0, PRES,    0,    0},
      {   0,    0, PRES,    0},
      {   0,    0,    0, PRES}
  }};

// ----------------------------------------------
// defines
// ----------------------------------------------
#define SCREENW         128
#define SCREENH         64
#define HALFW            64
#define HALFH            32

#define FOV              64

#define NUMTYPES 4                           // number of render types
#define LUT(a) (long)(pgm_read_word(&lut[a]))// return value from LUT in PROGMEM


void drawPixel( int x,int y, uint16_t color)
{
    DISPLAY_SetPixel( x, y, color );
}

void drawLine(int x0, int y0, int x1, int y1, uint16_t color)
{
     DISPLAY_Line(x0,y0,x1,y1, color);
}

void fillTriangle( int p1, int p2, int p3, int p4, int p5, int p6, uint16_t color)
{
}

//#define DEBUG                              // uncomment this for debugging output to serial (leave disabled to save memory if needed)

// ----------------------------------------------
// global variables
// ----------------------------------------------
Matrix4 m_world;

Vector3i mesh_rotation_start = {90, 90, 0};
  
Vector3i mesh_rotation = {90, 0, 0};
//Vector3i mesh_position = {0, 0, 0};

const unsigned int lut[] = {         // 0 to 90 degrees fixed point COSINE look up table
  16384, 
  16381, 
  16374, 
  16361, 
  16344, 
  16321, 
  16294, 
  16261, 
  16224, 
  16182, 
  16135, 
  16082, 
  16025, 
  15964, 
  15897, 
  15825, 
  15749, 
  15668, 
  15582, 
  15491, 
  15395, 
  15295, 
  15190, 
  15081, 
  14967, 
  14848, 
  14725, 
  14598, 
  14466, 
  14329, 
  14188, 
  14043, 
  13894, 
  13740, 
  13582, 
  13420, 
  13254, 
  13084, 
  12910, 
  12732, 
  12550, 
  12365, 
  12175, 
  11982, 
  11785, 
  11585, 
  11381, 
  11173, 
  10963, 
  10748, 
  10531, 
  10310, 
  10086, 
  9860, 
  9630, 
  9397, 
  9161, 
  8923, 
  8682, 
  8438, 
  8191, 
  7943, 
  7691, 
  7438, 
  7182, 
  6924, 
  6663, 
  6401, 
  6137, 
  5871, 
  5603, 
  5334, 
  5062, 
  4790, 
  4516, 
  4240, 
  3963, 
  3685, 
  3406, 
  3126, 
  2845, 
  2563, 
  2280, 
  1996, 
  1712, 
  1427, 
  1142, 
  857, 
  571, 
  285, 
  0
};

static int proj_nodes[NODECOUNT][2];         // projected nodes (x,y)
static int old_nodes[NODECOUNT][2];          // projected nodes of previous frame to check if we need to redraw
static unsigned char i;
static unsigned char draw_type = 1;          // 0 - vertex | 1 - wireframe | 2 - flat colors | ...


// fixed point multiplication
static long pMultiply(long x, long y) {
  return ( (x * y) + PROUNDBIT) >> PSHIFT;
}

// ----------------------------------------------
// SIN/COS from 90 degrees LUT
// ----------------------------------------------
long SIN(unsigned int angle) 
{
  angle += 90;
  if (angle > 450) return lut[0];
  if (angle > 360 && angle < 451) return -lut[angle-360];
  if (angle > 270 && angle < 361) return -lut[360-angle];
  if (angle > 180 && angle < 271) return  lut[angle-180];
  return lut[180-angle];
}

long COS(unsigned int angle) 
{
  if (angle > 360) return lut[0];
  if (angle > 270 && angle < 361) return  lut[360-angle];
  if (angle > 180 && angle < 271) return -lut[angle-180];
  if (angle > 90  && angle < 181) return -lut[180-angle];
  return lut[angle];
}

// ----------------------------------------------
// Matrix operation
// ----------------------------------------------
Matrix4 mMultiply(  Matrix4 mat1,  Matrix4 mat2 ) 
{
  Matrix4 mat=matrix_init;
  
  unsigned char r,c;
  for( c=0; c<4; c++ )
    for( r=0; r<4; r++ )
      mat.m[c][r] = pMultiply(mat1.m[0][r], mat2.m[c][0]) +
                    pMultiply(mat1.m[1][r], mat2.m[c][1]) +
                    pMultiply(mat1.m[2][r], mat2.m[c][2]) +
                    pMultiply(mat1.m[3][r], mat2.m[c][3]);
  return mat;
}

Matrix4 mRotateX( const unsigned int angle ) 
{
  Matrix4 mat=matrix_init;
  
  mat.m[1][1] =  COS(angle);
  mat.m[1][2] =  SIN(angle);
  mat.m[2][1] = -SIN(angle);
  mat.m[2][2] =  COS(angle);
  return mat;
}

Matrix4 mRotateY( const unsigned int angle ) 
{
  Matrix4 mat=matrix_init;
  
  mat.m[0][0] =  COS(angle);
  mat.m[0][2] = -SIN(angle);
  mat.m[2][0] =  SIN(angle);
  mat.m[2][2] =  COS(angle);
  return mat;
}

Matrix4 mRotateZ( const unsigned int angle ) 
{
  Matrix4 mat=matrix_init;
  
  mat.m[0][0] =  COS(angle);
  mat.m[0][1] =  SIN(angle);
  mat.m[1][0] = -SIN(angle);
  mat.m[1][1] =  COS(angle);
  return mat;
}

Matrix4 mTranslate( const long x, const long y, const long z ) 
{
  Matrix4 mat=matrix_init;
  
  mat.m[3][0] =  x << PSHIFT;
  mat.m[3][1] =  y << PSHIFT;
  mat.m[3][2] =  z << PSHIFT;
  return mat;
}

Matrix4 mScale( const float ratio ) 
{
  Matrix4 mat=matrix_init;
  
  mat.m[0][0] *= ratio;
  mat.m[1][1] *= ratio;
  mat.m[2][2] *= ratio;
  return mat;
}

// ----------------------------------------------
// Shoelace algorithm to get the surface
// ----------------------------------------------
int shoelace( int (*n)[2],  unsigned char index ) 
{
  unsigned char t;
  int surface = 0;
  for( t=0; t<3; t++ ) 
  {
    // (x1y2 - y1x2) + (x2y3 - y2x3) ...
    surface += (n[EDGE(index,t)][0]           * n[EDGE(index,(t<2?t+1:0))][1]) -
               (n[EDGE(index,(t<2?t+1:0))][0] * n[EDGE(index,t)][1]);
  }
  return surface / 2;
}

typedef uint8_t bool;
#define true 1
#define false 0
uint8_t hiding=1;
//#define FULLTRIANGLE

// ----------------------------------------------
// Shoelace algorithm for triangle visibility
// ----------------------------------------------
bool is_hidden( int (*n)[2], unsigned char index) 
{
  if( hiding==0 ) return false;
  // (x1y2 - y1x2) + (x2y3 - y2x3) ...
  return ( ( (n[EDGE(index,0)][0] * n[EDGE(index,1)][1]) -
             (n[EDGE(index,1)][0] * n[EDGE(index,0)][1])   ) +
           ( (n[EDGE(index,1)][0] * n[EDGE(index,2)][1]) -
             (n[EDGE(index,2)][0] * n[EDGE(index,1)][1])   ) +
           ( (n[EDGE(index,2)][0] * n[EDGE(index,0)][1]) -
             (n[EDGE(index,0)][0] * n[EDGE(index,2)][1])   ) ) < 0 ? false : true;
}

// ----------------------------------------------
// draw projected nodes
// ----------------------------------------------
void draw_vertex(int (*n)[2], uint16_t color) 
{
  i = NODECOUNT-1;
  do {
    drawPixel(n[i][0],n[i][1], color);
  } while(i--);
}

// ----------------------------------------------
// draw edges between projected nodes
// ----------------------------------------------
void draw_wireframe(int (*n)[2], uint16_t color) 
{
  i = TRICOUNT-1;
  do 
  {
    // don't draw triangle with negative surface value
    if( !is_hidden(n, i) ) 
    {
      // draw triangle edges - 0 -> 1 -> 2 -> 0
      drawLine(n[EDGE(i,0)][0], n[EDGE(i,0)][1], n[EDGE(i,1)][0], n[EDGE(i,1)][1], color);
      drawLine(n[EDGE(i,1)][0], n[EDGE(i,1)][1], n[EDGE(i,2)][0], n[EDGE(i,2)][1], color);
    #ifdef FULLTRIANGLE
      drawLine(n[EDGE(i,2)][0], n[EDGE(i,2)][1], n[EDGE(i,0)][0], n[EDGE(i,0)][1], color);
    #endif // FULLTRIANGLE
    }
  } 
  while(i--);
}

// ----------------------------------------------
// draw flat color (not flat shading)
// ----------------------------------------------
void draw_flat_color( int (*n)[2], uint16_t color) 
{
  i = TRICOUNT-1;
  int surface;
  uint16_t col = color;
  do 
  {
    // draw only triangles facing us
    if ((surface=shoelace(n, i)) < 0) 
    {
      // this is an ugly hack but it 'somehow' fakes shading
      // depending on the size of the surface of the triangle
      // change the color toward brighter/darker
      color = col * (surface * 0.001);

      fillTriangle(n[EDGE(i,0)][0], n[EDGE(i,0)][1],
                       n[EDGE(i,1)][0], n[EDGE(i,1)][1],
                       n[EDGE(i,2)][0], n[EDGE(i,2)][1],
                       color);
    }
  } 
  while(i--);
}

// ----------------------------------------------
// clear frame using bounding box (dirty mask)
// ----------------------------------------------
void clear_dirty(int (*n)[2]) 
{
  unsigned char x0=DISPLAYCOLS, y0=DISPLAYROWS, x1=0, y1=0, c;
  // get bounding box of mesh
  for (c=0; c<NODECOUNT; c++) {
    if (n[c][0] < x0) x0 = n[c][0];
    if (n[c][0] > x1) x1 = n[c][0];
    if (n[c][1] < y0) y0 = n[c][1];
    if (n[c][1] > y1) y1 = n[c][1];
  }
  // clear area
  RECT rect;
  rect.x=x0;
  rect.y=y0;
  rect.width=x1-x0+1;
  rect.height=y1-y0+1;
  DISPLAY_FillRectangle( &rect, COLOR0 );
}

// ----------------------------------------------
// write current drawing mode in corner of screen
// ----------------------------------------------
void draw_print(const int16_t color) 
{
}

// ----------------------------------------------
// setup
// ----------------------------------------------
void tiny3d_init(void) 
{
}

static int16_t up=50;
 
void testrotate(void)
{
    // rotation
    m_world = mRotateX(mesh_rotation.x);
    m_world = mMultiply(mRotateY(mesh_rotation.y), m_world);
    m_world = mMultiply(mRotateZ(mesh_rotation.z), m_world);
    // scaling
    //m_world = mMultiply(mScale(1.5), m_world);

    // project nodes with world matrix
    Vector3i p;
    for (i=0; i<NODECOUNT; i++) 
    {
      p.x = (m_world.m[0][0] * (NODE(i,0) >> PSHIFT)+
             m_world.m[1][0] * (NODE(i,1) >> PSHIFT) +
             m_world.m[2][0] * (NODE(i,2) >> PSHIFT) +
             m_world.m[3][0]) / PRES;
      
      p.y = (m_world.m[0][1] * (NODE(i,0) >> PSHIFT) +
             m_world.m[1][1] * (NODE(i,1) >> PSHIFT) +
             m_world.m[2][1] * (NODE(i,2) >> PSHIFT) +
             m_world.m[3][1]) / PRES;
            
      p.z = (m_world.m[0][2] * (NODE(i,0) >> PSHIFT) +
             m_world.m[1][2] * (NODE(i,1) >> PSHIFT) +
             m_world.m[2][2] * (NODE(i,2) >> PSHIFT) +
             m_world.m[3][2]) / PRES;

      // store projected node
      proj_nodes[i][0] = (FOV * p.x) / (FOV + p.z) + HALFW;
      proj_nodes[i][1] = (FOV * p.y) / (FOV + p.z) + HALFH;
    }

    if(up>=0)
    {
    // auto-rotation mode
      mesh_rotation.x+=1;
      mesh_rotation.y+=1;
      mesh_rotation.z++;
      up=up-1;
      if( up==0 )
      {
          up=-50;
      }
    }

    else
    {
      mesh_rotation.x-=1;
      mesh_rotation.y-=1;
      mesh_rotation.z--;
      up=up+1;
      if( up==0 )
      {
          up=50;
      }
    }

    if (mesh_rotation.x > 360) mesh_rotation.x = 0;
    if (mesh_rotation.y > 360) mesh_rotation.y = 0;
    if (mesh_rotation.z > 360) mesh_rotation.z = 0;
    
    if (mesh_rotation.x < 0) mesh_rotation.x = 360;
    if (mesh_rotation.y < 0) mesh_rotation.y = 360;
    if (mesh_rotation.z < 0) mesh_rotation.z = 360;
}

//============================================================================
//=======================[ tiny3d_orient ]====================================
//============================================================================

void tiny3d_orient(int16_t x, int16_t y, int16_t z)
{
  // rotation
  m_world=matrix_init;
  m_world = mRotateX(x);
  m_world = mMultiply(mRotateY(y), m_world);
  m_world = mMultiply(mRotateZ(z), m_world);

  // project nodes with world matrix
  Vector3i p;
  for (i=0; i<NODECOUNT; i++) 
  {
    p.x = (m_world.m[0][0] * (NODE(i,0) >> PSHIFT)+
           m_world.m[1][0] * (NODE(i,1) >> PSHIFT) +
           m_world.m[2][0] * (NODE(i,2) >> PSHIFT) +
           m_world.m[3][0]) / PRES;
      
    p.y = (m_world.m[0][1] * (NODE(i,0) >> PSHIFT) +
           m_world.m[1][1] * (NODE(i,1) >> PSHIFT) +
           m_world.m[2][1] * (NODE(i,2) >> PSHIFT) +
           m_world.m[3][1]) / PRES;
            
    p.z = (m_world.m[0][2] * (NODE(i,0) >> PSHIFT) +
           m_world.m[1][2] * (NODE(i,1) >> PSHIFT) +
           m_world.m[2][2] * (NODE(i,2) >> PSHIFT) +
           m_world.m[3][2]) / PRES;

    // store projected node
    proj_nodes[i][0] = (FOV * p.x) / (FOV + p.z) + HALFW;
    proj_nodes[i][1] = (FOV * p.y) / (FOV + p.z) + HALFH;
  }
}

//============================================================================
//=======================[ tiny3d_redraw ]====================================
//============================================================================

void tiny3d_redraw(void)
{
  // only redraw if nodes position have changed (less redraw - less flicker)
  if (memcmp(old_nodes, proj_nodes, sizeof(proj_nodes))) 
  {
    // render frame
    switch(draw_type) 
    {
      case 0: draw_vertex(old_nodes, COLOR0);
              draw_vertex(proj_nodes, COLOR1);
              break;
      case 1: if (TRICOUNT > 32) clear_dirty(old_nodes);
              else draw_wireframe(old_nodes, COLOR0);
              draw_wireframe(proj_nodes, COLOR1);
              break;
    }
    // copy projected nodes to old_nodes to check if we need to redraw next frame
    memcpy(old_nodes, proj_nodes, sizeof(proj_nodes));
  }
}
