#include "common.h"
#include <stm32_configuration.h>
#include <stm32f10x_spi.h>
#include <stm32f10x.h>

USART_InitTypeDef USART_InitStructure;
ErrorStatus HSEStartUpStatus;

//============================================================================
//=======================[ RCC_Configuration ]================================
//============================================================================

void RCC_Configuration(void)
{
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  /* USART2 clock enable */
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);

  /* USART1 clock enable */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE );
  
  /* GPIO A/B/C clock enable */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  /* GPIO D clock enable */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);
  
  // Enable Clock for AFIOEN
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);
  
  /* SPI2 clock enable */ 
  RCC_APB1PeriphClockCmd ( RCC_APB1Periph_SPI2, ENABLE );
  //enable DMA1 clock
  RCC_AHBPeriphClockCmd  ( RCC_AHBPeriph_DMA1, ENABLE );
}

//============================================================================
//=======================[ NVIC_Configuration ]===============================
//============================================================================


void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM
  /* Set the Vector Table base location at 0x20000000 */
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
    
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}


//============================================================================
//=======================[ GPIO_Configuration ]===============================
//============================================================================

void GPIO_Configuration(void)
{
  // port registers:    
  //  CRL  -- gpio 0..7
  //  CRH  -- gpio 8..15
  //  IDR  -- input  gpio 0..15
  //  ODR  -- output gpio 0..15
  //  BSRR -- bit set/reset
  //  BRR  -- bit reset
  //  LCKR -- lock
    
  // Port configuration register low
  // .... .... .... .... .... .... .... ccmm
  // input mode
  // .... .... .... .... .... .... .... 0000 - analog mode
  // .... .... .... .... .... .... .... 0100 - floating input (reset)
  // .... .... .... .... .... .... .... 1000 - input with pu/pd
  // .... .... .... .... .... .... .... 1100 - reserved
  // output mode, mm = 1..3
  // .... .... .... .... .... .... .... 00mm - output, push/pull
  // .... .... .... .... .... .... .... 01mm - output, open drain
  // .... .... .... .... .... .... .... 10mm - Alt func output, push/pull
  // .... .... .... .... .... .... .... 11mm - Alt func output, open drain

  // mode mm
  // mm=11: Output mode, max speed 50 MHz.
  // mm=00: input

  // conf cc
  // 00: General purpose output push-pull
  // 01: General purpose output Open-drain
  // 10: Alternate function output Push-pull
  // 11: Alternate function output Open-drain

  // GPIOA->CRH   gpio 8..15   8,9
  // .... .... .... .... .... .... .... 0011 - output, push/pull  gpioA8
  // .... .... .... .... .... .... 0011 .... - output, push/pull  gpioA9
  // 4    4    4    4    4    4    3    3
  // 0x

  GPIOA->CRH=0x44333333;

  // GPIOB->CRH   gpio 8..15   12,a13,a15
  // 1011 .... .... .... .... .... .... .... - Alt func output, push/pull  gpioA15
  // .... .... 1011 .... .... .... .... .... - Alt func output, push/pull  gpioA13
  // .... .... .... 0011 .... .... .... .... - output, push/pull  gpioA12
  // B    4    B    3    4    4    4    4
  // 0x

  GPIOB->CRH=0x44433434; // don't enable spi alt gpio here
  GPIOB->CRL=0x44444333; // pb0 for test
  
  // GPIOC->CRH   gpio 8..15   13
  // .... .... 0011 .... .... .... .... .... - output, push/pull  gpioC13 
  // 4    4    3    4    4    4    C    C
  // 0x
  GPIOC->CRH=0x44344444;

  GPIO_SetBits( GPIOB, GPIO_Pin_1 );  // 
}

//============================================================================
//=======================[ USART1_Configuration ]=============================
//============================================================================

void USART1_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

  USART_DeInit(USART1);
  USART_InitStructure.USART_BaudRate = 38400;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);

  USART_Cmd(USART1, ENABLE);

  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
}

//============================================================================
//=======================[ USART2_Configuration ]=============================
//============================================================================

void USART2_Configuration(void)
{
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

  /* Configure USART1 */
  USART_Init(USART2, &USART_InitStructure);

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  /* Enable the USART1 */
  USART_Cmd(USART2, ENABLE);
}











