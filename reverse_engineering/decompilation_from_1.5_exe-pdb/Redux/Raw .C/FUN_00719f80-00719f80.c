
undefined4 __thiscall FUN_00719f80(undefined4 param_1,allocator<char> *param_2)

{
  undefined4 uVar1;
  
  uVar1 = std::allocator<char>::allocator<char>(param_2);
  uVar1 = FUN_00417780(uVar1);
  FUN_007188d0(uVar1);
  uVar1 = FUN_00417780(param_2 + 1);
  FUN_0070b490(uVar1);
  return param_1;
}

