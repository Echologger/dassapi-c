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

    git clone --recursive https://github.com/Echologger/dassapi-c.git
    cd dassapi-c
    mkdir build
    cd build
    cmake ..
    make all
    make install

    // or build using Ninja
    
    git clone --recursive https://github.com/Echologger/dassapi-c.git
    cd dassapi-c
    mkdir build
    cd build
    cmake -GNinja ..
    ninja    
    
Build command for Windows:

    git clone --recursive https://github.com/Echologger/dassapi-c.git
    cd dassapi-c
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
                printf("Dass detected\n");

                DASSValue testvalue;

                // Time setting
                DASSSetCurrentTime(snrctx);
                FloatToDASSValue(14.0F, &testvalue);

                // Range Setting
                LongToDASSValue(10000, &testvalue);
                DASSSetValue(snrctx, IdRange, &testvalue);

                // Output Setting
                LongToDASSValue(110, &testvalue);
                DASSSetValue(snrctx, IdOutput, &testvalue);

                // Output Type Setting
                LongToDASSValue(0, &testvalue);
                DASSSetValue(snrctx, IdDmode, &testvalue);

                // Stepping Setting
                LongToDASSValue(10, &testvalue);
                DASSSetValue(snrctx, IdHstep, &testvalue);
                LongToDASSValue(10, &testvalue);
                DASSSetValue(snrctx, IdVstep, &testvalue);

                // Sector Setting
                LongToDASSValue(0, &testvalue);
                DASSSetValue(snrctx, IdSector, &testvalue);        

                DASSStart(snrctx);
                printf("DASS Is Running? -> %d\n", DASSIsRunning(snrctx));
        
                printf("Receiving 2kB Simple Data.\n");

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
                printf("DASS is not detected\n");
            }

            DASSClose(snrctx); // Close DASS's serial port
        }

        return 0;
    }
