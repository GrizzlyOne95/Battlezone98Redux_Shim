/*
 * Entry: 0051fc87
 * Name: InitFogTableInverted
 * Namespace: Global
 * Signature: void InitFogTableInverted(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitFogTableInverted(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int local_8;
  
  fVar4 = TerrainView.Fog_Break;
  local_8 = 0;
  do {
    if (local_8 < TerrainView.Fog_End) {
      if (TerrainView.Fog_Start < local_8) {
        fVar2 = ((float)local_8 - (float)TerrainView.Fog_Start) * TerrainView.Fog_InvWidth;
        fVar1 = fVar4 / (1.0 - fVar4);
        fVar3 = 1.0 / fVar1;
        if (fVar4 <= fVar2) {
          fVar3 = fVar2 - (1.0 - fVar3);
          fVar2 = fVar1;
        }
        fVar1 = 1.0 - fVar2 * fVar3;
        goto LAB_0051fceb;
      }
      fogTable[local_8] = 1.0;
    }
    else {
      fVar1 = 0.0;
LAB_0051fceb:
      fogTable[local_8] = fVar1;
    }
    local_8 = local_8 + 1;
    if (0xfff < local_8) {
      return;
    }
  } while( true );
}
