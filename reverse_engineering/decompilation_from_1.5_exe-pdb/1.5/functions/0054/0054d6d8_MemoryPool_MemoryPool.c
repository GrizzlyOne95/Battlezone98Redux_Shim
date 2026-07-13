/*
 * Entry: 0054d6d8
 * Name: MemoryPool::MemoryPool
 * Namespace: MemoryPool
 * Signature: MemoryPool * MemoryPool(MemoryPool * this, uint param_1, uint param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MemoryPool * __thiscall
MemoryPool::MemoryPool(MemoryPool *this,uint param_1,uint param_2,uint param_3)

{
  this->mSize = param_1;
  this->mGrow = param_3;
  this->mChunk = (void *)0x0;
  this->mFree = (void *)0x0;
  if (param_2 != 0) {
    Grow(this,param_2);
  }
  return this;
}
