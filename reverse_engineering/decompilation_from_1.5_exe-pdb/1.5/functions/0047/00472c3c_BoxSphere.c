/*
 * Entry: 00472c3c
 * Name: BoxSphere
 * Namespace: Global
 * Signature: int BoxSphere(BOX_INFO * param_1, _OBJ76 * param_2, float param_3, MAT_3D * param_4, float param_5, CLSN_INFO * param_6, CLSN_INFO * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
BoxSphere(BOX_INFO *param_1,_OBJ76 *param_2,float param_3,MAT_3D *param_4,float param_5,
         CLSN_INFO *param_6,CLSN_INFO *param_7)

{
  POINT_VEL PVar1;
  BBOX BVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  int in_EAX;
  MAT_3D *pMVar5;
  VECTOR_3D *pVVar6;
  VECTOR_3D *pVVar7;
  VECTOR_3D *pVVar8;
  EULER *pEVar9;
  int iVar10;
  float *pfVar11;
  VECTOR_3D *pVVar12;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar13;
  float *pfVar14;
  EULER *pEVar15;
  undefined1 auVar16 [12];
  undefined1 in_stack_fffffec8 [16];
  undefined4 in_stack_fffffed8;
  float fVar17;
  float in_stack_fffffee0;
  undefined4 uVar18;
  VECTOR_3D *__return_storage_ptr__;
  float *pfVar19;
  float fVar20;
  undefined1 local_e8 [72];
  MAT_3D local_a0;
  VECTOR_3D local_60;
  VECTOR_3D local_54;
  float local_48;
  float local_44;
  float local_40;
  VECTOR_3D local_3c;
  VECTOR_3D local_30;
  float local_24;
  float local_20;
  float local_1c;
  VECTOR_3D local_18;
  MAT_3D *local_c;
  float local_8;
  
  local_30.x = *(float *)(in_EAX + 0xc);
  local_30.y = *(float *)(in_EAX + 0x10);
  local_c = (MAT_3D *)(in_EAX + 0x38);
  local_30.z = *(float *)(in_EAX + 0x14);
  pMVar5 = Matrix_Inverse((MAT_3D *)(local_e8 + 8),unaff_EDI);
  pMVar13 = &local_a0;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  pMVar5 = Matrix_Multiply((MAT_3D *)(local_e8 + 8),(MAT_3D *)param_3,&local_a0);
  pMVar13 = &local_a0;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  Vector_Transform(&local_60,(VECTOR_3D *)&param_1[1].mat.front_x,1,&local_a0);
  local_24 = 0.0;
  local_20 = 0.0;
  local_1c = 0.0;
  pVVar8 = &local_18;
  pVVar6 = WorldVelocity(pVVar8,(VECTOR_3D)ZEXT812(0),(_OBJ76 *)param_1);
  local_48 = *(float *)(in_EAX + 0xc);
  local_44 = *(float *)(in_EAX + 0x10);
  local_40 = *(float *)(in_EAX + 0x14);
  local_24 = pVVar6->x;
  local_20 = pVVar6->y;
  local_1c = pVVar6->z;
  local_54.x = local_24 - local_48;
  local_54.y = local_20 - local_44;
  local_54.z = local_1c - local_40;
  pVVar6 = &local_54;
  __return_storage_ptr__ = &local_18;
  uVar18 = 0x472d11;
  pMVar5 = local_c;
  local_18.x = local_54.x;
  local_18.y = local_54.y;
  local_18.z = local_54.z;
  pVVar7 = Vector_Unrotate(__return_storage_ptr__,pVVar6,local_c);
  local_54.x = pVVar7->x;
  fVar17 = *(float *)&param_1[1].mat.field_0x24 * (float)param_2;
  local_54.y = pVVar7->y;
  local_54.z = pVVar7->z;
  pfVar11 = (float *)(in_EAX + 0x20);
  pVVar7 = &local_3c;
  *pfVar11 = *pfVar11 - fVar17;
  *(float *)(in_EAX + 0x24) = *(float *)(in_EAX + 0x24) - fVar17;
  *(float *)(in_EAX + 0x28) = *(float *)(in_EAX + 0x28) - fVar17;
  *(float *)(in_EAX + 0x2c) = *(float *)(in_EAX + 0x2c) + fVar17;
  *(float *)(in_EAX + 0x30) = *(float *)(in_EAX + 0x30) + fVar17;
  *(float *)(in_EAX + 0x34) = fVar17 + *(float *)(in_EAX + 0x34);
  fVar20 = 0.0;
  pfVar19 = &local_8;
  fVar17 = 8.40779e-45;
  pfVar14 = (float *)&stack0xfffffee0;
  for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pfVar14 = *pfVar11;
    pfVar11 = pfVar11 + 1;
    pfVar14 = pfVar14 + 1;
  }
  pVVar12 = &local_60;
  pfVar11 = (float *)&stack0xfffffec8;
  for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pfVar11 = pVVar12->x;
    pVVar12 = (VECTOR_3D *)&pVVar12->y;
    pfVar11 = pfVar11 + 1;
  }
  PVar1.v.y = (float)in_stack_fffffed8;
  auVar16 = in_stack_fffffec8._0_12_;
  PVar1.p.x = (float)auVar16._0_4_;
  PVar1.p.y = (float)auVar16._4_4_;
  PVar1.p.z = (float)auVar16._8_4_;
  PVar1.v.x = (float)in_stack_fffffec8._12_4_;
  PVar1.v.z = fVar17;
  BVar2.min.y = (float)uVar18;
  BVar2.min.x = in_stack_fffffee0;
  BVar2.min.z = (float)__return_storage_ptr__;
  BVar2.max.x = (float)pVVar6;
  BVar2.max.y = (float)pMVar5;
  BVar2.max.z = (float)pVVar8;
  iVar10 = PointBox(PVar1,BVar2,(float)param_4,pfVar19,pVVar7,fVar20);
  if (iVar10 == 0) {
    iVar10 = 0;
  }
  else {
    *(float *)((int)param_5 + 0x54) = local_3c.x;
    *(float *)((int)param_5 + 0x58) = local_3c.y;
    *(float *)((int)param_5 + 0x5c) = local_3c.z;
    VVar3.y = local_3c.y;
    VVar3.x = local_3c.x;
    VVar3.z = local_3c.z;
    pVVar8 = NegVector(&local_18,VVar3);
    (param_6->point).x = pVVar8->x;
    (param_6->point).y = pVVar8->y;
    (param_6->point).z = pVVar8->z;
    VVar4.y = local_30.y;
    VVar4.x = local_30.x;
    VVar4.z = local_30.z;
    pVVar8 = NegVector(&local_18,VVar4);
    *(float *)((int)param_5 + 0x60) = pVVar8->x;
    *(float *)((int)param_5 + 100) = pVVar8->y;
    *(float *)((int)param_5 + 0x68) = pVVar8->z;
    param_6->t = local_8;
    (param_6->vel).x = local_30.x;
    (param_6->vel).y = local_30.y;
    (param_6->vel).z = local_30.z;
    *(float *)((int)param_5 + 0x50) = local_8;
    param_6->collided = 1;
    *(undefined4 *)param_5 = 1;
    *(BOX_INFO **)((int)param_5 + 4) = param_1;
    param_6->obj = *(_OBJ76 **)(in_EAX + 0x1c);
    pEVar9 = ClassGetEuler((EULER *)local_e8,(_OBJ76 *)param_1);
    pfVar11 = (float *)((int)param_5 + 8);
    for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pfVar11 = pEVar9->mass;
      pEVar9 = (EULER *)&pEVar9->mass_inv;
      pfVar11 = pfVar11 + 1;
    }
    pEVar9 = ClassGetEuler((EULER *)local_e8,*(_OBJ76 **)(in_EAX + 0x1c));
    pEVar15 = &param_6->euler;
    for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1) {
      pEVar15->mass = pEVar9->mass;
      pEVar9 = (EULER *)&pEVar9->mass_inv;
      pEVar15 = (EULER *)&pEVar15->mass_inv;
    }
    pVVar8 = Vector_Rotate(&local_30,&local_3c,local_c);
    (param_6->normal).x = pVVar8->x;
    (param_6->normal).y = pVVar8->y;
    (param_6->normal).z = pVVar8->z;
    pVVar8 = NegVector(&local_30,*pVVar8);
    *(float *)((int)param_5 + 0x6c) = pVVar8->x;
    *(float *)((int)param_5 + 0x70) = pVVar8->y;
    *(float *)((int)param_5 + 0x74) = pVVar8->z;
    iVar10 = 1;
  }
  return iVar10;
}
