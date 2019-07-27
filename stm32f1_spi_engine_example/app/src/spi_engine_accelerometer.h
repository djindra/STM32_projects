// spi_engine_accelerometer.h
#ifndef __SPI_ENGINE_ACCELEROMETER_H__
#define __SPI_ENGINE_ACCELEROMETER_H__

#include "lsm6ds3.h"

// Define the gpio pins used by this peripheral
#define ACCEL_CS_PIN  GPIO_Pin_1
#define ACCEL_CS_PORT GPIOB

#define ACCEL_INT_PIN  GPIO_Pin_10
#define ACCEL_INT_PORT GPIOB

// exposed functions
uint8_t ACCEL_data_ready( void );
void ACCEL_Driver_Init(void);
void ACCEL_Read(void);
void ACCEL_Smooth(void);
int16_t ACCEL_data( int16_t axis );

// data bufffer used to read the chip data
extern uint8_t acceldata[];
// flag indicates accelerometer data has been read
extern uint8_t _accel_service;

// list the buffers
#define ACCELMEM  {0,acceldata,6,0},

// list the buffer logical reference numbers
#define ACCELMEM_ENUM ACCEL_BUF, 

// list the gpio pins required... for LOAD_PINS
#define ACCELPINS {ACCEL_CS_PORT, ACCEL_CS_PIN},

// list the gpio pin logical references... for LOAD_PIN_IDS
#define ACCELPIN_ENUM  ACCEL_CS,

// list the spi program logical reference numbers for this peripheral
#define ACCELPRG_ENUM  PRG_ACCEL_INIT, \
  PRG_ACCEL_READ,

// list the spi programs for this peripheral
#define ACCELPRGS  ACCEL_Cmds_Init, \
 ACCEL_Cmds_ReadAccel,

#endif // __SPI_ENGINE_ACCELEROMETER_H__

// Separate, specially loaded data:

#ifdef LOAD_PINS
#undef LOAD_PINS
ACCELPINS
#endif // LOAD_PINS

#ifdef LOAD_PIN_IDS
#undef LOAD_PIN_IDS
ACCELPIN_ENUM
#endif // LOAD_PIN_IDS

#ifdef LOAD_BUFFERS
#undef LOAD_BUFFERS
ACCELMEM
#endif // LOAD_BUFFERS

#ifdef LOAD_BUFFER_IDS
#undef LOAD_BUFFER_IDS
ACCELMEM_ENUM
#endif // LOAD_BUFFER_IDS

#ifdef LOAD_PRG_IDS
#undef LOAD_PRG_IDS
ACCELPRG_ENUM
#endif // LOAD_PRG_IDS

#ifdef LOAD_PRGS
#undef LOAD_PRGS
ACCELPRGS
#endif // LOAD_PRGS
