/*
 * Entry: 00526cbe
 * Name: Process_VLOC_Chunk
 * Namespace: Global
 * Signature: long Process_VLOC_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_VLOC_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  ulong uVar1;
  void *pvVar2;
  ChunkType *pCVar3;
  _OBJ76 *p_Var4;
  int iVar5;
  long *plVar6;
  undefined4 *puVar7;
  long *plVar8;
  ChunkType local_6c;
  long local_64 [12];
  undefined4 local_34;
  undefined4 local_30;
  IDType local_10;
  undefined4 local_c;
  void *local_8;
  
  pCVar3 = param_1;
  uVar1 = param_1[1].ckID.longID;
  pvVar2 = (*(_OBJ76 **)param_2)->class_ptr;
  puVar7 = (undefined4 *)0x0;
  local_8 = pvVar2;
  if (uVar1 == 0x26) {
    iVar5 = Is_Day_Time();
    if (iVar5 == 1) {
      *(undefined4 *)((int)pvVar2 + 0x104) = 0;
      return 1;
    }
    memset(&local_6c,0,100);
    strncpy((char *)&local_6c,"hdlt_msk",8);
    local_10 = pCVar3[1].ckID;
    plVar6 = &pCVar3[1].ckSize;
    plVar8 = local_64;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *plVar8 = *plVar6;
      plVar6 = plVar6 + 1;
      plVar8 = plVar8 + 1;
    }
    param_1 = &local_6c;
    local_34 = 0x6c6c756e;
    local_30 = 0;
    local_c = 0;
    p_Var4 = AddReps((ObjectType **)&param_1,(_OBJ76 *)0x0,1,1,1,
                     (_func___cdecl_void__OBJ76_ptr__OBJ76_ptr *)0x0);
    pvVar2 = param_2;
    if (p_Var4 == (_OBJ76 *)0x0) {
      return 0;
    }
    i_got_dibs_on_obj(*(_OBJ76 **)param_2,"vhclload");
    puVar7 = (undefined4 *)((int)local_8 + 0x104);
    *puVar7 = p_Var4;
    p_Var4->parent = *(_OBJ76 **)pvVar2;
    AddTerrainSpecial(p_Var4);
    GeoCache_AddRep(p_Var4,"hdlv_msk.geo",0,4);
  }
  else {
    if (uVar1 == 0x28) {
      puVar7 = (undefined4 *)((int)pvVar2 + 0xf4);
    }
    else if (uVar1 == 0x2a) {
      *(IDType *)((int)pvVar2 + 0xe8) = param_1[6].ckID;
      *(long *)((int)pvVar2 + 0xec) = param_1[6].ckSize;
      *(IDType *)((int)pvVar2 + 0xf0) = param_1[7].ckID;
      return 1;
    }
    p_Var4 = create_obj_ext(*(_OBJ76 **)param_2,(long64 *)0x0);
    if (p_Var4 == (_OBJ76 *)0x0) {
      return 0;
    }
    ClassCreate(p_Var4,pCVar3[1].ckID.longID);
    File_Matrix_To_I76_Matrix(&p_Var4->transform,(MAT_3D_FILE *)&pCVar3[1].ckSize);
  }
  if (puVar7 != (undefined4 *)0x0) {
    *puVar7 = p_Var4;
  }
  return 1;
}
