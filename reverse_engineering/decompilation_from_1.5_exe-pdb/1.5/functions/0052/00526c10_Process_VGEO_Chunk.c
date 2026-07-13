/*
 * Entry: 00526c10
 * Name: Process_VGEO_Chunk
 * Namespace: Global
 * Signature: long Process_VGEO_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_VGEO_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  _OBJ76 *p_Var1;
  ObjectType *local_74 [28];
  
  memset(local_74,0,0x70);
  GetObjectPtrs((ObjectType *)&param_1[1].ckSize,local_74,0x1c,param_1[1].ckID.longID);
  p_Var1 = AddReps(local_74,*(_OBJ76 **)param_2,7,4,param_1[1].ckID.longID,
                   (_func___cdecl_void__OBJ76_ptr__OBJ76_ptr *)0x0);
  return (uint)(p_Var1 != (_OBJ76 *)0x0);
}
