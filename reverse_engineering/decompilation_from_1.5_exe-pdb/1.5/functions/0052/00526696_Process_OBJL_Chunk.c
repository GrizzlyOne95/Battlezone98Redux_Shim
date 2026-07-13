/*
 * Entry: 00526696
 * Name: Process_OBJL_Chunk
 * Namespace: Global
 * Signature: long Process_OBJL_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_OBJL_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  tagENTITY *ptVar6;
  ushort uVar7;
  int iVar8;
  char *pcVar9;
  long lVar10;
  _OBJ76 *p_Var11;
  MAT_3D *pMVar12;
  VECTOR_3D *pVVar13;
  CLSN_BOXES *pCVar14;
  tagENTITY *ptVar15;
  _OBJ76 **pp_Var16;
  _OBJ76 *p_Var17;
  int iVar18;
  StructObjectType *pSVar19;
  VECTOR_3D *unaff_ESI;
  StructObjectType *pSVar20;
  float *pfVar21;
  StructObjectType *pSVar22;
  MAT_3D *pMVar23;
  float fVar24;
  MAT_3D local_1c0;
  StructObjectType local_180;
  float local_108 [6];
  undefined4 local_f0;
  undefined4 local_ec;
  float local_e8;
  double local_e0;
  double local_d8;
  double local_d0;
  VECTOR_3D local_c8;
  float local_bc;
  float fStack_b8;
  float fStack_b4;
  ENTITY_LOADER local_b0;
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  IDType local_50;
  float local_4c;
  IDType local_48;
  uint local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  _OBJ76 *local_24;
  VECTOR_3D *local_20;
  _OBJ76 *local_1c;
  float local_18;
  float local_14;
  float local_10;
  _OBJ76 *local_c;
  tagENTITY *local_8;
  
  pSVar19 = (StructObjectType *)(param_1 + 1);
  memset((short)&local_b0,0,0x54);
  local_b0.entObj = NewObj((_OBJ76 *)0x0,pSVar19,(long64 *)pSVar19,1);
  if (local_b0.entObj == (_OBJ76 *)0x0) {
    return 0;
  }
  uVar7 = PrjID2SeqNo(pSVar19->GeometryFile);
  local_44 = (uint)uVar7;
  *(uint *)&pSVar19->GeometryFile = (uint)pSVar19->GeometryFile & 0x7f7f7f7f;
  param_1[1].ckSize = param_1[1].ckSize & 0x7f7f7f7f;
  local_1c = (_OBJ76 *)param_1[0xd].ckSize;
  iVar8 = (int)local_1c * 0xc;
  pSVar20 = pSVar19;
  pSVar22 = &local_180;
  for (iVar18 = 0x1e; iVar18 != 0; iVar18 = iVar18 + -1) {
    *(int *)&pSVar22->GeometryFile = (int)pSVar20->GeometryFile;
    pSVar20 = (StructObjectType *)((int)&pSVar20->GeometryFile + 4);
    pSVar22 = (StructObjectType *)((int)&pSVar22->GeometryFile + 4);
  }
  memcpy(Vertex_Pool,param_1 + 0xe,(short)iVar8);
  pVVar13 = Vertex_Pool;
  local_20 = Vertex_Pool + 1;
  param_1 = (ChunkType *)Vertex_Pool;
  local_18 = Vertex_Pool->x;
  local_14 = Vertex_Pool->y;
  local_10 = Vertex_Pool->z;
  local_14 = Terrain_FindFloor((double)local_18,(double)local_10);
  pMVar12 = &Identity_Matrix;
  pMVar23 = &(local_b0.entObj)->transform;
  for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
    pMVar23->right_x = pMVar12->right_x;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
    pMVar23 = (MAT_3D *)&pMVar23->right_y;
  }
  ((local_b0.entObj)->transform).posit_x = (double)local_18;
  ((local_b0.entObj)->transform).posit_y = (double)local_14;
  ((local_b0.entObj)->transform).posit_z = (double)local_10;
  if (0 < (int)local_1c) {
    local_8 = (tagENTITY *)pVVar13;
    local_c = local_1c;
    do {
      ptVar15 = local_8;
      fVar24 = Terrain_FindFloor((double)(float)local_8->obj76,(double)*(float *)&local_8->bSphere);
      *(float *)&ptVar15->seqNo = fVar24;
      local_30 = (float)ptVar15->obj76;
      local_2c = *(float *)&ptVar15->seqNo;
      local_28 = *(float *)&ptVar15->bSphere;
      local_3c = local_30 - local_18;
      local_c = (_OBJ76 *)((int)&local_c[-1].bBox.max.z + 3);
      local_38 = local_2c - local_14;
      local_34 = local_28 - local_10;
      local_8->obj76 = (_OBJ76 *)local_3c;
      *(float *)&local_8->seqNo = local_38;
      *(float *)&local_8->bSphere = local_34;
      local_8 = (tagENTITY *)((int)local_8 + 0xc);
    } while (local_c != (_OBJ76 *)0x0);
    local_c = (_OBJ76 *)0x0;
  }
  local_8 = (tagENTITY *)0x0;
  local_24 = (_OBJ76 *)((int)&local_1c[-1].bBox.max.z + 3);
  if (0 < (int)local_24) {
    do {
      if (local_8 == (tagENTITY *)0x0) {
        pcVar9 = PrjID2Filename(pSVar19->GeometryFile,".sdf");
        lVar10 = LoadStructure(pSVar19,&local_b0,pcVar9);
        if (lVar10 == 0) {
          ClassDelete(local_b0.entObj);
          remove_obj(local_b0.entObj,"othrload");
          return 0;
        }
        p_Var11 = (local_b0.entObj)->child;
        local_1c = p_Var11;
        local_c = p_Var11;
      }
      else {
        p_Var11 = create_obj(local_b0.entObj,"othrload");
        local_c = p_Var11;
        if (p_Var11 == (_OBJ76 *)0x0) break;
        ClassCreate(p_Var11,CLASS_ID_STRUCTURE2);
        GeoCache_Clone(local_1c,p_Var11);
      }
      *(int *)&p_Var11->id = (int)(local_b0.entObj)->id;
      *(undefined4 *)((int)&p_Var11->id + 4) = *(undefined4 *)((int)&(local_b0.entObj)->id + 4);
      local_50 = param_1->ckID;
      local_4c = (float)param_1->ckSize;
      local_48 = param_1[1].ckID;
      local_3c = local_20->x;
      local_38 = local_20->y;
      local_34 = local_20->z;
      local_bc = local_3c - (float)local_50;
      fStack_b8 = local_38 - local_4c;
      fStack_b4 = local_34 - (float)local_48;
      VVar5.y = fStack_b8;
      VVar5.x = local_bc;
      VVar5.z = fStack_b4;
      local_30 = local_bc;
      local_2c = fStack_b8;
      local_28 = fStack_b4;
      local_40 = VecLen(VVar5);
      local_40 = local_40 * 0.5;
      pMVar12 = Build_Directinal_Matrix(&local_1c0,(VECTOR_3D *)&local_1c0,unaff_ESI);
      pfVar21 = local_108;
      for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
        *pfVar21 = pMVar12->right_x;
        pMVar12 = (MAT_3D *)&pMVar12->right_y;
        pfVar21 = pfVar21 + 1;
      }
      local_5c = local_f0;
      local_58 = local_ec;
      local_54 = local_e8;
      VVar4.y._0_2_ = (short)local_ec;
      VVar4.x = (float)local_f0;
      VVar4.y._2_2_ = (short)((uint)local_ec >> 0x10);
      VVar4.z = local_e8;
      pVVar13 = AddMultVectors(&local_c8,*(VECTOR_3D *)param_1,local_40,VVar4);
      local_18 = pVVar13->x;
      local_10 = pVVar13->z;
      local_14 = pVVar13->y - (local_c->bBox).min.y;
      local_8 = (tagENTITY *)((int)&local_8->obj76 + 1);
      param_1 = (ChunkType *)&param_1[1].ckSize;
      local_20 = local_20 + 1;
      local_e0 = (double)pVVar13->x;
      local_d8 = (double)local_14;
      local_d0 = (double)pVVar13->z;
      pfVar21 = local_108;
      pMVar12 = &local_c->transform;
      for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
        pMVar12->right_x = *pfVar21;
        pfVar21 = pfVar21 + 1;
        pMVar12 = (MAT_3D *)&pMVar12->right_y;
      }
    } while ((int)local_8 < (int)local_24);
  }
  while( true ) {
    pCVar14 = (CLSN_BOXES *)0x0;
    if (local_b0.clsnPlanesFound != 0) {
      pCVar14 = GetClsnPlanes(&local_b0.clsnPlanes);
    }
    ptVar15 = add_entity(local_b0.entObj,(short)local_44,pCVar14,
                         (float *)(-(uint)(local_b0.lodRangesFound != 0) & (uint)local_b0.lodRanges)
                        );
    if (ptVar15 == (tagENTITY *)0x0) {
      DEBUG_systemError("BattleZone cannot create entity - The world is full!\n");
      return 0;
    }
    reset_entity_pointer();
    local_8 = get_entity();
    if (local_8->obj76 != local_b0.entObj) {
      do {
        local_8 = get_entity();
      } while (local_8->obj76 != local_b0.entObj);
    }
    p_Var11 = local_8->obj76->child;
    if ((local_8->bSphere).radius <= 20.0) break;
    do {
      ptVar15 = local_8;
      pp_Var16 = &local_8->obj76->child;
      local_24 = *pp_Var16;
      if (local_24->sibling == (_OBJ76 *)0x0) {
        return 1;
      }
      *pp_Var16 = local_24->sibling;
      pVVar13 = get_obj_geometric_center(&local_c8,local_8->obj76);
      ptVar6 = local_8;
      (ptVar15->bSphere).origin.x = pVVar13->x;
      (ptVar15->bSphere).origin.y = pVVar13->y;
      (ptVar15->bSphere).origin.z = pVVar13->z;
      fVar24 = get_obj_radius(local_8->obj76,*pVVar13);
      (ptVar6->bSphere).radius = fVar24;
    } while (20.0 < (ptVar6->bSphere).radius);
    local_24->sibling = (_OBJ76 *)0x0;
    p_Var17 = NewObj((_OBJ76 *)0x0,&local_180,(long64 *)pSVar19,1);
    if (p_Var17 == (_OBJ76 *)0x0) {
      while (p_Var11 != (_OBJ76 *)0x0) {
        p_Var17 = p_Var11->sibling;
        remove_obj(p_Var11,"othrload");
        p_Var11 = p_Var17;
      }
      return 0;
    }
    pMVar12 = &(local_b0.entObj)->transform;
    pMVar23 = &p_Var17->transform;
    for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
      pMVar23->right_x = pMVar12->right_x;
      pMVar12 = (MAT_3D *)&pMVar12->right_y;
      pMVar23 = (MAT_3D *)&pMVar23->right_y;
    }
    p_Var17->child = p_Var11;
    dVar1 = (p_Var11->transform).posit_x + (p_Var17->transform).posit_x;
    dVar2 = (p_Var11->transform).posit_y + (p_Var17->transform).posit_y;
    dVar3 = (p_Var11->transform).posit_z + (p_Var17->transform).posit_z;
    do {
      p_Var11->parent = p_Var17;
      (p_Var11->transform).posit_x =
           ((p_Var17->transform).posit_x + (p_Var11->transform).posit_x) - dVar1;
      (p_Var11->transform).posit_y =
           ((p_Var11->transform).posit_y + (p_Var17->transform).posit_y) - dVar2;
      (p_Var11->transform).posit_z =
           ((p_Var11->transform).posit_z + (p_Var17->transform).posit_z) - dVar3;
      p_Var11 = p_Var11->sibling;
    } while (p_Var11 != (_OBJ76 *)0x0);
    (p_Var17->transform).posit_x = dVar1;
    (p_Var17->transform).posit_y = dVar2;
    (p_Var17->transform).posit_z = dVar3;
    local_b0.entObj = p_Var17;
  }
  return 1;
}
