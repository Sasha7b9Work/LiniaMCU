// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
    ����� ����������� ������������ ��� ��������������� ���������/������������ ������ �� ����
*/

class Buffer
{
public:
    Buffer(int capacity);
    ~Buffer();
    void Append(uint8);
    bool IsFull() const;
private:
    uint8 *buffer;
    int capacity;      // ������� ���� ����� ��������� � ������
    int size;           // ������� ���� �������� � ������
    void Allocate(int new_capacity);
    void Free();
};
