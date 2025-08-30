// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Generator/Generator_d.h"
#include "common/Command.h"
#include "Generator/FPGA/RegistersFPGA.h"
#include "Generator/FPGA/ParametersFPGA.h"


namespace FPGA
{
    static const int NUM_POINTS = 1024 * 8;

    void Init();

    void SetWaveForm(const Chan &, TypeForm::E);

    void SetFrequency(const Chan &);

    void SetAmplitude();

    // 1 - ������������� ����������, 0 - ������������� ����������
    void SetPolarity(const Chan &, uint8 polarity);

    // ������ ����������� ������
    void SingleStart();

    void TransformCodeToData(const uint8 codeIn[FPGA::NUM_POINTS * 2], float dataOut[FPGA::NUM_POINTS]);

    // ���������� ��������� �� ����� �������, ������������ �� ������
    uint8 *DataFreeSignal(const Chan &);

    // ��������� ������ �������, ������������ � ������
    void SaveExtSignal(const Chan &, uint8 *data); 

    // ���������� ��������� �� ����� ������������� ������� (���������� �����������)
    uint8 *DataDDS(const Chan &);

    // ������ ������������ ��������
    void WriteControlRegister();

    namespace ModeWork
    {
        enum E
        {
            None,
            DDS,            // �������� �� ����������� ������ ������� ������������ �������� - ����, �����������
            Impulse,        // �����, � ������� ������c� ����� ����� ������ �������
            Rectangle,
            Meander,
            PackedImpulse,  // ������ ���������
            Sine,
            Free,
            Count
        };

        E Current(const Chan &);
    };
};
