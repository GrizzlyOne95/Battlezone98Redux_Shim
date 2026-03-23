
undefined4 __thiscall FUN_006acb90(undefined4 *param_1,undefined4 param_2)

{
  undefined4 local_c;
  int *local_8;
  
  local_c = param_2;
  for (local_8 = (int *)*param_1; local_8 != (int *)0x0; local_8 = (int *)local_8[1]) {
    local_c = (**(code **)(*local_8 + 0xc))(local_c);
  }
  return local_c;
}

