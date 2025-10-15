// 2025/10/15 14:32:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/PCM/ParserPCM.h"
#include "Utils/StringUtils.h"
#include "Device/FPGA.h"
#include "Device/Chips.h"
#include "Hardware/HAL/HAL.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>

/*
    :FPGA:REG[0...9]:LENGHT [1...32]
    :FPGA:REG[0...9]:WRITE  [0....(uint)-1]

    :DAC[0...9]:LENGTH [8...32]
    :DAC[0...9]:WRITE [0...(uint)-1]

    :ADC[0...9]:LENGTH [8...32]
    :ADC[0...9]:READ

    :REG[0...9]:LENGTH [8...32]
    :REG[0...9]:WRITE [0...(uint)-1]
*/


namespace ParserPCM
{
    struct StructParser
    {
        pchar         begin_string;
        bool          (*func)(pchar);
        StructParser *structs;
    };

    //-------------------------------------------------------------------------------------------------------------------------

    static bool Func_FPGA_REG(pchar);

    static StructParser fpga[] =
    {
        { "REG",   Func_FPGA_REG, nullptr },         // :FPGA:REG...
        { nullptr, nullptr,       nullptr }
    };

    //-------------------------------------------------------------------------------------------------------------------------

    static bool Func_ADC(pchar);

    //-------------------------------------------------------------------------------------------------------------------------

    static bool Func_DAC(pchar);

    //-------------------------------------------------------------------------------------------------------------------------

    static bool Func_REG(pchar);

    //-------------------------------------------------------------------------------------------------------------------------

    static StructParser head[] =
    {
        { "FPGA",  nullptr,  fpga },             // :FPGA...
        { "ADC",   Func_ADC, nullptr },
        { "DAC",   Func_DAC, nullptr },
        { "REG",   Func_REG, nullptr },
        { nullptr, nullptr,  nullptr }
    };

    static bool ProcessStructures(pchar, StructParser *);
}


bool ParserPCM::Parse(pchar command)
{
    return ProcessStructures(command, head);
}


bool ParserPCM::ProcessStructures(pchar command, StructParser *handlers)
{
    if (command[0] == ':')
    {
        command++;
    }

    StructParser *handler = handlers;

    while (handler->begin_string)
    {
        if (SU::BeginWith(command, handler->begin_string))
        {
            if (handler->func)
            {
                pchar new_command = command + std::strlen(handler->begin_string);

                if (*new_command == ':')
                {
                    new_command++;
                }

                return handler->func(new_command);
            }
            else if (handler->structs)
            {
                return ProcessStructures(command + std::strlen(handler->begin_string), handler->structs);
            }
        }

        handler++;
    }

    return true;
}


bool ParserPCM::Func_FPGA_REG(pchar command)
{
    if (*command < '0' || *command > '9')
    {
        return false;
    }

    int num_reg = (int)((*command) | 0x30);

    command++;

    if (*command != ':')
    {
        return false;
    }

    command++;

    if (SU::BeginWith(command, "LENGTH "))                              // :FPGA:REG:LENGTH
    {
        command += std::strlen("LENGTH ");

        char *pos = nullptr;

        uint length = std::strtoul(command, &pos, 16);

        if (pos == command + std::strlen("LENGTH "))
        {
            FPGA::Reg::SetLength(num_reg, length);

            return true;
        }

        return false;
    }
    else if (SU::BeginWith(command, "WRITE "))                          // :FPGA:REG:WRITE
    {
        command += std::strlen("WRITE ");

        char *pos = nullptr;

        uint value = std::strtoul(command, &pos, 16);

        if (pos == command + std::strlen("WRITE "))
        {
            FPGA::Reg::Write(num_reg, value);

            return true;
        }

        return false;
    }

    return false;
}


bool ParserPCM::Func_ADC(pchar command)
{
    if (*command < '0' || *command > '9')
    {
        return false;
    }

    int num_adc = (int)(*command | 0x30);

    command++;

    if (*command != ':')
    {
        return false;
    }

    command++;

    if (SU::BeginWith(command, "LENGTH "))                              // :ADC:LENGTH
    {
        command += std::strlen("LENGTH ");

        char *pos = nullptr;

        uint length = std::strtoul(command, &pos, 16);

        if (pos == command + std::strlen("LENGTH "))
        {
            adcs[num_adc].SetLength(length);

            return true;
        }

        return false;
    }
    else if (std::strcmp(command, "READ") == 0)                         // :ADC:READ
    {
        uint value = adcs[num_adc].Read();

        char message[64];

        std::sprintf(message, ":ADC%d:READ %u", num_adc, value);

        HAL_USART1::TransmitString(message);

        return true;
    }

    return false;
}


bool ParserPCM::Func_DAC(pchar command)
{
    if (*command < '0' || *command > '9')
    {
        return false;
    }

    int num_dac = (int)(*command | 0x30);

    command++;

    if (*command != ':')
    {
        return false;
    }

    command++;

    if (SU::BeginWith(command, "LENGTH "))                              // :DAC:LENGTH
    {
        command += std::strlen("LENGTH ");

        char *pos = nullptr;

        uint length = std::strtoul(command, &pos, 16);

        if (pos == command + std::strlen("LENGTH "))
        {
            dacs[num_dac].SetLength(length);

            return true;
        }

        return false;
    }
    else if (SU::BeginWith(command, "WRITE "))                          // :DAC:WRITE
    {
        command += std::strlen("WRITE ");

        char *pos = nullptr;

        uint value = std::strtoul(command, &pos, 16);

        if (pos == command + std::strlen("WRITE "))
        {
            dacs[num_dac].Write(value);

            return true;
        }

        return false;
    }

    return false;
}


bool ParserPCM::Func_REG(pchar command)
{
    if (*command < '0' || *command > '9')
    {
        return false;
    }

    int num_reg = (int)(*command | 0x30);

    command++;

    if (*command != ':')
    {
        return false;
    }

    command++;

    if (SU::BeginWith(command, "LENGTH "))                              // :REG:LENGTH
    {
        command += std::strlen("LENGTH ");

        char *pos = nullptr;

        uint length = std::strtoul(command, &pos, 16);

        if (pos == command + std::strlen("LENGTH "))
        {
            regs[num_reg].SetLength(length);

            return true;
        }

        return false;
    }
    else if (SU::BeginWith(command, "WRITE "))                          // :REG:WRITE
    {
        command += std::strlen("WRITE ");

        char *pos = nullptr;

        uint value = std::strtoul(command, &pos, 16);

        if (pos == command + std::strlen("WRITE "))
        {
            regs[num_reg].Write(value);

            return true;
        }

        return false;
    }

    return false;
}
