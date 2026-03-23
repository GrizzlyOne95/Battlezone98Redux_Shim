
undefined4 FUN_006dc510(undefined2 *param_1,undefined1 *param_2,uint param_3)

{
  undefined4 uVar1;
  int local_8;
  
  if ((param_3 == 0) || (1 < param_3)) {
    *param_1 = 0;
    local_8 = 2;
    while (local_8 != 0) {
      local_8 = local_8 + -1;
      *param_1 = (short)CONCAT21(*param_1,*param_2);
      param_2 = param_2 + 1;
    }
    uVar1 = 2;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

