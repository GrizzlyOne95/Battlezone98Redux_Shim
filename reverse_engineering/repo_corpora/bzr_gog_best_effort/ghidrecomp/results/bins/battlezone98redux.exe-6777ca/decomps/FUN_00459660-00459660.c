
int __fastcall FUN_00459660(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846f68;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0045b7b0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *(undefined1 *)(param_1 + 0x14) = 1;
  FUN_0045b820(0x80);
  ExceptionList = local_10;
  return param_1;
}

