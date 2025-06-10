#include <cassert>
#include <iostream>
#include "MemoryPool.hpp"
#include <vector>

using namespace std;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    size_t blockSize = 32; 
    size_t numBlocks = 4;

    cout << "--- Simple Memory Pool ---" << endl;
    cout << "Create Pool with block size: " << blockSize << " and number of blocks: " << numBlocks << endl;
    MemoryPool pool(blockSize, numBlocks);
    vector<void*> allocated_blocks;
    pool.displayStatus();
    cout << "-------- Allocate --------" << endl;
    for (size_t i = 0; i < numBlocks - 1; i++) 
    {
        void* block = pool.allocate(sizeof(int));
        if (block) 
        {
            cout << "Allocated block " << (i + 1) << " at " << block << endl;
            allocated_blocks.push_back(block);
            int* my_int = static_cast<int*>(block);
            *my_int = 100 + i;
            cout << "-->Stored value: " << *my_int << endl;
            cout << "-->Free blocks now: " << pool.getFreeBlockCount() << endl;
        }
    }
    pool.displayStatus();
    cout << "------- Deallocate -------" << endl;
    if (!allocated_blocks.empty()) 
    {
        void* block_to_free = allocated_blocks.back();
        allocated_blocks.pop_back();
        cout << "Deallocating block at " << block_to_free << endl;
        pool.deallocate(block_to_free);
        cout << "  Free blocks now: " << pool.getFreeBlockCount() << endl;
        pool.displayStatus();
    }

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}