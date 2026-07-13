
int __thiscall FUN_00736560(int param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852adb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 8));
  local_8 = 0;
  FUN_007375c0(param_2,1);
  ExceptionList = local_10;
  return param_1;
}

