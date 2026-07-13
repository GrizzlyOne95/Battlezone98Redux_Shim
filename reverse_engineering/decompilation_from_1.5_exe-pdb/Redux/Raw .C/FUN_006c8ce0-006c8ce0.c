
allocator<char> * __thiscall FUN_006c8ce0(allocator<char> *param_1,undefined4 param_2)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>(param_1);
  local_8 = 0;
  *(undefined4 *)param_1 = param_2;
  FUN_006ac0d0(uVar1);
  param_1[4] = (allocator<char>)0x1;
  ExceptionList = local_10;
  return param_1;
}

