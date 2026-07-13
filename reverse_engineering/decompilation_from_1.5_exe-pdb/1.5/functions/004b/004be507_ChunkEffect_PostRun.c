/*
 * Entry: 004be507
 * Name: ChunkEffect::PostRun
 * Namespace: ChunkEffect
 * Signature: void PostRun(ChunkEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ChunkEffect::PostRun(ChunkEffect *this)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < this->chunkletCount) {
    do {
      GeoCache_Delete(this->chunkletList[iVar1]);
      remove_obj(this->chunkletList[iVar1],".\\fun3d\\ChunkEffect.cpp");
      iVar1 = iVar1 + 1;
    } while (iVar1 < this->chunkletCount);
  }
  operator_delete__(this->chunkletList);
  return;
}
