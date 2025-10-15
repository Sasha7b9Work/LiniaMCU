// 2025/10/15 14:53:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Utils/StringUtils.h"
#include <cstring>


bool SU::BeginWith(pchar str, pchar begin)
{
    uint length_begin = std::strlen(begin);

    if (std::strlen(str) < std::strlen(begin))
    {
        return false;
    }

    return std::memcmp((void *)str, begin, length_begin) == 0;
}
