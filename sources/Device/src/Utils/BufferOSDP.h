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
    void Append(char);
    bool IsFull() const;
    bool IsEmpty() const;
    void RemoveFirst(int);          // ������� ��������� ���������� ���� �� ������ ������
    const char &operator[](int) const;
    // ���������� ������ ������� �������
    int FirstPosition(char);
    pchar Data(int pos) const;
private:
    char *buffer;
    int capacity;      // ������� ���� ����� ��������� � ������
    int size;           // ������� ���� �������� � ������
    void Allocate(int new_capacity);
    void Free();
};
