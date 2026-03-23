
undefined1 FUN_006c91e0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 local_2c [4];
  undefined1 local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852730;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = FUN_006cdde0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  local_14 = local_18;
  local_20 = FUN_006dc710(&param_1,local_18);
  local_8._0_1_ = 1;
  local_1c = local_20;
  FUN_006cdb10(local_2c,local_20);
  local_8 = (uint)local_8._1_3_ << 8;
  ~<>();
  local_8 = 0xffffffff;
  FUN_006cd030();
  uVar1 = param_2;
  FUN_0042da60(param_2);
  FUN_006c9000(uVar1);
  ExceptionList = local_10;
  return local_28;
}

