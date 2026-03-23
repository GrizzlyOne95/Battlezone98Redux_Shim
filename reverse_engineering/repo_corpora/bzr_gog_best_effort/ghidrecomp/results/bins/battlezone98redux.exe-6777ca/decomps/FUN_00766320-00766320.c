
int __fastcall FUN_00766320(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d1e3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0083ead2(param_1,0xc,5,vector<>,FUN_00766f60);
  local_8 = 0;
  basic_string<>(uVar1);
  *(undefined4 *)(param_1 + 0x3c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x60) = 0;
  ExceptionList = local_10;
  return param_1;
}

