// Copyright (c) EofE Ultrasonics Co., Ltd., 2024
#if !defined(DASS710CWRAPPER_H)
#define DASS710CWRAPPER_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "DASSCommands.h"

#define SERIALPORT_TIMEOUT_MS 100U
#define VALUE_TEXT_SIZE 64U

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 ) || defined( _WIN64 ) 

#ifdef DLL_LIB
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#elif defined( __GNUC__ )

#ifdef DLL_LIB
#define DLL_EXPORT __attribute__((visibility("default")))
#else
#define DLL_EXPORT
#endif

#else
#error compiler not supported!

#endif

#ifdef __cplusplus
extern "C" {
#endif

struct DASSvalue_t
{
    char value_text[VALUE_TEXT_SIZE];
    int value_len;
};

typedef struct DASSvalue_t DASSValue;
typedef struct DASSvalue_t *pDASSValue;
typedef const struct DASSvalue_t *pcDASSValue;

typedef void *pSnrCtx;
typedef void *hDASS; 

/**
 * @brief   Initiate connection to DASS
 *
 * @note    This function is used for open port and check whether DASS is connected to it.
 *
 * @param[in]  portpath     path to serial port
 * @param[in]  baudrate     serial port baudrate
 
 * @return                  Valid handle to futher using to manage the DASS
 * @return                  NULL in case of failure
 */
DLL_EXPORT pSnrCtx DASS710Open(const char *portpath, uint32_t baudrate);


/**
 * @brief   Finalize connection to the DASS
 *
 * @note    This function is used for close port, it does not change the running state of the DASS.
 */
DLL_EXPORT void DASSClose(pSnrCtx snrctx);

/**
 * @brief   Read raw data from the DASS
 *
 * @note    This function should be used when echosounder is in the running state
 *
 * @param[in]  snrctx       Connection handle obtained by DASS function.
 * @param[in]  buffer       pointer for data buffer
 * @param[in]  baudrate     number of bytes to be read
 *
 * @return                  number of bytes read
 */
DLL_EXPORT size_t DASSReadData(pSnrCtx snrctx, uint8_t *buffer, size_t size);

/**
 * @brief   Get value for the given parameter (command)
 *
 * @note    This function can be used in any state on the DASS
 *
 * @param[in]  snrctx       Connection handle obtained by DASS function.
 * @param[in]  command      parameter for which command should be obtained
 * @param[out] value        value of given command
 *
 * @return                  0  - value is valid
 * @return                  -1 - value is invalid
 */
DLL_EXPORT int DASSGetValue(pSnrCtx snrctx, DASSCommandIds_t command, pDASSValue value);

/**
 * @brief   Set value for the given parameter (command)
 *
 * @note    This function can be used in any state on the DASS
 *
 * @param[in]  snrctx       Connection handle obtained by DASSOpen function.
 * @param[in]  command      parameter for which command should be set
 * @param[out] value        value of given command
 *
 * @return                  0  - value is set successfully
 * @return                  -1 - set value failed
 */
DLL_EXPORT int DASSSetValue(pSnrCtx snrctx, DASSCommandIds_t command, pcDASSValue value);

/**
 * @brief   Convert value read from echosounder to long 
 *
 * @note    Helper function
 *
 * @param[in]  value        Echosounder value to convert
 *
 * @return                  Converted value
 */
DLL_EXPORT long DASSValueToLong(pcDASSValue value);

/**
 * @brief   Convert value read from echosounder to float
 *
 * @note    Helper function
 *
 * @param[in]  value        Echosounder value to convert
 *
 * @return                  Converted value
 */
DLL_EXPORT float DASSValueToFloat(pcDASSValue value);

/**
 * @brief   Convert value read from DASS to null-terminated char*
 *
 * @note    Helper function
 *
 * @param[in]  value        DASS value to convert
 *
 * @return                  Converted value
 */
DLL_EXPORT const char *DASSValueToText(pcDASSValue value);

/**
 * @brief   Check whether DASS value is valid
 *
 * @note    Helper function
 *
 * @param[in]  value        DASS value to convert
 *
 * @return                  true - value is valid
 * @return                  false - value is invalid
 */
DLL_EXPORT bool IsValidDASSValue(pcDASSValue value);

/**
 * @brief   Convert long number to DASS value
 *
 * @note    Helper function
 *
 * @param[in]  num          Long number to convert
 * @param[out] value        Converted value
 */
DLL_EXPORT void LongToDASSValue(long num, pDASSValue value);

/**
 * @brief   Convert float number to DASS value
 *
 * @note    Helper function
 *
 * @param[in]  num          Long number to convert
 * @param[out] value        Converted value
 */
DLL_EXPORT void FloatToDASSValue(float num, pDASSValue value);

/**
 * @brief   Start the unit.
 *
 * @note    DASS will be in running state after this.
 *
 * @param[in]  snrctx       Connection handle obtained by DASSOpen function.
 */
DLL_EXPORT void DASSStart(pSnrCtx snrctx);

/**
 * @brief   Stop the unit.
 *
 * @note    DASS will be in stop state after this.
 *
 * @param[in]  snrctx       Connection handle obtained by DASSOpen function.
 */
DLL_EXPORT void DASSStop(pSnrCtx snrctx);

/**
 * @brief   Checking the running state of the DASS
 *
 * @note    Not affect the DASS state
 *
 * @param[in]  snrctx       Connection handle obtained by DASSOpen function.
 *
 * @return                  true - DASS in running state
 * @return                  false - DASS is not in running state
 */
DLL_EXPORT bool DASSIsRunning(pSnrCtx snrctx);

/**
 * @brief   Checking whether DASS is detected on serial port
 *
 * @note    Not affect the DASS state
 *
 * @param[in]  snrctx       Connection handle obtained by DASSOpen function.
 *
 * @return                  true - DASS is detected
 * @return                  false - DASS is not detected
 */
DLL_EXPORT bool DASSIsDetected(pSnrCtx snrctx);

/**
 * @brief   Detect DASS on serial port
 *
 * @note    DASS will be in stop state after this
 *
 * @param[in]  snrctx       Connection handle obtained by DASSOpen function.
 *
 * @return                  true - echosounder is detected
 * @return                  false - echosounder is not detected
 */
DLL_EXPORT bool DASSDetect(pSnrCtx snrctx);

/**
 * @brief   Set current time to the echosounder (UTC). It use current time from host PC.
 *
 * @note    It can be neccessary for sync NMEA output with GPS output
 *
 * @param[in]  snrctx       Connection handle obtained by DASS function.
 */
DLL_EXPORT void DASSSetCurrentTime(pSnrCtx snrctx);

#ifdef __cplusplus
}
#endif

#endif // !DASS710CWRAPPER_H
