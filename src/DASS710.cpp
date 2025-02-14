// Copyright (c) EofE Ultrasonics Co., Ltd., 2025
#include "DASS710.h"

DASS710::DASS710(std::shared_ptr<serial::Serial> SerialPort, std::map<int, DASSCommandList>& CommandList) :
    DASS(SerialPort, CommandList)
{

}

DASS710::~DASS710()
{

}
