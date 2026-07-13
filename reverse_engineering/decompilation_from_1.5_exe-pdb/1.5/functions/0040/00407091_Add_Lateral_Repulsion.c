/*
 * Entry: 00407091
 * Name: Add_Lateral_Repulsion
 * Namespace: Global
 * Signature: int Add_Lateral_Repulsion(VECTOR_3D param_1, VECTOR_3D param_2, VECTOR_3D param_3, float param_4, float param_5, VECTOR_3D * param_6, float param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Add_Lateral_Repulsion
          (VECTOR_3D param_1,VECTOR_3D param_2,VECTOR_3D param_3,float param_4,float param_5,
          VECTOR_3D *param_6,float param_7,int param_8)

{
  float fVar1;
  float fVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  float local_18;
  float local_10;
  float local_c;
  float local_8;
  
  local_24.y = 0.0;
  local_24.x = param_3.z;
  local_24.z = -param_3.x;
  local_18 = param_1.x - param_2.x;
  local_10 = param_1.z - param_2.z;
  local_30.z = param_2.z - param_1.z;
  fVar2 = SQRT(local_24.z * local_24.z + param_3.z * param_3.z);
  if (0.0001 <= fVar2) {
    fVar2 = ((param_2.x - param_1.x) * param_3.z + local_30.z * local_24.z) / fVar2;
    fVar1 = (param_3.y * 0.0 + (param_2.x - param_1.x) * param_3.x + local_30.z * param_3.z) /
            SQRT(param_3.z * param_3.z + param_3.y * param_3.y + param_3.x * param_3.x);
    local_c = LATERAL_DANGER_WIDTH * param_7;
    if ((((ABS(fVar2) < local_c != (ABS(fVar2) == local_c)) && (0.0 < fVar1)) &&
        (fVar1 <= COLLISION_LOOK_AHEAD_TIME * param_4)) && (0.0 < param_4)) {
      local_8 = local_18 * local_18 + local_10 * local_10;
      if (fVar2 <= 0.0) {
        local_c = (local_c + fVar2) / local_c;
      }
      else {
        local_c = -((local_c - fVar2) / local_c);
      }
      local_c = local_c * LATERAL_AVOIDANCE_MULTIPLIER;
      pVVar3 = Normalize_Vector(&local_30,&local_24);
      if (local_8 <= param_5 * param_5) {
        pVVar3 = AddMultVectors(&local_30,*param_6,local_c,*pVVar3);
        param_6->x = pVVar3->x;
        param_6->y = pVVar3->y;
        param_6->z = pVVar3->z;
      }
      return 1;
    }
  }
  return 0;
}
