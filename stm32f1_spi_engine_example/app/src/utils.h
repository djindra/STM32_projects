#ifndef __UTILS_H__
#define __UTILS_H__




#define GLOBALFLAG   0
#define OPFLAG   1
// global flags
#define FLAG_ADVERTISING 1
#define FLAG_NOTIFYEOF   2
#define FLAG_ADV_RESUME  4
#define FLAG_CONNECTED   8
#define FLAG_HOLDING     16
// op flags
#define FLAG_FLASH       1
#define FLAG_FLASHRESET  2


// total bytes to allocate
#define FLAGS_COUNT 2


void Util_setbit( uint16_t flag, uint8_t bit );
void Util_clrbit( uint16_t flag, uint8_t bit );
uint8_t Util_istrue( uint16_t flag, uint8_t bit );
uint8_t Util_isfalse( uint16_t flag, uint8_t bit );
void Util_bin2hex( uint8_t * pbuf, uint8_t data );
void Util_bin2hex16( uint8_t * pbuf, uint32_t data );
void Util_bin2hex32( uint8_t * pbuf, uint32_t data );
uint16_t Util_ascii2bin( uint8_t a );
uint16_t Util_ascii2bin_p3( uint8_t * p );
uint16_t Util_16bin2dec( uint8_t * pbuf, uint16_t data );
void Util_99bin2dec( uint8_t * pbuf, uint8_t data );
void delay_ms( uint16_t d );


#endif // __UTILS_H__


