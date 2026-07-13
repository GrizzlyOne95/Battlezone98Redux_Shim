
undefined4 FUN_0082c5be(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 1;
  if ((param_2 < 0x1f41) &&
     ((*(int *)(param_1 + 8) - *(int *)(param_1 + 0xc) >> 4) + param_2 < 0x1f41)) {
    if (0 < param_2) {
      if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) <= param_2 * 0x10) {
        FUN_0082f194(param_1,param_2);
      }
      uVar1 = *(int *)(param_1 + 8) + param_2 * 0x10;
      if (*(uint *)(*(int *)(param_1 + 0x14) + 8) < uVar1) {
        *(uint *)(*(int *)(param_1 + 0x14) + 8) = uVar1;
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

