// spi_engine_display.h
#ifndef __SPI_ENGINE_DISPLAY_H__
#define __SPI_ENGINE_DISPLAY_H__
#include "display.h"


void DISPLAY_Driver_Init(void);
void DISPLAY_Refresh(void);
void DISPLAY_Orient( uint8_t mode );
void DISPLAY_TurnOff( void );
void DISPLAY_TurnOn( void );



#ifdef DISPLAY_128X64
  #define PAGES 8
#else
  #define PAGES 4
#endif  // DISPLAY_128X64

#define DISPLAY_DC_PIN       GPIO_Pin_8
#define DISPLAY_DC_PORT      GPIOA

#define DISPLAY_RESET_PIN    GPIO_Pin_9
#define DISPLAY_RESET_PORT   GPIOA

#define DISPLAY_CS_PIN       GPIO_Pin_12
#define DISPLAY_CS_PORT      GPIOB

#define DISPLAY_SCL_PIN      GPIO_Pin_13
#define DISPLAY_SCL_PORT     GPIOB

#define DISPLAY_SDA_PIN      GPIO_Pin_15
#define DISPLAY_SDA_PORT     GPIOB

#define SPI_PORT 2




#define DISPLAYMEM {&DisplayMap[0*DISPLAYCOLS],0,128,0}, \
    {&DisplayMap[1*DISPLAYCOLS],0,128,0}, \
    {&DisplayMap[2*DISPLAYCOLS],0,128,0}, \
    {&DisplayMap[3*DISPLAYCOLS],0,128,0}, \
    {&DisplayMap[4*DISPLAYCOLS],0,128,0}, \
    {&DisplayMap[5*DISPLAYCOLS],0,128,0}, \
    {&DisplayMap[6*DISPLAYCOLS],0,128,0}, \
    {&DisplayMap[7*DISPLAYCOLS],0,128,0}, \
    
#define DISPLAYMEM_ENUM  DISP_PAGE0, \
    DISP_PAGE1, \
    DISP_PAGE2, \
    DISP_PAGE3, \
    DISP_PAGE4, \
    DISP_PAGE5, \
    DISP_PAGE6, \
    DISP_PAGE7, 
    
   
#define DISPLAYPINS {DISPLAY_CS_PORT, DISPLAY_CS_PIN}, \
    {DISPLAY_DC_PORT, DISPLAY_DC_PIN}, \
    {DISPLAY_RESET_PORT, DISPLAY_RESET_PIN}, \
    

  
    
#define DISPLAYPIN_ENUM DISPLAY_CS, \
    DISPLAY_DC, \
    DISPLAY_RESET, \
    
 
#define DISPLAYPRG_ENUM  PRG_DISPLAY_REFRESH, \
  PRG_DISPLAY_TURNON, \
  PRG_DISPLAY_TURNOFF, \
  PRG_DISPLAY_ORIENT1, \
  PRG_DISPLAY_ORIENT2, \
  PRG_DISPLAY_INIT,
  
  
#define DISPLAYPRGS DISPLAY_Cmds_Refresh, \
 DISPLAY_Cmds_TurnOn, \
 DISPLAY_Cmds_TurnOff, \
 DISPLAY_Cmds_Orient1, \
 DISPLAY_Cmds_Orient2, \
 DISPLAY_Cmds_Init,


#endif // __SPI_ENGINE_DISPLAY_H__


// pins:

#ifdef LOAD_PINS
#undef LOAD_PINS
DISPLAYPINS
#endif // LOAD_PINS

#ifdef LOAD_PIN_IDS
#undef LOAD_PIN_IDS
DISPLAYPIN_ENUM
#endif // LOAD_PIN_IDS

// memory buffers:

#ifdef LOAD_BUFFERS
#undef LOAD_BUFFERS
DISPLAYMEM
#endif // LOAD_BUFFERS

#ifdef LOAD_BUFFER_IDS
#undef LOAD_BUFFER_IDS
DISPLAYMEM_ENUM
#endif // LOAD_BUFFER_IDS


#ifdef LOAD_PRG_IDS
#undef LOAD_IDS
DISPLAYPRG_ENUM
#endif // LOAD_PRG_IDS

#ifdef LOAD_PRGS
#undef LOAD_PRGS
DISPLAYPRGS
#endif // LOAD_PRGS

