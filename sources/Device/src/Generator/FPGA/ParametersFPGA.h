// 2022/09/09 09:22:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Common/Common.h"
#include "Common/CommonTypes.h"


namespace FPGA
{
    // ����� �������
    namespace StartMode
    {
        enum E
        {
            Auto,           ///< ��������������
            Single,         ///< ����������� ������ �� ������� ������
            ComparatorA,    ///< ���������� ������ A (� ������ �������� �� ���� � ���� ������ AD9952 ������ A
            ShaperB         ///< ������������� ��������� ������ B (����� "���������� ������")
        };

        // ��������� ������ ������� ��� ������������� (0) ������� � ����������� (1) ������� signal
        void Set(const Chan &, uint8 signal, StartMode::E);
        StartMode::E Current(const Chan &, int type_signal);
    };

    namespace Packet
    {
        namespace Period
        {
            void Set(const Value &);
            Value &Current();
        }

        // ����� ��������� � ������
        namespace Number
        {
            // ������������� ����� ��������� � �����
            void Set(const uint n);
            uint Current();
        }
    }

    namespace Impulse
    {
        namespace Duration
        {
            void Set(const Chan &, const Value &);
            const Value &Current(const Chan &);
        }

        namespace Period
        {
            void Set(const Chan &, const Value &);
            const Value &Current(const Chan &);
        }
    }

    namespace StartStop
    {
        namespace Mode
        {
            enum E
            {
                Disable,
                Enable
            };

            void Set(E);
            E Current();
        }


        namespace Delay
        {
            // �������� ����� ���������� �� ������� ������� � ������� �������
            void Set(const Value &delay);
            Value &Current();
        }
    }
}
