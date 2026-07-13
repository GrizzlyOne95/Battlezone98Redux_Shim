/*
 * Entry: 0052163d
 * Name: GetGridXYZ
 * Namespace: Global
 * Signature: void GetGridXYZ(VECTOR_3D * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetGridXYZ(VECTOR_3D *param_1,float param_2,float param_3)

{
  ushort *puVar1;
  float *pfVar2;
  float *pfVar3;
  int local_1c;
  uint uStack_18;
  int local_14;
  int local_c;
  int local_8;
  
  local_c = 3;
  local_1c = SUB84((double)(param_2 * Terrain.Grid_Scale + 0.5 + (float)Float2Int),0);
  local_14 = SUB84((double)((float)Float2Int + Terrain.Grid_Scale * param_3 + 0.5),0);
  param_3 = (float)(local_14 + -1);
  pfVar2 = &param_1->y;
  do {
    local_8 = 3;
    pfVar3 = pfVar2 + 9;
    param_2 = (float)(local_1c + -1);
    do {
      ((VECTOR_3D *)(pfVar2 + -1))->x = (float)(int)param_2 * Terrain.Grid_Size;
      pfVar2[1] = (float)(int)param_3 * Terrain.Grid_Size;
      puVar1 = GetZonePtr((int)param_2,(int)param_3);
      uStack_18 = (uint)(*puVar1 & 0xfff);
      *pfVar2 = (float)uStack_18 * 0.1;
      pfVar2 = pfVar2 + 3;
      param_2 = (float)((int)param_2 + 1);
      local_8 = local_8 + -1;
    } while (local_8 != 0);
    param_3 = (float)((int)param_3 + 1);
    local_c = local_c + -1;
    pfVar2 = pfVar3;
  } while (local_c != 0);
  return;
}
