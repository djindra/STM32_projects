// spi_engine.c
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stm32f10x.h>

#include "common.h"
#include "utils.h"
#include <stm32_configuration.h>
#include "spi_engine.h"

// PERIPHERALS:
#include "spi_engine_display.h"
#include "spi_engine_accelerometer.h"

static void _spi_queue( uint8_t pnum );
static void _spi_prg_start( void );
static void _spi_int_on(void);
static void _start_dma(uint8_t page);

//   SPI1 - MOSI = PA7
//          MISO = PA6
//          SCK  = PA5
//          NSS  = PA4
//
//   DMA1 SPI1 RX = Channel 2
//   DMA1 SPI1 TX = Channel 3

//   SPI2 - MOSI = PB15
//          MISO = PB14
//          SCK  = PB13
//          NSS  = PB12
//
//   DMA1 SPI/I2S2 RX = Channel 4
//   DMA1 SPI/I2S2 TX = Channel 5



spi_io_t _iopin[]={
// PERIPHERALS:
#define LOAD_PINS
  #include "spi_engine_display.h"
#define LOAD_PINS
  #include "spi_engine_accelerometer.h"
};

enum{
// PERIPHERALS:
#define LOAD_PIN_IDS
  #include "spi_engine_display.h"
#define LOAD_PIN_IDS
  #include "spi_engine_accelerometer.h"
};

// memory buffers

const membuffer_t _buffer[]={
// PERIPHERALS:
#define LOAD_BUFFERS
  #include "spi_engine_display.h"
#define LOAD_BUFFERS
  #include "spi_engine_accelerometer.h"
};

// memory buffer ids

enum{
// PERIPHERALS:
#define LOAD_BUFFER_IDS
  #include "spi_engine_display.h"
#define LOAD_BUFFER_IDS
  #include "spi_engine_accelerometer.h"
};

// list of available programs: ids or index
// These are triggera at a bit position.
enum{
// PERIPHERALS:
#define LOAD_PRG_IDS
  #include "spi_engine_display.h"
#define LOAD_PRG_IDS
  #include "spi_engine_accelerometer.h"
};

// drivers:
// PERIPHERALS: C
#include "spi_engine_display.c"
#include "spi_engine_accelerometer.c"

// list of available programs: pointers
static const uint8_t * _spi_program[]={
// PERIPHERALS:
#define LOAD_PRGS
  #include "spi_engine_display.h"
#define LOAD_PRGS
  #include "spi_engine_accelerometer.h"
};


#if SPI_PORT==2 
#define SPI_IRQ_CHANNEL SPI2_IRQn
#define SPI_IRQ SPI2_IRQHandler
#define SPIPORT SPI2
#endif

#if SPI_PORT==1 
#define SPI_IRQ_CHANNEL SPI1_IRQn
#define SPIPORT SPI1
#define SPI_IRQ SPI1_IRQHandler
#endif



//============================================================================
//=======================[ spi support ]======================================
//============================================================================

static uint16_t _spiprog=0;
static uint8_t * _memoryp;
static uint16_t _memorycnt=0;
volatile uint8_t _dma_done=0;
static void _spi_nextstate( void );
volatile uint8_t rxirq=0;
static uint8_t _rxdone=0;
volatile uint8_t rdata=0;
static uint8_t * _spi_pc=0;
//static uint16_t _spi_dataindex;
//static uint8_t _spi_datacount=0;
static void _spi_txint_off( void );

//============================================================================
//=======================[ SPI_IRQHandler ]===================================
//============================================================================

void SPI_IRQ(void)
{
  if(  SPIPORT->SR & 2 ) // TX buffer empty
  {
    _spi_txint_off();
  }
  if(  SPIPORT->SR & 1 ) // RX has data
  {
    // must read the data!
    if( _memorycnt )
    {
      *_memoryp++=SPIPORT->DR;
      _memorycnt--;
    }
    else rdata=SPIPORT->DR; 
    rxirq=1;
  }
  _spi_nextstate(); // will send next byte, if any
}

//============================================================================
//=======================[ _spi_disable ]=====================================
//============================================================================

void _spi_disable( void )
{
}

//============================================================================
//=======================[ _spi_send ]========================================
//============================================================================

void _spi_send( uint8_t data )
{
  SPIPORT->DR=data;  // load data register, will transmit automatically
}

//============================================================================
//=======================[ _spi_txint_off ]===================================
//============================================================================

static void _spi_txint_off( void )
{
  SPIPORT->CR2=0x40;
}

//============================================================================
//=======================[ _spi_txint_on ]====================================
//============================================================================

void _spi_txint_on( void )
{
  SPIPORT->CR2=0xC0;  
}

//============================================================================
//=======================[ _spi_nextstate ]===================================
//============================================================================

// _spi_pc points to the command sequence.
 
static void _spi_nextstate( void )
{
  uint8_t page;        // this will hold memory buffer references
  uint8_t executing=1; // we will loop through commands until this is 0
  uint8_t nxt;         // next command to execute
  static uint8_t state_continue=0;
  
  if( _spi_pc==0 ) return; // There must be a program to execute.

  while( executing )
  {
    nxt=state_continue; // could be a continuation of previous command
    // (that is, some commands have two or more steps)
    if( nxt==0 ) nxt=*_spi_pc++; // no, it's a new command

    switch( nxt )
    {
      case 0:
        executing=0;  // should never get here
        break;

      // This is used to control things like chip select         
      case CMD_SETIO:
        {
          uint16_t ionum=*_spi_pc++; // pick up the pin#, advance the command
          GPIO_SetBits( _iopin[ionum].port, _iopin[ionum].pin ); // pin=1
        }
        break;

      // This is used to control things like chip select        
      case CMD_CLEARIO:
        {
          uint16_t ionum=*_spi_pc++; // pick up the pin#, advance the command
          GPIO_ResetBits( _iopin[ionum].port, _iopin[ionum].pin ); // pin=0
        }
        break;
        
      case CMD_TEST:
         //Debug_LED(4);
        break;

      // Send an immediate byte over spi
      case CMD_NEXTBYTE:
        rxirq=0; // clear rx status (so we can detect the next receive for deselct cs)
        _spi_send( *_spi_pc++ ); // data byte to display hardware, advance the command pointer
        state_continue=0; // will continue with the next bytecode
        executing=0; // will stop cmd loop but return on irq once data is sent
        break;

      // This is used for DMA buffers
      case CMD_SET_BUFFER:
        page=*_spi_pc++; // get the buffer #
        _memoryp=_buffer[page].destination; // NOTE: source buffer not implemented yet
        _memorycnt=_buffer[page].count; // this is how many bytes to transfer
        state_continue=0;  // will continue with the next bytecode
        break;

      // This handles SPI input, interrupt on each byte (not DMA)        
      case CMD_NEXTINBYTE:
        rxirq=0; // clear rx status (so we can detect the next receive for deselct cs)
        // (that is, we should guarantee we receive this byte prior to cs=1)
        _spi_send( 0 ); // normal spi input: send anything, receive next byte
        state_continue=CMD_NEXTINBYTE2;
        break;

      // We should have received an irq to have gotten here)
      case CMD_NEXTINBYTE2:
        if( rxirq ) // (may be a tx interrupt)
        {
          rxirq=0;
          if( _memorycnt ) // any more bytes to receive?
          {
            state_continue=CMD_NEXTINBYTE; // start another byte
          }
          else
          {
            // nothing left to receive
            state_continue=CMD_NEXTINBYTE3;
          }
        }
        else executing=0;  // exit and wait on rxirq (this was a tx irq)
        break;

      case CMD_NEXTINBYTE3:
        state_continue=0; // end this looping, advance to next cmd
        _rxdone=_rxdone | 1;
        // todo: do callback
        break;
       
      // write from memory to peripheral, no input
      case CMD_NEXTWBLOCK:
        page=*_spi_pc++; // next byte is the memory buffer#
        _start_dma(page);
        executing=0; // exit and wait on irq
        state_continue=CMD_NEXTWBLOCK2; // then come back when dma is done
        break;

      // This handles the write dma termination        
      case CMD_NEXTWBLOCK2:
        if( _dma_done ) 
        {
          _dma_done=0;
          state_continue=0; // end of dma steps
          _spi_int_on(); // we'll be using spi interrupts again
        }
        executing=0; // exit and wait on irq
        break;

      // This handles the rx complete interrupt.
      // We need this to know when it's safe to raise chip select.
      // If CS is raised too early it could cut off the last transmitted byte.
      case CMD_WAITRX:
          if( rxirq )
          {
            state_continue=0; // end this wait, advance to next cmd
          }
          else executing=0; // wait on next irq or trigger
        break;

     // This handles the end of a 'program'.
      case CMD_END:
        executing=0; 
        _spi_pc=0;
        _spi_disable();
        break;

      default:
        break;
    } // end switch
  } // end while
  
  // When a 'program' completes, see if another is waiting.
  if( _spi_pc==0 ) 
  {
    // will get here only if _spi_pc was not zero
    // on the original call, so CMD_END was executed.
      _spi_prg_start();
  }
}

//============================================================================
//=======================[ _spi_queue ]=======================================
//============================================================================

// The command sequences must be synchronized
// since one cannot interrupt another.
// Doing so would confuse the controller.
// So a command will start only when a previous
// sequence is finished.

static void _spi_queue( uint8_t pnum )
{
  _spiprog=_spiprog | (1<<pnum);
  _spi_prg_start();  
}

//============================================================================
//=======================[ _spi_prg_start ]===================================
//============================================================================

// Check for a trigger flag. If one is set then 
// clear the flag and run that program.

static void _spi_prg_start( void )
{
  uint8_t * prg=0;

  if( _spiprog ==0 ) return;
  if( _spi_pc!=0 ) return;
  
  uint16_t bit=1;
  uint8_t i=0;
  
  while( bit )
  {
      if( bit & _spiprog )
      {
        _spiprog=_spiprog ^ bit;
        bit=0;
        prg=(uint8_t *) _spi_program[i];       
      }
      bit=bit<<1;
      i++;
  }
  _spi_pc=prg;
  _spi_nextstate();
}

//============================================================================
//=======================[ SPI_Engine_Configure ]=============================
//============================================================================

static uint8_t _configured=0;

void SPI_Engine_Configure( uint8_t port )
{
  if( _configured ) return;
  _configured=1;
  // CR1
  // 0... .... .... .... - 2 line unidirectional
  // 1... .... .... .... - 1 line bidirectional
  // .0.. .... .... .... - output disabled
  // .1.. .... .... .... - output enabled (transmit only mode)
  // ..0. .... .... .... - crc disabled
  // ...0 .... .... .... - data phase, no crc 
  // .... 0... .... .... - 8 bit
  // .... .0.. .... .... - full duplex
  // .... ..1. .... .... - Software slave management enabled
  // .... ...1 .... .... - slave select
  // .... .... 0... .... - MSB transmitted first
  // .... .... .1.. .... - Peripheral enabled SPE
  // .... .... ..00 0... - baud rate, fastest
  // .... .... .... .1.. - master
  // .... .... .... ..1. - CK to 1 when idle  (CPOL)
  // .... .... .... ...1 - The second clock transition is the first data capture edge
  // 0100 0011 0000 0111
  SPIPORT->CR1=0x0307;

  // CR2
  // 1... .... - TXE interrupt on
  // .1.. .... - RXNE interrupt on
  // ..0. .... - Error interrupt off
  // .... .0.. - SS output off
  // .... ..0. - Tx buffer DMA disabled  SPI_CR2_TXDMAEN
  // .... ...0 - Rx buffer DMA disabled
  SPIPORT->CR2=0x40;  // tx int off, rx on

  // enable interrupt logic
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = SPI_IRQ_CHANNEL; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  SPIPORT->CR1=SPIPORT->CR1 | SPI_CR1_SPE; // 0x40 enable spi

  //                         FEDCBA98        
  GPIOB->CRH= GPIOB->CRH & 0x0f00ffff; // enable spi gpio last!
  GPIOB->CRH= GPIOB->CRH | 0xBBB30000; // alt pins for SPI
}

//============================================================================
//=======================[ dma ]==============================================
//============================================================================

// DMA interrupt status register (DMA_ISR)
//
// .... 7777 6666 5555 4444 3333 2222 1111 - channel
// .... .... .... .... .... .... .... 1... - TEIF1 got transfer error
// .... .... .... .... .... .... .... .1.. - HTIF1 got half transfer
// .... .... .... .... .... .... .... ..1. - TCIF1 got transfer complete int
// .... .... .... .... .... .... .... ...1 - GIF1  got global int

// DMA interrupt flag clear register (DMA_IFCR) IFCR
// 
// .... 7777 6666 5555 4444 3333 2222 1111 - channel
// .... .... .... .... .... .... .... 1... - CTEIF1 clear transfer error
// .... .... .... .... .... .... .... .1.. - CHTIF1 clear half transfer
// .... .... .... .... .... .... .... ..1. - CTCIF1 clear transfer complete int
// .... .... .... .... .... .... .... ...1 - CGIF1  clear global int

// DMA channel x configuration register (DMA_CCRx)
//
// .... .... .... .... .0.. .... .... .... - memory to memory = off
// .... .... .... .... ..00 .... .... .... - priority low
// .... .... .... .... ..01 .... .... .... -   "      medium
// .... .... .... .... ..10 .... .... .... -   "      high
// .... .... .... .... ..11 .... .... .... -   "      very high
// .... .... .... .... .... 00.. .... .... - memory size 8 bits
// .... .... .... .... .... ..00 .... .... - peripheral size 8 bits
// .... .... .... .... .... .... 1... .... - memory increment mode
// .... .... .... .... .... .... .0.. .... - peripheral increment mode disabled
// .... .... .... .... .... .... ..0. .... - Circular mode disabled
// .... .... .... .... .... .... ...1 .... - read from memory
// .... .... .... .... .... .... .... 0... - Transfer error interrupt disable
// .... .... .... .... .... .... .... .0.. - half transfer interrupt disable
// .... .... .... .... .... .... .... ..1. - transfer complete int enable
// .... .... .... .... .... .... .... ...1 - channel enable
//                        0    0    9    3

// DMA_CNDTRx  data length to transfer
// DMA_CPARx   peripheral address
// DMA_CMARx   memory address

//============================================================================
//=======================[ DMA_IRQHandler ]===================================
//============================================================================

#if SPI_PORT==2 
#define DMA_IRQHandler DMA1_Channel5_IRQHandler
#define DMA_NUM DMA1
#define DMA_CLEAR DMA1_IT_TC5
#define DMA_CHANNEL DMA1_Channel5
#endif

#if SPI_PORT==1
#define DMA_IRQHandler DMA1_Channel3_IRQHandler
#define DMA_NUM DMA1
#define DMA_CLEAR DMA1_IT_TC3
#define DMA_CHANNEL DMA1_Channel3
#endif

void DMA_IRQHandler(void)
{
  //Clear the selected DMAy interrupt pending bits  
  DMA_NUM->IFCR = DMA_CLEAR;
  // dma disable
  DMA_CHANNEL->CCR   = 0;   
  _dma_done=1;
  _spi_nextstate(); // advance the spi state machine
  rxirq=1; // simulate rx irq
}

//============================================================================
//=======================[ _spi_int_on ]======================================
//============================================================================

void _spi_int_on(void)
{
  SPIPORT->CR2 |= 0x80; // tx int enable
}

//============================================================================
//=======================[ _start_dma ]=======================================
//============================================================================

void _start_dma(uint8_t page)
{
  SPIPORT->CR1 &= ~SPI_CR1_SPE; // 0x40 disable spi
  SPIPORT->CR2 = 0;
  SPIPORT->CR1=0x0307; // .... ..11 .... .111

  // setup dma addresses
  DMA_CHANNEL->CMAR =(uint32_t) _buffer[page].source;
  DMA_CHANNEL->CPAR = (uint32_t) &SPIPORT->DR;
  // a display page is 128 bytes, but this code is general purpose
  // do it's specified in a structure
  DMA_CHANNEL->CNDTR = _buffer[page].count;
  DMA_CHANNEL->CCR   = 0x0093;
  // clear interrupt flags
  DMA_NUM->IFCR = DMA_CLEAR; // DMA_IFCR_CTCIF5 ;
  // enable transmit dma
  SPIPORT->CR2 |= SPI_CR2_TXDMAEN ;
  // enable spi ... will now start transmitting
  SPIPORT->CR1 |= SPI_CR1_SPE; // 0x40;  //   .1.. .... enable spi
}

  
//GPIO_SetBits( DISPLAY_DC_PORT, DISPLAY_DC_PIN );
//GPIO_ResetBits( DISPLAY_DC_PORT, DISPLAY_DC_PIN );
