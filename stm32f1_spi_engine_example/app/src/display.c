#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "common.h"
#include "display.h"

// Routines based on previous work by Don Jindra

// primary conditional build switches
#define INCLUDE_PIXELS
 #define INCLUDE_LINES        // needs INCLUDE_PIXELS
// #define INCLUDE_RECTANGLES   // needs INCLUDE_PIXELS
#define INCLUDE_FILL
// #define INCLUDE_IMAGES        // needs INCLUDE_PIXELS
#define INCLUDE_TEXT
#define INCLUDE_SCROLL

// include font(s)
#ifdef INCLUDE_TEXT 
#include "font1.h"
#include "font2.h"
#endif // INCLUDE_TEXT 

static uint8_t _orientation=0;
uint8_t DisplayMap[16*DISPLAYROWS]; //512 or 1024 bytes
static uint8_t _font=0;

//============================================================================

// Point into local display memory with this structure.
// rowp points to the appropriate byte
// bitmask is the bit to use in that byte

typedef struct DISPLAYptr{
  uint8_t * rowp;
  uint8_t bitmask;
} DISPLAY_t;

//============================================================================
//=======================[ _gotoXY ]==========================================
//============================================================================

// for text, if needed

static void _gotoXY(int x, int y) 
{
}

//============================================================================
//=======================[ _getRow ]==========================================
//============================================================================

static void _getRow( uint16_t row, DISPLAY_t * p )
{
  p->rowp=DisplayMap+(DISPLAYCOLS*(row>>3));  // image is vertical so each byte is 8 rows
  p->bitmask=0x1<<(row&7);
}

//============================================================================
//=======================[ _getRows ]=========================================
//============================================================================

#ifdef INCLUDE_FILL

uint8_t _getRows( uint16_t row, DISPLAY_t * p )
{
  p->rowp=DisplayMap+(DISPLAYCOLS*(row>>3));  // image is vertical so each byte is 8 rows
  p->bitmask=0x0FF<<(row&7);
  return 8-(row&7);
}

#endif // INCLUDE_FILL

//============================================================================
//=======================[ DISPLAY_SetPixel ]=====================================
//============================================================================

#ifdef INCLUDE_PIXELS

void DISPLAY_SetPixel( uint16_t x, uint16_t y, uint8_t bit )
{
  DISPLAY_t d;
  
  if( _orientation==0 )
  {
    if( (x<DISPLAYCOLS) && (y<DISPLAYROWS) )
    {
      _getRow( y, &d );
      if( bit )
      {
        d.rowp[x]=d.rowp[x] | d.bitmask;
      }
      else
      {
        d.rowp[x]=d.rowp[x] & (~d.bitmask);
      }
    }
  }
  else
  {
    x=31-x;  

    if( (y<DISPLAYCOLS) && (x<DISPLAYROWS) )
    {
      _getRow( x, &d );
      if( bit )
      {
        d.rowp[y]=d.rowp[y] | d.bitmask;
      }
      else
      {
        d.rowp[y]=d.rowp[y] & (~d.bitmask);
      }
    }      
  }
}

#endif // INCLUDE_PIXELS

//============================================================================
//=======================[ DISPLAY_Clear ]========================================
//============================================================================

void DISPLAY_Clear(void) 
{
  DISPLAY_t d;
  _getRow( 0, &d );
  memset( d.rowp, 0, DISPLAYCOLS*(DISPLAYROWS>>3) );

  _gotoXY( 0, 0 ); //After we clear the display, return to the home position
}

//============================================================================
//=======================[ _absv ]============================================
//============================================================================

#ifdef INCLUDE_LINES

// a simple absolute value function

static int _absv( int x )
{
  if( x<0 ) x=0-x;
  return x;
}

#endif // INCLUDE_LINES

//============================================================================
//=======================[ DISPLAY_Line ]=====================================
//============================================================================

#ifdef INCLUDE_LINES

// draw a line from (x0,x0) to (x1,y1)

void DISPLAY_Line(int x0, int y0, int x1, int y1, uint16_t color) 
{
  int dx = _absv(x1-x0); 
  int sx = x0<x1 ? 1 : -1;
  
  int dy = _absv(y1-y0); 
  int sy = y0<y1 ? 1 : -1; 
  
  int err = (dx>dy ? dx : -dy)/2;
  int e2;
 
  for(;;)
  {
    DISPLAY_SetPixel(x0,y0, color);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) 
    { 
      err -= dy; 
      x0 += sx; 
    }
    if (e2 < dy) 
    { 
      err += dx; 
      y0 += sy; 
    }
  }
}

#endif // INCLUDE_LINES

//============================================================================
//=======================[ DISPLAY_Frame]=====================================
//============================================================================

#ifdef INCLUDE_RECTANGLES

// basically, draw a box frame

void DISPLAY_Frame( RECT * rect, int color1, int color2 )
{
  int xi;
  int yi;
  int xlimit;
  int ylimit;
  
  xlimit=rect->x+rect->width-1;
  ylimit=rect->y+rect->height-1;

  // top & bottom  
  for( xi=rect->x; xi<=xlimit; xi++ )
  {
    DISPLAY_SetPixel( xi, rect->y, color1 );
    DISPLAY_SetPixel( xi, ylimit, color2 );
  }

  // left & right
  if( rect->height>2 )
  {  
    for( yi=rect->y+1; yi<=ylimit-1; yi++ )
    {
      DISPLAY_SetPixel( rect->x, yi, color2 );
      DISPLAY_SetPixel( xlimit, yi, color1 );
    }
  }
}

#endif // INCLUDE_RECTANGLES

//============================================================================
//=======================[ DISPLAY_FillRectangle ]============================
//============================================================================

#ifdef INCLUDE_FILL

void DISPLAY_FillRectangle( RECT * rect, uint8_t color )
{
  DISPLAY_t d;
  uint16_t pagerows;
  uint16_t y;
  uint16_t i;
  RECT lrect;

  if(_orientation==1)
  {
    lrect.y=(DISPLAYROWS)-rect->x;
    lrect.y=lrect.y-rect->width;
    lrect.x=rect->y;
    lrect.height=rect->width;
    lrect.width=rect->height;
    rect=&lrect;
  } // end orientation=horizontal
	
  y=rect->y;
  if(y>DISPLAYROWS-1) return;
  uint16_t remainingrows=rect->height;
  if( (y+remainingrows) > (DISPLAYROWS) ) remainingrows=(DISPLAYROWS-y);

  // todo: clip x
	
  while( remainingrows)
  {
    pagerows=_getRows( y, &d);
    if( pagerows>remainingrows)
    {
      //limit mask
      uint8_t mask2= 0xFF>>(pagerows-remainingrows);
      d.bitmask=d.bitmask&mask2;
      pagerows=remainingrows;
    }
    if( color==1 )
    {
      for( i=rect->x; i<(rect->x+rect->width); i++ )
      {
        d.rowp[i]=d.rowp[i] | d.bitmask;
      }
    }
    else
    {
      d.bitmask=d.bitmask ^ 0xFF;
      for( i=rect->x; i<(rect->x+rect->width); i++ )
      {
        d.rowp[i]=d.rowp[i] & d.bitmask;
      }
    }
    remainingrows=remainingrows-pagerows;
    y=y+pagerows;
  } // end while
}
#endif // INCLUDE_FILL

//============================================================================
//=======================[ DISPLAY_InvertRectangle ]==========================
//============================================================================

#ifdef INCLUDE_RECTANGLES

void DISPLAY_InvertRectangle( RECT * rect, int color1, int color2 )
{
}

#endif // INCLUDE_RECTANGLES

//============================================================================
//=======================[ DISPLAY_InvertScreen ]=============================
//============================================================================

void DISPLAY_InvertScreen( void )
{
  uint16_t i;
  for( i=0; i<sizeof(DisplayMap); i++ )
  {
    DisplayMap[i]=DisplayMap[i]^0xFF;
  }
}

//============================================================================
//=======================[ IMAGES ]===========================================
//============================================================================

#ifdef INCLUDE_IMAGES

void DISPLAY_Image( RECT * rect, const IMAGE * image )
{
  uint8_t c;
  uint8_t mask=0;
  uint16_t i;
  uint16_t imgx;
  uint16_t height;
  uint16_t imgy;
  uint8_t * p;
  uint16_t width;

  if( rect )
  {
    imgy=rect->y;
    p=( uint8_t * ) &image->width;
    width=*p;
    p=( uint8_t * ) &image->height;
    height=*p;
    p=( uint8_t * )&image->data[0];
  
    while( height-- )
    {
      imgx=rect->x; // start of row
      // do all of this row
      for( i=0; i<width; i++ )    
      {
        if( mask==0 ) // any more pixel data in the byte?
        {
          // no, load another
          mask=0x80; // start at msbit
          c=*p++;
        }
        DISPLAY_SetPixel( imgx++, imgy, c&mask ); 
        mask=mask>>1;
      }
      imgy++; // next row down
      mask=0; // force an end of data in this image byte
    } // end while height
  } // end rect
}

#endif // INCLUDE_IMAGES

//============================================================================
//=======================[ TEXT ]=============================================
//============================================================================

#ifdef INCLUDE_TEXT

//============================================================================
//=======================[ DISPLAY_PrintString ]==============================
//============================================================================

void DISPLAY_PrintString( TEXTRECT * text, char * p )
{
  uint8_t * dp;
  uint8_t b;
  uint8_t c;
  uint8_t i;

  c=*p++;
  
  if( _font==0 )
  {
    dp=DisplayMap+(text->y*128+text->x);
    while( c )
    {
      for( i=0; i<5; i++ )
      {
        b=font1[c - 0x20][i];
        *dp++=b;
      }
      *dp++=0;
      c=*p++;
    } // end while
  }
  else
  {
    dp=DisplayMap+(text->y*128*2+text->x);
    uint8_t * dp2=dp+128;
    uint8_t b2;
    while( c )
    {
      for( i=0; i<10; i++ )
      {
        b=font2[(c-0x20)*2][i];
        b2=font2[(c-0x20)*2+1][i];
        *dp++=b;
        *dp2++=b2;
      }
      *dp++=0;
      *dp2++=0;
      c=*p++;
    } // end while
  }
}

//============================================================================
//=======================[ DISPLAY_StringWidth ]==============================
//============================================================================

uint16_t DISPLAY_StringWidth( char * p )
{
  uint16_t width=0;
  return width;     
}

#endif // INCLUDE_TEXT

//============================================================================
//=======================[ DISPLAY_SetFont ]==================================
//============================================================================

uint8_t DISPLAY_SetFont( uint8_t font )
{
  _font=font;
  return 0;
}

//============================================================================
//=======================[ DISPLAY_ScrollLeft1 ]==============================
//============================================================================
#ifdef INCLUDE_SCROLL

void DISPLAY_ScrollLeft1(void)
{
  DISPLAY_t d;  
  _getRow( 0, &d ); // y=0
  memcpy( d.rowp, d.rowp+1 , DISPLAYCOLS-1 );
  d.rowp[DISPLAYCOLS-1]=0;
  _getRow( 8, &d ); // y=8
  memcpy( d.rowp, d.rowp+1 , DISPLAYCOLS-1 );
  d.rowp[DISPLAYCOLS-1]=0;
  _getRow( 16, &d ); // y=16
  memcpy( d.rowp, d.rowp+1 , DISPLAYCOLS-1 );
  d.rowp[DISPLAYCOLS-1]=0;
  _getRow( 24, &d ); // y=24
  memcpy( d.rowp, d.rowp+1 , DISPLAYCOLS-1 );
  d.rowp[DISPLAYCOLS-1]=0;
}

#endif // INCLUDE_SCROLL

//============================================================================
//=======================[ DISPLAY_Orientation ]==============================
//============================================================================

void DISPLAY_Orientation( uint8_t orient )
{
  _orientation=orient;
}

//============================================================================
//=======================[ DISPLAY_Init ]=====================================
//============================================================================

void DISPLAY_Init(void )
{
  DISPLAY_SetFont(0);
}

