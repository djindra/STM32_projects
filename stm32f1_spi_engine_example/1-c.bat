PATH=C:\tools\MinGW\msys\1.0\bin;C:\tools\GNU_Tools_ARM_Embedded\4.9_2015q1\bin;C:\Windows\System32

make -f mymakefile
del app\src\*.o
del app\src\*.lst

rem timeout /t 4
pause
