
void __fastcall FUN_00584f50(undefined4 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084bc0b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Ordnance::vftable;
  local_8 = 0;
  if (*(short *)(param_1 + 0x1f) != 0) {
    uVar2 = FUN_004bcc60(param_1 + 0x1f,(int)param_1 + 0x7e);
    FUN_005857e0(uVar2);
  }
  local_8 = 0xffffffff;
  FUN_0044dc30(uVar1);
  ExceptionList = local_10;
  return;
}

