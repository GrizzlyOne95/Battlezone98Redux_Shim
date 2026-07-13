/*
 * Entry: 00473bc5
 * Name: preclsn
 * Namespace: Global
 * Signature: int preclsn(POINT_VEL param_1, POINT_VEL param_2, float param_3, float param_4, float * param_5, VECTOR_3D * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
preclsn(POINT_VEL param_1,POINT_VEL param_2,float param_3,float param_4,float *param_5,
       VECTOR_3D *param_6)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  int iVar3;
  VECTOR_3D *pVVar4;
  VECTOR_3D local_2c;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar3 = ZeroVector(param_1.v);
  if ((iVar3 == 0) || (iVar3 = ZeroVector(param_2.v), iVar3 == 0)) {
    local_20 = param_2.p.x - param_1.p.x;
    local_1c = param_2.p.y - param_1.p.y;
    local_18 = param_2.p.z - param_1.p.z;
    local_2c.x = param_1.v.x - param_2.v.x;
    local_2c.y = param_1.v.y - param_2.v.y;
    local_2c.z = param_1.v.z - param_2.v.z;
    local_8 = local_2c.x * local_2c.x + local_2c.y * local_2c.y + local_2c.z * local_2c.z;
    if ((local_8 < 0.0001) ||
       (local_8 = (local_2c.x * local_20 + local_2c.y * local_1c + local_2c.z * local_18) / local_8,
       param_4 < local_8)) {
      local_8 = param_4;
    }
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    if (0.0 < local_8) {
      VVar1.y = local_1c;
      VVar1.x = local_20;
      VVar1.z = local_18;
      VVar2.y = local_2c.y;
      VVar2.x = local_2c.x;
      VVar2.z = local_2c.z;
      pVVar4 = AddMultVectors(&local_2c,VVar1,-local_8,VVar2);
      local_14 = pVVar4->x;
      local_10 = pVVar4->y;
      local_c = pVVar4->z;
    }
    else {
      local_8 = 0.0;
    }
    *param_5 = local_8;
    if (local_14 * local_14 + local_c * local_c + local_10 * local_10 <= param_3 * param_3) {
      param_6->x = local_14;
      param_6->y = local_10;
      param_6->z = local_c;
      return 1;
    }
  }
  return 0;
}
