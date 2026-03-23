
void FUN_006f8080(undefined4 param_1)

{
  undefined1 *puStack_c0;
  code *pcStack_bc;
  code *pcStack_b8;
  undefined4 uStack_b4;
  code *pcStack_b0;
  code *pcStack_ac;
  uint uStack_a8;
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 *local_74;
  undefined4 local_70;
  undefined1 local_6c [8];
  undefined4 local_64;
  undefined1 local_60 [8];
  undefined1 local_58 [8];
  undefined1 *local_50;
  code *local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  code *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008557d6;
  local_10 = ExceptionList;
  uStack_a8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_ac = (code *)0x89926c;
  pcStack_b0 = (code *)0x400;
  uStack_b4 = 0x6f80c3;
  FUN_006d08b0();
  if (0 < *(int *)(local_14 + 0xa10)) {
    local_4c = FUN_007098c0;
    local_48 = 0;
    pcStack_ac = (code *)local_60;
    pcStack_b0 = (code *)0x6f80ed;
    pcStack_b0 = (code *)FUN_006e1540();
    local_8 = 0;
    pcStack_ac = _1_exref;
    uStack_b4 = local_48;
    pcStack_b8 = local_4c;
    pcStack_bc = (code *)local_8c;
    puStack_c0 = (undefined1 *)0x6f811c;
    local_40 = pcStack_b0;
    local_38 = pcStack_b0;
    local_44 = FUN_006eadb0();
    local_8._0_1_ = 1;
    local_50 = (undefined1 *)&puStack_c0;
    local_2c = local_44;
    local_64 = FUN_006eae00(local_44);
    pcStack_ac = (code *)FUN_006d4050(local_58,*(undefined4 *)(local_14 + 0xa10));
    pcStack_b0 = (code *)0x6f8171;
    local_3c = pcStack_ac;
    local_34 = pcStack_ac;
    FID_conflict_operator_();
    pcStack_ac = (code *)0x6f8179;
    FUN_006ca8c0();
    local_8 = (uint)local_8._1_3_ << 8;
    pcStack_ac = (code *)0x6f8188;
    ~input_processor<>();
    local_8 = 0xffffffff;
    pcStack_ac = (code *)0x6f8197;
    FUN_006ca8c0();
  }
  local_24 = FUN_00708d60;
  local_20 = 0;
  pcStack_ac = (code *)local_6c;
  pcStack_b0 = (code *)0x6f81b1;
  uStack_b4 = FUN_006e1540();
  local_8 = 2;
  pcStack_ac = _2_exref;
  pcStack_b0 = _1_exref;
  pcStack_b8 = (code *)local_20;
  pcStack_bc = local_24;
  puStack_c0 = local_a4;
  local_28 = uStack_b4;
  local_1c = uStack_b4;
  local_30 = FUN_0070a660();
  local_8._0_1_ = 3;
  local_74 = (undefined1 *)&puStack_c0;
  local_18 = local_30;
  local_70 = FUN_0070a6c0(local_30);
  FUN_006ffbc0(param_1,local_14 + 0xa30,0x4000);
  local_8 = CONCAT31(local_8._1_3_,2);
  pcStack_ac = (code *)0x6f8234;
  ~input_processor<>();
  local_8 = 0xffffffff;
  pcStack_ac = (code *)0x6f8243;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return;
}

