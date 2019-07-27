// spi_engine.h
#ifndef __SPI_ENGINE_H__
#define __SPI_ENGINE_H__
void SPI_Engine_Configure( uint8_t port );

// commands in the irq state engine

enum{
CMD_SETIO=1,
CMD_CLEARIO,
CMD_NEXTBYTE,
CMD_NEXTWBLOCK,
CMD_NEXTWBLOCK2,
CMD_NEXTINBYTE,
CMD_NEXTINBYTE2,
CMD_NEXTINBYTE3,
CMD_SET_BUFFER,
CMD_WAITRX,
CMD_TEST,
CMD_END
};

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} spi_io_t;

typedef struct {
    uint8_t * source;
    uint8_t * destination;
    uint16_t count;
    uint8_t * flag;
} membuffer_t;

#endif // __SPI_ENGINE_H__