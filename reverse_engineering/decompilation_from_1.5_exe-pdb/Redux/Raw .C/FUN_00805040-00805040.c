
undefined4 * __thiscall FUN_00805040(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = uVar1;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 2));
  return param_1;
}

