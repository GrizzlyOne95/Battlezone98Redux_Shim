
allocator<char> * __fastcall FUN_006cd940(allocator<char> *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852cd3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>(param_1);
  local_8 = 0;
  *(undefined4 *)param_1 = 0;
  vector<>(uVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  vector<>();
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  ExceptionList = local_10;
  return param_1;
}

