// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "FDrive_d.h"
#include "Generator/Generator_d.h"
#include "Hardware/HAL/HAL.h"
#include "usbh_diskio.h"


namespace DDrive
{
    struct State
    {
        enum E
        {
            Disconnected,   // ��������� �������� ����� ������
            NeedMount,      // ���������� ������������ ������, ��������� ������������
            Connected,      // ������ ������������ � ��������������
            NeedUnmount     // ��������� �������������
        } value;
    };

    static USBH_HandleTypeDef USB_host;

    void *DDrive::handle = &USB_host;

    static State::E state = State::Disconnected;

    // ����� �������� �������������� �������
    static Command command = Command::Count;

    static FATFS FatFS;

    static char USBDISKPath[4];

    // true, ���� ������ ����������
    volatile static bool isConnected = false;

    // � ��� ������� �������� ��� ������ ������� �� OTG FS
    static void USBH_UserProcess(USBH_HandleTypeDef *, uint8 id);
}




static void DDrive::USBH_UserProcess(USBH_HandleTypeDef *, uint8 id)
{
    switch(id)
    {
        case HOST_USER_SELECT_CONFIGURATION:
            //LOG_WRITE("HOST_USER_SELECT_CONFIGURATION");
            break;

        case HOST_USER_CLASS_ACTIVE:
            //LOG_WRITE("HOST_USER_CLASS_ACTIVE");
            state = State::NeedMount;
            break;

        case HOST_USER_CLASS_SELECTED:
            //LOG_WRITE("HOST_USER_CLASS_SELECTED");
            break;

        case HOST_USER_CONNECTION:
            //LOG_WRITE("HOST_USER_CONNECTION");
            break;

        case HOST_USER_DISCONNECTION:
            //LOG_WRITE("HOST_USER_DISCONNECTION");
            state = State::NeedUnmount;
            break;
    }
}


void DDrive::Init()
{
    HAL_HCD::Init();

    if (FATFS_LinkDriver(&USBH_Driver, USBDISKPath) == FR_OK) //-V2001
    {
        USBH_StatusTypeDef res = USBH_Init(&USB_host, USBH_UserProcess, 0);
        res = USBH_RegisterClass(&USB_host, USBH_MSC_CLASS);
        res = USBH_Start(&USB_host);
    }
}


void DDrive::Update()
{
    USBH_Process(&USB_host);

    if(state == State::NeedMount)
    {
        FRESULT result = f_mount(&FatFS, USBDISKPath, 0);

        Message::FDrive::Mount((result == FR_OK) ? (uint8)1 : (uint8)2).Transmit();

        state = State::Connected;

        if(result == FR_OK)
        {
//            LOG_WRITE("������ ��������������");
        }
        else
        {
//            LOG_WRITE("�� ������� �������������� ������");
        }
    }
    else if(state == State::NeedUnmount)
    {
        f_mount(0, "", 0);

        Message::FDrive::Mount(0).Transmit();

        state = State::Disconnected;

//        LOG_WRITE("������ �������������");
    }
}


/*
static bool GetNameDir(const char *fullPath, int numDir, char *nameDirOut, StructForReadDir *s)
{
    memcpy(s->nameDir, (void *)fullPath, strlen(fullPath));
    s->nameDir[strlen(fullPath)] = '\0';

    DIR *pDir = &s->dir;
    if (f_opendir(pDir, s->nameDir) == FR_OK)
    {
        int numDirs = 0;
        FILINFO *pFNO = &s->fno;
        bool alreadyNull = false;
        while (true)
        {
            if (f_readdir(pDir, pFNO) != FR_OK)
            {
                *nameDirOut = '\0';
                f_closedir(pDir);
                return false;
            }
            if (pFNO->fname[0] == 0)
            {
                if (alreadyNull)
                {
                    *nameDirOut = '\0';
                    f_closedir(pDir);
                    return false;
                }
                alreadyNull = true;
            }
            if (numDir == numDirs && (pFNO->fattrib & AM_DIR))
            {
                strcpy(nameDirOut, pFNO->fname);
                return true;
            }
            if ((pFNO->fattrib & AM_DIR) && (pFNO->fname[0] != '.'))
            {
                numDirs++;
            }
        }
    }
    return false;
}
*/
