
undefined4 * __thiscall FUN_005c18e0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *local_c;
  undefined4 *local_8;
  
  param_1[4] = param_2;
  *param_1 = 0x43480000;
  param_1[1] = 0;
  param_1[3] = 0;
  *(undefined1 *)(param_1 + 2) = 0;
  local_c = param_1;
  local_8 = param_1;
  FUN_0041fe40(&local_c);
  return local_8;
}

