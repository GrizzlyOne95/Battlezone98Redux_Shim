/*
 * Entry: 00475be1
 * Name: PointBox
 * Namespace: Global
 * Signature: int PointBox(POINT_VEL param_1, BBOX param_2, float param_3, float * param_4, VECTOR_3D * param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
PointBox(POINT_VEL param_1,BBOX param_2,float param_3,float *param_4,VECTOR_3D *param_5,
        float param_6)

{
  int iVar1;
  int extraout_ECX;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar1 = IntersectSides(param_1.p.x,param_1.v.x,param_2.min.x - param_6,param_2.max.x + param_6,
                         &local_10,&local_14);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = IntersectSides(param_1.p.z,param_1.v.z,param_2.min.z - param_6,param_2.max.z + param_6,
                         &local_8,&local_c);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_10 < local_8) {
    local_10 = local_8;
  }
  if (local_c < local_14) {
    local_14 = local_c;
  }
  iVar1 = IntersectSides(param_1.p.y,param_1.v.y,param_2.min.y - param_6,param_2.max.y + param_6,
                         &local_8,&local_c);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = extraout_ECX;
  if (local_10 < local_8) {
    iVar1 = 2;
    local_10 = local_8;
  }
  if (local_c < local_14) {
    local_14 = local_c;
  }
  if (local_14 < local_10) {
    return 0;
  }
  if (local_14 < 0.0) {
    return 0;
  }
  if (param_3 < local_10) {
    return 0;
  }
  if (iVar1 == 0) {
    if (param_1.v.x <= 0.0) {
      local_20 = 1.0;
    }
    else {
      local_20 = -1.0;
    }
    local_1c = 0.0;
LAB_00475d8f:
    local_18 = 0.0;
  }
  else {
    if (iVar1 != 1) {
      if (iVar1 != 2) goto LAB_00475d95;
      local_20 = 0.0;
      if (param_1.v.y <= 0.0) {
        local_1c = 1.0;
      }
      else {
        local_1c = -1.0;
      }
      goto LAB_00475d8f;
    }
    local_20 = 0.0;
    local_1c = 0.0;
    if (param_1.v.z <= 0.0) {
      local_18 = 1.0;
    }
    else {
      local_18 = -1.0;
    }
  }
  param_2.max.x = local_20;
  param_2.max.y = local_1c;
  param_2.max.z = local_18;
LAB_00475d95:
  if ((local_10 < 0.0) &&
     (param_6 + 0.1 <
      (param_2.max.x * param_1.v.x + param_2.max.z * param_1.v.z + param_2.max.y * param_1.v.y) *
      local_10)) {
    return 0;
  }
  *param_4 = local_10;
  param_5->x = param_2.max.x;
  param_5->y = param_2.max.y;
  param_5->z = param_2.max.z;
  return 1;
}
