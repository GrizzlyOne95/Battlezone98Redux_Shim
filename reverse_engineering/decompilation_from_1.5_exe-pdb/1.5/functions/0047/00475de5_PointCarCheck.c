/*
 * Entry: 00475de5
 * Name: PointCarCheck
 * Namespace: Global
 * Signature: int PointCarCheck(POINT_VEL param_1, tagENTITY * param_2, float param_3, float * param_4, VECTOR_3D * param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
PointCarCheck(POINT_VEL param_1,tagENTITY *param_2,float param_3,float *param_4,VECTOR_3D *param_5,
             float param_6)

{
  POINT_VEL PVar1;
  BBOX BVar2;
  BBOX *pBVar3;
  MAT_3D *pMVar4;
  VECTOR_3D *pVVar5;
  VECTOR_3D *pVVar6;
  int iVar7;
  tagENTITY *unaff_EBX;
  float *pfVar8;
  undefined4 *puVar9;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar10;
  float *pfVar11;
  undefined4 *puVar12;
  undefined1 auVar13 [12];
  undefined1 in_stack_ffffff00 [20];
  float fVar14;
  undefined8 in_stack_ffffff18;
  undefined4 uVar15;
  VECTOR_3D *__return_storage_ptr__;
  MAT_3D local_b4;
  MAT_3D local_74;
  float local_34 [6];
  BBOX local_1c;
  
  pBVar3 = GetCarBBox(&local_1c,unaff_EBX);
  pfVar8 = local_34;
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar8 = (pBVar3->min).x;
    pBVar3 = (BBOX *)&(pBVar3->min).y;
    pfVar8 = pfVar8 + 1;
  }
  pMVar4 = Matrix_Inverse(&local_b4,unaff_EDI);
  pMVar10 = &local_74;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    pMVar10->right_x = pMVar4->right_x;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  Vector_Transform(&param_1.p,&param_1.p,1,&local_74);
  pMVar4 = &unaff_EBX->obj76->transform;
  pVVar6 = &param_1.v;
  __return_storage_ptr__ = &local_1c.max;
  uVar15 = 0x475e44;
  pVVar5 = Vector_Unrotate(__return_storage_ptr__,pVVar6,pMVar4);
  param_1.v.x = pVVar5->x;
  param_1.v.y = pVVar5->y;
  param_1.v.z = pVVar5->z;
  fVar14 = 8.40779e-45;
  pfVar8 = local_34;
  pfVar11 = (float *)&stack0xffffff18;
  pVVar5 = (VECTOR_3D *)param_4;
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar11 = *pfVar8;
    pfVar8 = pfVar8 + 1;
    pfVar11 = pfVar11 + 1;
  }
  puVar12 = (undefined4 *)&stack0xffffff00;
  puVar9 = (undefined4 *)register0x00000010;
  for (iVar7 = 6; puVar9 = puVar9 + 1, iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *puVar9;
    puVar12 = puVar12 + 1;
  }
  PVar1.v.z = fVar14;
  auVar13 = in_stack_ffffff00._0_12_;
  PVar1.p.x = (float)auVar13._0_4_;
  PVar1.p.y = (float)auVar13._4_4_;
  PVar1.p.z = (float)auVar13._8_4_;
  PVar1.v.x = (float)in_stack_ffffff00._12_4_;
  PVar1.v.y = (float)in_stack_ffffff00._16_4_;
  BVar2.min.z = (float)uVar15;
  BVar2.min.x = (float)(int)in_stack_ffffff18;
  BVar2.min.y = (float)(int)((ulonglong)in_stack_ffffff18 >> 0x20);
  BVar2.max.x = (float)__return_storage_ptr__;
  BVar2.max.y = (float)pVVar6;
  BVar2.max.z = (float)pMVar4;
  iVar7 = PointBox(PVar1,BVar2,(float)param_2,(float *)param_3,pVVar5,(float)param_5);
  if (iVar7 != 0) {
    pVVar6 = Vector_Rotate(&local_1c.max,(VECTOR_3D *)param_4,&unaff_EBX->obj76->transform);
    *param_4 = pVVar6->x;
    param_4[1] = pVVar6->y;
    param_4[2] = pVVar6->z;
  }
  return (uint)(iVar7 != 0);
}
