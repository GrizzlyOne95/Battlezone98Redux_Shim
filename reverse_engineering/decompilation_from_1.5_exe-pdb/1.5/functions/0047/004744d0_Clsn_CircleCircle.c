/*
 * Entry: 004744d0
 * Name: Clsn_CircleCircle
 * Namespace: Global
 * Signature: int Clsn_CircleCircle(CIRCLE param_1, CIRCLE param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Clsn_CircleCircle(CIRCLE param_1,CIRCLE param_2)

{
  float fVar1;
  float fVar2;
  float in_ECX;
  VECTOR_2D VVar3;
  undefined4 local_c;
  undefined4 local_8;
  
  VVar3 = Vec2D_Subtract(param_2.origin,param_1.origin);
  local_c = VVar3.x;
  local_8 = VVar3.z;
  fVar2 = local_8 * local_8 + in_ECX * local_c;
  fVar1 = (param_2.radius + param_1.radius) * (param_2.radius + param_1.radius);
  if (fVar2 < fVar1 != (fVar2 == fVar1)) {
    return 1;
  }
  return 0;
}
