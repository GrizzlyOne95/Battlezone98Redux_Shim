/*
 * Entry: 0051384f
 * Name: Mapgrid_RemoveMiniBuilding
 * Namespace: Global
 * Signature: void Mapgrid_RemoveMiniBuilding(tagMINIBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_RemoveMiniBuilding(tagMINIBUILDING *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1->tiley;
  iVar2 = param_1->tilex;
  if ((((iVar2 < 0) || (mapsizex <= iVar2)) || (iVar1 < 0)) || (mapsizey <= iVar1)) {
    tlog(1,"Mapgrid_RemoveMiniBuilding: coordinate (%d,%d) out of range (0,0,%d,%d)");
  }
  else {
    if (param_1->gridprev == (tagMINIBUILDING *)0x0) {
      mapgrid[(int)(iVar1 + (iVar1 >> 0x1f & 0xfU)) >> 4]
      [(int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4].firstminibuilding = param_1->gridnext;
    }
    else {
      param_1->gridprev->gridnext = param_1->gridnext;
    }
    if (param_1->gridnext != (tagMINIBUILDING *)0x0) {
      param_1->gridnext->gridprev = param_1->gridprev;
    }
    param_1->gridprev = (tagMINIBUILDING *)0x0;
    param_1->gridnext = (tagMINIBUILDING *)0x0;
  }
  return;
}
