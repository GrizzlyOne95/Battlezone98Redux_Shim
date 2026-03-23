
undefined4 FUN_007cea60(undefined4 param_1)

{
  uint uVar1;
  undefined1 local_40 [12];
  undefined1 local_34 [12];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849af0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = FUN_004bb540(local_40);
  local_8 = 0;
  local_18 = local_1c;
  local_24 = FID_conflict_operator_(local_34,param_1);
  local_8._0_1_ = 1;
  local_20 = local_24;
  local_28 = FUN_0076f9b0(uVar1);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return local_28;
}

