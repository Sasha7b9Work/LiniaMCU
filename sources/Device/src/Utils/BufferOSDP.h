// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
    Класс единственно предназначен для автоматического выделения/освобождения памяти из кучи
*/

class BufferOSDP
{
public:
    BufferOSDP(int capacity);
    ~BufferOSDP();
    void Append(uint8);
    bool IsFull() const;
    bool IsEmpty() const;
    void RemoveFirst(int);          // Удалить некоторое количество байт из начала буфера
    const uint8 &operator[](int) const;
private:
    uint8 *buffer;
    int capacity;      // Столько байт может храниться в буфере
    int size;           // Столько байт хранится в буфере
    void Allocate(int new_capacity);
    void Free();
};
