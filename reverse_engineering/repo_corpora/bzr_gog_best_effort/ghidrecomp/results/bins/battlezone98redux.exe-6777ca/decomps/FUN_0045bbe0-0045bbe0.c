
undefined4 FUN_0045bbe0(int *param_1)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  if (0 < DAT_00978fa8) {
    piVar2 = (int *)FUN_004da060(DAT_00978e3c);
    uVar3 = (**(code **)(*piVar2 + 0x34))(param_1);
    return uVar3;
  }
  if (param_1 == (int *)0x0) {
    return 0;
  }
  iVar4 = FUN_00417c70();
  iVar5 = FUN_004a7370();
  if (iVar5 == 0) {
    if (iVar4 != 0) {
      iVar5 = (**(code **)(param_1[6] + 4))();
      iVar4 = (**(code **)(*(int *)(iVar4 + 0x18) + 4))();
      if (((iVar5 == iVar4) && (iVar4 = FUN_0045bba0(), -1 < iVar4)) &&
         (((cVar1 = (**(code **)(*param_1 + 0x38))(), cVar1 != '\0' &&
           (cVar1 = FUN_0045bbc0(), cVar1 == '\0')) ||
          ((iVar4 = FUN_0045bba0(), 0x22 < iVar4 && (iVar4 = FUN_0045bba0(), iVar4 < 0x2d)))))) {
        return 1;
      }
    }
    return 0;
  }
  if (iVar5 != 1) {
    return 0;
  }
  iVar5 = (**(code **)param_1[6])();
  if (*(int *)(iVar5 + 0x1c) == 3) {
    return 3;
  }
  iVar5 = (**(code **)param_1[6])();
  if (*(int *)(iVar5 + 0x14) == 0x53435250) {
    return 0;
  }
  iVar5 = (**(code **)param_1[6])();
  if (*(int *)(iVar5 + 0x14) == 0x4745495a) {
    return 0;
  }
  if ((iVar4 != 0) && (cVar1 = FUN_004db510(param_1), cVar1 != '\0')) {
    return 5;
  }
  return 4;
}

