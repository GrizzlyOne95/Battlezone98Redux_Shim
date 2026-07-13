/*
 * Entry: 0048570b
 * Name: ConstructionRig::SetConstructionMatrix
 * Namespace: ConstructionRig
 * Signature: void SetConstructionMatrix(ConstructionRig * this, VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ConstructionRig::SetConstructionMatrix(ConstructionRig *this,VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  VECTOR_3D_LONG VVar1;
  MAT_3D *pMVar2;
  int iVar3;
  VECTOR_3D *unaff_ESI;
  float *pfVar4;
  VECTOR_3D *unaff_EDI;
  MAT_3D local_a0;
  float local_60 [16];
  float local_20;
  float local_1c;
  float local_18;
  ConstructionRig *local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_20 = param_1->x;
  local_10 = param_1->x;
  local_c = param_1->y;
  local_8 = param_1->z;
  VVar1.y = (double)local_c;
  VVar1.x = (double)local_10;
  VVar1.z._0_4_ = SUB84((double)local_8,0);
  VVar1.z._4_4_ = (int)((ulonglong)(double)local_8 >> 0x20);
  local_14 = this;
  local_1c = FindFloor(VVar1);
  local_18 = param_1->z;
  local_10 = param_2->x;
  local_c = 0.0;
  local_8 = param_2->z;
  pMVar2 = Build_Directinal_Matrix(&local_a0,unaff_EDI,unaff_ESI);
  pfVar4 = local_60;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pfVar4 = pfVar4 + 1;
  }
  pfVar4 = local_60;
  pMVar2 = &local_14->dropMat;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar2->right_x = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  return;
}
