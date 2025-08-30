// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Command.h"

#ifdef PANEL
#include "Generator/Generator_p.h"
#else
#ifdef PLOADER
#include "Generator/Generator_p.h"
#else
#include "Generator/Generator_d.h"
#endif
#endif


struct SimpleMessage  // -V690
{
    explicit SimpleMessage();
    explicit SimpleMessage(int size, uint8);
 
    ~SimpleMessage();

    void Create(int size, uint8);
    // ���������� ��������� �� ��������� �����
    SimpleMessage *Clone();
    // ���������� ��������� ����������� ����������.
    void ResetPointer() { taken = 0; };

    bool CreateFromMessage(const SimpleMessage *message);
    // ������� ��������� � ���������� ������
    bool CreateAllocate(const uint8 *buffer, int size);
    // �������� ����������� ���������� ������
    bool AllocateMemory(int size);
    // ����� ���������� ������. ����� ������ ���� ������� �������� �� ��������� ������ ������
    void TakeRemainigData(uint8 *data);
    // ���������� ��������� �� ���������� ������. ������ ����� ������� �����
    uint8 *RemainingData() const;
    // ���������� ������
    void FreeMemory();
    // ���������� ������ ������
    int Size() const;
    // ���������� true, ���� ��� null-����� (������ �� ��������)
    bool IsEmpty() const;
    // ���������� true, ���� ��������� ���������
    bool IsEquals(const SimpleMessage *message) const;
    // ���������� ��������� �� pos-� �������. ������ ��� ����������� �����
    char *String(int pos);

    void PutUINT8(uint8 data);
    void PutINT16(int16 data);
    void PutUINT16(uint16 data);
    void PutINT(int data);
    void PutUINT(uint data);
    void PutUINT64(uint64 data);
    void PutFLOAT(float data);
    void PutData(const uint8 *data, int length);

    uint8  TakeUINT8();
    int16  TakeINT16();
    uint16 TakeUINT16();
    int    TakeINT();
    uint   TakeUINT();
    uint64 TakeUINT64();
    float  TakeFLOAT();
    uint8 *TakeData(int pos = 0);

    // �������� ��������� ����������
    void Transmit();
    // �������� ��������� ���������� � ���������, ���� ��� ������� ������������ �����
    void TransmitAndSend();

protected:

    // ������ ���������� ������
    int allocated;
    // ����� ������ ������, ���� 0, ���� ������ �� ��������
    uint8 *buffer;
    // ������� ������ ������ ��������� �������. ������������ ��� Put
    int used;
    // �� ����� ������� ���������. ������������ ��� Take
    int taken;

    SimpleMessage(const SimpleMessage &) : allocated(0), buffer(0), used(0), taken(0) {};
    SimpleMessage &operator=(const SimpleMessage &);

public:
    static int created;
    static int destroed;
    static int createdSize;
    static int destroedSize;
};


namespace Message
{

    // ��������� ��������� - ��� ������ ����� ������������
    struct RequestData : public SimpleMessage
    {
        RequestData();
    };


    // ��������� � �������
    struct Log : public SimpleMessage
    {
        Log(char *string);
    };


    // ��������� ������ �������
    struct StartMode : public SimpleMessage
    {
        StartMode(uint8 ch, uint8 mode);
    };


    // ����� �����/���� ����������� �������
    struct SetStartStopMode : public SimpleMessage
    {
        // mode : 0 - ���������
        //        1 - �������
        SetStartStopMode(int mode);
    };

    // ��������� �������� ������� ������������� ���������
    struct SetClockImpulse : public SimpleMessage
    {
        // 0 - 100 ���, 1 - 1 ���
        SetClockImpulse(int clock);
    };

    // ������ � �������
    struct WriteRegister : public SimpleMessage
    {
        WriteRegister(uint8 reg, uint64 data);
    };


    // ��������� ����������� ������
    struct DebugMode : public SimpleMessage
    {
        // mode == 1/0 - ��������/��������� ����� �������
        DebugMode(uint8 mode);
    };


    // ��������/��������� �����
    struct EnableChannel : public SimpleMessage
    {
        // ch : 0 - A, 1 - B
        // enable : 0 - ���������, 1 - ��������
        EnableChannel(uint8 ch, uint8 enable);
    };

    struct SingleStart : public SimpleMessage
    {
        SingleStart();
    };

    // ��������� ���� ��������
    struct RegCPU : public SimpleMessage
    {
        RegCPU(uint8 port, uint8 pin, uint8 state);
    };


    struct Debug : public SimpleMessage
    {
        Debug();
    };


    struct SetFreqMeterTrigK : public SimpleMessage
    {
        SetFreqMeterTrigK(int16 k);
    };


    namespace FDrive
    {
        // ������ ����� �����
        struct FileName : public SimpleMessage
        {
            FileName(uint8 numFile, char *name);
        };


        struct FileString : public SimpleMessage
        {
            FileString(uint numString, char *nameFile);
        };


        // ����� ��������� � ������ � ������� ��������
        struct NumDirsAndFiles : public SimpleMessage
        {
            NumDirsAndFiles(uint numDirs, uint numFiles);
            NumDirsAndFiles(char *directory);
        };


        // ��������� � ���������������/�������������� �����
        struct Mount : public SimpleMessage
        {
            // mount :
            // 0 - ������ �������������;
            // 1 - ������ ������ ��������������
            // 2 - ������ ������������� �� �������
            Mount(uint8 mount);
        };


        // ������ ������� �����
        struct FileSize : public SimpleMessage
        {
            FileSize(uint8 numFile, uint size);
        };


        struct RequestPictureDDSfromFile : public SimpleMessage
        {
            // ������ �������� � ������������ �� ����� numberFile
            RequestPictureDDSfromFile(uint8 numberFile);

            // �����
            RequestPictureDDSfromFile(uint8 numberFile, uint8 data[240]);
        };

        // ��������� ��������� ���� � FPGA
        struct LoadDDSfromFile : public SimpleMessage
        {
            LoadDDSfromFile(uint8 ch, uint8 numFile, char *directory);
        };


        struct CreateFFile : public SimpleMessage
        {
            CreateFFile(pchar name);
        };

        struct WriteToFile : public SimpleMessage
        {
            WriteToFile(void *data, int size);
        };

        struct CloseFile : public SimpleMessage
        {
            CloseFile();
        };
    }


    namespace Storage
    {
        struct RequestPictureDDS : public SimpleMessage
        {
            // ������ ����������� ������������� ������� �� ����
            RequestPictureDDS(uint8 ch);

            // �����
            RequestPictureDDS(uint8 ch, uint8 data[240]);
        };

        struct LoadDDS : public SimpleMessage
        {
            LoadDDS();
        };
    }

    namespace Set
    {

        // ��������� ����� �������
        struct FormWave : public SimpleMessage
        {
            FormWave(uint8 ch, uint8 form);
        };


        // ��������� ���������
        struct Amplitude : public SimpleMessage
        {
            Amplitude(uint8 ch, uint64 amplitude);
        };


        // ��������� �������� ������� �� ������
        struct Offset : public SimpleMessage
        {
            Offset(uint8 ch, uint64 offset);
        };


        // ������������� ���������� ��� ������� ���������
        struct Param : public SimpleMessage
        {
            Param(Command::E param, uint8 ch, uint64 value);
            Param(Command::E param, uint8 ch, uint8 choice);
        };
    }

    namespace FreqMeter
    {

        // ��������� ��������� �����������
        struct Measure : public SimpleMessage
        {
            Measure(uint frequency);
        };
    }

    namespace SCPI
    {
        // ������ SCPI
        struct Data : public SimpleMessage
        {
            Data(uint8 *data, int length);
        };
    }

    // ������� �������������� ������������ � ��������� �������������� �������� ����������
    struct CalibrateSet : public SimpleMessage
    {
        CalibrateSet(uint8 ch, uint8 signal, uint8 range, uint8 parameter);
    };

    // ������� �������������� ������������
    struct CalibrateLoad : public SimpleMessage
    {
        CalibrateLoad(uint8 ch, uint8 signal, uint8 range, uint8 parameter);
    };
}
