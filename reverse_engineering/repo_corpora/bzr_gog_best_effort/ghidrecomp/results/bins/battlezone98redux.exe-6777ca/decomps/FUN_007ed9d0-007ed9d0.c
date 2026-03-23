
undefined4 * __thiscall
FUN_007ed9d0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,char param_4)

{
  undefined4 uVar1;
  undefined4 *local_c;
  
  *param_1 = param_3;
  param_1[1] = *param_1;
  param_1[2] = 0;
  param_1[3] = param_2;
  local_c = param_1;
  if (param_4 == '\0') {
    local_c = (undefined4 *)0x0;
  }
  uVar1 = FUN_007d7240(local_c);
  param_1[2] = uVar1;
  return param_1;
}

