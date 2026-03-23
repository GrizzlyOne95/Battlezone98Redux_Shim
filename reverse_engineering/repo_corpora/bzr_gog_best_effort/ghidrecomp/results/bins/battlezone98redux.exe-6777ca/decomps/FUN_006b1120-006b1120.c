
void __fastcall FUN_006b1120(int param_1)

{
  uint uVar1;
  undefined1 local_1c [8];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850520;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  FUN_006c8ce0(param_1 + 0x18);
  local_8 = 0;
  while (*(char *)(local_14 + 0xd0) == '\0') {
    FUN_006c8de0();
    FUN_006c8f00();
    local_8._0_1_ = 1;
    FUN_006b0cb0(1,local_1c);
    FUN_006ad700(local_1c);
    FUN_006c8db0();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006c8f30();
  }
  local_8 = 0xffffffff;
  FUN_006c8d50(uVar1);
  ExceptionList = local_10;
  return;
}

