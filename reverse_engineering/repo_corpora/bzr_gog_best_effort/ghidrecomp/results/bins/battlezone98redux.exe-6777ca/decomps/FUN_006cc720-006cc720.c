
undefined4 __thiscall FUN_006cc720(allocator<char> *param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)std::allocator<char>::allocator<char>(param_1);
  FUN_00447eb0(*(int *)(param_1 + 4) * 0x20 + *piVar1);
  return param_2;
}

