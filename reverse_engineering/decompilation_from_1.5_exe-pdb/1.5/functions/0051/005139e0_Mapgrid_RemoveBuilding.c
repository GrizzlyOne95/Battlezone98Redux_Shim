/*
 * Entry: 005139e0
 * Name: Mapgrid_RemoveBuilding
 * Namespace: Global
 * Signature: void Mapgrid_RemoveBuilding(tagBUILDING * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_RemoveBuilding(tagBUILDING *param_1,int param_2,int param_3)

{
  int iVar1;
  tagMAPGRID *ptVar2;
  int iVar3;
  tagBUILDING *ptVar4;
  
  if ((((param_2 < 0) || (mapsizex <= param_2)) || (param_3 < 0)) || (mapsizey <= param_3)) {
    tlog(1,"Mapgrid_RemoveBuilding: coordinate (%d,%d) out of range (0,0,%d,%d)");
  }
  else {
    iVar1 = param_1->team;
    iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0xfU)) >> 4;
    ptVar2 = mapgrid[(int)(param_3 + (param_3 >> 0x1f & 0xfU)) >> 4];
    if (param_1->gridprev == (tagBUILDING *)0x0) {
      ptVar2[iVar3].firstbuilding[iVar1] = param_1->gridnext;
    }
    else {
      param_1->gridprev->gridnext = param_1->gridnext;
    }
    if (param_1->gridnext != (tagBUILDING *)0x0) {
      param_1->gridnext->gridprev = param_1->gridprev;
    }
    param_1->gridprev = (tagBUILDING *)0x0;
    param_1->gridnext = (tagBUILDING *)0x0;
    ptVar2[iVar3].nrbuildings[iVar1] = ptVar2[iVar3].nrbuildings[iVar1] + -1;
    tlog_gdm("Mapgrid_RemoveBuilding (%08x,%d) at (%d,%d)\n");
    for (ptVar4 = ptVar2[iVar3].firstbuilding[iVar1]; ptVar4 != (tagBUILDING *)0x0;
        ptVar4 = ptVar4->gridnext) {
      tlog_gdm(" grid has %08x\n");
    }
  }
  return;
}
