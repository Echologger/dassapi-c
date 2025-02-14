List of DASS Commands
===========================================

| CommandID | Text command | Description | Value | Items | Comment |
|:---|:---|---|:---:|:---:|---|
| IdInfo | #help<br>#info<br>?  | Show info screen | N/A | N/A | Show info screen and command list |
| IdGo | #go | Start unit | N/A | N/A | Start unit |
| Idreset | #reset | Reset unit | N/A | N/A | Reset unit |
| IdRange | #range | Set working range | 1000~200000 | mm | Depend of current working frequency |
| IdRangeH | #rangeh | Set working range for high frequency | 1000~200000 | mm | Depend of high working frequency |
| IdRangeL | #rangel | Set working range for low frequency | 1000~200000 | mm | Depend of low working frequency |
| IdTxLength | #txlength | Set transmit pulse length | 10~200 | µseconds | Pulse length in microsecond |
| IdTxLengthH | #txlengthh | Set transmit pulse length for high frequency | 10~200 | µseconds | Pulse length in microsecond |
| IdTxLengthL | #txlengthl | Set transmit pulse length for low frequency | 10~200 | µseconds | Pulse length in microsecond |
| IdGain | #gain | Set gain for current frequency | ±60 | dB | Gain for current working frequency |
| IdGainH | #gainh | Set gain for high frequency | ±60 | dB | Gain for high frequency |
| IdGainL | #gainl | Set gain for low frequency | ±60 | dB | Gain for low frequency |
| IdTVGMode |#tvgmode|Set TVGMode |0~2|dB/m|Absorbtion transmission losses value for current working frequency |
| IdTVGAbs | #tvgabs | Set TL value for current frequency | 0~2 | dB/m | Absorbtion transmission losses value for current working frequency |
| IdTVGAbsH | #tvgabsh | Set TL value for high frequency | 0~2 | dB/m | Absorbtion transmission losses value for high frequency |
| IdTVGAbsL | #tvgabsl | Set TL value for low frequency | 0~2 | dB/m | Absorbtion transmission losses value for low frequency |
| IdTVGSprd | #tvgsprd | Set spreading law coeff. for current frequency | 10~40 | N/A | Spreading transmission losses coefficient K*log(R) |
| IdSound | #sound | Set speed of sound | 1000~2000 | m/s | Speed of sound in m/s |
| IdDeadzone | #deadzone | Set deadzone for current frequency | 0~Range | mm | Set deadzone for current frequency |
| IdDeadzoneH | #deadzoneh | Set deadzone for current frequency | 0~Range | mm | Set deadzone for current frequency |
| IdDeadzoneL | #deadzonel | Set deadzone for current frequency | 0~Range | mm | Set deadzone for current frequency |
| IdThreshold | #threshold | Set threshold for current frequency | 10~80 | % of FS | Percent of full scale |
| IdOffset | #offset | Set offset for current frequency| ±1000 | mm | Offset in millimeters |
| IdOutput | #output | Set output mode | 1~255 | N/A | Vary. Refer to user manual. Modes 1~3 are compatible with EU400. |
| IdSamplFreq | #samplfreq | Set output sampling frequency | 6250~100000 | Hz | Set 0 to Auto. |
| IdTime | #time | Set current UTC time | 0~4294967295 | seconds | Seconds since 1970/01/01 00:00 UTC. Clear upon reset. |
| IdVersion | #version | Firmware version | Any | N/A | Should be threated as test string |
| IdSetHighFreq | #setfreqhigh<br>#setfh | Set high working frequency | N/A| N/A| Set high working frequency |
| IdSetLowFreq | #setfreqlow<br>#setfl | Set low working frequency | N/A | N/A | Set low working frequency |
| IdSetDualFreq | #setfd | Set dual working frequency | N/A | N/A | Set dual/simultaneous mode  |
| IdGetHighFreq | #getfh | Get high working frequency | N/A | N/A | Get high working frequency |
| IdGetLowFreq | #getfl | Get low working frequency | N/A | N/A | Get low working frequency |
| IdGetWorkFreq | #getfw | Get current working frequency | N/A | N/A | Get working frequency |
| IdHstep | #hstep | Set Horizontal step size | 1~180 | degrees | Set Horizontal step size in microsteps (0.1 degrees) |
| IdVstep | #vstep | Set Vertical step size | 1~180 | degrees | Set Vertical step size in microsteps (0.1 degrees) |
| IdHdir | #hdir | Set Horizontal direction | 0~1 | N/A | Set Horizontal direction of rotation (0,1 - CW, CCW) |
| IdVdir | #vdir | Set Vertical direction | 0~1 | N/A | Set Vertical direction of rotation (0,1 - CW, CCW) |
| IdSector | #sector | Sector mode on/off | 0~1 | N/A | Sector mode on/off for horizontal scaaning (0,1 - OFF, ON) |
| IdHheading | #hheading | Sector direction for horizontal scanning | 0~360 | degrees | Sector direction for horizontal scanning |
| IdVheading | #vheading | Sector direction for vertical scanning | 0~190, 350~360 | degrees | Sector direction for vertical scanning (0 ~ 190, 350 ~ 360) |
| IdHsangle | #hsangle | Sector size for horizontal scanning | 0~360 | degrees | Sector size for horizontal scanning |
| IdVsangle | #vsangle | Sector size for vertical scanning | 0~200 | degrees | Sector size for vertical scanning |
| IdDmode | #dmode | Set opertation mode | 0~3 | N/A | Set opertation mode |
| IdSmode | #smode | Set which direction to rotate first | 0~1 | N/A | Set which direction to rotate first (0,1 - Horizontal, Vertical) |
| IdRmode | #rmode | Set variable resolution in 3D | 0~1 | N/A | Set variable resolution in 3D (0,1 - Constant, Variable) |
| IdGyro | #gyro | gyroscope data on/off | 0~1 | N/A | gyroscope data on/off (0,1 - OFF, ON) |
| IdGyroCali | #gyro_c | gyroscope calibration | N/A | N/A | gyroscope calibration |