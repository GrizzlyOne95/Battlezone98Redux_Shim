/*
 * Entry: 0047226b
 * Name: BoxBox
 * Namespace: Global
 * Signature: int BoxBox(BOX_INFO * param_1, BOX_INFO * param_2, float param_3, CLSN_INFO * param_4, CLSN_INFO * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
BoxBox(BOX_INFO *param_1,BOX_INFO *param_2,float param_3,CLSN_INFO *param_4,CLSN_INFO *param_5)

{
  POINT_VEL PVar1;
  BBOX BVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  int in_EAX;
  VECTOR_3D *pVVar7;
  MAT_3D *pMVar8;
  VECTOR_3D *pVVar9;
  EULER *pEVar10;
  int iVar11;
  BBOX *pBVar12;
  float *pfVar13;
  float *pfVar14;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar15;
  float *pfVar16;
  EULER *pEVar17;
  undefined1 auVar18 [12];
  undefined1 in_stack_fffffdd8 [20];
  float fVar19;
  float in_stack_fffffdf0;
  undefined4 uVar20;
  VECTOR_3D *__return_storage_ptr__;
  VECTOR_3D *__return_storage_ptr___00;
  float fVar21;
  float fVar22;
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
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  MAT_3D *local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_10 = *(float *)(in_EAX + 0x2c);
  local_c = *(float *)(in_EAX + 0x30);
  local_8 = *(float *)(in_EAX + 0x34);
  local_20 = *(float *)(in_EAX + 0x20);
  local_1c = *(float *)(in_EAX + 0x24);
  local_18 = *(float *)(in_EAX + 0x28);
  local_2c = local_10 + local_20;
  local_28 = local_c + local_1c;
  local_24 = local_8 + local_18;
  VVar6.y = local_28;
  VVar6.x = local_2c;
  VVar6.z = local_24;
  pVVar7 = ScaleVector(&local_a8,0.5,VVar6);
  local_9c.x = *(float *)(in_EAX + 0x20);
  local_90 = pVVar7->x;
  local_9c.y = pVVar7->y;
  local_70 = pVVar7->z;
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
  local_14 = &param_1->mat;
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
  pMVar8 = Matrix_Inverse((MAT_3D *)(local_178 + 8),unaff_EDI);
  pMVar15 = &local_130;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    pMVar15->right_x = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pMVar15 = (MAT_3D *)&pMVar15->right_y;
  }
  pMVar8 = Matrix_Multiply((MAT_3D *)(local_178 + 8),(MAT_3D *)(in_EAX + 0x38),&local_130);
  pMVar15 = &local_130;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    pMVar15->right_x = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pMVar15 = (MAT_3D *)&pMVar15->right_y;
  }
  Vector_Transform(local_1d8,&local_9c,8,&local_130);
  *(undefined4 *)param_3 = 0;
  *(BOX_INFO **)((int)param_3 + 0x50) = param_2;
  param_2 = (BOX_INFO *)0x0;
  do {
    __return_storage_ptr___00 = &local_f0;
    VVar4.y = (float)*(undefined4 *)((int)&local_9c.y + (int)param_2);
    VVar4.x = (float)*(undefined4 *)((int)&(param_2->pv).p.x + (int)&local_9c.x);
    VVar4.z = *(float *)((int)&local_9c.z + (int)param_2);
    pVVar7 = WorldVelocity(__return_storage_ptr___00,VVar4,*(_OBJ76 **)(in_EAX + 0x1c));
    local_20 = (param_1->pv).v.x;
    local_1c = (param_1->pv).v.y;
    local_18 = (param_1->pv).v.z;
    local_2c = pVVar7->x;
    local_28 = pVVar7->y;
    local_24 = pVVar7->z;
    local_b4.x = local_2c - local_20;
    pVVar7 = &local_b4;
    local_b4.y = local_28 - local_1c;
    __return_storage_ptr__ = &local_3c;
    local_b4.z = local_24 - local_18;
    uVar20 = 0x472424;
    pMVar8 = local_14;
    local_10 = local_b4.x;
    local_c = local_b4.y;
    local_8 = local_b4.z;
    pVVar9 = Vector_Unrotate(__return_storage_ptr__,pVVar7,local_14);
    local_cc[3] = pVVar9->x;
    fStack_bc = pVVar9->y;
    fStack_b8 = pVVar9->z;
    pVVar9 = &local_a8;
    fVar22 = 0.0;
    local_cc[0] = *(float *)((int)&(param_2->pv).p.x + (int)&local_1d8[0].x);
    local_cc[1] = (float)*(undefined4 *)((int)&local_1d8[0].y + (int)param_2);
    pfVar14 = &local_30;
    local_cc[2] = (float)*(undefined4 *)((int)&local_1d8[0].z + (int)param_2);
    fVar21 = *(float *)((int)param_3 + 0x50);
    fVar19 = 8.40779e-45;
    pBVar12 = &param_1->box;
    pfVar13 = (float *)&stack0xfffffdf0;
    for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar13 = (pBVar12->min).x;
      pBVar12 = (BBOX *)&(pBVar12->min).y;
      pfVar13 = pfVar13 + 1;
    }
    pfVar13 = local_cc;
    pfVar16 = (float *)&stack0xfffffdd8;
    for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar16 = *pfVar13;
      pfVar13 = pfVar13 + 1;
      pfVar16 = pfVar16 + 1;
    }
    PVar1.v.z = fVar19;
    auVar18 = in_stack_fffffdd8._0_12_;
    PVar1.p.x = (float)auVar18._0_4_;
    PVar1.p.y = (float)auVar18._4_4_;
    PVar1.p.z = (float)auVar18._8_4_;
    PVar1.v.x = (float)in_stack_fffffdd8._12_4_;
    PVar1.v.y = (float)in_stack_fffffdd8._16_4_;
    BVar2.min.y = (float)uVar20;
    BVar2.min.x = in_stack_fffffdf0;
    BVar2.min.z = (float)__return_storage_ptr__;
    BVar2.max.x = (float)pVVar7;
    BVar2.max.y = (float)pMVar8;
    BVar2.max.z = (float)__return_storage_ptr___00;
    iVar11 = PointBox(PVar1,BVar2,fVar21,pfVar14,pVVar9,fVar22);
    if (iVar11 != 0) {
      *(float *)((int)param_3 + 0x50) = local_30;
      *(undefined4 *)((int)param_3 + 0x54) =
           *(undefined4 *)((int)&(param_2->pv).p.x + (int)&local_9c.x);
      *(undefined4 *)((int)param_3 + 0x58) = *(undefined4 *)((int)&local_9c.y + (int)param_2);
      *(undefined4 *)((int)param_3 + 0x5c) = *(undefined4 *)((int)&local_9c.z + (int)param_2);
      *(float *)((int)param_3 + 0x60) = local_10;
      *(float *)((int)param_3 + 100) = local_c;
      *(float *)((int)param_3 + 0x68) = local_8;
      *(float *)((int)param_3 + 0x6c) = local_a8.x;
      *(float *)((int)param_3 + 0x70) = local_a8.y;
      *(float *)((int)param_3 + 0x74) = local_a8.z;
      *(undefined4 *)param_3 = 1;
      pfVar14 = local_cc;
      pfVar13 = local_e4;
      for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
        *pfVar13 = *pfVar14;
        pfVar14 = pfVar14 + 1;
        pfVar13 = pfVar13 + 1;
      }
    }
    param_2 = (BOX_INFO *)&(param_2->pv).v;
  } while ((int)param_2 < 0x60);
  if (*(int *)param_3 == 0) {
    iVar11 = 0;
  }
  else {
    *(_OBJ76 **)((int)param_3 + 4) = param_1->obj;
    pEVar10 = ClassGetEuler((EULER *)local_178,param_1->obj);
    pfVar14 = (float *)((int)param_3 + 8);
    for (iVar11 = 0x12; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar14 = pEVar10->mass;
      pEVar10 = (EULER *)&pEVar10->mass_inv;
      pfVar14 = pfVar14 + 1;
    }
    param_4->collided = 1;
    param_4->obj = *(_OBJ76 **)(in_EAX + 0x1c);
    pEVar10 = ClassGetEuler((EULER *)local_178,*(_OBJ76 **)(in_EAX + 0x1c));
    pEVar17 = &param_4->euler;
    for (iVar11 = 0x12; iVar11 != 0; iVar11 = iVar11 + -1) {
      pEVar17->mass = pEVar10->mass;
      pEVar10 = (EULER *)&pEVar10->mass_inv;
      pEVar17 = (EULER *)&pEVar17->mass_inv;
    }
    fVar21 = *(float *)((int)param_3 + 0x50);
    param_4->t = fVar21;
    VVar3.y = local_e4[1];
    VVar3.x = local_e4[0];
    VVar3.z = local_e4[2];
    VVar5.y = (float)uStack_d4;
    VVar5.x = local_e4[3];
    VVar5.z = fStack_d0;
    pVVar7 = AddMultVectors(&local_3c,VVar3,fVar21,VVar5);
    (param_4->point).x = pVVar7->x;
    (param_4->point).y = pVVar7->y;
    (param_4->point).z = pVVar7->z;
    (param_4->vel).x = ((VECTOR_3D *)((int)param_3 + 0x60))->x;
    (param_4->vel).y = *(float *)((int)param_3 + 100);
    (param_4->vel).z = *(float *)((int)param_3 + 0x68);
    pVVar7 = NegVector(&local_3c,*(VECTOR_3D *)((int)param_3 + 0x60));
    *(float *)((int)param_3 + 0x60) = pVVar7->x;
    *(float *)((int)param_3 + 100) = pVVar7->y;
    *(float *)((int)param_3 + 0x68) = pVVar7->z;
    pVVar7 = Vector_Rotate(&local_3c,(VECTOR_3D *)((int)param_3 + 0x6c),local_14);
    ((VECTOR_3D *)((int)param_3 + 0x6c))->x = pVVar7->x;
    *(float *)((int)param_3 + 0x70) = pVVar7->y;
    *(float *)((int)param_3 + 0x74) = pVVar7->z;
    pVVar7 = NegVector(&local_3c,*pVVar7);
    (param_4->normal).x = pVVar7->x;
    (param_4->normal).y = pVVar7->y;
    (param_4->normal).z = pVVar7->z;
    iVar11 = 1;
  }
  return iVar11;
}
