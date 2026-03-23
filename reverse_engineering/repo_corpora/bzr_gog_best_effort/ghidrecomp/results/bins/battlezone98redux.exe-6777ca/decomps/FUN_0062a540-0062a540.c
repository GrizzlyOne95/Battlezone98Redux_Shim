
undefined4 FUN_0062a540(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (((param_1 < 0) || (0x1ff < param_1)) || (*(int *)(&DAT_02a17498 + param_1 * 0x20) == 0)) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = 0;
    }
    uVar1 = 0xffffffff;
  }
  else {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = &DAT_02a17498 + param_1 * 0x20;
    }
    uVar1 = 0;
  }
  return uVar1;
}

