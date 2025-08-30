// 2022/08/30 11:42:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Common/Common.h"
#include "Common/CommonTypes.h"


namespace FPGA
{
    namespace Clock
    {
        // ������� ������� ��� ������������ �������� � ������� ���������. ��� ������������ �������� [0 ��� ... 40 ���]
        // ������� ������� 100 ���, ��� ������������ ����� - 1 ���
        namespace Impulse
        {
            enum E
            {
                _100MHz,
                _1MHz,
                Count
            };

            bool Is100MHz();
            bool Is1MHz();

            // �������� ��� ������� ��������� ������������ � �������
            inline int GetDivider1MHz()   { return 1000; };
            inline int GetDivider100MHz() { return 10; };

            // ����������� �������� ���������
            void RecalculateRegistersIfNeed();
        }

        // �������� ������� ������������� ������������ ��������
        namespace AD992
        {
            enum E
            {
                _100MHz,
                _1MHz
            };

            void Set(E);

            bool Is100MHz();
        };
    }
}
