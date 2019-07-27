#ifndef __DISPLAY_H__
#define __DISPLAY_H__

typedef struct Rect{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
} RECT;

typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t fcolor;
    int8_t bcolor;
    uint8_t flags;
} TEXTRECT;

typedef struct Image{
	uint16_t width;
	uint16_t height;
	uint8_t data[];
} IMAGE;

void DISPLAY_Init(void);
void DISPLAY_SetPixel( uint16_t x, uint16_t y, uint8_t bit );
void DISPLAY_Clear(void);
//void DISPLAY_RefreshPage( uint8_t page );
void DISPLAY_Line(int x0, int y0, int x1, int y1, uint16_t color);
void DISPLAY_Frame( RECT * rect, int color1, int color2 );
void DISPLAY_FillRectangle( RECT * rect, uint8_t color );
void DISPLAY_InvertRectangle( RECT * rect, int color1, int color2 );
void DISPLAY_PrintString( TEXTRECT * text, char * p );
void DISPLAY_TurnOn( void );
void DISPLAY_TurnOff( void );
uint8_t DISPLAY_SetFont( uint8_t font );
void DISPLAY_Orient( uint8_t mode );
void DISPLAY_Image( RECT * rect, const IMAGE * image );
uint16_t DISPLAY_StringWidth( char * p );
//void Splash( uint16_t mode );
void DISPLAY_ScrollLeft1(void);
void DISPLAY_SetGUI_Refresh(uint8_t mode );
void DISPLAY_Orientation( uint8_t orient );
void DISPLAY_OnOff( void );
void DISPLAY_InvertScreen( void );
extern uint8_t DisplayMap[]; //512 or 1024 bytes



#define DISPLAYCOLS 128

#ifdef DISPLAY_128X64
  #define DISPLAYROWS 64
#else
  #define DISPLAYROWS 32
#endif // DISPLAY_128X64    


#define ORIENT_UP   0
#define ORIENT_DOWN 1
	
#endif // __DISPLAY_H__
