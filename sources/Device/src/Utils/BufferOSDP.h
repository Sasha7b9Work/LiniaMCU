// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
    ����� ����������� ������������ ��� ��������������� ���������/������������ ������ �� ����
*/

class BufferOSDP
{
public:
    BufferOSDP(int capacity);
    ~BufferOSDP();
    void Append(uint8);
    bool IsFull() const;
    bool IsEmpty() const;
    void RemoveFirst(int);          // ������� ��������� ���������� ���� �� ������ ������
    const uint8 &operator[](int) const;
private:
    uint8 *buffer;
    int capacity;      // ������� ���� ����� ��������� � ������
    int size;           // ������� ���� �������� � ������
    void Allocate(int new_capacity);
    void Free();
};
