/*
 * Entry: 0051a40f
 * Name: Squad_Unit_Is_Appropriate
 * Namespace: Global
 * Signature: int Squad_Unit_Is_Appropriate(tagUNIT * param_1, Mapgrid_Goal * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Type propagation algorithm not settling */

int __cdecl Squad_Unit_Is_Appropriate(tagUNIT *param_1,Mapgrid_Goal *param_2)

{
  undefined4 *puVar1;
  Mapgrid_Goal *pMVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  
  pMVar2 = param_2;
  AddGridPoint(param_2->column,param_2->row);
  puVar1 = (undefined4 *)(param_1->id + 0x20);
  iVar3 = (**(code **)*puVar1)();
  if (*(int *)(iVar3 + 0x20) == 0x54544e4b) {
    iVar3 = (param_1->tilepos).x;
    iVar4 = (param_1->tilepos).y;
    iVar4 = (int)(iVar4 + (iVar4 >> 0x1f & 7U)) >> 3;
    iVar3 = (int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3;
    if (*(int *)((int)(AI_map->team[param_1->team]->strategic_targets).grid[iVar4][iVar3] + 4) == 2)
    {
      if (iVar3 != param_2->column) {
        return 0;
      }
      bVar6 = iVar4 == param_2->row;
      goto LAB_0051a48c;
    }
    param_2 = (Mapgrid_Goal *)0x2;
  }
  else {
    param_2 = (Mapgrid_Goal *)0x1;
  }
  iVar3 = pMVar2->_padding_;
  if (iVar3 == 1) {
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x4d4c5952) {
      return 1;
    }
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x57494e47) {
      return 1;
    }
    uVar5 = 2;
  }
  else if ((iVar3 == 2) || (iVar3 == 4)) {
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x54544e4b) {
      return 0;
    }
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x54555252) {
      return 0;
    }
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x4857545a) {
      return 0;
    }
    uVar5 = 1;
    if (((param_2 == (Mapgrid_Goal *)0x2) &&
        (iVar3 = (param_1->tilepos).x, (int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3 == pMVar2->column))
       && (iVar3 = (param_1->tilepos).y, (int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3 == pMVar2->row)) {
      uVar5 = 3;
    }
  }
  else if (iVar3 == 5) {
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x4857545a) {
      return 0;
    }
    uVar5 = (pMVar2->min_scripted_force < 100) + 1;
  }
  else {
    if (iVar3 == 6) {
      iVar3 = (**(code **)*puVar1)();
      if (*(int *)(iVar3 + 0x20) == 0x4d4c5952) {
        return 1;
      }
      iVar3 = (**(code **)*puVar1)();
      bVar6 = *(int *)(iVar3 + 0x20) == 0x57494e47;
LAB_0051a48c:
      if (bVar6) {
        return 1;
      }
      return 0;
    }
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x54544e4b) {
      return 0;
    }
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x54555252) {
      return 0;
    }
    iVar3 = (**(code **)*puVar1)();
    if (*(int *)(iVar3 + 0x20) == 0x4857545a) {
      return 0;
    }
    uVar5 = 1;
  }
  return (uint)((uVar5 & (uint)param_2) != 0);
}
