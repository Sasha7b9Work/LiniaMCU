// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "common/Common.h"
#include "Common/CommonTypes.h"
#ifdef PANEL
#include "Display/Text.h"
#include "Settings/Settings.h"
#endif
#include "Utils/Math.h"
#include <cmath>


Chan ChA(Chan::A);
Chan ChB(Chan::B);


TypeForm::E TypeForm::current[2] = { TypeForm::Sine, TypeForm::Sine };


// ������� ����, ���� ������ ������� buffer - ����. � pos ������������ ������� �������� �� ������ � ���� ������
static void ProcessSign(pchar const buffer, int *pos, int *sign);

// ������� ������ �� ��������� ��������� ����� ����� �����
static int FindIntegerPart(pchar const buffer, int start);

// ������� ����� ����� �� ������ ��������
static uint AssembleInteger(pchar const buffer, int start, int end);

// ������� ����� �� ���� ��� ����� ��������. � end ������������ ������� ���������� �������
static uint AssembleTriple(pchar const buffer, int start, int *end);

// ����� ��� ���������� ���������� �������� �������
static Order::E stored = Order::Count;

// ������ ���� ����� �� buffer. ���������� ��������� �� ������ ������� ����� �����
static bool GetSign(int &sign, char *begin, char **end);

// ���������� �������� �� ������� (������� e)
static bool GetIntPart(Value &value, char *begin, char **end, int numDigitsAfterComma);

// ���������� ������� (��, ��� ����� ������� e)
static bool GetPower(int &power, char *begin, char **end);


Value::Value(pchar const buffer, Order::E order) //-V730
{
    FromString(buffer, Order::GetPow10(order));
}


Value::Value(double v)
{
    FromDouble(v);
}


Value::Value(int v)
{
    FromINT(v);
}


bool Value::FromString(pchar buffer, char **end, int numDigitsAfterComma)
{
    char *begin = (char *)buffer;

    int sign = 0;

    if (!GetSign(sign, begin, end))
    {
        return false;
    }

    begin = *end;

    if (!GetIntPart(*this, begin, end, numDigitsAfterComma))
    {
        return false;
    }

    begin = *end;

    int pow = 0;
    
    if (!GetPower(pow, begin, end))
    {
        return false;
    }

    MulPow10(pow);

    SetSign(sign);

    return true;
}


static bool GetSign(int &sign, char *begin, char **end)
{
    if (*begin == '-')
    {
        *end = begin + 1;
        sign = -1;
        return true;
    }
    else if (*begin == '+')
    {
        *end = begin + 1;
        sign = 1;
        return true;
    }

    if (*begin >= '0' && *begin <= '9')
    {
        *end = begin;
        sign = 1;
        return true;
    }

    *end = begin;
    return false;
}


#ifdef PANEL
static bool GetIntPart(Value &value, char *begin, char **end, int numDigitsAfterComma)
{
    *end = begin;

    if (*begin < '0' || *begin > '9')
    {
        return false;
    }

    String buffer;

    bool comma = false;         // true ����� ��������, ��� ����� ��� ����

    while ((**end >= '0' && **end <= '9') || **end == '.' || **end == ',')
    {
        if (**end == '.' || **end == ',')
        {
            comma = true;
        }
        else if(comma)
        {
            numDigitsAfterComma--;
        }

        if (numDigitsAfterComma >= 0)
        {
            buffer.Append(**end);
        }
        
        *end = *end + 1;
    }

    value = Value(buffer.c_str(), Order::One);

    return true;
}
#else
static bool GetIntPart(Value &, char *, char **, int)
{
    return true;
}
#endif


#ifdef PANEL
static bool GetPower(int &pow, char *begin, char **end)
{
    if (*begin != 'e' && *begin != 'E')
    {
        *end = begin;
        pow = 0;
        return true; 
    }

    begin++;

    if ((*begin < '0' || *begin > '9') && (*begin != '-' && *begin != '+'))
    {
        *end = begin;
        pow = 0;
        return true;
    }

    String buffer;

    while ((*begin >= '0' && *begin <= '9') || *begin == '-' || *begin == '+')
    {
        buffer.Append(*begin);
        begin++;
    }

    *end = begin;

    pow = Value(buffer.c_str(), Order::One).Integer();

    return true;
}
#else
static bool GetPower(int &, char *, char **)
{
    return true;
}
#endif


void Value::FromString(pchar const buffer, int pow10)
{
    int pos = 0;                                    // ������� �������������� ������� � buffer
    int sign = 1;                                   // ������������� �������� �������� ������������� ����

    ProcessSign(buffer, &pos, &sign);               // ������������ ���������� � �����

    int units = 0;
    uint mUnits = 0;
    uint uUnits = 0;
    uint nUnits = 0;

    int end = FindIntegerPart(buffer, pos);         // ������� ��������� ����� �����

    units = (int)AssembleInteger(buffer, pos, end);    // ������� ����� �����

    if (buffer[end] == '.' || buffer[end] == ',')
    {
        mUnits = AssembleTriple(buffer, end + 1, &end);
        uUnits = AssembleTriple(buffer, end, &end);
        nUnits = AssembleTriple(buffer, end, &end);
    }

    FromUnits(units, mUnits, uUnits, nUnits, sign);

    if (pow10 > 0)
    {
        uint pow = Math::Pow10(pow10);
        Mul(pow);
    }
    else if (pow10 < 0)
    {
        uint pow = Math::Pow10(-pow10);
        Div(pow);
    }
}


void Value::FromUnits(int units, uint mUnits, uint uUnits, uint nUnits, int sign)
{
    value = (uint)units;
    value *= 1000 * 1000 * 1000;

    value += (uint)(nUnits + uUnits * 1000 + mUnits * 1000 * 1000);

    if (sign < 0)
    {
        SetSign(sign);
    }
}


static void ProcessSign(pchar const buffer, int *pos, int *sign)
{
    if (buffer[0] == '+')
    {
        *sign = 1;
        *pos = *pos + 1;
    }
    else if (buffer[0] == '-')
    {
        *sign = -1;
        *pos = *pos + 1;
    }
}


static int FindIntegerPart(pchar const buffer, int start)
{
    int pos = start;

    while (buffer[pos] >= '0' && buffer[pos] <= '9')
    {
        pos++;
    }

    return pos;
}


static uint AssembleInteger(pchar const buffer, int start, int end)
{
    char stack[20];

    int posStack = 0;

    for (int i = start; i < end; i++)
    {
        stack[posStack++] = buffer[i];
    }

    uint result = 0;

    uint pow = 1;

    while (posStack > 0)
    {
        char value = stack[(posStack--) - 1];

        result += (value & 0x0F) * pow;

        pow *= 10;
    }

    return result;
}


static uint AssembleTriple(pchar const buffer, int start, int *end)
{
    char stack[3];
    int posStack = 0;

    uint result = 0;

    int i = start;

    while ((buffer[i] >= '0' && buffer[i] <= '9') &&
           (posStack < 3))
    {
        stack[posStack] = buffer[i];
        posStack++;
        i++;
    }

    while (posStack < 3)                    // �������� �� 3 ��������
    {
        stack[posStack++] = '0';
    }

    *end = i;

    uint pow = 1;

    while (posStack > 0)
    {
        char value = stack[(posStack--) - 1];

        result += (value & 0x0F) * pow;

        pow *= 10;
    }

    return result;
}


void Value::FromDouble(double v)
{
    int sign = (v < 0.0) ? -1 : 1;

    value = (uint64)(std::fabs(v) * 1.E9);

    if (sign < 0)
    {
        SetSign(-1);
    }
}


void Value::FromINT(int v)
{
    FromUnits(v < 0 ? -v : v, 0, 0, 0, v < 0 ? -1 : 1);
}


double Value::ToDouble() const
{
    return (double)(AbsRawValue()) / 1E9 * (double)Sign();
}


uint64 Value::ToAbsNS() const
{
    return AbsRawValue();
}


int Value::Sign() const
{
    //                fedcba9876543210
    return (value & 0x8000000000000000U) ? -1 : 1;
}


uint64 Value::AbsRawValue() const
{   //                fedcba9876543210
    return (value & 0x7fffffffffffffff);
}


bool Value::IsZero() const
{
    return AbsRawValue() == 0;
}


void Value::Div(uint div)
{
    int sign = Sign();

    SetSign(1);

    value /= div;

    SetSign(sign);
}


void Value::Mul(uint mul)
{
    int sign = Sign();

    SetSign(1);

    value *= mul;

    SetSign(sign);
}


void Value::SetSign(int sign)
{
    if (sign >= 0)
    {
        //         fedcba9876543210
        value &= 0x7FFFFFFFFFFFFFFFU;       // \todo ��� ��� ����� ��������?
    }
    else
    {
        //         fedcba9876543210
        value |= 0x8000000000000000U;           // ������������� ������� �������������� �����
    }
}


int Value::Integer() const
{
    uint64 val = AbsRawValue();

    return (int)(val / (1000 * 1000 * 1000)) * Sign();
}


int Value::FractNano() const
{
    Value val = *this;
    val.SetSign(1);

    int whole = val.Integer();

    return (int)(val.value - (int)(whole * 1000 * 1000 * 1000));
}


void Value::Add(Value add)
{
    int sign = Sign();
    int signAdd = add.Sign();

    SetSign(1);
    add.SetSign(1);

    if(sign > 0 && signAdd > 0)
    {
        value += add.value;
    }
    else if(sign < 0 && signAdd < 0)
    {
        value += add.value;
        SetSign(-1);
    }
    else if(sign > 0 && signAdd < 0)
    {
        if(value >= add.value)
        {
            value -= add.value;
        }
        else
        {
            value = add.value - value;
            SetSign(-1);
        }
    }
    else
    {
        if(add.value >= value)
        {
            value = add.value - value;
        }
        else
        {
            value -= add.value;
            SetSign(-1);
        }
    }
}


void Value::Sub(Value val)
{
    val.SetSign(-val.Sign());

    Add(val);
}


Value &Value::TestSub(Value val)
{
    static Value test(0);

    test = *this;

    test.Sub(val);

    return test;
}


void Value::MulPow10(int pow)
{
    while (pow > 0)
    {
        Mul(10);
        pow--;
    }

    while (pow < 0)
    {
        Div(10);
        pow++;
    }
}


bool Value::operator<(const Value &rhs) const
{
    return ToDouble() < rhs.ToDouble();
}


bool Value::operator<=(const Value &rhs) const
{
    return ToDouble() <= rhs.ToDouble();
}


bool Value::operator>(const Value &rhs) const
{
    return ToDouble() > rhs.ToDouble();
}


bool Value::operator>=(const Value &rhs) const
{
    return ToDouble() >= rhs.ToDouble();
}


bool Value::operator==(const Value &rhs) const
{
    return (value == rhs.value);
}


bool Value::operator!=(const Value &rhs) const
{
    return (value != rhs.value);
}


Order::E Value::GetOrder() const
{
    Value temp = *this;
    temp.SetSign(1);

    int integer = temp.Integer();

    if      (integer >= 1000 * 1000) { return Order::Mega;  }
    else if (integer >= 1000)        { return Order::Kilo;  }
    else if (integer > 0)            { return Order::One;   }

    int fract = temp.FractNano();

    if      (fract >= 1000 * 1000)   { return Order::Milli; }
    else if (fract >= 1000)          { return Order::Micro; }
    else if (fract > 0)              { return Order::Nano;  }

    return Order::One;
}


void Order::Store(Order::E order)
{
    stored = order;
}


Order::E Order::Restore()
{
    return stored;
}


int Order::GetPow10(Order::E order)
{
    static const int pows[Count] =
    {
        6,  // Mega
        3,  // Kilo
        0,  // One
        -3, // Milli
        -6, // Micro
        -9  // Nano
    };

    return pows[order];
}


int Value::GetDigit(int position, Order::E order) const
{
    Value _value = *this;
    _value.SetSign(1);

    order = (order == Order::Count) ? _value.GetOrder() : order;

    position += Order::GetPow10(order);

    if (position < 0)
    {
        int divider = 100 * 1000 * 1000;       // �� ��� ����� ����� ������ ���������� ����������

        int fract = _value.FractNano();

        while (position < -1)
        {
            if (divider == 0)
            {
                return -1;
            }

            fract %= divider;
            divider /= 10;
            position++;
        }

        return (divider == 0) ? -1 : (fract / divider);
    }
    else
    {
        int whole = _value.Integer();

        while (position > 0)
        {
            whole /= 10;
            position--;
        }

        return (whole % 10);
    }
}


char Value::GetChar(int position, Order::E order) const
{
    int digit = GetDigit(position, order);

    return (digit == -1) ? '\0' : (char)(GetDigit(position, order) | 0x30);
}


int Value::GetPositionFirstDigit(Order::E order) const
{
    Value _value = *this;

    _value.SetSign(1);

    int result = 0;

    if (_value.Integer() > 0)
    {
        int whole = _value.Integer();

        while (whole > 9)
        {
            whole /= 10;
            result++;
        }
    }
    else
    {
        int fract = _value.FractNano();

        if (fract == 0)
        {
            return 0;
        }

        do
        {
            result--;
            fract *= 10;
        } while (fract < (100 * 1000 * 1000));
    }

    return result - Order::GetPow10(order == Order::Count ? _value.GetOrder() : order);
}


void TypeForm::Set(const Chan &ch, E form)
{
    current[ch] = form;
}


TypeForm::E TypeForm::Current(const Chan &ch)
{
    return current[ch];
}


#ifdef PANEL

bool Chan::Enabled() const
{
    return set.enabled[value];
}

#endif
