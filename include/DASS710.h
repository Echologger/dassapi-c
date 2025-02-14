// Copyright (c) EofE Ultrasonics Co., Ltd., 2025
#if !defined(DASS710_H)
#define DASS710_H

#include "ISonar.h"
#include <cstdint>
#include <thread>
#include <string>
#include <vector>
#include <memory>
#include <regex>
#include <map>

#include "serial/serial.h"
#include "DASSCommands.h"
#include "DASS.h"

namespace
{
    std::map<int, DASSCommandList> DASS710Commands =
    {
        { DASSCommandIds::IdInfo,              { "#info",       "",      "" }},
        { DASSCommandIds::IdRange,             { "#range",      "10000", " - #range[ ]{0,}\\[[ ]{0,}([0-9]{1,}) mm[ ]{0,}\\].*" }},
        { DASSCommandIds::IdRangeH,            { "#rangeh",     "10000", " - #rangeh[ ]{0,}\\[[ ]{0,}([0-9]{1,}) mm[ ]{0,}\\].*" }},
        { DASSCommandIds::IdRangeL,            { "#rangel",     "10000", " - #rangel[ ]{0,}\\[[ ]{0,}([0-9]{1,}) mm[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTxLength,          { "#txlength",   "50",    " - #txlength[ ]{0,}\\[[ ]{0,}([0-9]{1,}) uks[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTxLengthH,         { "#txlengthh",  "50",    " - #txlengthh[ ]{0,}\\[[ ]{0,}([0-9]{1,}) uks[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTxLengthL,         { "#txlengthl",  "100",   " - #txlengthl[ ]{0,}\\[[ ]{0,}([0-9]{1,}) uks[ ]{0,}\\].*" }},
        { DASSCommandIds::IdGain,              { "#gain",       "0.0",   " - #gain[ ]{0,}\\[[ ]{0,}([+-]?([0-9]*[.])?[0-9]+) dB[ ]{0,}\\].*" }},
        { DASSCommandIds::IdGainH,             { "#gainh",      "0.0",   " - #gainh[ ]{0,}\\[[ ]{0,}([+-]?([0-9]*[.])?[0-9]+) dB[ ]{0,}\\].*" }},
        { DASSCommandIds::IdGainL,             { "#gainl",      "0.0",   " - #gainl[ ]{0,}\\[[ ]{0,}([+-]?([0-9]*[.])?[0-9]+) dB[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTVGMode,           { "#tvgmode",    "1",     " - #tvgmode[ ]{0,}\\[[ ]{0,}([0-4]{1})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTVGAbs,            { "#tvgabs",     "0.140", " - #tvgabs[ ]{0,}\\[[ ]{0,}([+-]?([0-9]*[.])?[0-9]+) dB\\/m[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTVGAbsH,           { "#tvgabsh",    "0.140", " - #tvgabsh[ ]{0,}\\[[ ]{0,}([+-]?([0-9]*[.])?[0-9]+) dB\\/m[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTVGAbsL,           { "#tvgabsl",    "0.060", " - #tvgabsl[ ]{0,}\\[[ ]{0,}([+-]?([0-9]*[.])?[0-9]+) dB\\/m[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTVGSprd,           { "#tvgsprd",    "15.0",  " - #tvgsprd[ ]{0,}\\[[ ]{0,}([+-]?([0-9]*[.])?[0-9]+)[ ]{0,}\\].*" }},
        { DASSCommandIds::IdSound,             { "#sound",      "1500",  " - #sound[ ]{0,}\\[[ ]{0,}([0-9]{1,}) mps[ ]{0,}\\].*" }},
        { DASSCommandIds::IdDeadzone,          { "#deadzone",   "300",   " - #deadzone[ ]{0,}\\[[ ]{0,}([0-9]{1,}) mm[ ]{0,}\\].*" }},
        { DASSCommandIds::IdDeadzoneH,         { "#deadzoneh",  "300",   " - #deadzoneh[ ]{0,}\\[[ ]{0,}([0-9]{1,}) mm[ ]{0,}\\].*" }},
        { DASSCommandIds::IdDeadzoneL,         { "#deadzonel",  "500",   " - #deadzonel[ ]{0,}\\[[ ]{0,}([0-9]{1,}) mm[ ]{0,}\\].*" }},
        { DASSCommandIds::IdThreshold,         { "#threshold",  "10",    " - #threshold[ ]{0,}\\[[ ]{0,}([0-9]{1,}) %[ ]{0,}\\].*" }},
        { DASSCommandIds::IdOffset,            { "#offset",     "0",     " - #offset[ ]{0,}\\[[ ]{0,}([0-9]{1,}) mm[ ]{0,}\\].*" }},
        { DASSCommandIds::IdOutput,            { "#output",     "110",   " - #output[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdSamplFreq,         { "#samplfreq",  "0",     " - #samplfreq[ ]{0,}\\[[ ]{0,}([0-9]{1,6})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdTime,              { "#time",       "0",     " - #time[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},

        { DASSCommandIds::IdSetHighFreq,       { "#setfh",      "",      "" }},
        { DASSCommandIds::IdSetLowFreq,        { "#setfl",      "",      "" }},

        { DASSCommandIds::IdGetHighFreq,       { "#getfh",      "",      ".*High Frequency:[ ]{0,}([0-9]{4,})Hz.*" }},
        { DASSCommandIds::IdGetLowFreq,        { "#getfl",      "",      ".*Low Frequency:[ ]{0,}([0-9]{4,})Hz.*" }},
        { DASSCommandIds::IdGetWorkFreq,       { "#getf",       "",      ".*:[ ]{1,}([0-9]{4,})Hz[ ]{0,}\\(Active\\).*" }},

        { DASSCommandIds::IdGo,                { "#go",         "",      "" }},
        { DASSCommandIds::Idreset,             { "#reset",      "",      "" }},

        { DASSCommandIds::IdHstep,             { "#hstep",      "10",    " - #hstep[ ]{0,}\\[[ ]{0,}([0-9]{1,}) degree[ ]{0,}\\].*" }},
        { DASSCommandIds::IdVstep,             { "#vstep",      "10",    " - #vstep[ ]{0,}\\[[ ]{0,}([0-9]{1,}) degree[ ]{0,}\\].*" }},
        { DASSCommandIds::IdHdir,              { "#hdir",       "0",     " - #hdir[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdVdir,              { "#vdir",       "0",     " - #vdir[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdSector,            { "#sectpr",     "0",     " - #sector[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdHheading,          { "#hheading",   "0",     " - #hheading[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdVheading,          { "#vheading",   "45",    " - #vheading[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdHsangle,           { "#hsangle",    "360",   " - #hsangle[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdVsangle,           { "#vsangle",    "90",    " - #vsangle[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdDmode,             { "#dmode",      "0",     " - #dmode[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdSmode,             { "#smode",      "0",     " - #smode[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdRmode,             { "#rmode",      "0",     " - #rmode[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdGyro,              { "#gyro",       "0",     " - #gyro[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }},
        { DASSCommandIds::IdGyroCali,          { "#gyro_c",     "",      "" }}
    };
}

class DASS710 : public DASS
{
public:
    DASS710(std::shared_ptr<serial::Serial> SerialPort, std::map<int, DASSCommandList> &CommandList = DASS710Commands);
    virtual ~DASS710();
};


#endif // DASS710_H
