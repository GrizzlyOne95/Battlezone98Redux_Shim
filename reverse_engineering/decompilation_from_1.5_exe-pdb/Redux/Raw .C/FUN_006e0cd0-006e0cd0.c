
allocator<char> * __fastcall FUN_006e0cd0(allocator<char> *param_1)

{
  uint uVar1;
  undefined4 uVar2;
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
  uVar2 = FUN_006abdd0(uVar1);
  *(undefined4 *)param_1 = uVar2;
  ExceptionList = local_10;
  return param_1;
}

