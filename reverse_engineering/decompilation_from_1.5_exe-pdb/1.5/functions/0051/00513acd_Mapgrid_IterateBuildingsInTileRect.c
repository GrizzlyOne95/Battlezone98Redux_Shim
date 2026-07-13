/*
 * Entry: 00513acd
 * Name: Mapgrid_IterateBuildingsInTileRect
 * Namespace: Global
 * Signature: void Mapgrid_IterateBuildingsInTileRect(_func___cdecl_void_tagBUILDING_ptr_void_ptr * param_1, void * param_2, int param_3, int param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Mapgrid_IterateBuildingsInTileRect
          (_func___cdecl_void_tagBUILDING_ptr_void_ptr *param_1,void *param_2,int param_3,
          int param_4,int param_5,int param_6)

{
  tagBUILDING *ptVar1;
  uint uVar2;
  tagBUILDING *ptVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_1c;
  int local_18;
  int local_c;
  
  iVar4 = (int)((param_4 - maxbuildingysize) + (param_4 - maxbuildingysize >> 0x1f & 0xfU)) >> 4;
  iVar6 = (int)(param_6 + 0xf + (param_6 + 0xf >> 0x1f & 0xfU)) >> 4;
  iVar5 = (int)((param_5 + 0xf >> 0x1f & 0xfU) + param_5 + 0xf) >> 4;
  iVar8 = (int)((param_3 - maxbuildingxsize) + (param_3 - maxbuildingxsize >> 0x1f & 0xfU)) >> 4;
  if (iVar4 < 1) {
    iVar4 = 0;
  }
  if (mapgridysize <= iVar6) {
    iVar6 = mapgridysize;
  }
  if (iVar8 < 1) {
    iVar8 = 0;
  }
  if (mapgridxsize <= iVar5) {
    iVar5 = mapgridxsize;
  }
  for (; iVar4 < iVar6; iVar4 = iVar4 + 1) {
    if (iVar8 < iVar5) {
      iVar7 = iVar8 * 0x10c + 0xc0;
      local_1c = iVar5 - iVar8;
      do {
        local_18 = 0x10;
        local_c = iVar7;
        do {
          ptVar1 = *(tagBUILDING **)((int)mapgrid[iVar4]->nrunits + local_c);
          while (ptVar3 = ptVar1, ptVar3 != (tagBUILDING *)0x0) {
            ptVar1 = ptVar3->gridnext;
            if ((((ptVar3->tilex < param_5) && (ptVar3->tiley < param_6)) &&
                (uVar2 = *(uint *)&ptVar3->buildingtype->field_0x24,
                param_3 < (int)((uVar2 >> 0x12 & 0xf) + ptVar3->tilex))) &&
               (param_4 < (int)((uVar2 >> 0x16 & 0xf) + ptVar3->tiley))) {
              (*param_1)(ptVar3,param_2);
            }
          }
          local_c = local_c + 4;
          local_18 = local_18 + -1;
        } while (local_18 != 0);
        iVar7 = iVar7 + 0x10c;
        local_1c = local_1c + -1;
      } while (local_1c != 0);
    }
  }
  return;
}
