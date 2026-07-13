/*
 * Entry: 00513559
 * Name: Mapgrid_RemoveUnit
 * Namespace: Global
 * Signature: void Mapgrid_RemoveUnit(tagUNIT * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_RemoveUnit(tagUNIT *param_1,int param_2,int param_3)

{
  int *piVar1;
  char cVar2;
  tagMAPGRID *ptVar3;
  int iVar4;
  
  if ((((-1 < param_2) && (param_2 < mapsizex)) && (-1 < param_3)) && (param_3 < mapsizey)) {
    iVar4 = (int)(param_2 + (param_2 >> 0x1f & 0xfU)) >> 4;
    ptVar3 = mapgrid[(int)(param_3 + (param_3 >> 0x1f & 0xfU)) >> 4];
    cVar2 = param_1->team;
    if (param_1->gridprev == (tagUNIT *)0x0) {
      ptVar3[iVar4].firstunit[cVar2] = param_1->gridnext;
    }
    else {
      param_1->gridprev->gridnext = param_1->gridnext;
    }
    if (param_1->gridnext != (tagUNIT *)0x0) {
      param_1->gridnext->gridprev = param_1->gridprev;
    }
    param_1->gridprev = (tagUNIT *)0x0;
    param_1->gridnext = (tagUNIT *)0x0;
    piVar1 = ptVar3[iVar4].nrunits + cVar2;
    *piVar1 = *piVar1 + -1;
    return;
  }
  tlog(1,"Mapgrid_RemovePart: coordinate (%d,%d) out of range (0,0,%d,%d)");
  return;
}
