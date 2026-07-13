/*
 * Entry: 004e32dc
 * Name: NetUtil_ReduceVector
 * Namespace: Global
 * Signature: REDUCED_VEC NetUtil_ReduceVector(VECTOR_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

REDUCED_VEC __cdecl NetUtil_ReduceVector(VECTOR_3D param_1)

{
  ushort uVar1;
  ushort extraout_DX;
  REDUCED_VEC RVar2;
  float in_stack_00000010;
  
  uVar1 = NetUtil_ReduceFloat(param_1.y);
  *(ushort *)param_1.x = uVar1;
  uVar1 = NetUtil_ReduceFloat(param_1.z);
  *(ushort *)((int)param_1.x + 2) = uVar1;
  uVar1 = NetUtil_ReduceFloat(in_stack_00000010);
  *(ushort *)((int)param_1.x + 4) = uVar1;
  RVar2.z = extraout_DX;
  RVar2._0_4_ = param_1.x;
  return RVar2;
}
