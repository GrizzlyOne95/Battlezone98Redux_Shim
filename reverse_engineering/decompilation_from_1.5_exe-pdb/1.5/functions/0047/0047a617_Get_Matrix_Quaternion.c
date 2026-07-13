/*
 * Entry: 0047a617
 * Name: Get_Matrix_Quaternion
 * Namespace: Global
 * Signature: QUAT * Get_Matrix_Quaternion(QUAT * __return_storage_ptr__, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

QUAT * __cdecl Get_Matrix_Quaternion(QUAT *__return_storage_ptr__,MAT_3D *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  QUAT *pQVar4;
  int iVar5;
  float *in_EDX;
  MAT_3D *pMVar6;
  MAT_3D *unaff_EDI;
  float *pfVar7;
  float local_54 [6];
  float local_3c;
  float local_34;
  QUAT local_14;
  
  fVar1 = in_EDX[8];
  fVar2 = in_EDX[6];
  pMVar6 = &Identity_Matrix;
  pfVar7 = local_54;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar7 = pMVar6->right_x;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
    pfVar7 = pfVar7 + 1;
  }
  fVar3 = fVar1 * fVar1 + fVar2 * fVar2;
  if (0.001 <= fVar3) {
    local_3c = 1.0 / SQRT(fVar3);
    local_54[0] = local_3c * fVar1;
    local_3c = local_3c * fVar2;
  }
  else {
    local_54[0] = *in_EDX;
    local_3c = in_EDX[2];
  }
  local_54[2] = -local_3c;
  local_34 = local_54[0];
  pQVar4 = Matrix_to_Quaternion(&local_14,unaff_EDI);
  (__return_storage_ptr__->n).x = (pQVar4->n).x;
  (__return_storage_ptr__->n).y = (pQVar4->n).y;
  (__return_storage_ptr__->n).z = (pQVar4->n).z;
  __return_storage_ptr__->w = pQVar4->w;
  return __return_storage_ptr__;
}
