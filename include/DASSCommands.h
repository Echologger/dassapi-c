// Copyright (c) EofE Ultrasonics Co., Ltd., 2025
#if !defined(DUALAXISOMMANDS_H)
#define DUALAXISOMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

enum DASSCommandIds
{
    IdInfo = 0, 
    Idreset,
    Iddefault,
    IdGo,
    IdRange,
    IdRangeH,
    IdRangeL,
    IdTxLength,
    IdTxLengthH,
    IdTxLengthL,
    IdGain,
    IdGainH,
    IdGainL,
    IdTVGMode,
    IdTVGAbs,
    IdTVGAbsH,
    IdTVGAbsL,
    IdTVGSprd,    
    IdSound,
    IdDeadzone,
    IdDeadzoneH,
    IdDeadzoneL,
    IdThreshold,
    IdOffset,
    IdOutput,
    IdSamplFreq,
    IdTime,
    IdVersion,

    IdSetHighFreq,
    IdSetLowFreq,
    
    IdGetHighFreq,
    IdGetLowFreq,
    IdGetWorkFreq,

    IdHstep,
    IdVstep,
    IdHdir,
    IdVdir,
    IdSector,
    IdHheading,
    IdVheading,
    IdHsangle,
    IdVsangle,
    IdDmode,
    IdSmode,
    IdRmode,
    IdGyro,
    IdGyroCali
};

typedef enum DASSCommandIds DASSCommandIds_t;

struct DASSCommandList
{
    const char* command_text;
    const char* default_value;
    const char* regex_match_text;
};

#ifdef __cplusplus
}
#endif

#endif //DUALAXISOMMANDS_H
