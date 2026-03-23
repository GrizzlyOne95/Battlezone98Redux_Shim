
void FUN_006feeb0(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_94 [40];
  undefined4 uStack_6c;
  undefined4 uStack_68;
  uint uStack_64;
  undefined1 *local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00856070;
  local_10 = ExceptionList;
  uStack_64 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_50 = 0;
  local_8 = 0;
  local_60 = auStack_94;
  local_14 = uStack_64;
  local_5c = FUN_00700b40(&stack0x0000000c);
  uStack_68 = FUN_00700c20(param_2);
  local_8._0_1_ = 1;
  uStack_6c = 0x6fef1f;
  local_58 = uStack_68;
  local_54 = uStack_68;
  <>();
  local_50 = local_50 | 1;
  local_8 = (uint)local_8._1_3_ << 8;
  uStack_68 = 0x6fef34;
  ~input_processor<>();
  local_8 = 0xffffffff;
  uStack_68 = 0x6fef43;
  FUN_006e4380();
  ExceptionList = local_10;
  uStack_64 = 0x6fef5b;
  FUN_0083e885();
  return;
}

