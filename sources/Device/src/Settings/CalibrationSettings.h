// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "common/Command.h"
#include "common/CommonTypes.h"
#include "Generator/Calibrator.h"


#ifndef WIN32
#pragma anon_unions
#endif


struct CalibrationSettings
{
#define NUM_CHAN       2

#define NUM_SIGNALS    2

#define NUM_RANGES     5

#define NUM_PARAMETERS 4
    /*
    * 0 : ������
    * 1 : +5�
    * 2 : 0�
    * 3 : -5�
    */

    union //-V2514
    {
        struct
        {
            int16 cal_a_imp[NUM_CHAN];                                      // ���������� ��� ���������

            int16 cal[NUM_CHAN][NUM_SIGNALS][NUM_RANGES][NUM_PARAMETERS];

            int16 kFreqMeterTrig;       // ������������� ����������� ������ ������������� �����������
        };

        uint8 unused[256];
    };
    
    CalibrationSettings& operator =(const CalibrationSettings &);

    static int16 *GetK(uint8 channel, CalSignal::E, uint8 range, uint8 parameter);

    static int16 *GetFreqMeterK();
};


extern CalibrationSettings setCal;
