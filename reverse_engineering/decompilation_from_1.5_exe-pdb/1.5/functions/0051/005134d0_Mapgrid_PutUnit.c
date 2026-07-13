/*
 * Entry: 005134d0
 * Name: Mapgrid_PutUnit
 * Namespace: Global
 * Signature: void Mapgrid_PutUnit(tagUNIT * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_PutUnit(tagUNIT *param_1,int param_2,int param_3)

{
  int *piVar1;
  tagUNIT **pptVar2;
  char cVar3;
  tagMAPGRID *ptVar4;
  tagUNIT *ptVar5;
  int iVar6;
  
  if ((((-1 < param_2) && (param_2 < mapsizex)) && (-1 < param_3)) && (param_3 < mapsizey)) {
    iVar6 = (int)(param_2 + (param_2 >> 0x1f & 0xfU)) >> 4;
    ptVar4 = mapgrid[(int)(param_3 + (param_3 >> 0x1f & 0xfU)) >> 4];
    cVar3 = param_1->team;
    pptVar2 = ptVar4[iVar6].firstunit + cVar3;
    ptVar5 = *pptVar2;
    if (ptVar5 != (tagUNIT *)0x0) {
      ptVar5->gridprev = param_1;
    }
    param_1->gridprev = (tagUNIT *)0x0;
    param_1->gridnext = ptVar5;
    piVar1 = ptVar4[iVar6].nrunits + cVar3;
    *piVar1 = *piVar1 + 1;
    *pptVar2 = param_1;
    return;
  }
  tlog(1,"Mapgrid_PutPart: coordinate (%d,%d) out of range (0,0,%d,%d)");
  return;
}
