# STM32_projects

This code is described at http://djindracode.blogspot.com/2019/07/a-general-purpose-spi-engine.html

I built it with gcc and "make" in Windows 7.

There are two batch files.

1-c.bat:

  PATH=C:\tools\MinGW\msys\1.0\bin;C:\tools\GNU_Tools_ARM_Embedded\4.9_2015q1\bin;C:\Windows\System32 \
  make -f mymakefile \
  del app\src\*.o \
  del app\src\*.lst \

2-run.bat:

  PATH=C:\tools\MinGW\msys\1.0\bin;C:\tools\GNU_Tools_ARM_Embedded\4.9_2015q1\bin; \
  "C:\tools\stm32\utility\ST-LINK Utility\ST-LINK_CLI.exe"  -P stm32f1_spi_engine.hex \
  "C:\tools\stm32\utility\ST-LINK Utility\ST-LINK_CLI.exe"  -Rst \

  
In Windows Explorer I navigate to the directory where these batch files reside. Then I just double click on each batch to compile and load the code.

The path is an example. It's how I have my tools setup.

The following must be installed somewhere on your system:

  * MinGW 
  * The GCC cross compiler for ARM 
  * ST-LINK_CLI.exe 

I avoid modifying my system environment when I setup for any build process. I don't want to clutter the system with a bunch of randomly installed tools and hope the search path is correct. So I create a special, temporary path for every build process I use.

Therefore, modify the paths above to reflect your system.

Eventually I'll add a schematic for the hardware I used for this code. But it's very simple.