// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "defines.h"
#include "CommonTypes.h"


struct TypeForm
{
    enum E
    {
        Sine,           // �����
        RampPlus,       // ����+
        RampMinus,      // ����-
        Triangle,       // �����������
        Meander,        // ������
        Impulse,        // ��������
        Packet,         // ����� ���������
        Free,           // ������������ ������
        Count
    };

    static void Set(const Chan &, E);

    static E Current(const Chan &);

private:

    static E current[2];
};


namespace Order
{
    enum E
    {
        Mega,
        Kilo,
        One,
        Milli,
        Micro,
        Nano,
        Count
    };

    cstr Suffix(Order::E order);

    // ���������� �������, �������������� �������
    int GetPow10(Order::E order);

    // ��������� order �� ���������� ������
    void Store(Order::E order);

    // ������������ ��������, ����� ���������� �������� Store()
    Order::E Restore();
};


struct Value
{
    explicit Value(double v);
    explicit Value(int v);

    // ���� �������� �� ���������� �������������. ��� ���� ������ �������� ����� ���� ���� ("+" ��� "-"), ������� ����� ���������� �� ����� ������ ("."),
    // � order ��������, �� ������� ����� ��������� �������� ����� (3 - �������� �� 1000, -3 - ��������� �� 1000)
    explicit Value(pchar const buffer, Order::E order);

    void FromUnits(int units, uint mUnits = 0, uint uUnits = 0, uint nUnits = 0, int sign = 1);
    void FromDouble(double v);
    void FromUINT64(uint64 v) { value = v; }
    void FromINT(int v);
    void FromString(pchar  const buffer, int pow10);
    bool FromString(pchar buffer, char **end, int numDigitsAfterComma);

    double ToDouble() const;
    uint64 ToAbsNS() const;
    uint64 GetRawValue() const { return value; }

    void Div(uint div);
    void Mul(uint mul);
    void Add(Value value);
    void Sub(Value value);

    // ���������� ������� ����� ����� � value �� �� ������ ����������� ��������
    Value &TestSub(Value value);

    // �������� �� 10 � ������� pow
    void MulPow10(int pow);

    void SetSign(int sign);

    // ���������� ����
    int Sign() const;

    // ���������� ����� �����
    int Integer() const;
      
    // ���������� ���������� ���������� � ������� �����
    int FractNano() const;

    uint64 AbsRawValue() const;

    bool IsZero() const;

    // ����������:
    // Order::Mega  - Value::Integer() >= 1e6
    // Order::Kilo  - Value::Integer() >= 1e3
    // Order::One   - Value::Integer() >= 0
    // Order::Milli - Value::Integer() >= 1e-3
    // Order::Micro - Value::Integer() >= 1e-6
    Order::E GetOrder() const;

    // ��������� ������ ��������
    cstr ToString(bool sign, Order::E order = Order::Count) const;

    // ���������� ������ � ������� position. ���� �� �����������. ����� ��������� �������������� order. One - ����� ������, Kilo - ����� ����� � ��� �����.
    // Order::Count - ��������� �� ��������� - ������� � ������� ������������ ����������� ��������� ��������
    char GetChar(int postition, Order::E order) const;

    int GetPositionFirstDigit(Order::E order) const;

    // ���������� ����� � ������� position. ����� ��������� �������������� order. One - ����� ������, Kilo - ����� ����� � ��� �����.
    // Order::Count - ��������� �� ��������� - ������� � ������� ������������ ����������� ��������� ��������
    int GetDigit(int position, Order::E order = Order::Count) const;

    bool operator<(const Value &) const;
    bool operator>(const Value &) const;
    bool operator<=(const Value &) const;
    bool operator>=(const Value &) const;
    bool operator==(const Value &) const;
    bool operator!=(const Value &) const;

private:

    uint64 value;       // �������� ��������� � �������� ��������� "����". ������������� � "1" ������� ��� ��������, ��� ����� �������������
};
