
undefined4 __thiscall FUN_0070dfd0(undefined4 param_1,allocator<char> *param_2)

{
  undefined4 uVar1;
  
  uVar1 = std::allocator<char>::allocator<char>(param_2);
  uVar1 = FUN_00417780(uVar1);
  FUN_007188d0(uVar1);
  uVar1 = FUN_00417780(param_2 + 8);
  FUN_00718910(uVar1);
  return param_1;
}

