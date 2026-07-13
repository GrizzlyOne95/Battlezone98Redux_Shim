
undefined4
FUN_00589c20(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined8 local_14;
  char *local_8;
  
  local_8 = (char *)FUN_00589620(param_1,param_2);
  if (local_8 == (char *)0x0) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = param_4;
      param_3[1] = param_5;
    }
    uVar1 = 0;
  }
  else {
    if (param_3 != (undefined4 *)0x0) {
      local_14 = 0;
      strncpy((char *)&local_14,local_8,8);
      *param_3 = (undefined4)local_14;
      param_3[1] = local_14._4_4_;
    }
    uVar1 = 1;
  }
  return uVar1;
}

