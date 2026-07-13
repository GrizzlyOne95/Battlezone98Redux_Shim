/*
 * Entry: 0052158d
 * Name: GetTileXYZ
 * Namespace: Global
 * Signature: void GetTileXYZ(VECTOR_3D * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetTileXYZ(VECTOR_3D *param_1,float param_2,float param_3)

{
  ushort *puVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float local_1c;
  uint local_14;
  uint uStack_10;
  int local_8;
  
  local_8 = 3;
  local_1c = (float)(SUB84((double)(param_2 * Terrain.Grid_Scale + (float)Float2Int),0) & 0xfffffffe
                    );
  local_14 = SUB84((double)(Terrain.Grid_Scale * param_3 + (float)Float2Int),0);
  param_3 = (float)(local_14 & 0xfffffffe);
  pfVar3 = &param_1->y;
  do {
    param_2 = local_1c;
    iVar2 = 3;
    pfVar4 = pfVar3 + 9;
    do {
      ((VECTOR_3D *)(pfVar3 + -1))->x = (float)(int)param_2 * Terrain.Grid_Size;
      pfVar3[1] = (float)(int)param_3 * Terrain.Grid_Size;
      puVar1 = GetZonePtr((int)param_2,(int)param_3);
      uStack_10 = (uint)(*puVar1 & 0xfff);
      *pfVar3 = (float)uStack_10 * 0.1;
      pfVar3 = pfVar3 + 3;
      param_2 = (float)((int)param_2 + 1);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    param_3 = (float)((int)param_3 + 1);
    local_8 = local_8 + -1;
    pfVar3 = pfVar4;
  } while (local_8 != 0);
  return;
}
