// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Memory
{
    void Init();

    // �������� ������� ������ �������� size ���� � ��������� ��������� �� ����
    void *Allocate(uint size);

    // ����������� ����� ���������� ������� ������
    void Free(void *address);
};
