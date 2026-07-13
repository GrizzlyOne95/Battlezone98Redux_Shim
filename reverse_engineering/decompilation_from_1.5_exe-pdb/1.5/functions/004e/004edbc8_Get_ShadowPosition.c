/*
 * Entry: 004edbc8
 * Name: Get_ShadowPosition
 * Namespace: Global
 * Signature: int Get_ShadowPosition(VECTOR_3D * param_1, VECTOR_3D param_2, VECTOR_3D param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Get_ShadowPosition(VECTOR_3D *param_1,VECTOR_3D param_2,VECTOR_3D param_3)

{
  float *unaff_EBX;
  float *pfVar1;
  float fVar2;
  float fVar3;
  int local_8;
  
  fVar2 = Terrain_FindFloor((double)(float)param_1,(double)param_2.y);
  fVar3 = Terrain_FindFloor((double)param_2.z,(double)param_3.y);
  if ((fVar2 < param_2.x) && (param_3.x < fVar3)) {
    local_8 = 0;
    do {
      fVar2 = (param_2.z + (float)param_1) * 0.5;
      *unaff_EBX = fVar2;
      unaff_EBX[1] = (param_3.x + param_2.x) * 0.5;
      fVar3 = (param_3.y + param_2.y) * 0.5;
      unaff_EBX[2] = fVar3;
      fVar2 = Terrain_FindFloor((double)fVar2,(double)fVar3);
      if (ABS(fVar2 - unaff_EBX[1]) < 0.2) {
        return 1;
      }
      pfVar1 = (float *)&param_1;
      if (0.0 <= fVar2 - unaff_EBX[1]) {
        pfVar1 = &param_2.z;
      }
      local_8 = local_8 + 1;
      *pfVar1 = (float)*unaff_EBX;
      pfVar1[1] = (float)unaff_EBX[1];
      pfVar1[2] = (float)unaff_EBX[2];
    } while (local_8 < 10);
  }
  return 0;
}
