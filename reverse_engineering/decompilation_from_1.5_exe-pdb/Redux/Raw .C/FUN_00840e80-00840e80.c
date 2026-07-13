
int __fastcall FUN_00840e80(undefined4 *param_1)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar3 = FUN_008407b0(param_1,param_1[4]);
  if (param_1[4] != 0) {
    puVar5 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar5 = (undefined4 *)*param_1;
    }
    sVar1 = *(short *)((int)puVar5 + iVar3 * 2);
    if ((sVar1 == 0x2f) || (sVar1 == 0x5c)) {
      bVar2 = true;
      goto LAB_00840ebf;
    }
  }
  bVar2 = false;
LAB_00840ebf:
  iVar4 = FUN_008413f0(param_1,iVar3);
  if (iVar3 != 0) {
    while (iVar3 + -1 != iVar4) {
      puVar5 = param_1;
      if (7 < (uint)param_1[5]) {
        puVar5 = (undefined4 *)*param_1;
      }
      sVar1 = *(short *)((int)puVar5 + iVar3 * 2 + -2);
      if (((sVar1 != 0x2f) && (sVar1 != 0x5c)) || (iVar3 = iVar3 + -1, iVar3 == 0)) break;
    }
  }
  if (((iVar3 == 1) && (iVar4 == 0)) && (bVar2)) {
    return -1;
  }
  return iVar3;
}

