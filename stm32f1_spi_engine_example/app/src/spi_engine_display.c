// controller = SSD1306

// connector assignment:
//
// cpu io     module        function
// ------     ------------  ------------
//   3        lcd8          cs 
//   4        lcd9          reset
//   5        lcd10         data/command
//   6        lcd11         sclk
//   7        lcd12         sdin

#define SWITCHON 1
#define SWITCHOFF 2

//============================================================================

// spi initialization program

static const uint8_t DISPLAY_Cmds_Init[]={ 
  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_CLEARIO, DISPLAY_CS,  // select the display
  CMD_NEXTBYTE, 0xAE,       // display off
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB0,       // set page address
  CMD_NEXTBYTE, 0x81,       // contract control
  CMD_NEXTBYTE, 0xCF,       // 128
  CMD_NEXTBYTE, 0xA1,       // set segment remap
  CMD_NEXTBYTE, 0xA6,       // normal / reverse
  CMD_NEXTBYTE, 0xA8,       // multiplex ratio
#ifdef DISPLAY_128X64
  CMD_NEXTBYTE, 0x3F,       // duty = 1/64
#else
  CMD_NEXTBYTE, 0x1F,       // duty = 1/32
#endif // DISPLAY_128X64    
  CMD_NEXTBYTE, 0xC8,       // Com scan direction
  CMD_NEXTBYTE, 0xD3,       // set display offset
  CMD_NEXTBYTE, 0x00,
  CMD_NEXTBYTE, 0xD5,       // set osc division
  CMD_NEXTBYTE, 0x80,
  CMD_NEXTBYTE, 0xD9,       // set pre-charge period
  CMD_NEXTBYTE, 0x1f,
  CMD_NEXTBYTE, 0xDA,       // set COM pins
#ifdef DISPLAY_128X64
  CMD_NEXTBYTE, 0x12, 
#else
  CMD_NEXTBYTE, 0x00, 
#endif // DISPLAY_128X64      
  CMD_NEXTBYTE, 0xdb,       // set vcomh
  CMD_NEXTBYTE, 0x40,
  CMD_NEXTBYTE, 0x8d,       // set charge pump enable
  CMD_NEXTBYTE, 0x14,       // options? 0x10 0x14
  CMD_NEXTBYTE, 0xAF,       // display ON
  CMD_WAITRX,
  CMD_SETIO, DISPLAY_CS,    // deselect the display
  CMD_END
};


static const uint8_t DISPLAY_Cmds_Refresh[]={
  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_CLEARIO, DISPLAY_CS,  // select the display
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB0,       // set page 0 address
  CMD_SETIO, DISPLAY_DC,    // data mode
  CMD_NEXTWBLOCK, DISP_PAGE0, // 128*0

  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB1,       // set page 1 address
  CMD_SETIO, DISPLAY_DC,    // data mode
  CMD_NEXTWBLOCK, DISP_PAGE1, // 128*1

  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB2,       // set page 2 address
  CMD_SETIO, DISPLAY_DC,    // data mode
  CMD_NEXTWBLOCK, DISP_PAGE2, // 128*2

  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB3,       // set page 3 address
  CMD_SETIO, DISPLAY_DC,    // data mode
  CMD_NEXTWBLOCK, DISP_PAGE3, // 128*3

// the 128x64 display has 8 pages  
#ifdef DISPLAY_128X64
  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB4,       // set page 3 address
  CMD_SETIO, DISPLAY_DC,    // data mode
  CMD_NEXTWBLOCK, DISP_PAGE4, // 128*4

  CMD_CLEARIO, DISPLAY_DC,  // command mode  
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB5,       // set page 3 address
  CMD_SETIO, DISPLAY_DC,    // data mode 
  CMD_NEXTWBLOCK, DISP_PAGE5, // 128*5
  
  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB6,       // set page 3 address
  CMD_SETIO, DISPLAY_DC,    // data mode
  CMD_NEXTWBLOCK, DISP_PAGE6, // 128*6

  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_NEXTBYTE, 0x00,       // set lower column address
  CMD_NEXTBYTE, 0x10,       // set higher column address
  CMD_NEXTBYTE, 0x00,       // set display start line
  CMD_NEXTBYTE, 0xB7,       // set page 3 address
  CMD_SETIO, DISPLAY_DC,    // data mode
  CMD_NEXTWBLOCK, DISP_PAGE7, // 128*7
#endif // DISPLAY_128X64

  CMD_WAITRX,
  CMD_SETIO, DISPLAY_CS,    // deselect the display 
  CMD_CLEARIO, DISPLAY_DC,  // command mode 
  CMD_END,
};


// spi orientation 1 program

static const uint8_t DISPLAY_Cmds_Orient1[]={
  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_CLEARIO, DISPLAY_CS,  // select the display
  CMD_NEXTBYTE, 0xA0, 
  CMD_NEXTBYTE, 0xC0,
//  CMD_SETIO, DISPLAY_DC,    // data mode 
  CMD_WAITRX,
  CMD_SETIO, DISPLAY_CS,    // deselect   
  CMD_END
};

// spi orientation 2 program

static const uint8_t DISPLAY_Cmds_Orient2[]={
  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_CLEARIO, DISPLAY_CS,  // select the display
  CMD_NEXTBYTE, 0xA1,
  CMD_NEXTBYTE, 0xC8, 
//  CMD_SETIO, DISPLAY_DC,    // data mode 
  CMD_WAITRX, 
  CMD_SETIO, DISPLAY_CS,    // deselect 
  CMD_END
};

// spi display on program

static const uint8_t DISPLAY_Cmds_TurnOn[]={
  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_CLEARIO, DISPLAY_CS,  // select the display
  CMD_NEXTBYTE, 0xAF,
//  CMD_SETIO, DISPLAY_DC,    // data mode 
  CMD_WAITRX,
  CMD_SETIO, DISPLAY_CS,    // deselect 
  CMD_END
};

// spi display off program

static const uint8_t DISPLAY_Cmds_TurnOff[]={
  CMD_CLEARIO, DISPLAY_DC,  // command mode
  CMD_CLEARIO, DISPLAY_CS,  // select the display
  CMD_NEXTBYTE, 0xAE,
//  CMD_SETIO, DISPLAY_DC,    // data mode 
  CMD_WAITRX,
  CMD_SETIO, DISPLAY_CS,    // deselect 
  CMD_END
};

static uint8_t _onoff=0;

//============================================================================
//=======================[ DISPLAY_Driver_Init ]==============================
//============================================================================

void DISPLAY_Driver_Init(void)
{
  // reset the display hardware
  GPIO_SetBits( DISPLAY_RESET_PORT, DISPLAY_RESET_PIN );
  delay_ms(2);
  GPIO_ResetBits( DISPLAY_RESET_PORT, DISPLAY_RESET_PIN );
  delay_ms(10);
  GPIO_SetBits( DISPLAY_RESET_PORT, DISPLAY_RESET_PIN );
    
  SPI_Engine_Configure(2);
  _spi_queue( PRG_DISPLAY_INIT );
}

//============================================================================
//=======================[ DISPLAY_Refresh ]==================================
//============================================================================

void DISPLAY_Refresh(void)
{
  _spi_queue( PRG_DISPLAY_REFRESH );
}

//============================================================================
//=======================[ DISPLAY_OnOff ]====================================
//============================================================================

void DISPLAY_OnOff( void )
{
  static uint8_t offstate=0;
  if( _onoff==SWITCHON )
  {
    _spi_queue( PRG_DISPLAY_TURNON );
    _onoff=0;
  }
  else if( _onoff==SWITCHOFF )
  {
    if( offstate==0 )
    {
      _spi_queue( PRG_DISPLAY_TURNOFF );
      DISPLAY_Clear();
    }
    _onoff=0;
  }
}

//============================================================================
//=======================[ DISPLAY_TurnOn ]===================================
//============================================================================

void DISPLAY_TurnOn( void )
{
  _spi_queue( PRG_DISPLAY_TURNON );
  _onoff=SWITCHON;
}

//============================================================================
//=======================[ DISPLAY_TurnOff ]==================================
//============================================================================

void DISPLAY_TurnOff( void )
{
  _spi_queue( PRG_DISPLAY_TURNOFF );
  _onoff=SWITCHOFF;
}

//============================================================================
//=======================[ DISPLAY_Orient ]===================================
//============================================================================

void DISPLAY_Orient( uint8_t mode )
{
  if( mode==0 )
  {
    _spi_queue( PRG_DISPLAY_ORIENT1 );
  }
  else 
  {
    _spi_queue( PRG_DISPLAY_ORIENT2 );
  }
}



