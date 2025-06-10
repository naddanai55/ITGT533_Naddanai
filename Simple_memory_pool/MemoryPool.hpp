#pragma once

#include <iostream>

using namespace std;

class MemoryPool 
{
public:
    MemoryPool(size_t blockSize, size_t numBlocks);
    ~MemoryPool();

    void* allocate(size_t requestedSize);
    void deallocate(void* ptr);

    void displayStatus() const;
    size_t getFreeBlockCount() const;
    size_t getTotalBlockCount() const; 
    size_t getBlockSize() const;       

private:
    size_t m_blockSize;       
    size_t m_numBlocks;       
    size_t m_freeBlocksCount; 

    char* m_memoryBlock;      
    char* m_nextFreeBlock;    
};