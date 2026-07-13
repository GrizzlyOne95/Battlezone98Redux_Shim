
void __fastcall FUN_006b1460(int param_1)

{
  uint uVar1;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850578;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c8ce0(param_1 + 0x10);
  local_8 = 0;
  for (local_14 = *(int *)(param_1 + 0x28); local_14 != 0; local_14 = *(int *)(local_14 + 0x14)) {
    FUN_004fbb60();
    FUN_006b1f00(local_14);
  }
  local_8 = 0xffffffff;
  FUN_006c8d50(uVar1);
  ExceptionList = local_10;
  return;
}

