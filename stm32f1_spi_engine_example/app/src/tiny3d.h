#ifndef TINY3D_H
#define TINY3D_H

// ----------------------------------------------
// defines
// ----------------------------------------------
#define PRES             16384
#define PSHIFT           14
#define PROUNDBIT        (1 << (PSHIFT-1))

// ----------------------------------------------
// typedef
// ----------------------------------------------
typedef struct {
  long x, y, z;
} Vector3;

typedef struct {
  int x, y, z;
} Vector3i;

// fixed point identity matrix
/*

typedef struct {
  long m[4][4] = {
      {PRES,    0,    0,    0},
      {   0, PRES,    0,    0},
      {   0,    0, PRES,    0},
      {   0,    0,    0, PRES}
  };
} Matrix4;




*/

typedef struct {
  long m[4][4];
}Matrix4;


void tiny3d_init(void);
void testrotate(void);
void tiny3d_redraw(void);
void tiny3d_orient(int16_t x, int16_t y, int16_t z);

#endif // TINY3D_H
