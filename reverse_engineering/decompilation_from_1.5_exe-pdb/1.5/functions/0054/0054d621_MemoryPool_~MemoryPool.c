/*
 * Entry: 0054d621
 * Name: MemoryPool::~MemoryPool
 * Namespace: MemoryPool
 * Signature: void ~MemoryPool(MemoryPool * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MemoryPool::~MemoryPool(MemoryPool *this)

{
  void *pvVar1;
  
  pvVar1 = this->mChunk;
  while (pvVar1 != (void *)0x0) {
    pvVar1 = *(void **)this->mChunk;
    free(this->mChunk);
    this->mChunk = pvVar1;
  }
  return;
}
