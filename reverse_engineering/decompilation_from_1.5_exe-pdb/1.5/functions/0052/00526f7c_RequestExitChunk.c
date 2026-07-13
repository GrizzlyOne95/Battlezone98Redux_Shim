/*
 * Entry: 00526f7c
 * Name: RequestExitChunk
 * Namespace: Global
 * Signature: long RequestExitChunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl RequestExitChunk(ChunkType *param_1,void *param_2,void *param_3)

{
  return (uint)((param_1->ckID).longID == 0x54495845);
}
