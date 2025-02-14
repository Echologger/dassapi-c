// Copyright (c) EofE Ultrasonics Co., Ltd., 2025
#if !defined(DASS_H)
#define DASS_H

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

namespace
{
    std::map<int, DASSCommandList> DualAxisCommands =
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
        { DASSCommandIds::Idreset,             { "#reset",         "",      "" }},

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
        { DASSCommandIds::IdRmode,             { "#rmode",      "0",     " - #rmode[ ]{0,}\\[[ ]{0,}([0-9]{1,})[ ]{0,}\\].*" }}
    };
}

/**
    @class DASS

    DASS is used for access to DASS710.
 */

class DASS : public ISonar
{    
    /**
    *   Serial port class used by DASS
    */
    std::shared_ptr<serial::Serial>serial_port_;

    /**
    *   Data return by the unit after host issued command to it
    */
    std::string command_result_;

    /**
    *   #info command result line by line
    */
    std::vector<std::string> info_lines_;

    /**
    *   This map contains all available command for the DASS
    */
    std::map<int, DASSCommandList>& DASS_commands_;

    /**
    *   This map contains all current settings of the DASS
    */
    std::map<DASSCommandIds_t, std::string> DASS_settings_;

    /**
    *   Current running status of the DASS
    */
    bool is_running_;

    /**
    *   Current detected status of the DASS
    */
    bool is_detected_;

    /**
     *   @brief Send command to the echosounder
     *   @param command - command to send
     *   @return 1 - command successfuly execute, 2 - invalid argument, 3 - invalid command, -2 - timeout occured
     */
    int SendCommand(DASSCommandIds command);

    /**
     *   @brief Receive responce for command sent to the echosounder
     *   @return 1 - command successfuly execute, 2 - invalid argument, 3 - invalid command, -2 - timeout occured
     */
    int SendCommandResponseCheck();

    /**
     *   @brief Waiting until echosounder send back "command prompt" character
     *   @param timeoutms - timeout in milliseconds
     *   @return 1 - command prompt received, -2 - timeout occured
     */
    int WaitCommandPrompt(int64_t timeoutms) const;

    void GetAllValues();
    void SetAllValues();

    /**
     *   @brief Send #info command and parse it to echosounder_settings_
     *   @return 1 - command successfuly execute, 2 - invalid argument, 3 - invalid command, -2 - timeout occured
     */
    int GetSonarInfo();

public:

    /**
        Constructor
    */
    DASS(std::shared_ptr<serial::Serial> SerialPort, std::map<int, DASSCommandList>& CommandList = DualAxisCommands);

    /**
    *   @brief Set DASS's value   
    */
    bool SetValue(DASSCommandIds Command, const std::string &SonarValue);

    /**
    *   @brief Get DASS's value. Value is stored internally in the class.
    *   @return std::string reference to Value
    */  
    const std::string &GetValue(DASSCommandIds command);

    /**
    *   @brief Set current time to DASS
    */  
    void SetCurrentTime();

    /**
    *   @brief Get serial port used for access to DASS.
    *   @return std::shared_ptr<serial::Serial> reference
    */
    std::shared_ptr<serial::Serial> &GetSerialPort();

    virtual void GetSettings() override;
    virtual void SetSettings() override;
    virtual void Start() override;
    virtual void Stop() override;

    virtual bool Detect() override;

    virtual bool IsRunning() override;
    virtual bool IsDetected() override;
};

#endif // DASS_H
