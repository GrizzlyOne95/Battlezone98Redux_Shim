/*
 * Entry: 005257e9
 * Name: LoadObjects
 * Namespace: Global
 * Signature: long LoadObjects(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl LoadObjects(ChunkType *param_1,void *param_2,void *param_3)

{
  ChunkType *pCVar1;
  
  pCVar1 = GenericChunkHandler(param_1,ObjectChunkDefs,3,(void *)0x0,param_2,1,param_3);
  return (uint)(pCVar1 != (ChunkType *)0x0);
}
