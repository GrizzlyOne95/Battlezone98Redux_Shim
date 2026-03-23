
void FUN_006db160(void)

{
  undefined4 uStack_78;
  undefined1 *puStack_74;
  code *pcStack_70;
  undefined4 uStack_6c;
  undefined1 *puStack_68;
  code *pcStack_64;
  uint uStack_60;
  undefined1 local_5c [24];
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  code *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853980;
  local_10 = ExceptionList;
  uStack_60 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_64 = (code *)0x898dfc;
  puStack_68 = (undefined1 *)0x400;
  uStack_6c = 0x6db1a0;
  FUN_006d08b0();
  if (*(int *)(local_14 + 0xa24) == 0) {
    *(undefined4 *)(local_14 + 0xa24) = 1;
    local_34 = FUN_006e9ba0;
    local_30 = 0;
    pcStack_64 = (code *)local_3c;
    puStack_68 = (undefined1 *)0x6db207;
    puStack_68 = (undefined1 *)FUN_006e1540();
    local_8 = 0;
    pcStack_64 = _1_exref;
    uStack_6c = local_30;
    pcStack_70 = local_34;
    puStack_74 = local_5c;
    uStack_78 = 0x6db233;
    local_1c = puStack_68;
    local_18 = puStack_68;
    local_24 = FUN_006eadb0();
    local_8._0_1_ = 1;
    local_28 = (undefined1 *)&uStack_78;
    local_20 = local_24;
    local_2c = FUN_006eae00(local_24);
    FUN_006e1100();
    local_8 = (uint)local_8._1_3_ << 8;
    pcStack_64 = (code *)0x6db26b;
    ~input_processor<>();
    local_8 = 0xffffffff;
    pcStack_64 = (code *)0x6db27a;
    FUN_006ca8c0();
  }
  else {
    pcStack_64 = (code *)0x898e60;
    puStack_68 = (undefined1 *)0x400;
    uStack_6c = 0x6db1c4;
    FUN_006d08b0();
    pcStack_64 = (code *)0x9;
    puStack_68 = local_44;
    uStack_6c = 0x6db1cf;
    pcStack_64 = (code *)make_error_code();
    puStack_68 = (undefined1 *)0x6db1db;
    FUN_006daf10();
  }
  ExceptionList = local_10;
  return;
}

