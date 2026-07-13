
allocator<char> * __fastcall FUN_006d1180(allocator<char> *param_1)

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
  FUN_006b2a10(uVar1);
  FUN_006d3540();
  ExceptionList = local_10;
  return param_1;
}

