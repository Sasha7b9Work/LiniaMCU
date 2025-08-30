// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
    ����� ����������� ������������ ��� ��������������� ���������/������������ ������ �� ����
*/

class Buffer
{
public:
    Buffer(uint size);
    ~Buffer();
    bool ReSize(uint size);
    uint8 *Data();
    float *DataFloat();
    uint   Size() const;
private:
    void Allocate(uint size);
    void Free();
    void *buffer;
    uint size;
};
