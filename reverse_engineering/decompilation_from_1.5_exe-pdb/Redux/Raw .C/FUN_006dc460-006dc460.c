
undefined4 FUN_006dc460(int *param_1,byte *param_2,uint param_3)

{
  undefined4 uVar1;
  int local_8;
  
  if ((param_3 == 0) || (3 < param_3)) {
    *param_1 = 0;
    local_8 = 4;
    while (local_8 != 0) {
      local_8 = local_8 + -1;
      *param_1 = *param_1 * 0x100 + (uint)*param_2;
      param_2 = param_2 + 1;
    }
    uVar1 = 4;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

