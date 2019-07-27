//#include "spi_engine_accelerometer.h"    not here!


uint8_t acceldata[6];
uint8_t _accel_service=0;


// GY-LSM6DS3
//   CS    PB11
//   INT1  PB10

// WHO_AM_I reg 0F = 0110 1010 0x6A
// write 1F,0


static const uint8_t ACCEL_Cmds_Init[]={ 
  CMD_CLEARIO, ACCEL_CS,  // select the accelerometer
  CMD_NEXTBYTE, LSM6DS3_CTRL9_XL,
  CMD_NEXTBYTE, 0x38,
  CMD_SETIO, ACCEL_CS,    // deselect 
  
  CMD_CLEARIO, ACCEL_CS,  // select the accelerometer
  CMD_NEXTBYTE, LSM6DS3_CTRL1_XL,
  //CMD_NEXTBYTE, 0x10,
  CMD_NEXTBYTE, 0x40,  // 104 hz
  //CMD_NEXTBYTE, 0x50,  // 208 hz  
  //CMD_NEXTBYTE, 0x60,  // 416 hz  
  CMD_SETIO, ACCEL_CS,    // deselect 

  CMD_CLEARIO, ACCEL_CS,  // select the accelerometer
  CMD_NEXTBYTE, LSM6DS3_INT1_CTRL,
  CMD_NEXTBYTE, 1,
  CMD_SETIO, ACCEL_CS,    // deselect 
  
  CMD_CLEARIO, ACCEL_CS,  // select the accelerometer
  CMD_NEXTBYTE, LSM6DS3_CTRL10_C,
  CMD_NEXTBYTE, 0,
  CMD_SETIO, ACCEL_CS,    // deselect 

  CMD_CLEARIO, ACCEL_CS,  // select the accelerometer
  CMD_NEXTBYTE, LSM6DS3_MASTER_CONFIG,
  CMD_NEXTBYTE, 0x80,
  CMD_SETIO, ACCEL_CS,    // deselect 

  CMD_CLEARIO, ACCEL_CS,  // select the accelerometer
  CMD_NEXTBYTE, LSM6DS3_CTRL4_C,
  CMD_NEXTBYTE, 0x2c,
  CMD_SETIO, ACCEL_CS,    // deselect 
 
  CMD_CLEARIO, ACCEL_CS,  // select the accelerometer
  CMD_NEXTBYTE, LSM6DS3_CTRL2_G,
  CMD_NEXTBYTE, 0x40,
  CMD_SETIO, ACCEL_CS,    // deselect 
  CMD_END 
};

static const uint8_t ACCEL_Cmds_ReadAccel[]={ 
  CMD_CLEARIO, ACCEL_CS,  // select the accelerometer
  CMD_NEXTBYTE,  LSM6DS3_OUTX_L_XL +0x80,  // register for data
  CMD_SET_BUFFER, ACCEL_BUF,
  CMD_NEXTINBYTE,
  CMD_SETIO, ACCEL_CS,    // deselect 
  CMD_END
};

//============================================================================
//=======================[ ACCEL_Driver_Init ]================================
//============================================================================

// INT1 is PB10
// Port B pin 10 generates an interrupt to the NVIC on a rising edge.

void ACCEL_Driver_Init(void)
{
  AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI1_PA; // old port 
  AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PA;  // PORTB
  EXTI->IMR   |= EXTI_IMR_MR1;               // unmask interrupt
  EXTI->EMR   &= ~EXTI_EMR_MR1;              // no event 
  EXTI->FTSR  &= ~EXTI_FTSR_TR1;             // no falling edge trigger 
  EXTI->RTSR  |= EXTI_RTSR_TR1;              // set rising edge trigger 
  
  // Interrupt 
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //EXTI15_10_IRQn; //EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  _spi_queue( PRG_ACCEL_INIT );
  SPI_Engine_Configure(2);
}

//============================================================================
//=======================[ ACCEL_Read ]=======================================
//============================================================================

void ACCEL_Read(void)
{
  _spi_queue( PRG_ACCEL_READ );
}

//============================================================================
//=======================[ ACCEL_Smooth ]=====================================
//============================================================================

int32_t avgxyz[3]={0,0,0};
#define AVGS 3


void ACCEL_Smooth(void)
{
  int16_t d;
  int16_t i=0;
     
  for( i=0; i<3; i++ )
  {
    d=acceldata[i*2+1];
    d=d<<8;
    d=d | acceldata[i*2+0];
     
    if( avgxyz[i]==0 ) avgxyz[i]=d<<AVGS;
    else
    {
      avgxyz[i]=avgxyz[i]-(avgxyz[i]>>AVGS);
      avgxyz[i]=avgxyz[i]+d;
    }
  }
}
            

//============================================================================
//=======================[ ACCEL_data ]=======================================
//============================================================================

#define SMOOTH

int16_t ACCEL_data( int16_t axis )
{
    int32_t d;
    #ifdef SMOOTH
      d=avgxyz[axis]>>AVGS;
    #else
      d=acceldata[axis*2+1];
      d=d<<8;
      d=d | acceldata[axis*2+0];  
    #endif //  SMOOTH
    return d;
}

//============================================================================
//=======================[ ACCEL_data_ready ]=================================
//============================================================================

uint8_t ACCEL_data_ready( void )
{
  uint8_t status=_accel_service;
  _accel_service=0;
  return status;
}

//============================================================================
//=======================[ EXTI1_IRQHandler ]=================================
//============================================================================

void EXTI1_IRQHandler(void)
{
  _accel_service=_accel_service | 1;
  EXTI->PR |= EXTI_PR_PR1;
}
