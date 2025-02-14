// Copyright (c) EofE Ultrasonics Co., Ltd., 2025
#include <cstdio>
#include <cstdarg>
#include <string>

#include "DASS.h"
#include "DASS710.h"
#include "DASSCWrapper.h"
#include "serial/serial.h"

#if defined(_MSC_VER) && _MSC_VER < 1900

#define snprintf c99_snprintf
#define vsnprintf c99_vsnprintf

__inline int c99_vsnprintf(char *outBuf, size_t size, const char *format, va_list ap)
{
    int count = -1;

    if (size != 0)
        count = _vsnprintf_s(outBuf, size, _TRUNCATE, format, ap);
    if (count == -1)
        count = _vscprintf(format, ap);

    return count;
}

__inline int c99_snprintf(char *outBuf, size_t size, const char *format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
    count = c99_vsnprintf(outBuf, size, format, ap);
    va_end(ap);

    return count;
}

#endif

pSnrCtx DASS710Open(const char* portpath, uint32_t baudrate)
{
    pSnrCtx ctx = nullptr;

    try
    {
        std::shared_ptr<serial::Serial> serialPort(new serial::Serial(portpath, baudrate, serial::Timeout::simpleTimeout(SERIALPORT_TIMEOUT_MS)));
        ctx = reinterpret_cast<pSnrCtx>(new DASS(serialPort));
    }
    catch (...)
    {
        // In case of any exception this function returns nullptr
    }

    return ctx;
}

void DASSClose(pSnrCtx snrctx)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    delete ss;
    snrctx = nullptr;
}

size_t DASSReadData(pSnrCtx snrctx, uint8_t *buffer, size_t size)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    return ss->GetSerialPort()->read(buffer, size);
}

long DASSValueToLong(pcDASSValue value)
{
    return std::stol(value->value_text);
}

float DASSValueToFloat(pcDASSValue value)
{
    return std::stof(value->value_text);
}

const char *DASSValueToText(pcDASSValue value)
{
    return value->value_text;
}

bool IsValidDASSValue(pcDASSValue value)
{
    return !((0 == value->value_len) || (0 == strlen(value->value_text)));
}

void LongToDASSValue(long num, pDASSValue value)
{
    value->value_len = snprintf(value->value_text, sizeof(value->value_text), "%ld", num);
}

void FloatToDASSValue(float num, pDASSValue value)
{
    value->value_len = snprintf(value->value_text, sizeof(value->value_text), "%f", num);
}

int DASSGetValue(pSnrCtx snrctx, DASSCommandIds_t command, pDASSValue value)
{
    int result = -1;

    auto ss = reinterpret_cast<DASS*>(snrctx);
    std::string ssvalue = ss->GetValue(command);

    (void)snprintf(value->value_text, sizeof(value->value_text), "%s", ssvalue.c_str());
    value->value_len = (int)ssvalue.length();

    return (ssvalue.length() > 0) ? 0 : -1;
}

int DASSSetValue(pSnrCtx snrctx, DASSCommandIds_t command, pcDASSValue value)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    bool result = ss->SetValue(command, value->value_text);

    return (false != result) ? 0 : -1;
}

bool DASSDetect(pSnrCtx snrctx)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    return ss->Detect();
}

void DASSStart(pSnrCtx snrctx)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    ss->Start();
}

void DASSStop(pSnrCtx snrctx)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    ss->Stop();
}

bool DASSIsRunning(pSnrCtx snrctx)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    return ss->IsRunning();
}

bool DASSIsDetected(pSnrCtx snrctx)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    return ss->IsDetected();
}

void DASSSetCurrentTime(pSnrCtx snrctx)
{
    auto ss = reinterpret_cast<DASS*>(snrctx);
    ss->SetCurrentTime();
}
