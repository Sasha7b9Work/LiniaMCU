// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Generator/FPGA/FPGA.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Settings/CalibrationSettings.h"
#include <stm32f4xx_hal.h>


#define SECTOR_0                    ((uint)0x08000000)          // 16k  ���������
#define SECTOR_1                    ((uint)0x08004000)          // 16k
#define SECTOR_2                    ((uint)0x08008000)          // 16k
#define SECTOR_3                    ((uint)0x0800c000)          // 16k
#define SECTOR_CALIBRATION_4        ((uint)0x08010000)          // 64k  SettingsCalibration
#define SIZE_SECTOR_CALIBRATION     (64 * 1024)
#define SECTOR_5                    ((uint)0x08020000)          // 128k �������� �������� 1
#define SECTOR_6                    ((uint)0x08040000)          // 128k �������� �������� 2
#define SECTOR_7                    ((uint)0x08060000)          // 128k �������� �������� 3
#define SECTOR_8                    ((uint)0x08080000)          // 128k
#define SECTOR_9                    ((uint)0x080a0000)          // 128k
#define SECTOR_TEMP_10              ((uint)0x080c0000)          // 128k ����������� ��� ������������� ������� � ������ � ��� ���������� � DLoader
#define SIZE_SECTOR_TEMP            (128 * 1024)
#define SECTOR_SIGNAL_FPGA_11       ((uint)0x080e0000)          // ������ � ������ ����� �������
#define SIZE_SECTOR_SIGNAL_FPGA     (128 * 1024)

#define CLEAR_FLASH_FLAGS \
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP    |  /* end of operation flag              */   \
                           FLASH_FLAG_OPERR  |  /* operation error flag               */   \
                           FLASH_FLAG_WRPERR |  /* write protected error flag         */   \
                           FLASH_FLAG_PGAERR |  /* programming alignment error flag   */   \
                           FLASH_FLAG_PGPERR |  /* programming parallelism error flag */   \
                           FLASH_FLAG_PGSERR);  /* programming sequence error flag    */


// ������� ������ � ��������� ������� startAddress
static void EraseSector(uint startAddress);
// ���������� size ���� �� ������� data �� ������ address
static void WriteData(uint dest, void *src, uint size);
// ���������� ��������� ������������� ������� � ��������� ������� address. ����� �������� ����, ���������� -1
static uint GetSector(uint address);


namespace HAL_EEPROM
{
    namespace Signal
    {
        // ���������� ����� EEPROM, ���� ���� ��������� ������ ����� ������
        static uint AddressForData(const Chan &);
    }
}


static void EraseSector(uint startAddress)
{
    if (GetSector(startAddress) == (uint)(-1))
    {
        return;
    }

    CLEAR_FLASH_FLAGS;

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef isFLASH;
    isFLASH.TypeErase = TYPEERASE_SECTORS;
    isFLASH.Sector = GetSector(startAddress);
    isFLASH.NbSectors = 1;
    isFLASH.VoltageRange = VOLTAGE_RANGE_3;

    uint error = 0;

    HAL_FLASHEx_Erase(&isFLASH, &error);

    HAL_FLASH_Lock();
}


static uint GetSector(uint address)
{
    struct StructSector
    {
        uint number;
        uint startAddress;
    };

    static const StructSector sectors[] =
    {
        {FLASH_SECTOR_4,  SECTOR_CALIBRATION_4},
        {FLASH_SECTOR_10, SECTOR_TEMP_10},
        {FLASH_SECTOR_11, SECTOR_SIGNAL_FPGA_11},
        {}
    };

    int i = 0;
    while (sectors[i].startAddress)
    {
        if (sectors[i].startAddress == address)
        {
            return sectors[i].number;
        }
        i++;
    }

    return (uint)(-1);
}


static void WriteData(uint dest, void *src, uint size)
{
    CLEAR_FLASH_FLAGS;

    HAL_FLASH_Unlock();

    for (uint i = 0; i < size; i++)
    {
        HAL_FLASH_Program(TYPEPROGRAM_BYTE, dest++, ((uint8 *)src)[i]);
    }

    HAL_FLASH_Lock();
}


void HAL_EEPROM::Signal::Save(const Chan &ch, uint16 data[DGenerator::DDS_NUM_POINTS])
{
    uint sizeData = FPGA::NUM_POINTS * sizeof(data[0]);

    EraseSector(SECTOR_TEMP_10);                                                        // �������� ������ ��� ��������� ������ ��� ���������� ���������� ��� ������, ������� �� ����� ��������������
    WriteData(SECTOR_TEMP_10, (void *)SECTOR_SIGNAL_FPGA_11, sizeData * Chan::Count);   // ��������� ������������ ������ //-V566
    EraseSector(SECTOR_SIGNAL_FPGA_11);                                                 // ������� ������ ��� �������� ������
    WriteData(AddressForData(ch), data, sizeData);                                      // ���������� ������ ������

    Chan chan = ch.IsA() ? ChB : ChA;

    data = (uint16 *)SECTOR_TEMP_10; //-V566

    if (chan.IsB())
    {
        data += FPGA::NUM_POINTS;                                                        // ��������� ��������� �� ������ ������, ������� �� ��������� ��������������
    }

    WriteData(AddressForData(chan), data, sizeData);                                      // � ��������� ��
}


uint HAL_EEPROM::Signal::AddressForData(const Chan &ch)
{
    uint result = SECTOR_SIGNAL_FPGA_11;

    if (ch.IsB())
    {
        result += FPGA::NUM_POINTS * sizeof(uint16);
    }

    return result;
}


uint16 *HAL_EEPROM::Signal::Get(const Chan &ch)
{
    uint16 *result = (uint16 *)(SECTOR_SIGNAL_FPGA_11); //-V566

    if (ch.IsB())
    {
        result += FPGA::NUM_POINTS;
    }

    return result;
}


void HAL_EEPROM::Init()
{
    uint *data = (uint *)SECTOR_SIGNAL_FPGA_11; //-V566

    for (int i = 0; i < (FPGA::NUM_POINTS * Chan::Count); i++)
    {
        if (data[i] != (uint)(-1))
        {
            return;
        }
    }

    EraseSector(SECTOR_SIGNAL_FPGA_11);

    float *address = (float *)SECTOR_SIGNAL_FPGA_11; //-V566

    float value = 0.0F;

    for (int i = 0; i < (FPGA::NUM_POINTS * Chan::Count); i++)
    {
        WriteData((uint)address, &value, 4);
    }
}
