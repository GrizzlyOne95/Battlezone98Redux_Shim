
void FUN_008312f6(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_90;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74 [27];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar6 = 0;
  piVar2 = local_74;
  for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  iVar3 = *(int *)(param_2 + 0x1c);
  iVar5 = 1;
  local_90 = 0;
  iVar7 = 0;
  local_84 = 1;
  do {
    iVar1 = 0;
    iVar4 = local_84;
    if ((iVar3 < local_84) && (iVar4 = iVar3, iVar3 < iVar5)) break;
    if (iVar5 <= iVar4) {
      piVar2 = (int *)(*(int *)(param_2 + 0xc) + -8 + iVar5 * 0x10);
      iVar4 = (iVar4 - iVar5) + 1;
      iVar5 = iVar5 + iVar4;
      iVar1 = 0;
      do {
        if (*piVar2 != 0) {
          iVar1 = iVar1 + 1;
        }
        piVar2 = piVar2 + 4;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    local_74[iVar7] = local_74[iVar7] + iVar1;
    local_84 = local_84 * 2;
    local_90 = local_90 + iVar1;
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x1b);
  local_78 = 0;
  local_7c = 0;
  iVar3 = 1 << (*(byte *)(param_2 + 7) & 0x1f);
  if (iVar3 != 0) {
    iVar5 = iVar3 << 5;
    do {
      iVar5 = iVar5 + -0x20;
      iVar7 = *(int *)(param_2 + 0x10) + iVar5;
      iVar3 = iVar3 + -1;
      if (*(int *)(iVar7 + 8) != 0) {
        iVar7 = FUN_00830c97(iVar7 + 0x10,local_74);
        local_7c = local_7c + iVar7;
        local_78 = local_78 + 1;
      }
    } while (iVar3 != 0);
  }
  iVar3 = 1;
  iVar5 = FUN_00830c97(param_3,local_74);
  iVar4 = iVar5 + local_7c + local_90;
  local_80 = 0;
  local_84 = 0;
  iVar5 = 0;
  iVar7 = 0;
  if (0 < iVar4) {
    piVar2 = local_74;
    do {
      if ((0 < *piVar2) && (iVar6 = iVar6 + *piVar2, iVar3 / 2 < iVar6)) {
        local_84 = iVar6;
        local_80 = iVar3;
      }
      iVar5 = local_84;
      iVar7 = local_80;
      if (iVar6 == iVar4) break;
      iVar3 = iVar3 * 2;
      piVar2 = piVar2 + 1;
    } while (iVar3 / 2 < iVar4);
  }
  FUN_00831491(param_1,param_2,iVar7,(local_90 + local_78 + 1) - iVar5);
  FUN_0083e885();
  return;
}

