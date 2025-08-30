// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
    #pragma once
#include "CommonTypes.h"


// ��������� ������� ��� �������� � �������� ���������
struct Command
{
    // ������ "->" ��������, ��� �������� ������ �� ������� � ������

    enum E
    {
          // 0
          // RequestData
/* <-> */    RequestData,                // ������ ������. ������ ��������� ���������� ��������� �� ������� ������� ������ ��� ��������.
             EnableChannel,              // ��������/��������� �����
          // 0           1       2
          // SetFomrWave NumChan Form
             SetFormWave,                // ���������� ����� �������
             SetFrequency,               // ���������� �������
             SetAmplitude,               // ���������� ���������
             SetOffset,                  // ���������� ��������
             SetDuration,
             SetPhase,
             ModeDebug,                  // ��������� ����������� ������ - ����� ���� ����������� ������� � FPGA
             SetDelayStartStop,          // ��������
          // 0             1            2...9
          // WriteRegister NameRegister Value64
             WriteRegister,              // ������� �������� � �������
             SetDurationRise,
             SetDurationFall,
             SetDurationStady,
             SetDutyFactor,
             SetManipulation,            // ���������� ����� �����������
             SetManipulationDuration,    // ���������� ������������ ������� � ������ �����������
             SetManipulationPeriod,      // ���������� ������ ���������� ��������� � ������ �����������
             SetPacketPeriod,
             SetPacketNumber,
          // 0            1        2
          // SetStartMode NUM_CHAN value
             SetStartMode,               // ���������� ����� ������� �� ������
             SetPeriod,                  // ���������� ������
          // 0           1        2
          // SetPolarity NUM_CHAN polarity
             SetPolarity,
          // 0            1       3...
          // LoadFormDDS, NumChan Points
             LoadFormDDS,               // ��������� ����� ������� ������������� �����
          // 0            1...5
          // FreqMeasure, ���������
/*  -> */    FreqMeasure,               // ��������� ��������� ����������� � ������
          //  0
          // Log
/*  -> */    Log,                       // ��������� ��� ������ � ���
          // 0 . ����� ������� �� 255 ���� ���� (�������� ����������� ����) ���� �� ��������, ���������� ��������� � ������ � ������� ���������� ����������         
          // ����� :
          // 0                       1...5   6...9
          //                         NumDirs NumFiles
/* <-> */    FDrive_NumDirsAndFiles,    // ������ ���������� ��������� � ������
          // 0             1
          //               data
/*  -> */    FDrive_Mount,              // ��������� � ���������������� ������. data == 0 - ������ �������������. 1 - ������ ��������������
          // 0                  1    ...
          //                    �����  ����_�_�������������_��������
/* <-> */    FDrive_RequestDir,         // ������ ����� ��������
          // 0                  1
          //                    ����� ����_�_�������������_��������
/* <-> */   FDrive_RequestFile,         // ������ ����� �����
        //  0      1...5    6...9
        //  Test   size     crc32
/* <-> */   Test,                               // ������� ��� ������������ SPI
/* <-> */   FDrive_RequestFileSize,             // ������ ������� �����
/* <-> */   FDrive_RequestFileString,           // ������� ������ �� �����
/* <-> */   FDrive_LoadDDSfromFile,             // ��������� ������ � ������. ������� ��� ���������, ���������� �������� �������� �������, � �� ��������� ���������� ��� �� ���������
/* <-> */   FDrive_RequestPictureDDSfromFile,   // �������� ����������� ����� �������
         // 0           1...5     6.....
         // SCPI_Data   sizeData  data 
/* <-> */   SCPI_Data,                      // �� VCP ������� ������ ���� � VCP ����� �������� ������
            PortCPU,
            CalibrationLoad,
            CalibrationSet,

            // byte(com)
            StartApplication,               // ������ ��������� ����������. ���� �������� Device ��� ������� Panel �� �����
            // byte(com)
            RequestUpgrade,                 // ������ �� ����������
            // byte(com) | byte(0...100)
            PortionUpgradeDevice,           // ���������� � ���������� ����� �������� Device
            // byte(com) | word(������)
            AnswerUpgradePanel,             // ���� �������� DLoader �������� � ���, ��� ������� ���������� Panel
            // byte(com) | hword(num)
            RequestPortionUpgradePanel,     // ������ �� ������ �������� Panel
            // byte(com) | hword(num) | word(crc32) | 512 bytes
            AnswerPortionUpgradePanel,      // ����� �� ������ ������ �������� Panel

            Debug,
            SetFreqMeterTrigK,              // ��������� �������������� ������������ ��� ������ ������������� �����������
            RequestPictureDDSfromStorage,   // ������ ����������� �������, ����������� � ����
            LoadDDSfromStorage,             // �������� ������� �� ����
            FDrive_CreateFile,
            FDrive_WriteToFile,
            FDrive_CloseFile,
            SingleStart,                    // ��� ����������� �������
            SetStartStopMode,               // ����� �����/���� ��� ����������� �������
            Count
    } value;
    Command(E v) : value(v) {};
    Command(const uint8 v) : value((E)v) {};
    operator uint8() const { return (uint8)value; };
    cstr Name() const;
    operator E() const { return value; };
    operator uint8() { return (uint8)value; }
private:
    cstr Value(uint8 *buffer) const;
};


struct Register
{
    enum E
    {
        deleted_Multiplexor1,   // \todo ��� ���� �������
        deleted_Multiplexor2,
        OffsetA,
        OffsetB,
        FreqMeterLevel,
        FreqMeterHYS,
        FPGA_RG0_Control,           // ����������� �������
        FPGA_RG1_Freq,              // ������� ���� �������
        FPGA_RG2_Amplitude,         // ������� ���� ����������
        FPGA_RG3_RectA,             // ������� ���� ������� ������������� ����� ������ �
        FPGA_RG4_RectB,             // ������� ���� ������� ������������� ����� ������ B
        FPGA_RG5_PeriodImpulseA,    // ������� ���� ������� ������������� ��������� ������ �
        FPGA_RG6_DurationImpulseA,  // ������� ���� ������������ ������������ ��������� ������ �
        FPGA_RG7_PeriodImpulseB,    // ������� ���� ������� ������������� ��������� ������ B
        FPGA_RG8_DurationImpulseB,  // ������� ���� ������������ ������������ ��������� ������ B
        FPGA_RG9_FreqMeter,         // ������� ���������� �����������
        FPGA_RG10_Offset,           // ������� ��������
        FreqMeter_Resist,
        FreqMeter_Couple,
        FreqMeter_Filtr,
        Count
    } value;
    explicit Register(E v) : value(v) {};
    explicit Register(uint8 v) : value((E)v) {};
    cstr Name() const;
    operator E() { return value; }
};


#define LENGTH_SPI_BUFFER   30

#define SPI_SLAVE_SYNBYTE   0x53

#define SPI_MASTER_SYNBYTE  0xAC

#define NAME_FORM(form, lang)  Form(form).Name(lang)
#define FORM_RU(form) NAME_FORM(form, 0)
#define FORM_EN(form) NAME_FORM(form, 1)
