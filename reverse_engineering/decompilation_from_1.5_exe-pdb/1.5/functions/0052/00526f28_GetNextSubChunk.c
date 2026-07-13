/*
 * Entry: 00526f28
 * Name: GetNextSubChunk
 * Namespace: Global
 * Signature: int GetNextSubChunk(ChunkType * param_1, ChunkType * * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNextSubChunk(ChunkType *param_1,ChunkType **param_2,void *param_3)

{
  ChunkType *pCVar1;
  
  if ((param_3 == (void *)0x0) || (param_1 < param_3)) {
    pCVar1 = (ChunkType *)((int)&param_1->ckID + param_1->ckSize);
    *param_2 = pCVar1;
    if ((param_3 == (void *)0x0) || (pCVar1 < param_3)) {
      return 1;
    }
  }
  return 0;
}
