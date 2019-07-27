#include <stdint.h>
#include <string.h>
#include <stm32f10x.h>
#include <stm32f10x_conf.h>
#include <stm32_configuration.h>
#include <stm32f10x_tim.h>
#include "common.h"
#include "spi_engine.h"
#include "spi_engine_display.h"
#include "spi_engine_accelerometer.h"
#include "display.h"
#include "timer.h"
#include "utils.h"
#include "tiny3d.h"

#define INCLUDE_ACCEL

uint8_t buf[20];
int16_t xx=0;
int16_t yy=0;
int16_t zz=0;
int16_t xa=0;
int16_t ya=0;
int16_t za=0;

static uint8_t ledstate=0;

#define FONT0_HEIGHT 1
#define FONT1_HEIGHT 2
#define FONT2_HEIGHT 2
#define FONT3_HEIGHT 2

#define ORIENT_UP   0
#define ORIENT_DOWN 1

//============================================================================
//=======================[ GFXMGR_SetFont ]===================================
//============================================================================

uint8_t _current_fontheight=FONT0_HEIGHT;

uint8_t GFXMGR_SetFont( uint8_t font )
{
  static uint8_t savefont=0;
  uint8_t oldfont;
  DISPLAY_SetFont(font);
  // temp:
  if( font==0 ) _current_fontheight=FONT0_HEIGHT;
  if( font==1 ) _current_fontheight=FONT1_HEIGHT;
  if( font==2 ) _current_fontheight=FONT2_HEIGHT;
  if( font==3 ) _current_fontheight=FONT3_HEIGHT;
  oldfont=savefont;
  savefont=font;
  return oldfont;
}

//============================================================================
//=======================[ GFX_PrintLine ]====================================
//============================================================================

void GFX_PrintLine( uint8_t line, char * p )
{
  TEXTRECT txt;
  txt.x=0;
  txt.y=line*_current_fontheight;
  txt.width=DISPLAYCOLS;
  txt.height=_current_fontheight; //10; 20160601
  txt.fcolor=1;
  txt.bcolor=0;
  txt.flags=CLEARBG;
  DISPLAY_PrintString( &txt, p );
}

//============================================================================
//=======================[ SysTick_Handler ]==================================
//============================================================================

volatile uint32_t msticks;
volatile uint8_t mstick=0;

void SysTick_Handler(void)
{
  msticks++;
  mstick=mstick | 1;
}

//============================================================================
//=======================[ systickInit ]======================================
//============================================================================

void systickInit (uint16_t frequency)
{
  SysTick->LOAD = 9000 - 1;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}
 
//============================================================================
//=======================[ lu_angle ]=========================================
//============================================================================
#include "angles.h"

int16_t lu_angle( int16_t raw )
{
  int16_t dd;
  dd=raw;
  if( dd & 0x8000 )
  {
    if( dd< -16383 ) dd=-16383;
    dd=-dd;
    dd=dd>>6;
    dd=dd&0xFF;
    dd=angle[dd];
    raw=dd;
  }
  else
  {
    if( dd> 16383 ) dd=16383;
    dd=dd>>6;
    dd=dd&0xFF;
    dd=angle[dd];
    raw=360-dd;
  }
  return raw;
}

//============================================================================//
//=======================[ main ]=============================================//
//============================================================================//

#define INCLUDE_TINY3D
#define TEST3D 
 
int main()
{
  RCC_Configuration();
  NVIC_Configuration();

  GPIO_Configuration();

  systickInit(1000);
  
  timer_init();  
   
  DISPLAY_Driver_Init();
  DISPLAY_Init();
  DISPLAY_SetFont(0);
  DISPLAY_Clear();
    
  ACCEL_Driver_Init();
    
  {
    TEXTRECT txt;
    txt.x=0;
    txt.y=1; //line*_current_fontheight;
    txt.width=DISPLAYCOLS;
    txt.height=8;// _current_fontheight; //10; 20160601
    txt.fcolor=1;
    txt.bcolor=0;
    txt.flags=CLEARBG;
    DISPLAY_PrintString( &txt,  "Here" );
    DISPLAY_Refresh();
  }


  DISPLAY_Orient(1);

  #ifdef INCLUDE_ACCEL    
    ACCEL_Read(); // starts accelerometer interrupts
    // from now on it will run continuously
  #endif // INCLUDE_ACCEL     

  #ifdef INCLUDE_TINY3D      
    tiny3d_init();
  #endif // INCLUDE_TINY3D 

  while(1)
  {
    #ifdef INCLUDE_ACCEL 
      static uint16_t trigger=0;
    #endif // INCLUDE_ACCEL 
         
      static uint16_t mscount=0;

      while( mscount<50 )
      {
        if( mstick )
        {
          mstick=0;
          mscount++;
        }
      } // end while tick
        
      mscount=0;

      if( ledstate==0 ) 
      {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        ledstate=1;
      }
      else
      {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        ledstate=0;
      }

  #ifdef INCLUDE_ACCEL        
      trigger++;
      if( trigger==4 )
      {
        trigger=0;
        memset( buf, 0, sizeof(buf) );
        yy=ACCEL_data(0);
        ya=lu_angle(yy);
        
        xx=ACCEL_data(1);
        xa=lu_angle(xx);
          
        zz=ACCEL_data(2);

        zz=-zz;
        za=lu_angle(zz);
          
        Util_bin2hex16( buf, xx );
        GFX_PrintLine(0, (char *)buf);
          
        Util_16bin2dec( buf, xa );
        GFX_PrintLine(1, (char *)buf);          

        #ifdef TEST3D          
          tiny3d_orient( xa, ya, 0 );
          tiny3d_redraw();          
        #endif // TEST3D 
      }
      
      if( ACCEL_data_ready() )
      {
        ACCEL_Smooth();
        ACCEL_Read();
        DISPLAY_Refresh();
      }
  #endif // INCLUDE_ACCEL        

    } // end while(1)
}


