
undefined4 __thiscall FUN_004964a0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  allocator<char> local_5;
  
  uVar1 = std::allocator<char>::allocator<char>(&local_5);
  _Vector_alloc<>(uVar1);
  uVar1 = FUN_00417780(param_3);
  FUN_00496550(param_2,uVar1);
  return param_1;
}

