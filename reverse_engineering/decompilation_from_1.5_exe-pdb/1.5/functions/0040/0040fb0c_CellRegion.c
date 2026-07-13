/*
 * Entry: 0040fb0c
 * Name: CellRegion
 * Namespace: Global
 * Signature: uchar CellRegion(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl CellRegion(float param_1,float param_2)

{
  float fVar1;
  uchar uVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar3;
  
  fVar1 = param_1 * Terrain.Grid_Scale;
  floor((double)(Terrain.Grid_Scale * param_2));
  _ftol2_sse();
  iVar3 = extraout_EAX;
  floor((double)fVar1);
  _ftol2_sse();
  uVar2 = CellRegion(extraout_EAX_00,iVar3);
  return uVar2;
}
