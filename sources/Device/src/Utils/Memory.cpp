// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Memory.h"
#include <cstring>


/*
    ������������� ������ ���������� � ������� ����� ����.
    ���������� � ���������� ������ �������� � ������� �������� Block, ������� ����������� �� ����� � ������ ����. �������� ����������� ����� �������, ��� ������, �� ������� ��� ���������, 
    ������������� �� ����� ���� � ������, �.�. (���������� ������ �� ������ ��������)

    lastBlock - 4, lastBlock - 3, lastBlock - 2, lastBlock - 1
    address      > address       > address      > begin
*/


// ��������� ���������� ���� ������.
struct Block
{
    uint8 *address;   // ����� ����������� ����� ������
    uint size;      // ������ ����������� ����� ������
    Block *Next() { return 0; };
};


#define SIZE_POOL (1 * 1024)
static uint8 pool[SIZE_POOL];
//static uint8 *begin = pool;
static Block *firstBlock = ((Block *)&pool[SIZE_POOL]) - 1;
//static Block *lastBlock = nullptr;



// ����� ��������� ������� ������. ���� ������ ��� - ���������� ����.
static uint8 *FindRegion(uint size);
// ���������� ��������� �� ����, ���������� �� ����� address
//static Block *FindBlockWithAddress(const uint8 *address);
// �������� ��������� Block � ������
static void InsertBlock(Block *block);
// ���������� ����� ������� (�� ������) ����������� ����� ������
static Block *FirstBlock();
// ���������� ����� ���������� (�� ������) ����������� ����� ������. LastBlokc() < FirstBlock()
//static Block *LastBlock();



void Memory::Init()
{
    std::memset(pool, 0, SIZE_POOL);
}


void *Memory::Allocate(uint size)
{
    uint8 *mem = FindRegion(size);

    if (mem)
    {
        Block block = { mem, size };
        InsertBlock(&block);
    }

    return (void *)mem;
}


static void InsertBlock(Block * /*block*/)
{
    //Block *first = FirstBlock();
    //Block *last = LastBlock();
}



void Memory::Free(void * /*address*/)
{

}


static uint8 *FindRegion(uint /*size*/)
{
    Block *block = FirstBlock();

    while (block->address != 0)
    {
        block = block->Next();
    }
    
    return 0;
}


/*
static Block *FindBlockWithAddress(const uint8 *address)
{
    Block *block = lastBlock;
    while (block->address != 0)
    {
        if (block->address == address)
        {
            return block;
        }
    }

    return 0;
}
*/


static Block *FirstBlock()
{
    if (firstBlock->address == 0)
    {
        return nullptr;
    }

    return firstBlock;
}


/*
static Block *LastBlock()
{
    if (!FirstBlock())
    {
        return nullptr;
    }

    Block *block = FirstBlock();

    do
    {
        block--;														// -V769
    } while (block->address != 0);

    return block + 1;
}
*/
