/*
 * Entry: 005258fc
 * Name: Process_SOBJ_Chunk
 * Namespace: Global
 * Signature: long Process_SOBJ_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_SOBJ_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  _GEOMETRY *p_Var1;
  
  p_Var1 = Geom_Load((long64)param_1[1]);
  *(_GEOMETRY **)(*(int *)param_2 + 100) = p_Var1;
  return 1;
}
