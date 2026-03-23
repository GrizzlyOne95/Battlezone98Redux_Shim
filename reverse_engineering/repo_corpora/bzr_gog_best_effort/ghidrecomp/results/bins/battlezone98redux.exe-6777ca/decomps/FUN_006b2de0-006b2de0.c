
undefined4 * __thiscall FUN_006b2de0(undefined4 *param_1,allocator<char> *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)std::allocator<char>::allocator<char>(param_2);
  *param_1 = *puVar1;
  return param_1;
}

