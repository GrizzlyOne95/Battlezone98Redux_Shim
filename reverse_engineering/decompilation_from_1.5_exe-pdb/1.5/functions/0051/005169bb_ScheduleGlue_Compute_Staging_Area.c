/*
 * Entry: 005169bb
 * Name: ScheduleGlue_Compute_Staging_Area
 * Namespace: Global
 * Signature: void ScheduleGlue_Compute_Staging_Area(SquadUnitInfo * param_1, int param_2, float param_3, float param_4, VECTOR_3D * param_5, float * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
ScheduleGlue_Compute_Staging_Area
          (SquadUnitInfo *param_1,int param_2,float param_3,float param_4,VECTOR_3D *param_5,
          float *param_6)

{
  VECTOR_3D VVar1;
  float *pfVar2;
  VECTOR_3D *pVVar3;
  float fVar4;
  VECTOR_3D local_34;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  fVar4 = 0.0;
  local_1c = 0.0;
  local_18 = 0.0;
  local_14 = 0.0;
  local_10 = 0.0;
  local_c = 0.0;
  local_8 = 0;
  if (0 < param_2) {
    do {
      if (param_1[local_8].send != false) {
        pfVar2 = (float *)(**(code **)((param_1[local_8].craft)->_padding_ + 0xc))();
        local_28 = *pfVar2;
        local_24 = pfVar2[1];
        local_20 = pfVar2[2];
        local_34.x = local_28 + local_1c;
        local_c = (float)((int)local_c + 1);
        local_34.y = local_24 + local_18;
        local_34.z = local_20 + local_14;
        local_1c = local_34.x;
        local_18 = local_34.y;
        local_14 = local_34.z;
      }
      fVar4 = 0.0;
      local_8 = local_8 + 1;
    } while (local_8 < param_2);
    if (1 < (int)local_c) {
      VVar1.y = local_18;
      VVar1.x = local_1c;
      VVar1.z = local_14;
      pVVar3 = ScaleVector(&local_34,1.0 / (float)(int)local_c,VVar1);
      local_c = 0.0;
      param_5->x = pVVar3->x;
      param_5->y = pVVar3->y;
      local_8 = 0;
      param_5->z = pVVar3->z;
      do {
        if (param_1[local_8].send != false) {
          pfVar2 = (float *)(**(code **)((param_1[local_8].craft)->_padding_ + 0xc))();
          local_28 = *pfVar2;
          local_24 = pfVar2[1];
          local_20 = pfVar2[2];
          local_34.x = param_5->x;
          local_34.y = param_5->y;
          local_34.z = param_5->z;
          if (ABS(local_10) <= 8.0) {
            local_10 = 8.0;
          }
          fVar4 = (ABS(local_34.z - local_20) + ABS(local_34.x - local_28)) / local_10;
          if (local_c < fVar4) {
            local_c = fVar4;
          }
        }
        local_8 = local_8 + 1;
      } while (local_8 < param_2);
      fVar4 = Get_Time();
      fVar4 = fVar4 + local_c;
    }
  }
  *param_6 = fVar4;
  return;
}
