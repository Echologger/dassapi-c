# DASSapi-c Echologger DASS API for C/C++/C#
====================================================================================

Prerequisites
-------------

- `Git` version control system

Git can be downloaded from [Git Webpage](https://git-scm.com/downloads)

- `CMake` build system

Git can be downloaded from [CMake download webpage](https://cmake.org/download/)

- optional `Ninja` utility

Can be downloaded from [Ninja webpage](https://ninja-build.org/)

Build tools
-----------

- `ARM GCC` GCC GNU toolchain > 7.0.0 must be used for Linux build
- `Visual Studio` > 2013 or `MSYS64` for Windows build
- optional `Ninja` utility

Build command for Linux:

    git clone --recursive https://github.com/Echologger/DASSapi-c.git
    cd DASSapi-c
    mkdir build
    cd build
    cmake ..
    make all
    make install

    // or build using Ninja
    
    git clone --recursive https://github.com/Echologger/DASSapi-c.git
    cd DASSapi-c
    mkdir build
    cd build
    cmake -GNinja ..
    ninja    
    
Build command for Windows:

    git clone --recursive https://github.com/Echologger/DASSapi-c.git
    cd DASSapi-c
    mkdir build
    cd build
    cmake ..
    // in case of Visual Studio toolchain cmake produce a solution file, which can be used to make binaries later on
    // in case of MSYS cmake produce a 'Makefile' file, which can be used by `make` utility
    
Binary files can be found at the /exe or build folder

Using example:

    #include <stdio.h>
    #include "DASSCWrapper.h"

    int main(void)
    {
        pSnrCtx snrctx = DASS710Open("\\\\.\\COM31", 115200U); // DASS open in Windows
        //pSnrCtx snrctx = DASS710Open("/dev/ttyS31", 115200U); // DASS open in Linux
        
        if (NULL != snrctx)
        {
            bool is_detected = DASSDetect(snrctx);
            
            if(true == is_detected)
            {
                printf("Sonar detected\n");

                EchosounderValue testvalue;

                EchosounderSetCurrentTime(snrctx);

                FloatToEchosounderValue(14.0F, &testvalue);
                printf("Set IdTVGSprdH. Result must be -1 for single frequency echosounder\n");
                int result = EchosounderSetValue(snrctx, IdTVGSprdH, &testvalue);
                printf("result = %d\n", result);

                printf("Set IdTVGSprd. Result must be 0 for single frequency echosounder\n");
                FloatToEchosounderValue(10.0F, &testvalue); // Set TVG spreading value
                result = EchosounderSetValue(snrctx, IdTVGSprd, &testvalue);
                printf("result = %d\n", result);

                LongToEchosounderValue(10000, &testvalue);
                EchosounderSetValue(snrctx, IdRange, &testvalue); // Set #range value

                LongToEchosounderValue(3, &testvalue);
                EchosounderSetValue(snrctx, IdOutput, &testvalue); // Set #output value

                printf("Start Echosounder\n");
                EchosounderStart(snrctx);
                printf("Echosounder Is Running? -> %d\n", EchosounderIsRunning(snrctx));

                printf("Get IdTVGSprd. Result must be 10.0 for single frequency echosounder\n");
                EchosounderGetValue(snrctx, IdTVGSprd, &testvalue);
                printf("tgvsprd => %.1f\n", EchosounderValueToFloat(&testvalue));

                printf("Receiving 1kB NMEA Data.\n");

                size_t totalbytes = 0;

                while(totalbytes < 1024)
                {          
                    uint8_t buffer[16];
                    size_t size = DASSReadData(snrctx, buffer, 16);

                    totalbytes += size;

                    for (int i = 0; i < size; i++)
                    {
                        putchar(buffer[i]);
                    }            
                }

                printf("\nStop DASS\n");
                DASSStop(snrctx); // Stop DASS's output
                printf("DASS Is Running? -> %d\n", DASSIsRunning(snrctx));
            }
            else
            {
                printf("Sonar is not detected\n");
            }

            DASSClose(snrctx); // Close DASS's serial port
        }

        return 0;
    }
