// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"


int main()
{
    HAL::Init();
    HAL_TIM::Delay(500);             // �������� ����� ��� ����, ����� AD9952 ����� ������ ���������� �������������
  
    while (1)
    {
    }
}
