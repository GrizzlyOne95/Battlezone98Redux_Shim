/*
 * Entry: 0054c587
 * Name: Matrix_Inverse
 * Namespace: Global
 * Signature: MAT_3D * Matrix_Inverse(MAT_3D * __return_storage_ptr__, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl Matrix_Inverse(MAT_3D *__return_storage_ptr__,MAT_3D *param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float *in_ECX;
  float *pfVar4;
  int iVar5;
  float10 in_ST0;
  float10 in_ST1;
  float10 in_ST2;
  float10 fVar6;
  float10 in_ST3;
  float10 fVar7;
  
  fVar2 = in_ECX[3];
  fVar3 = in_ECX[6];
  __return_storage_ptr__->right_x = *in_ECX;
  __return_storage_ptr__->right_y = fVar2;
  __return_storage_ptr__->right_z = fVar3;
  fVar2 = in_ECX[4];
  fVar3 = in_ECX[7];
  __return_storage_ptr__->up_x = in_ECX[1];
  __return_storage_ptr__->up_y = fVar2;
  __return_storage_ptr__->up_z = fVar3;
  fVar2 = in_ECX[5];
  fVar3 = in_ECX[8];
  __return_storage_ptr__->front_x = in_ECX[2];
  __return_storage_ptr__->front_y = fVar2;
  __return_storage_ptr__->front_z = fVar3;
  iVar5 = 3;
  pfVar4 = in_ECX;
  do {
    fVar7 = in_ST3;
    fVar6 = in_ST2;
    in_ST3 = in_ST1;
    in_ST2 = in_ST0;
    pfVar1 = pfVar4 + 2;
    in_ST0 = (float10)*pfVar4 * (float10)*(double *)(in_ECX + 10) +
             (float10)pfVar4[1] * (float10)*(double *)(in_ECX + 0xc);
    pfVar4 = pfVar4 + 3;
    iVar5 = iVar5 + -1;
    in_ST1 = (float10)*pfVar1 * (float10)*(double *)(in_ECX + 0xe);
  } while (iVar5 != 0);
  __return_storage_ptr__->posit_z =
       (double)-(in_ST0 + (float10)*pfVar1 * (float10)*(double *)(in_ECX + 0xe));
  __return_storage_ptr__->posit_x = (double)-(fVar7 + fVar6);
  __return_storage_ptr__->posit_y = (double)-(in_ST2 + in_ST3);
  return __return_storage_ptr__;
}
