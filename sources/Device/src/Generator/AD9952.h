// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "common/Common.h"
#include "common/CommonTypes.h"
#include "Hardware/CPU.h"
#include "Hardware/HAL/HAL_PIO.h"


namespace AD9952
{
    void Init();

    // ��� ��������� ����� ������� "������" ����� �������� ��� �������, ����� ��� ������� ��������� � ������ ������ ��������-���� �� �����
    void SetAmplitudeForMeander(const Chan &);

    void SetAmplitude(const Chan &);

    void SetFrequency(const Chan &);

    void SetPhase(const Chan &, Value phase);

    // �����������
    namespace Manipulation
    {
        // True ��������, ��� ����������� ��������
        extern bool enabled[Chan::Count];

        // ����������/�������� ������������� ��������� �������� "����"
        void SetEnabled(const Chan &, bool enable);

        inline bool IsEnabled(const Chan &ch) { return enabled[ch]; };
    };
};
