// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#pragma once
#include "common/Messages.h"


#define SIZE_CHUNK        512            /* ������ ������������ ������ ������ */


namespace Message
{
    // ���� ���������� device ��� ������ ���������� �� ������
    class StartMainApplication : public SimpleMessage
    {
    public:
        StartMainApplication();
    };

    // ���� ���������� ������ ������ ������ �� ����������
    class RequestUpgrade : public SimpleMessage
    {
    public:
        RequestUpgrade();
    };

    // ���� ���������� ���������� �������� ������ ���������� ����� �������� device
    class PortionUpgradeDevice : public SimpleMessage
    {
    public:
        PortionUpgradeDevice(int portion);
    };

    // ��� ��������� DLoader �������� � PLoader, ���� ��������� ���� �������� Panel
    class AnswerUpgradePanel : public SimpleMessage
    {
    public:
        AnswerUpgradePanel(int size);
    };

    // ���� ���������� PLoader ����������� ������ ���������� �������� SIZE_CHUNK
    class RequestPortionUpgradePanel : public SimpleMessage
    {
    public:
        RequestPortionUpgradePanel(int16 num);
    };

    // ���� ��������� DLoader ������� �� ������ ������ ���������� �� PLoader
    class AnswerPortionUpgradePanel : public SimpleMessage
    {
    public:
        AnswerPortionUpgradePanel(int16 num, uint8 data[SIZE_CHUNK]);
    };
}
