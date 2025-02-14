// Copyright (c) EofE Ultrasonics Co., Ltd., 2025
#include <stdio.h>

#include "DASSCWrapper.h"

int main()
{

    printf("Dass Detect");
    pSnrCtx snrctx = DASS710Open("\\\\.\\COM2", 115200U);

    if (NULL != snrctx)
    {
        bool sf = DASSDetect(snrctx);
        printf("Sonar detected => %d\n", sf);
    }

    DASSClose(snrctx);    
    return 0;
}
