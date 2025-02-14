// Copyright (c) EofE Ultrasonics Co., Ltd., 2025
#include <stdio.h>

#include "DASSCWrapper.h"

int main()
{
    pSnrCtx snrctx = DASS710Open("\\\\.\\COM2", 115200U);
    int result = 0;

    if (NULL != snrctx)
    {
        bool sf = DASSDetect(snrctx);
        printf("DASS detected => %d\n", sf);

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
#if 1
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
#endif        

        DASSStart(snrctx);
        printf("DASS Is Running? -> %d\n", DASSIsRunning(snrctx));
        
        printf("Receiving 2kB Simple Data.\n");

        size_t totalbytes = 0;

        while(totalbytes < 2048)
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
        DASSStop(snrctx);
        printf("DASS Is Running? -> %d\n", DASSIsRunning(snrctx));
        DASSClose(snrctx);    
    }

    return 0;
}
