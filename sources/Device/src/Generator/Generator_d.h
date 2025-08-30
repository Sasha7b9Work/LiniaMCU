// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Generator/AD9952.h"
#include "Generator/AD5697.h"
#include "Generator/FPGA/FPGA.h"
#include "common/Command.h"


namespace DGenerator
{
    static const int DDS_NUM_POINTS = 8 * 1024;

    void Init();

    void EnableChannel(const Chan &, bool enable);

    void SingleStart();

    // ������ �������� ����� ��� ���������� - � ������ ���������� ����� ����� ����������� ��������� �������� �������
    void SetFormWave(const Chan &, TypeForm::E form, bool tuneFiltr);

    void SetOffset(const Chan &, const Value &offset);

    void SetFrequency(const Chan &, const Value &frequency);

    void SetAmplitude(const Chan &, const Value &amplitude);

    void SetDuration(const Chan &, const Value &duration);

    void SetPhase(const Chan &, const Value &phase);

    void SetDelayStartStop(const Chan &, const Value &delay);

    void SetManipulationDuration(const Chan &, const Value &duration);

    void SetManipulationPeriod(const Chan &, const Value &period);

    void SetPacketPeriod(const Chan &, const Value &duration);

    void SetPacketNumber(const Chan &, const Value &number);

    void SetPeriod(const Chan &, const Value &period);
};


struct Attenuation
{
    enum E
    {
        _0Db,
        _10Db,
        _20Db,
        _30Db,
        Count
    } value;

    explicit Attenuation(Attenuation::E v) : value(v) { }
    float Units() const;
    cstr Name() const;
};


namespace Amplifier
{
    void Init();
    
    // ��������� ��������� � ������������ � �������� �����������
    void Tune(const Chan &);

    void Tune(const Chan &, int range);
    
    // ���������� ����������� �������� � ����� ����� ������, ������� ���������� � ���������. ��������� ��� �������� 10 ���, �� ������ 10 �� ����� ��������� �� 3.16
    double GetAmplification(const Chan &);

    // ���������� �������� ��������� � �������������
    void TuneAndLock(const Chan &, bool enabled, Attenuation::E attenuation);

    void Lock();

    // ��������������
    void Unlock();
   
    // ���������� true, ���� �� ������ ������ ������� ���������
    bool IsEnabled(const Chan &);

    // ��������/��������� ���������� ��������� ���������
    void Enable(const Chan &, bool enable);
};


namespace SettingsGenerator
{
    // ������� ������� �� ������
    extern Value frequency[Chan::Count];

    // ������� ������������� ��������� �� ������
    extern Value amplitude[Chan::Count];

    // ������� ������������� �������� �� ������
    extern Value offset[Chan::Count];

    // ���������� ������������� �� ������ ���������. ��������� ������������ ��� ����� ����������
    inline double Amplitude(const Chan &ch) { return amplitude[ch].ToDouble(); }

    inline Value AmplitudeValue(const Chan &ch) { return amplitude[ch]; }

    // ���������� ������������� �� ������ ��������
    inline double Offset(const Chan &ch) { return offset[ch].ToDouble(); }

    inline Value OffsetValue(const Chan &ch) { return offset[ch]; }

    // ���������� ������������� ������� �� ������
    inline double Frequency(const Chan &ch) { return frequency[ch].ToDouble(); }
};
