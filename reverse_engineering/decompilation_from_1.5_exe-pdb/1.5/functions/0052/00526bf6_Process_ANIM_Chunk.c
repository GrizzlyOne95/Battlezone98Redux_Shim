/*
 * Entry: 00526bf6
 * Name: Process_ANIM_Chunk
 * Namespace: Global
 * Signature: long Process_ANIM_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_ANIM_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  long lVar1;
  
  lVar1 = AnimObj_Add(param_1,param_2,param_3);
  return (uint)(lVar1 == 0);
}
