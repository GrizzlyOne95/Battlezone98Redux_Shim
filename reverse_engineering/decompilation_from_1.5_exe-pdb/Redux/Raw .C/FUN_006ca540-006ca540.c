
void __fastcall FUN_006ca540(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006cd7e0(*(undefined4 *)(param_1 + 8));
  local_8 = 0xffffffff;
  FUN_00417c60(uVar1);
  ExceptionList = local_10;
  return;
}

