/*
 * Entry: 0040fac8
 * Name: CellTeam
 * Namespace: Global
 * Signature: ushort CellTeam(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl CellTeam(float param_1,float param_2)

{
  float fVar1;
  ushort uVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar3;
  
  fVar1 = param_1 * Terrain.Grid_Scale;
  floor((double)(Terrain.Grid_Scale * param_2));
  _ftol2_sse();
  iVar3 = extraout_EAX;
  floor((double)fVar1);
  _ftol2_sse();
  uVar2 = CellTeam(extraout_EAX_00,iVar3);
  return uVar2;
}
