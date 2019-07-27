#ifndef __LSM6DS3_H__
#define __LSM6DS3_H__

#define LSM6DS3_FUNC_CFG_ACCESS 0x01
#define LSM6DS3_SENSOR_SYNC_TIME_FRAME 0x04
#define LSM6DS3_FIFO_CTRL1 0x06
#define LSM6DS3_FIFO_CTRL2 0x07
#define LSM6DS3_FIFO_CTRL3 0x08
#define LSM6DS3_FIFO_CTRL4 0x09
#define LSM6DS3_FIFO_CTRL5 0x0A
#define LSM6DS3_ORIENT_CFG_G 0x0B

#define LSM6DS3_INT1_CTRL 0x0D
// 0... .... - step recognition interrupt enable
// .0.. .... - significant motion interrupt enable
// ..0. .... - FIFO full flag interrupt enable
// ...0 .... - FIFO overrun interrupt
// .... 0... - FIFO threshold interrupt
// .... .0.. - Boot status available
// .... ..1. - gyroscope Data Ready
// .... ...1 - Accelerometer Data Ready

#define LSM6DS3_INT2_CTRL 0x0E
#define LSM6DS3_WHO_AM_I 0x0F

#define LSM6DS3_CTRL1_XL  0x10 // Accelerometer ODR register setting
// 0000 .... - power down
// 0001 .... - 12.5 Hz
// 0010 .... - 26 hz
// 0011 .... - 52 hz
// 0100 .... - 104 hz
// 0101 .... - 208 hz
// 0110 .... - 416 hz
// 0111 .... - 833 hz
// 1000 .... - 1.66k hz
// 1001 .... - 3.33k hz
// 1010 .... - 6.66k hz
// .... 00.. = +- 2g Accelerometer full-scale
// .... 01.. = +- 16g
// .... 10.. = +- 4g
// .... 11.. = +- 8g
// .... ..00 - 400 hz Anti-aliasing filter bandwidth
// .... ..01 - 200 hz  "
// .... ..10 - 100 hz  "
// .... ..11 - 50 hz   "
// 0100 0000

#define LSM6DS3_CTRL2_G   0x11  // Angular rate sensor control register
// 0000 .... - Power down
// 0001 .... - 12.5 hz
// 0010 .... - 26 hz
// 0011 .... - 52 hz
// 0100 .... - 104 hz 
// 0101 .... - 208 hz
// 0110 .... - 416 hz
// 0111 .... - 833 hz
// 1000 .... - 16.66 hz
// .... 00.. - 250 dps Gyroscope full-scale
// .... 01.. - 500 dps
// .... 10.. - 1000 dps
// .... 11.. - 2000 dps
// .... ..1. - 125 dps full-scale
// .... ...0 = always 0

#define LSM6DS3_CTRL3_C 0x12
// 1... .... - boot
// .0.. .... - Block Data Update continuous
// .1.. .... - Block Data Update when MSB and LSB have been read
// ..0. .... - interrupt active high
// ..1. .... - interrupt active low
// ...0 .... - push/pull
// .... 0... - 4 wire spi (vs 3 wire)
// .... .1.. - automatically increment register address
// .... ..0. - Little Endian
// .... ...1 - reset
// 0    4

#define LSM6DS3_CTRL4_C 0x13
// 0... .... - bandwidth determined by ODR selection
// 1... .... - bandwidth determined by setting BW_XL[1:0] in CTRL1_XL (
// .0.. .... - not sleep
// ..1. .... - all ints on INT1 
// ...0 .... - disable temperature
// .... 1... = Data-ready mask
// .... .1.. - i2c disable
// .... ..0. - always
// .... ...0 - FIFO depth al threshold level
// 2    c

#define LSM6DS3_CTRL5_C 0x14
// 000. .... - no rounding (default)
// 011. .... - gyroscope + accelerometer rounding
// .... 0000 - self test disabled

#define LSM6DS3_CTRL6_C 0x15
// 0... .... - external trigger disabled
// .0.. .... - level-sensitive trigger disabled
// ..0. .... - level-sensitive latched disabled
// ...0 .... - 0=high-performance operating mode enabled

#define LSM6DS3_CTRL7_G 0x16
#define LSM6DS3_CTRL8_XL 0x17
#define LSM6DS3_CTRL9_XL 0x18
// ..11 1... - EN xyx


#define LSM6DS3_CTRL10_C 0x19

#define LSM6DS3_MASTER_CONFIG 0x1A
// 1... .... - enable DRDY on INT1
// .0.. .... - not hub data
// ..0. .... - always
// ...0 .... - Sensor hub signal is the XL/Gyro data-ready
// .... 0... - internal pull-up on auxiliary I2C line disabled
// .... .0.. - I2C interface pass-through disabled
// .... ..0. - hard-iron correction algorithm disabled
// .... ...0 - master I2C of sensor hub disabled

#define LSM6DS3_WAKE_UP_SRC 0x1B
// 00.. .... - always 00
// ..1. .... - free-fall event
// ...1 .... - sleep event
// .... 1... - wakeup event
// .... .1.. - wakeup event on X-axis
// .... ..1. - wakeup event on Y-axis
// .... ...1 - wakeup event on Z-axis

#define LSM6DS3_TAP_SRC 0x1C
#define LSM6DS3_D6D_SRC 0x1D

#define LSM6DS3_STATUS_REG 0x1E
// .... .1.. - temperature data available
// .... ..1. - gyroscope data available
// .... ...1 - accelerometer data available

#define LSM6DS3_OUT_TEMP_L 0x20
#define LSM6DS3_OUT_TEMP 0x21
#define LSM6DS3_OUTX_L_G 0x22
#define LSM6DS3_OUTX_H_G 0x23
#define LSM6DS3_OUTY_L_G 0x24
#define LSM6DS3_OUTY_H_G 0x25
#define LSM6DS3_OUTZ_L_G 0x26
#define LSM6DS3_OUTZ_H_G 0x27

#define LSM6DS3_OUTX_L_XL 0x28
#define LSM6DS3_OUTX_H_XL 0x29
#define LSM6DS3_OUTY_L_XL 0x2A
#define LSM6DS3_OUTY_H_XL 0x2B
#define LSM6DS3_OUTZ_L_XL 0x2C
#define LSM6DS3_OUTZ_H_XL 0x2D
#define LSM6DS3_FIFO_STATUS1 0x3A
#define LSM6DS3_FIFO_STATUS2 0x3B
#define LSM6DS3_FIFO_STATUS3 0x3C
#define LSM6DS3_FIFO_STATUS4 0x3D
#define LSM6DS3_FIFO_DATA_OUT_L 0x3E
#define LSM6DS3_FIFO_DATA_OUT_H 0x3F
#define LSM6DS3_TIMESTAMP0_REG 0x40
#define LSM6DS3_TIMESTAMP1_REG 0x41
#define LSM6DS3_TIMESTAMP2_REG 0x42
#define LSM6DS3_STEP_TIMESTAMP_L 0x49
#define LSM6DS3_STEP_TIMESTAMP_H 0x4A
#define LSM6DS3_STEP_COUNTER_L 0x4B
#define LSM6DS3_STEP_COUNTER_H 0x4C
#define LSM6DS3_FUNC_SRC 0x53
#define LSM6DS3_TAP_CFG 0x58
#define LSM6DS3_TAP_THS_6D 0x59
#define LSM6DS3_INT_DUR2 0x5A
#define LSM6DS3_WAKE_UP_THS 0x5B
#define LSM6DS3_WAKE_UP_DUR 0x5C
#define LSM6DS3_FREE_FALL 0x5D
#define LSM6DS3_MD1_CFG 0x5E
#define LSM6DS3_MD2_CFG 0x5F




#endif // __LSM6DS3_H__