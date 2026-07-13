/*
 * Entry: 0054d6c9
 * Name: MemoryPool::Free
 * Namespace: MemoryPool
 * Signature: void Free(MemoryPool * this, void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MemoryPool::Free(MemoryPool *this,void *param_1)

{
  *(void **)param_1 = this->mFree;
  this->mFree = param_1;
  return;
}
