static const uint8_t font2[][10] =
{
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 20
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00}, // 21 !
  {0x00,0x00,0x00,0x00,0x33,0x33,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x3F,0x3F,0x00,0x00,0x3F,0x3F,0x00,0x00}, // 22 "
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0x30,0x30,0xFF,0xFF,0x30,0x30,0xFF,0xFF,0x30,0x30}, // 23 #
  {0x03,0x03,0x3F,0x3F,0x03,0x03,0x3F,0x3F,0x03,0x03}, 
  {0x30,0x30,0xCC,0xCC,0xFF,0xFF,0xCC,0xCC,0x0C,0x0C}, // 24 $
  {0x0C,0x0C,0x0C,0x0C,0x3F,0x3F,0x0C,0x0C,0x03,0x03}, 
  {0x0F,0x0F,0x0F,0x0F,0xC0,0xC0,0x30,0x30,0x0C,0x0C}, // 25 %
  {0x0C,0x0C,0x03,0x03,0x00,0x00,0x3C,0x3C,0x3C,0x3C}, 
  {0x3C,0x3C,0xC3,0xC3,0x33,0x33,0x0C,0x0C,0x00,0x00}, // 26 &
  {0x0F,0x0F,0x30,0x30,0x33,0x33,0x0C,0x0C,0x33,0x33}, 
  {0x00,0x00,0x33,0x33,0x0F,0x0F,0x00,0x00,0x00,0x00}, // 27 '
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0xF0,0xF0,0x0C,0x0C,0x03,0x03,0x00,0x00}, // 28 (
  {0x00,0x00,0x03,0x03,0x0C,0x0C,0x30,0x30,0x00,0x00}, 
  {0x00,0x00,0x03,0x03,0x0C,0x0C,0xF0,0xF0,0x00,0x00}, // 29 )
  {0x00,0x00,0x30,0x30,0x0C,0x0C,0x03,0x03,0x00,0x00}, 
  {0x30,0x30,0xC0,0xC0,0xFC,0xFC,0xC0,0xC0,0x30,0x30}, // 2a *
  {0x03,0x03,0x00,0x00,0x0F,0x0F,0x00,0x00,0x03,0x03}, 
  {0xC0,0xC0,0xC0,0xC0,0xFC,0xFC,0xC0,0xC0,0xC0,0xC0}, // 2b +
  {0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 2c ,
  {0x00,0x00,0x33,0x33,0x0F,0x0F,0x00,0x00,0x00,0x00}, 
  {0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0}, // 2d -
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 2e .
  {0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x00,0x00,0xC0,0xC0,0x30,0x30,0x0C,0x0C}, // 2f /
  {0x0C,0x0C,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0xFC,0xFC,0x03,0x03,0xC3,0xC3,0x33,0x33,0xFC,0xFC}, // 30 0
  {0x0F,0x0F,0x33,0x33,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0x00,0x00,0x0C,0x0C,0xFF,0xFF,0x00,0x00,0x00,0x00}, // 31 1
  {0x00,0x00,0x30,0x30,0x3F,0x3F,0x30,0x30,0x00,0x00}, 
  {0x0C,0x0C,0x03,0x03,0x03,0x03,0xC3,0xC3,0x3C,0x3C}, // 32 2
  {0x30,0x30,0x3C,0x3C,0x33,0x33,0x30,0x30,0x30,0x30}, 
  {0x03,0x03,0x03,0x03,0x33,0x33,0xCF,0xCF,0x03,0x03}, // 33 3
  {0x0C,0x0C,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0xC0,0xC0,0x30,0x30,0x0C,0x0C,0xFF,0xFF,0x00,0x00}, // 34 4
  {0x03,0x03,0x03,0x03,0x03,0x03,0x3F,0x3F,0x03,0x03}, 
  {0x3F,0x3F,0x33,0x33,0x33,0x33,0x33,0x33,0xC3,0xC3}, // 35 5
  {0x0C,0x0C,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0xF0,0xF0,0xCC,0xCC,0xC3,0xC3,0xC3,0xC3,0x00,0x00}, // 36 6
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0x03,0x03,0x03,0x03,0xC3,0xC3,0x33,0x33,0x0F,0x0F}, // 37 7
  {0x00,0x00,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0x3C,0x3C,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0x3C,0x3C}, // 38 8
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0x3C,0x3C,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xFC,0xFC}, // 39 9
  {0x00,0x00,0x30,0x30,0x30,0x30,0x0C,0x0C,0x03,0x03}, 
  {0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00,0x00,0x00}, // 3a :
  {0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00,0x00,0x00}, // 3b ;
  {0x00,0x00,0x33,0x33,0x0F,0x0F,0x00,0x00,0x00,0x00}, 
  {0xC0,0xC0,0x30,0x30,0x0C,0x0C,0x03,0x03,0x00,0x00}, // 3c <
  {0x00,0x00,0x03,0x03,0x0C,0x0C,0x30,0x30,0x00,0x00}, 
  {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}, // 3d =
  {0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03}, 
  {0x00,0x00,0x03,0x03,0x0C,0x0C,0x30,0x30,0xC0,0xC0}, // 3e >
  {0x00,0x00,0x30,0x30,0x0C,0x0C,0x03,0x03,0x00,0x00}, 
  {0x0C,0x0C,0x03,0x03,0x03,0x03,0xC3,0xC3,0x3C,0x3C}, // 3f ?
  {0x00,0x00,0x00,0x00,0x33,0x33,0x00,0x00,0x00,0x00}, 
  {0x0C,0x0C,0xC3,0xC3,0xC3,0xC3,0x03,0x03,0xFC,0xFC}, // 40 @
  {0x0F,0x0F,0x30,0x30,0x3F,0x3F,0x30,0x30,0x0F,0x0F}, 
  {0xFC,0xFC,0x03,0x03,0x03,0x03,0x03,0x03,0xFC,0xFC}, // 41 A
  {0x3F,0x3F,0x03,0x03,0x03,0x03,0x03,0x03,0x3F,0x3F}, 
  {0xFF,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0x3C,0x3C}, // 42 B
  {0x3F,0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0xFC,0xFC,0x03,0x03,0x03,0x03,0x03,0x03,0x0C,0x0C}, // 43 C
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x0C,0x0C}, 
  {0xFF,0xFF,0x03,0x03,0x03,0x03,0x0C,0x0C,0xF0,0xF0}, // 44 D
  {0x3F,0x3F,0x30,0x30,0x30,0x30,0x0C,0x0C,0x03,0x03}, 
  {0xFF,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0x03,0x03}, // 45 E
  {0x3F,0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}, 
  {0xFF,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0x03,0x03}, // 46 F
  {0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0xFC,0xFC,0x03,0x03,0xC3,0xC3,0xC3,0xC3,0xCC,0xCC}, // 47 G
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x3F,0x3F}, 
  {0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFF,0xFF}, // 48 H
  {0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F}, 
  {0x00,0x00,0x03,0x03,0xFF,0xFF,0x03,0x03,0x00,0x00}, // 49 I
  {0x00,0x00,0x30,0x30,0x3F,0x3F,0x30,0x30,0x00,0x00}, 
  {0x00,0x00,0x00,0x00,0x03,0x03,0xFF,0xFF,0x03,0x03}, // 4a J
  {0x0C,0x0C,0x30,0x30,0x30,0x30,0x0F,0x0F,0x00,0x00}, 
  {0xFF,0xFF,0xC0,0xC0,0x30,0x30,0x0C,0x0C,0x03,0x03}, // 4b K
  {0x3F,0x3F,0x00,0x00,0x03,0x03,0x0C,0x0C,0x30,0x30}, 
  {0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 4c L
  {0x3F,0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}, 
  {0xFF,0xFF,0x0C,0x0C,0xF0,0xF0,0x0C,0x0C,0xFF,0xFF}, // 4d M
  {0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F}, 
  {0xFF,0xFF,0x30,0x30,0xC0,0xC0,0x00,0x00,0xFF,0xFF}, // 4e N
  {0x3F,0x3F,0x00,0x00,0x00,0x00,0x03,0x03,0x3F,0x3F}, 
  {0xFC,0xFC,0x03,0x03,0x03,0x03,0x03,0x03,0xFC,0xFC}, // 4f O
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0xFF,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0x3C,0x3C}, // 50 P
  {0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0xFC,0xFC,0x03,0x03,0x03,0x03,0x03,0x03,0xFC,0xFC}, // 51 Q
  {0x0F,0x0F,0x30,0x30,0x33,0x33,0x0C,0x0C,0x33,0x33}, 
  {0xFF,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0x3C,0x3C}, // 52 R
  {0x3F,0x3F,0x00,0x00,0x03,0x03,0x0C,0x0C,0x30,0x30}, 
  {0x3C,0x3C,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0x03,0x03}, // 53 S
  {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0x03,0x03,0x03,0x03,0xFF,0xFF,0x03,0x03,0x03,0x03}, // 54 T
  {0x00,0x00,0x00,0x00,0x3F,0x3F,0x00,0x00,0x00,0x00}, 
  {0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF}, // 55 U
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF}, // 56 V
  {0x03,0x03,0x0C,0x0C,0x30,0x30,0x0C,0x0C,0x03,0x03}, 
  {0xFF,0xFF,0x00,0x00,0xC0,0xC0,0x00,0x00,0xFF,0xFF}, // 57 W
  {0x0F,0x0F,0x30,0x30,0x0F,0x0F,0x30,0x30,0x0F,0x0F}, 
  {0x0F,0x0F,0x30,0x30,0xC0,0xC0,0x30,0x30,0x0F,0x0F}, // 58 X
  {0x3C,0x3C,0x03,0x03,0x00,0x00,0x03,0x03,0x3C,0x3C}, 
  {0x3F,0x3F,0xC0,0xC0,0x00,0x00,0xC0,0xC0,0x3F,0x3F}, // 59 Y
  {0x00,0x00,0x00,0x00,0x3F,0x3F,0x00,0x00,0x00,0x00}, 
  {0x03,0x03,0x03,0x03,0xC3,0xC3,0x33,0x33,0x0F,0x0F}, // 5a Z
  {0x3C,0x3C,0x33,0x33,0x30,0x30,0x30,0x30,0x30,0x30}, 
  {0x00,0x00,0xFF,0xFF,0x03,0x03,0x03,0x03,0x00,0x00}, // 5b [
  {0x00,0x00,0x3F,0x3F,0x30,0x30,0x30,0x30,0x00,0x00}, 
  {0x0C,0x0C,0x30,0x30,0xC0,0xC0,0x00,0x00,0x00,0x00}, // 5c
  {0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x0C,0x0C}, 
  {0x00,0x00,0x03,0x03,0x03,0x03,0xFF,0xFF,0x00,0x00}, // 5d ]
  {0x00,0x00,0x30,0x30,0x30,0x30,0x3F,0x3F,0x00,0x00}, 
  {0x30,0x30,0x0C,0x0C,0x03,0x03,0x0C,0x0C,0x30,0x30}, // 5e ^
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 5f _
  {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}, 
  {0x00,0x00,0x03,0x03,0x0C,0x0C,0x30,0x30,0x00,0x00}, // 60 `
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x30,0x30,0x30,0x30,0x30,0x30,0xC0,0xC0}, // 61 a
  {0x0C,0x0C,0x33,0x33,0x33,0x33,0x33,0x33,0x3F,0x3F}, 
  {0xFF,0xFF,0xC0,0xC0,0x30,0x30,0x30,0x30,0xC0,0xC0}, // 62 b
  {0x3F,0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0xC0,0xC0,0x30,0x30,0x30,0x30,0x30,0x30,0x00,0x00}, // 63 c
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x0C,0x0C}, 
  {0xC0,0xC0,0x30,0x30,0x30,0x30,0xC0,0xC0,0xFF,0xFF}, // 64 d
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x3F,0x3F}, 
  {0xC0,0xC0,0x30,0x30,0x30,0x30,0x30,0x30,0xC0,0xC0}, // 65 e
  {0x0F,0x0F,0x33,0x33,0x33,0x33,0x33,0x33,0x03,0x03}, 
  {0xC0,0xC0,0xFC,0xFC,0xC3,0xC3,0x03,0x03,0x0C,0x0C}, // 66 f
  {0x00,0x00,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0xF0,0xF0,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC}, // 67 g
  {0x00,0x00,0x33,0x33,0x33,0x33,0x33,0x33,0x0F,0x0F}, 
  {0xFF,0xFF,0xC0,0xC0,0x30,0x30,0x30,0x30,0xC0,0xC0}, // 68 h
  {0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F}, 
  {0x00,0x00,0x30,0x30,0xF3,0xF3,0x00,0x00,0x00,0x00}, // 69 i
  {0x00,0x00,0x30,0x30,0x3F,0x3F,0x30,0x30,0x00,0x00}, 
  {0x00,0x00,0x00,0x00,0x30,0x30,0xF3,0xF3,0x00,0x00}, // 6a j
  {0x0C,0x0C,0x30,0x30,0x30,0x30,0x0F,0x0F,0x00,0x00}, 
  {0xFF,0xFF,0x00,0x00,0xC0,0xC0,0x30,0x30,0x00,0x00}, // 6b k
  {0x3F,0x3F,0x03,0x03,0x0C,0x0C,0x30,0x30,0x00,0x00}, 
  {0x00,0x00,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,0x00}, // 6c l
  {0x00,0x00,0x30,0x30,0x3F,0x3F,0x30,0x30,0x00,0x00}, 
  {0xF0,0xF0,0x30,0x30,0xC0,0xC0,0x30,0x30,0xC0,0xC0}, // 6d m
  {0x3F,0x3F,0x00,0x00,0x03,0x03,0x00,0x00,0x3F,0x3F}, 
  {0xF0,0xF0,0xC0,0xC0,0x30,0x30,0x30,0x30,0xC0,0xC0}, // 6e n
  {0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F}, 
  {0xC0,0xC0,0x30,0x30,0x30,0x30,0x30,0x30,0xC0,0xC0}, // 6f o
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x30,0x30,0x0F,0x0F}, 
  {0xF0,0xF0,0x30,0x30,0x30,0x30,0x30,0x30,0xC0,0xC0}, // 70 p
  {0x3F,0x3F,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00}, 
  {0xC0,0xC0,0x30,0x30,0x30,0x30,0xC0,0xC0,0xF0,0xF0}, // 71 q
  {0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x3F,0x3F}, 
  {0xF0,0xF0,0xC0,0xC0,0x30,0x30,0x30,0x30,0xC0,0xC0}, // 72 r
  {0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, 
  {0xC0,0xC0,0x30,0x30,0x30,0x30,0x30,0x30,0x00,0x00}, // 73 s
  {0x30,0x30,0x33,0x33,0x33,0x33,0x33,0x33,0x0C,0x0C}, 
  {0x30,0x30,0xFF,0xFF,0x30,0x30,0x00,0x00,0x00,0x00}, // 74 t
  {0x00,0x00,0x0F,0x0F,0x30,0x30,0x30,0x30,0x0C,0x0C}, 
  {0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0}, // 75 u
  {0x0F,0x0F,0x30,0x30,0x30,0x30,0x0C,0x0C,0x3F,0x3F}, 
  {0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0}, // 76 v
  {0x03,0x03,0x0C,0x0C,0x30,0x30,0x0C,0x0C,0x03,0x03}, 
  {0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0}, // 77 w
  {0x0F,0x0F,0x30,0x30,0x0F,0x0F,0x30,0x30,0x0F,0x0F}, 
  {0x30,0x30,0xC0,0xC0,0x00,0x00,0xC0,0xC0,0x30,0x30}, // 78 x
  {0x30,0x30,0x0C,0x0C,0x03,0x03,0x0C,0x0C,0x30,0x30}, 
  {0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0}, // 79 y
  {0x00,0x00,0x33,0x33,0x33,0x33,0x33,0x33,0x0F,0x0F}, 
  {0x30,0x30,0x30,0x30,0x30,0x30,0xF0,0xF0,0x30,0x30}, // 7a z
  {0x30,0x30,0x3C,0x3C,0x33,0x33,0x30,0x30,0x30,0x30}, 
  {0x00,0x00,0xC0,0xC0,0x3C,0x3C,0x03,0x03,0x00,0x00}, // 7b {
  {0x00,0x00,0x00,0x00,0x0F,0x0F,0x30,0x30,0x00,0x00}, 
  {0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00}, // 7c |
  {0x00,0x00,0x00,0x00,0x3F,0x3F,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0x03,0x03,0x3C,0x3C,0xC0,0xC0,0x00,0x00}, // 7d }
  {0x00,0x00,0x30,0x30,0x0F,0x0F,0x00,0x00,0x00,0x00}, 
  {0x00,0x00,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0xC0,0xC0}, // 7e
  {0x03,0x03,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00}, 
  {0xC0,0xC0,0x3C,0x3C,0x03,0x03,0x3C,0x3C,0xC0,0xC0}, // 7f
  {0x3F,0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x3F,0x3F}, 
}; 
 