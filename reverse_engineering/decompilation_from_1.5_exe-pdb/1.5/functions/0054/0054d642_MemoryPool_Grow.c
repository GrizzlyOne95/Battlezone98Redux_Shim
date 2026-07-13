/*
 * Entry: 0054d642
 * Name: MemoryPool::Grow
 * Namespace: MemoryPool
 * Signature: void Grow(MemoryPool * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MemoryPool::Grow(MemoryPool *this,uint param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = malloc(this->mSize * param_1 + 0x10);
  *puVar2 = this->mChunk;
  this->mChunk = puVar2;
  memset(puVar2 + 1,0xff,this->mSize * param_1 + 0xc);
  puVar1 = puVar2 + 4;
  while (param_1 = param_1 - 1, param_1 != 0) {
    puVar3 = (undefined4 *)(this->mSize + (int)puVar1);
    *puVar1 = puVar3;
    puVar1 = puVar3;
  }
  *puVar1 = this->mFree;
  this->mFree = puVar2 + 4;
  return;
}
