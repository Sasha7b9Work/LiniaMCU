// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct SimpleMessage;


namespace DVCP
{
    static const int DEVICE_FS = 0;

    // �������������
    void Init();

    void SendData(const void *data, uint size = 0);
    // ��������� ������ ��� ������������ �������
    void SendString(char *data);
    // �������� ������ � �������� ����� ������
    void SendStringEOF(char *data);

    void SendByte(uint8 data);

    extern void *handle;

    namespace Handler
    {
        void Processing(SimpleMessage *msg);
    };

    void SetConnectedToUSB(bool connected);

    void SetCableUSBisConnected(bool connected);
};
