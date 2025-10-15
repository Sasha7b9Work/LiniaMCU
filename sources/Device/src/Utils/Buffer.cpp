// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Utils/Buffer.h"
#include <cstdlib>
#include <cstring>


Buffer::Buffer(int new_capacity) : buffer(nullptr), size(0)
{
    Allocate(new_capacity);
}


Buffer::~Buffer()
{
    Free();
}


void Buffer::Free()
{
    std::free(buffer);
    size = 0;
    capacity = 0;
}


void Buffer::Allocate(int new_capacity)
{
    uint8 *temp = nullptr;

    if (size)
    {
        temp = (uint8 *)std::malloc((uint)capacity);
        std::memcpy(temp, buffer, (uint)capacity);
    }

    std::free(buffer);

    buffer = (uint8 *)std::malloc((uint)new_capacity);
    std::memset(buffer, 0, (uint)new_capacity);
    std::memcpy(buffer, temp, (uint)capacity);
    capacity = new_capacity;

    if (temp)
    {
        std::free(temp);
    }
}


void Buffer::Append(uint8 byte)
{
    if (IsFull())
    {
        Allocate(capacity + 1024);
    }

    buffer[size++] = byte;
}


bool Buffer::IsFull() const
{
    return (size == capacity);
}
