/*
 * Entry: 00526f6c
 * Name: RequestChunk
 * Namespace: Global
 * Signature: long RequestChunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl RequestChunk(ChunkType *param_1,void *param_2,void *param_3)

{
  return (uint)((void *)(param_1->ckID).longID == param_2);
}
