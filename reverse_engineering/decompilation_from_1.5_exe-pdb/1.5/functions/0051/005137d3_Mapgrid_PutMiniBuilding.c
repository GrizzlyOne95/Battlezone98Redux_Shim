/*
 * Entry: 005137d3
 * Name: Mapgrid_PutMiniBuilding
 * Namespace: Global
 * Signature: void Mapgrid_PutMiniBuilding(tagMINIBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_PutMiniBuilding(tagMINIBUILDING *param_1)

{
  int iVar1;
  int iVar2;
  tagMAPGRID *ptVar3;
  tagMINIBUILDING *ptVar4;
  
  iVar1 = param_1->tiley;
  iVar2 = param_1->tilex;
  if ((((iVar2 < 0) || (mapsizex <= iVar2)) || (iVar1 < 0)) || (mapsizey <= iVar1)) {
    tlog(1,"Mapgrid_PutMiniBuilding: coordinate (%d,%d) out of range (0,0,%d,%d)");
  }
  else {
    ptVar3 = mapgrid[(int)(iVar1 + (iVar1 >> 0x1f & 0xfU)) >> 4];
    ptVar4 = ptVar3[(int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4].firstminibuilding;
    param_1->gridnext = ptVar4;
    if (ptVar4 != (tagMINIBUILDING *)0x0) {
      ptVar4->gridprev = param_1;
    }
    param_1->gridprev = (tagMINIBUILDING *)0x0;
    ptVar3[(int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4].firstminibuilding = param_1;
  }
  return;
}
