/*
 * Entry: 005138e0
 * Name: Mapgrid_PutBuilding
 * Namespace: Global
 * Signature: void Mapgrid_PutBuilding(tagBUILDING * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_PutBuilding(tagBUILDING *param_1,int param_2,int param_3)

{
  int *piVar1;
  tagBUILDING **pptVar2;
  int iVar3;
  tagMAPGRID *ptVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  tagBUILDING *ptVar8;
  
  if ((((param_2 < 0) || (mapsizex <= param_2)) || (param_3 < 0)) || (mapsizey <= param_3)) {
    tlog(1,"Mapgrid_PutBuildingBegunConstruction: coordinate (%d,%d) out of range (0,0,%d,%d)");
  }
  else {
    uVar7 = *(uint *)&param_1->buildingtype->field_0x24;
    uVar6 = uVar7 >> 0x12 & 0xf;
    if ((uint)maxbuildingxsize <= uVar6) {
      maxbuildingxsize = uVar6;
    }
    uVar7 = uVar7 >> 0x16 & 0xf;
    if ((uint)maxbuildingysize <= uVar7) {
      maxbuildingysize = uVar7;
    }
    iVar3 = param_1->team;
    iVar5 = (int)(param_2 + (param_2 >> 0x1f & 0xfU)) >> 4;
    ptVar4 = mapgrid[(int)(param_3 + (param_3 >> 0x1f & 0xfU)) >> 4];
    pptVar2 = ptVar4[iVar5].firstbuilding + iVar3;
    ptVar8 = *pptVar2;
    if (ptVar8 != (tagBUILDING *)0x0) {
      ptVar8->gridprev = param_1;
    }
    param_1->gridprev = (tagBUILDING *)0x0;
    param_1->gridnext = ptVar8;
    piVar1 = ptVar4[iVar5].nrbuildings + iVar3;
    *piVar1 = *piVar1 + 1;
    *pptVar2 = param_1;
    tlog_gdm("Mapgrid_PutBuildingBegunConstruction (%08x,%d) at (%d,%d)\n");
    for (ptVar8 = *pptVar2; ptVar8 != (tagBUILDING *)0x0; ptVar8 = ptVar8->gridnext) {
      tlog_gdm(" grid has %08x\n");
    }
  }
  return;
}
