// 2025/10/15 14:32:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device/PCM/ParserPCM.h"
#include "Utils/StringUtils.h"
#include "Device/FPGA.h"
#include <cstring>
#include <cstdlib>

/*
    :FPGA:REG[0...9]:LENGHT [1...32]
    :FPGA:REG[0...9]:WRITE  [0....(uint)-1]

    :ADC[0...9]:LENGTH [8...32]
    :ADC[0...9]:WRITE [0...(uint)-1]

    :DAC[0...9]:LENGTH [8...32]
    :DAC[0...9]:READ

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

    static StructParser dac[] =
    {
        { nullptr, nullptr,  nullptr }
    };

    //-------------------------------------------------------------------------------------------------------------------------

    static StructParser reg[] =
    {
        { nullptr, nullptr,  nullptr }
    };

    //-------------------------------------------------------------------------------------------------------------------------

    static StructParser head[] =
    {
        { "FPGA",  nullptr,  fpga },             // :FPGA...
        { "ADC",   Func_ADC, nullptr },
        { "DAC",   nullptr,  dac },
        { "REG",   nullptr,  reg },
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
    return false;
}
