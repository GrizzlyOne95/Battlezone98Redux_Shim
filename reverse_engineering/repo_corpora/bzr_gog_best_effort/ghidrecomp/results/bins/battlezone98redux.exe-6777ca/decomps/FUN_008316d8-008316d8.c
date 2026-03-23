
uint FUN_008316d8(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = param_2 + 1;
  do {
    iVar1 = FUN_00830ecf(param_1,uVar4);
    if (*(int *)(iVar1 + 8) == 0) {
      uVar2 = uVar4 - param_2;
      while (1 < uVar2) {
        uVar2 = param_2 + uVar4 >> 1;
        iVar1 = FUN_00830ecf(param_1,uVar2);
        if (*(int *)(iVar1 + 8) != 0) {
          param_2 = uVar2;
          uVar2 = uVar4;
        }
        uVar4 = uVar2;
        uVar2 = uVar4 - param_2;
      }
      return param_2;
    }
    uVar2 = uVar4 * 2;
    param_2 = uVar4;
    uVar4 = uVar2;
  } while (uVar2 < 0x7ffffffe);
  iVar1 = 1;
  while (iVar3 = FUN_00830ecf(param_1,iVar1), *(int *)(iVar3 + 8) != 0) {
    iVar1 = iVar1 + 1;
  }
  return iVar1 - 1;
}

