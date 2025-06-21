#include "MemoryPool.hpp"
#include <iostream> 
#include <cassert>

using namespace std;

MemoryPool::MemoryPool(size_t blockSize, size_t numBlocks) : m_blockSize(blockSize), m_numBlocks(numBlocks), m_freeBlocksCount(numBlocks), m_nextFreeBlock(nullptr)
{
    assert(blockSize > 0 && "Block size must  > 0");
    assert(numBlocks > 0 && "Number of blocks must > 0");
    assert(blockSize >= sizeof(char*) && "Block size too small");

    m_memoryBlock = new char[m_blockSize * m_numBlocks];
    m_nextFreeBlock = m_memoryBlock;
    char* currentBlock = m_memoryBlock;
    for (size_t i = 0; i < m_numBlocks - 1; i++) 
    {
        *(reinterpret_cast<char**>(currentBlock)) = currentBlock + m_blockSize;
        currentBlock += m_blockSize;
    }
    *(reinterpret_cast<char**>(currentBlock)) = nullptr;
   
}

MemoryPool::~MemoryPool() 
{
    delete[] m_memoryBlock;
}

void* MemoryPool::allocate(size_t requestedSize) 
{
    assert(requestedSize > 0 && "Cannot allocate 0 byte");
    assert(requestedSize <= m_blockSize && "Requested size exceeds block size");
    assert(m_freeBlocksCount > 0 && "Memory pool is full");
    assert(m_nextFreeBlock != nullptr && "Memory pool is full");

    char* blockToAllocate = m_nextFreeBlock;
    m_nextFreeBlock = *(reinterpret_cast<char**>(blockToAllocate));
    m_freeBlocksCount--;
    return static_cast<void*>(blockToAllocate);
}

void MemoryPool::deallocate(void* ptr) 
{
    if (ptr == nullptr)
    {
        return;
    }
    char* charPtr = static_cast<char*>(ptr);

    assert(charPtr >= m_memoryBlock && "Pointer is out of pool bounds (too low).");
    assert(charPtr < (m_memoryBlock + (m_numBlocks * m_blockSize)) && "Pointer is out of pool bounds (too high).");
    assert(((charPtr - m_memoryBlock) % m_blockSize == 0) && "Pointer is not aligned to a block boundary.");
    assert(m_freeBlocksCount < m_numBlocks && "Attempting to deallocate to an already full pool (or count mismatch).");

    *(reinterpret_cast<char**>(ptr)) = m_nextFreeBlock;
    m_nextFreeBlock = charPtr;
    m_freeBlocksCount++;
}

void MemoryPool::displayStatus() const 
{
    cout << "--- Memory Pool Status ---" << endl;
    cout << "Block Size:         " << m_blockSize << " bytes" << endl;
    cout << "Total Blocks:       " << m_numBlocks << endl;
    cout << "Free Blocks:        " << m_freeBlocksCount << endl;
    cout << "Used Blocks:        " << (m_numBlocks - m_freeBlocksCount) << endl;
    cout << "Memory Pool Start:  " << static_cast<void*>(m_memoryBlock) << endl;
    cout << "Next Free Block:    " << static_cast<void*>(m_nextFreeBlock) << endl;
    cout << "--------------------------" << endl;
}

size_t MemoryPool::getFreeBlockCount() const 
{
    return m_freeBlocksCount;
}

size_t MemoryPool::getTotalBlockCount() const 
{
    return m_numBlocks;
}

size_t MemoryPool::getBlockSize() const 
{
    return m_blockSize;
}
