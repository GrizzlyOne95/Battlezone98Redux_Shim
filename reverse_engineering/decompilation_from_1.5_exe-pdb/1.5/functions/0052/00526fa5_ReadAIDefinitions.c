/*
 * Entry: 00526fa5
 * Name: ReadAIDefinitions
 * Namespace: Global
 * Signature: long ReadAIDefinitions(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ReadAIDefinitions(ChunkType *param_1,void *param_2,void *param_3)

{
  ChunkType *pCVar1;
  
  pCVar1 = GenericChunkHandler(param_1,AIChunkDefs,2,(void *)0x0,param_2,1,param_3);
  return (uint)(pCVar1 != (ChunkType *)0x0);
}
