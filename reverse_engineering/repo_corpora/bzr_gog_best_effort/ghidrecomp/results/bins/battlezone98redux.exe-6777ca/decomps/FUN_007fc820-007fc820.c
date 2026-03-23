
undefined4 __fastcall FUN_007fc820(undefined4 param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00864558;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_007fc750(&stack0x00000004);
  local_8._0_1_ = 2;
  FUN_007fc640(&stack0x00000024);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d7950(uVar1);
  local_8 = 0xffffffff;
  FUN_007fb7c0();
  ExceptionList = local_10;
  return param_1;
}

