
undefined4 __thiscall FUN_006da620(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  allocator<char> local_5;
  
  uVar1 = std::allocator<char>::allocator<char>(&local_5);
  _Vector_alloc<>(uVar1);
  FUN_006e89d0(param_2,param_3);
  return param_1;
}

