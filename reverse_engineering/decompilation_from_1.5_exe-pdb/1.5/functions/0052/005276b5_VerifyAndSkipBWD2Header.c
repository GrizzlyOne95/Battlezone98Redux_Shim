/*
 * Entry: 005276b5
 * Name: VerifyAndSkipBWD2Header
 * Namespace: Global
 * Signature: ChunkType * VerifyAndSkipBWD2Header(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ChunkType * __cdecl VerifyAndSkipBWD2Header(ChunkType *param_1,void *param_2,void *param_3)

{
  ChunkType *pCVar1;
  
  pCVar1 = GenericChunkHandler(param_1,BWD2ChunkDefs,2,(void *)0x0,param_2,1,param_3);
  return pCVar1;
}
