/*
 * Entry: 00522eab
 * Name: Terrain_Create
 * Namespace: Global
 * Signature: int Terrain_Create(long param_1, long param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Terrain_Create(long param_1,long param_2,float param_3)

{
  int iVar1;
  float10 fVar2;
  
  Terrain.Grid_Size = 10.0;
  Terrain.Shade_Type = param_1;
  Terrain.Grid_Scale = 0.1;
  ReadTerrainIni();
  Init_Page_Tbl();
  PrecomputeIllumination();
  PrecomputeCoplanarFlags();
  Terrain_Init_PathPlan();
  InitFogTable();
  SetTerrainPrefs((uint)(UserProfilePtr->graphicDetail).terrain);
  param_1 = 0;
  do {
    iVar1 = param_1 + 1;
    fVar2 = (float10)fsin((float10)param_1 * (float10)0.049087387);
    WaveTable[param_1] = (float)fVar2;
    param_1 = iVar1;
  } while (iVar1 < 0x80);
  return 1;
}
