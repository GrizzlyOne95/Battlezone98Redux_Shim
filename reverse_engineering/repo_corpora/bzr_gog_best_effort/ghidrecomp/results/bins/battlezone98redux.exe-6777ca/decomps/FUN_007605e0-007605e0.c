
undefined4 FUN_007605e0(uint *param_1,undefined1 *param_2,uint param_3)

{
  undefined4 uVar1;
  int local_8;
  
  if ((param_3 == 0) || (3 < param_3)) {
    local_8 = 0x20;
    while (local_8 != 0) {
      local_8 = local_8 + -8;
      *param_2 = (char)(*param_1 >> ((byte)local_8 & 0x1f));
      param_2 = param_2 + 1;
    }
    uVar1 = 4;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

