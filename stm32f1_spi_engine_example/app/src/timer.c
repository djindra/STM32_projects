// timer.c
#include <stm32f10x.h>
#include <stm32f10x_conf.h>
#include <stm32_configuration.h>
#include <stm32f10x_tim.h>
#include "common.h"
#include "timer.h"

static uint32_t _tick=0;
static uint8_t _tick_hit=0;

//============================================================================//
//=======================[ TIM2_IRQHandler ]==================================//
//============================================================================//

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    _tick++;
    _tick_hit=1;
  }
}

//============================================================================//
//=======================[ EnableTimerInterrupt ]=============================//
//============================================================================//


void EnableTimerInterrupt()
{
  NVIC_InitTypeDef nvicStructure;
  nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
  nvicStructure.NVIC_IRQChannelSubPriority = 1;
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvicStructure);
}


//============================================================================//
//=======================[ timer_init ]=======================================//
//============================================================================//

void timer_init(void)
{
  TIM_TimeBaseInitTypeDef timerInitStructure; 
  timerInitStructure.TIM_Prescaler = 1000; // 4000
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = 500;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  timerInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &timerInitStructure);
  TIM_Cmd(TIM2, ENABLE);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  EnableTimerInterrupt(); 
}   

//============================================================================//
//=======================[ timer_status ]=====================================//
//============================================================================//


uint8_t timer_status(void)
{
  uint8_t status=0;

  if(  _tick_hit==1 )
  {
    _tick_hit=0;
    status=1;
  }
  return status;
}

