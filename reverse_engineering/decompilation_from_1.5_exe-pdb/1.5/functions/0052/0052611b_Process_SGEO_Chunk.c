/*
 * Entry: 0052611b
 * Name: Process_SGEO_Chunk
 * Namespace: Global
 * Signature: long Process_SGEO_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_SGEO_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  ulong uVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  StructObjectType **ppSVar4;
  StructObjectType *local_1c [6];
  
  uVar1 = param_1[1].ckID.longID;
  ppSVar4 = local_1c;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *ppSVar4 = (StructObjectType *)0x0;
    ppSVar4 = ppSVar4 + 1;
  }
  GetStructObjectPtrs((StructObjectType *)&param_1[1].ckSize,local_1c,6,uVar1);
  p_Var2 = AddStructReps(local_1c,*(_OBJ76 **)param_2,3,2,param_1[1].ckID.longID,
                         (_func___cdecl_void__OBJ76_ptr__OBJ76_ptr *)0x0);
  return (uint)(p_Var2 != (_OBJ76 *)0x0);
}
