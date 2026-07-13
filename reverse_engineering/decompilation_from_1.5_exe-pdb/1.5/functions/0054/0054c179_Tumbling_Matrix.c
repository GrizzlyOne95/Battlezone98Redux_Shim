/*
 * Entry: 0054c179
 * Name: Tumbling_Matrix
 * Namespace: Global
 * Signature: MAT_3D * Tumbling_Matrix(MAT_3D * __return_storage_ptr__, float param_1, float param_2, float param_3, float param_4, float param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl
Tumbling_Matrix(MAT_3D *__return_storage_ptr__,float param_1,float param_2,float param_3,
               float param_4,float param_5)

{
  float fVar1;
  float fVar2;
  MAT_3D *pMVar3;
  int iVar4;
  MAT_3D *pMVar5;
  SINCOS SVar6;
  float fVar7;
  float fVar8;
  MAT_3D local_60;
  SINCOS local_20;
  SINCOS local_18;
  float local_10;
  float local_c;
  float local_8;
  
  Rand_Counter = Rand_Counter + 1U & 0xff;
  local_18 = SinCos(Pseudo_Rand_Number[Rand_Counter] * param_5);
  Rand_Counter = Rand_Counter + 1U & 0xff;
  SVar6 = SinCos(Pseudo_Rand_Number[Rand_Counter] * param_5);
  local_10 = local_20.Cos * local_18.Cos;
  local_20.Sin = SVar6.Sin;
  local_c = local_20.Sin * local_18.Cos;
  local_20.Cos = SVar6.Cos;
  local_8 = local_18.Sin * local_20.Cos;
  fVar8 = local_18.Sin * local_20.Sin;
  fVar1 = local_8;
  fVar7 = local_18.Cos;
  if (0.0009999999 <= ABS(param_3 - 1.0)) {
    fVar7 = 1.0 / SQRT(param_4 * param_4 + param_2 * param_2);
    fVar1 = fVar7 * param_2 * param_3;
    fVar2 = fVar7 * param_3 * param_4;
    fVar7 = fVar2 * fVar8;
    fVar8 = param_4 * local_10 + fVar2 * local_8 + fVar1 * fVar8 + local_c * param_2;
    fVar1 = (fVar1 * local_8 + (local_10 * param_2 - local_c * param_4)) - fVar7;
    fVar7 = local_18.Cos * param_3 - SQRT(1.0 - param_3 * param_3) * local_18.Sin;
  }
  local_20 = SVar6;
  pMVar3 = Build_Axis_Rotation_Matrix(&local_60,param_1,fVar1,fVar7,fVar8);
  pMVar5 = __return_storage_ptr__;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  return __return_storage_ptr__;
}
