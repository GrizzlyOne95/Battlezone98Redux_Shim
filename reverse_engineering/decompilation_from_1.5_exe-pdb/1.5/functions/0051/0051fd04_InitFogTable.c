/*
 * Entry: 0051fd04
 * Name: InitFogTable
 * Namespace: Global
 * Signature: void InitFogTable(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitFogTable(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  uint extraout_EAX;
  int iVar6;
  int local_8;
  
  fVar5 = TerrainView.Fog_Break;
  iVar4 = useD3D;
  iVar6 = 0;
  if (useD3D == 0) {
    if (FogDirection == 0) {
      Light_Terrain_Vertex_List = inverseLighting;
      InitFogTableInverted();
      return;
    }
    Light_Terrain_Vertex_List = normalLighting;
  }
  else {
    Light_Terrain_Vertex_List = FogAndLumaLighting;
  }
  local_8 = 0;
  do {
    if (local_8 < TerrainView.Fog_End) {
      if (TerrainView.Fog_Start < local_8) {
        fVar2 = ((float)local_8 - (float)TerrainView.Fog_Start) * TerrainView.Fog_InvWidth;
        fVar1 = fVar5 / (1.0 - fVar5);
        fVar3 = 1.0 / fVar1;
        if (fVar5 <= fVar2) {
          fVar3 = fVar2 - (1.0 - fVar3);
          fVar2 = fVar1;
        }
        fVar2 = fVar2 * fVar3;
      }
      else {
        fVar2 = 0.0;
      }
      fogTable[local_8] = fVar2;
    }
    else {
      fogTable[local_8] = 1.0;
    }
    local_8 = local_8 + 1;
  } while (local_8 < 0x1000);
  if (iVar4 != 0) {
    do {
      _ftol2_sse();
      *(uint *)((int)fogTable256 + iVar6) = extraout_EAX & 0xff;
      iVar6 = iVar6 + 4;
    } while (iVar6 < 0x4000);
  }
  return;
}
