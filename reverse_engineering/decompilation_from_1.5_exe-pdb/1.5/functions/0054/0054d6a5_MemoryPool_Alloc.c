/*
 * Entry: 0054d6a5
 * Name: MemoryPool::Alloc
 * Namespace: MemoryPool
 * Signature: void * Alloc(MemoryPool * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MemoryPool::Alloc(MemoryPool *this)

{
  undefined4 *puVar1;
  
  if (this->mFree == (void *)0x0) {
    if (this->mGrow == 0) {
      return (void *)0x0;
    }
    Grow(this,this->mGrow);
  }
  puVar1 = this->mFree;
  this->mFree = (void *)*puVar1;
  return puVar1;
}
