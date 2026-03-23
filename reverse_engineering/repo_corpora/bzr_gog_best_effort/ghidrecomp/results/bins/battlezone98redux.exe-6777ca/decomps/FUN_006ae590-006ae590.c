
allocator<char> * __fastcall FUN_006ae590(allocator<char> *param_1)

{
  void *pvVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>(param_1);
  local_8 = 0;
  *(undefined4 *)(param_1 + 4) = 0x400;
  *(undefined4 *)(param_1 + 8) = 0xffffffff;
  pvVar1 = operator_new(*(int *)(param_1 + 4) * 4 + 4);
  *(void **)param_1 = pvVar1;
  **(undefined4 **)param_1 = 0;
  ExceptionList = local_10;
  return param_1;
}

