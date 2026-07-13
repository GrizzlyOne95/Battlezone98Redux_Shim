/*
 * Entry: 00472629
 * Name: BoxGeom
 * Namespace: Global
 * Signature: int BoxGeom(BOX_INFO * param_1, _OBJ76 * param_2, MAT_3D * param_3, float param_4, CLSN_INFO * param_5, CLSN_INFO * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
BoxGeom(BOX_INFO *param_1,_OBJ76 *param_2,MAT_3D *param_3,float param_4,CLSN_INFO *param_5,
       CLSN_INFO *param_6)

{
  POINT_VEL PVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  int in_EAX;
  VECTOR_3D *pVVar6;
  MAT_3D *pMVar7;
  VECTOR_3D *pVVar8;
  EULER *pEVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar13;
  float *pfVar14;
  EULER *pEVar15;
  float in_stack_fffffdf0;
  undefined4 uVar16;
  VECTOR_3D *__return_storage_ptr__;
  _OBJ76 *p_Var17;
  VECTOR_3D *__return_storage_ptr___00;
  CLSN_GEOM *pCVar18;
  float fVar19;
  VECTOR_3D local_1d8 [8];
  undefined1 local_178 [72];
  MAT_3D local_130;
  VECTOR_3D local_f0;
  float local_e4 [4];
  undefined4 uStack_d4;
  float fStack_d0;
  float local_cc [4];
  float fStack_bc;
  float fStack_b8;
  VECTOR_3D local_b4;
  VECTOR_3D local_a8;
  VECTOR_3D local_9c;
  float local_90;
  float local_8c;
  undefined4 local_88;
  undefined4 local_84;
  float local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  float local_70;
  undefined4 local_6c;
  float local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  VECTOR_3D local_3c;
  CLSN_GEOM *local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_10 = *(float *)(in_EAX + 0x2c);
  local_c = *(float *)(in_EAX + 0x30);
  local_8 = *(float *)(in_EAX + 0x34);
  local_28 = *(float *)(in_EAX + 0x20);
  local_24 = *(float *)(in_EAX + 0x24);
  local_30 = (CLSN_GEOM *)param_1[1].mat.up_z;
  local_20 = *(float *)(in_EAX + 0x28);
  local_1c = local_10 + local_28;
  local_18 = local_c + local_24;
  local_14 = local_8 + local_20;
  VVar5.y = local_18;
  VVar5.x = local_1c;
  VVar5.z = local_14;
  pVVar6 = ScaleVector(&local_b4,0.5,VVar5);
  local_9c.x = *(float *)(in_EAX + 0x20);
  local_90 = pVVar6->x;
  local_9c.y = pVVar6->y;
  local_70 = pVVar6->z;
  local_9c.z = *(float *)(in_EAX + 0x28);
  local_88 = *(undefined4 *)(in_EAX + 0x28);
  local_84 = *(undefined4 *)(in_EAX + 0x2c);
  local_7c = *(undefined4 *)(in_EAX + 0x28);
  local_78 = *(undefined4 *)(in_EAX + 0x2c);
  local_6c = *(undefined4 *)(in_EAX + 0x2c);
  local_64 = *(undefined4 *)(in_EAX + 0x34);
  local_58 = *(undefined4 *)(in_EAX + 0x34);
  local_54 = *(undefined4 *)(in_EAX + 0x20);
  local_4c = *(undefined4 *)(in_EAX + 0x34);
  local_48 = *(undefined4 *)(in_EAX + 0x20);
  local_8c = local_9c.y;
  local_80 = local_9c.y;
  local_74 = local_9c.y;
  local_68 = local_9c.y;
  local_60 = local_90;
  local_5c = local_9c.y;
  local_50 = local_9c.y;
  local_44 = local_9c.y;
  local_40 = local_70;
  local_10 = local_90;
  local_c = local_9c.y;
  local_8 = local_70;
  pMVar7 = Matrix_Inverse((MAT_3D *)(local_178 + 8),unaff_EDI);
  pMVar13 = &local_130;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar7->right_x;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  pMVar7 = Matrix_Multiply((MAT_3D *)(local_178 + 8),(MAT_3D *)(in_EAX + 0x38),&local_130);
  pMVar13 = &local_130;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar7->right_x;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  Vector_Transform(local_1d8,&local_9c,8,&local_130);
  local_1c = 0.0;
  local_18 = 0.0;
  local_14 = 0.0;
  pVVar6 = WorldVelocity(&local_a8,(VECTOR_3D)ZEXT812(0),(_OBJ76 *)param_1);
  local_28 = pVVar6->x;
  local_24 = pVVar6->y;
  local_20 = pVVar6->z;
  *(MAT_3D **)((int)param_4 + 0x50) = param_3;
  *(undefined4 *)param_4 = 0;
  param_3 = (MAT_3D *)0x0;
  do {
    __return_storage_ptr___00 = &local_f0;
    VVar3.y = (float)*(undefined4 *)((int)&local_9c.y + (int)param_3);
    VVar3.x = (float)*(undefined4 *)((int)&param_3->right_x + (int)&local_9c.x);
    VVar3.z = *(float *)((int)&local_9c.z + (int)param_3);
    pVVar6 = WorldVelocity(__return_storage_ptr___00,VVar3,*(_OBJ76 **)(in_EAX + 0x1c));
    local_1c = pVVar6->x;
    local_18 = pVVar6->y;
    local_14 = pVVar6->z;
    local_a8.x = local_1c - local_28;
    pVVar6 = &local_a8;
    local_a8.y = local_18 - local_24;
    __return_storage_ptr__ = &local_3c;
    local_a8.z = local_14 - local_20;
    uVar16 = 0x472809;
    p_Var17 = param_2;
    local_10 = local_a8.x;
    local_c = local_a8.y;
    local_8 = local_a8.z;
    pVVar8 = Vector_Unrotate(__return_storage_ptr__,pVVar6,(MAT_3D *)param_2);
    local_cc[3] = pVVar8->x;
    fStack_bc = pVVar8->y;
    fStack_b8 = pVVar8->z;
    pVVar8 = &local_b4;
    pfVar12 = &local_2c;
    fVar19 = *(float *)((int)param_4 + 0x50);
    local_cc[0] = *(float *)((int)&param_3->right_x + (int)&local_1d8[0].x);
    local_cc[1] = (float)*(undefined4 *)((int)&local_1d8[0].y + (int)param_3);
    local_cc[2] = (float)*(undefined4 *)((int)&local_1d8[0].z + (int)param_3);
    pfVar11 = local_cc;
    pfVar14 = (float *)&stack0xfffffdf0;
    pCVar18 = local_30;
    for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pfVar14 = *pfVar11;
      pfVar11 = pfVar11 + 1;
      pfVar14 = pfVar14 + 1;
    }
    PVar1.p.y = (float)uVar16;
    PVar1.p.x = in_stack_fffffdf0;
    PVar1.p.z = (float)__return_storage_ptr__;
    PVar1.v.x = (float)pVVar6;
    PVar1.v.y = (float)p_Var17;
    PVar1.v.z = (float)__return_storage_ptr___00;
    iVar10 = Cgeom_PointTest(PVar1,pCVar18,fVar19,pfVar12,pVVar8);
    if (iVar10 != 0) {
      *(float *)((int)param_4 + 0x50) = local_2c;
      *(undefined4 *)((int)param_4 + 0x54) =
           *(undefined4 *)((int)&param_3->right_x + (int)&local_9c.x);
      *(undefined4 *)((int)param_4 + 0x58) = *(undefined4 *)((int)&local_9c.y + (int)param_3);
      *(undefined4 *)((int)param_4 + 0x5c) = *(undefined4 *)((int)&local_9c.z + (int)param_3);
      *(float *)((int)param_4 + 0x60) = local_10;
      *(float *)((int)param_4 + 100) = local_c;
      *(float *)((int)param_4 + 0x68) = local_8;
      *(float *)((int)param_4 + 0x6c) = local_b4.x;
      *(float *)((int)param_4 + 0x70) = local_b4.y;
      *(float *)((int)param_4 + 0x74) = local_b4.z;
      *(undefined4 *)param_4 = 1;
      pfVar12 = local_cc;
      pfVar11 = local_e4;
      for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
        *pfVar11 = *pfVar12;
        pfVar12 = pfVar12 + 1;
        pfVar11 = pfVar11 + 1;
      }
    }
    param_3 = (MAT_3D *)&param_3->up_x;
  } while ((int)param_3 < 0x60);
  if (*(int *)param_4 == 0) {
    iVar10 = 0;
  }
  else {
    *(BOX_INFO **)((int)param_4 + 4) = param_1;
    pEVar9 = ClassGetEuler((EULER *)local_178,(_OBJ76 *)param_1);
    pfVar12 = (float *)((int)param_4 + 8);
    for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pfVar12 = pEVar9->mass;
      pEVar9 = (EULER *)&pEVar9->mass_inv;
      pfVar12 = pfVar12 + 1;
    }
    param_5->collided = 1;
    param_5->obj = *(_OBJ76 **)(in_EAX + 0x1c);
    pEVar9 = ClassGetEuler((EULER *)local_178,*(_OBJ76 **)(in_EAX + 0x1c));
    pEVar15 = &param_5->euler;
    for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1) {
      pEVar15->mass = pEVar9->mass;
      pEVar9 = (EULER *)&pEVar9->mass_inv;
      pEVar15 = (EULER *)&pEVar15->mass_inv;
    }
    fVar19 = *(float *)((int)param_4 + 0x50);
    param_5->t = fVar19;
    VVar2.y = local_e4[1];
    VVar2.x = local_e4[0];
    VVar2.z = local_e4[2];
    VVar4.y = (float)uStack_d4;
    VVar4.x = local_e4[3];
    VVar4.z = fStack_d0;
    pVVar6 = AddMultVectors(&local_3c,VVar2,fVar19,VVar4);
    (param_5->point).x = pVVar6->x;
    (param_5->point).y = pVVar6->y;
    (param_5->point).z = pVVar6->z;
    (param_5->vel).x = ((VECTOR_3D *)((int)param_4 + 0x60))->x;
    (param_5->vel).y = *(float *)((int)param_4 + 100);
    (param_5->vel).z = *(float *)((int)param_4 + 0x68);
    pVVar6 = NegVector(&local_3c,*(VECTOR_3D *)((int)param_4 + 0x60));
    *(float *)((int)param_4 + 0x60) = pVVar6->x;
    *(float *)((int)param_4 + 100) = pVVar6->y;
    *(float *)((int)param_4 + 0x68) = pVVar6->z;
    pVVar6 = Vector_Rotate(&local_3c,(VECTOR_3D *)((int)param_4 + 0x6c),(MAT_3D *)param_2);
    ((VECTOR_3D *)((int)param_4 + 0x6c))->x = pVVar6->x;
    *(float *)((int)param_4 + 0x70) = pVVar6->y;
    *(float *)((int)param_4 + 0x74) = pVVar6->z;
    pVVar6 = NegVector(&local_3c,*pVVar6);
    (param_5->normal).x = pVVar6->x;
    (param_5->normal).y = pVVar6->y;
    (param_5->normal).z = pVVar6->z;
    iVar10 = 1;
  }
  return iVar10;
}
