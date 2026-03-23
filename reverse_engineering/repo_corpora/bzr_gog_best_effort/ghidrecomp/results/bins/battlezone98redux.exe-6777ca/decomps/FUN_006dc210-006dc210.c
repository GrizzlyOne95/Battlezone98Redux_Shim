
undefined4 FUN_006dc210(undefined4 param_1,undefined1 *param_2,uint param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int local_8;
  
  if ((param_3 == 0) || (7 < param_3)) {
    local_8 = 0x40;
    while (local_8 != 0) {
      local_8 = local_8 + -8;
      uVar1 = __aullshr();
      *param_2 = uVar1;
      param_2 = param_2 + 1;
    }
    uVar2 = 8;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

