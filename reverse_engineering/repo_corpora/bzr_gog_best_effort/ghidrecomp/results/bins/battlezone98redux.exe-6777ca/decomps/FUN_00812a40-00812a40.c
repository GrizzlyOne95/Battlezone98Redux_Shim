
void FUN_00812a40(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined1 local_60 [52];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008649a9;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar5 = 0;
  local_14 = uVar1;
  basic_string<>("kleene");
  local_8 = 1;
  uVar3 = extraout_var;
  uVar2 = FUN_008139f0(local_60,param_2);
  local_8._0_1_ = 2;
  uVar4 = uVar2;
  FUN_00809900(local_2c,uVar2);
  local_8._0_1_ = 1;
  FUN_00800170(uVar1,uVar2,uVar3,uVar4,uVar5 | 1);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

