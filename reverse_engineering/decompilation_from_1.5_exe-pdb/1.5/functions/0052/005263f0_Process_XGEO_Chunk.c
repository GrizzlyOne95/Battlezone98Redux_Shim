/*
 * Entry: 005263f0
 * Name: Process_XGEO_Chunk
 * Namespace: Global
 * Signature: long Process_XGEO_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_XGEO_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  _OBJ76 *p_Var3;
  ObjectType *local_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  local_10 = (ObjectType *)0x0;
  uStack_c = 0;
  uStack_8 = 0;
  GetObjectPtrs((ObjectType *)&param_1[1].ckSize,&local_10,3,param_1[1].ckID.longID);
  if (*(int *)((int)param_2 + 4) != 0) {
    iVar2 = _strnicmp((char *)local_10,"null",4);
    if (iVar2 == 0) {
      puVar1 = *(undefined4 **)((int)param_2 + 4);
      *puVar1 = 0x6c6c756e;
      puVar1[1] = 0;
    }
    else {
      puVar1 = *(undefined4 **)((int)param_2 + 4);
      *puVar1 = (int)local_10->GeometryFile;
      puVar1[1] = *(undefined4 *)((int)&local_10->GeometryFile + 4);
    }
  }
  *(int *)((int)param_2 + 8) = (int)local_10->GeometryFile;
  *(undefined4 *)((int)param_2 + 0xc) = *(undefined4 *)((int)&local_10->GeometryFile + 4);
  p_Var3 = AddReps(&local_10,*(_OBJ76 **)param_2,3,1,param_1[1].ckID.longID,
                   (_func___cdecl_void__OBJ76_ptr__OBJ76_ptr *)0x0);
  *(_OBJ76 **)((int)param_2 + 0x10) = p_Var3;
  return (uint)(p_Var3 != (_OBJ76 *)0x0);
}
