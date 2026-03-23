
undefined4 __thiscall FUN_006cc180(allocator<char> *param_1,undefined4 param_2)

{
  allocator<char> **ppaVar1;
  allocator<char> *paStack_c;
  allocator<char> *local_8;
  
  ppaVar1 = &paStack_c;
  paStack_c = param_1;
  local_8 = param_1;
  std::allocator<char>::allocator<char>(param_1);
  FUN_006d0b60(ppaVar1);
  FUN_006d0c50();
  return param_2;
}

