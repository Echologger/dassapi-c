API Functions description
=========================

| API Function | Description | Parameters | Outputs | Comment |
|---|---|---|---|---|
| pSnrCtx DASS710Open(const char *portpath, uint32_t baudrate) | Initiate connection to DASS710 | **portpath**     path to serial port<br>**baudrate**     serial port baudrate | Valid handle to futher using to manage the DASS or<br>**NULL** in case of failure | |
| void DASSClose(pSnrCtx snrctx) | This function is used for close port, it does not change the running state of the DASS | **snrctx**       Connection handle obtained by DASS710Open function | None | |
| size_t DASSReadData(pSnrCtx snrctx, uint8_t *buffer, size_t size) | Read raw data from the DASS | **snrctx**       Connection handle obtained by DASS710Open function<br>**buffer**       pointer for data buffer<br>**size**     number of bytes to be read | Bytes received | This function should be used when DASS is in the running state |
| int DASSGetValue(pSnrCtx snrctx, DASSCommandIds_t command, pDASSValue value) | Get value for the given parameter (command) | **snrctx**       Connection handle obtained by DASS710Open function<br>**command**      parameter for which command should be obtained<br>**value**        value of given command | **0** - value is valid<br>**-1** - value is invalid | This function can be used in any state on the DASS |
| int DASSGetValue(pSnrCtx snrctx, DASSCommandIds_t command, pcDASSValue value) | Set value for the given parameter (command) | **snrctx**       Connection handle obtained by DASS710Open function<br>**command**      parameter for which command should be set<br>**value**        value of given command | **0**  - value is set successfully<br>**-1** - set value failed | This function can be used in any state on the DASS |
| long DASSValueToLong(pcDASSValue value) | Convert value read from DASS to long | **value**        DASS value to convert | Converted value | Helper function |
| float DASSValueToFloat(pcDASSValue value) | Convert value read from DASS to float | **value**        DASS value to convert | Converted value | Helper function |
| const char *DASSValueToText(pcDASSValue value) | Convert value read from DASS to null-terminated char* | **value**        DASS value to convert | Converted value | Helper function |
| bool IsValidDASSValue(pcDASSValue value) | Check whether DASS value is valid | **value**        DASS value to check | **true** - value is valid<br>**false** - value is invalid | Helper function |
| void LongToDASSValue(long num, pDASSValue value) | Convert long number to DASS value | **num**          Long number to convert<br>**value**        Converted value | None | Helper function |
| void FloatToDASSValue(float num, pDASSValue value) | Convert float number to DASS value | **num**          Float number to convert<br>**value**        Converted value | None | Helper function |
| void DASSStart(pSnrCtx snrctx) | Start the unit | **snrctx**       Connection handle obtained by DASS710Open function | None | DASS will be in running state after this |
| void DASSStop(pSnrCtx snrctx) | Stop the unit | **snrctx**       Connection handle obtained by DASS710Open function | None | DASS will be in stop state after this |
| bool DASSIsRunning(pSnrCtx snrctx) | Checking the running state of the DASS | **snrctx**       Connection handle obtained by DASS710Open function | **true** - DASS in running state<br>**false** - DASS is not in running state | Not affected the DASS state |
| bool DASSIsDetected(pSnrCtx snrctx) | Checking whether DASS is detected on serial port | **snrctx**       Connection handle obtained by DASS710Open function | **true** - DASS is detected<br>**false** - DASS is not detected | Not affected the DASS state |
| bool DASSDetect(pSnrCtx snrctx) | Detect DASS on serial port | **snrctx**       Connection handle obtained by DASS710Open function | **true** - DASS is detected<br>**false** - DASS is not detected | DASS will be in stop state after this |
| void DASSSetCurrentTime(pSnrCtx snrctx) | Set current time to the DASS (UTC). It use current time from host PC | **snrctx**       Connection handle obtained by DASS710Open function | None | It can be neccessary for sync output with GPS output |
