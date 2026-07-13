
int __thiscall FUN_007e7b00(int param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863ca8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007de290(param_2);
  local_8 = 0;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 100));
  ExceptionList = local_10;
  return param_1;
}

