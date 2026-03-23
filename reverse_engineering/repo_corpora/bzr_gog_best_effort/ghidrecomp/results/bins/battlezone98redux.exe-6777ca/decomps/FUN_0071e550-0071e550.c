
undefined4 * __thiscall FUN_0071e550(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00417780(param_2);
  allocator<>(uVar1);
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  *param_2 = 0;
  param_2[2] = 0;
  param_2[1] = 0;
  return param_1;
}

