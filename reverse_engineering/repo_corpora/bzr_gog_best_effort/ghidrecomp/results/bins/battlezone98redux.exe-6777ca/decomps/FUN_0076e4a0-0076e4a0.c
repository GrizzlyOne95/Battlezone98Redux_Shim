
void FUN_0076e4a0(void)

{
  char cVar1;
  undefined1 auStack_74 [4];
  undefined4 uStack_70;
  char *pcStack_6c;
  uint uStack_68;
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  undefined1 local_4c [12];
  undefined1 local_40 [12];
  undefined4 local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085dc60;
  local_10 = ExceptionList;
  uStack_68 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_6c = local_40;
  uStack_70 = 0x76e4d7;
  FUN_004bb540();
  local_8 = 0;
  pcStack_6c = local_4c;
  uStack_70 = 0x76e4ed;
  FUN_004bb570();
  local_8 = CONCAT31(local_8._1_3_,1);
  pcStack_6c = "---------------------------------\n";
  uStack_70 = 0x76e4fb;
  FUN_007d6a70();
  while( true ) {
    pcStack_6c = local_4c;
    uStack_70 = 0x76e50a;
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') break;
    local_28 = auStack_74;
    local_2c = FUN_004bbb20(local_40);
    FUN_0076e020();
    pcStack_6c = (char *)0x76e535;
    FUN_00732df0();
  }
  pcStack_6c = local_58;
  uStack_70 = 0x76e546;
  pcStack_6c = (char *)FUN_004bb540();
  local_8._0_1_ = 2;
  uStack_70 = 0x76e55f;
  local_1c = pcStack_6c;
  local_18 = pcStack_6c;
  FUN_0076e610();
  local_8._0_1_ = 1;
  pcStack_6c = (char *)0x76e56b;
  FUN_004bb3b0();
  pcStack_6c = local_64;
  uStack_70 = 0x76e57a;
  pcStack_6c = (char *)FUN_004bb570();
  local_8._0_1_ = 3;
  uStack_70 = 0x76e593;
  local_24 = pcStack_6c;
  local_20 = pcStack_6c;
  FUN_0076e610();
  local_8 = CONCAT31(local_8._1_3_,1);
  pcStack_6c = (char *)0x76e59f;
  FUN_004bb3b0();
  pcStack_6c = "---------------------------------\n";
  uStack_70 = 0x76e5a9;
  FUN_007d6a70();
  while( true ) {
    pcStack_6c = local_4c;
    uStack_70 = 0x76e5b8;
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') break;
    local_30 = auStack_74;
    local_34 = FUN_004bbb20(local_40);
    FUN_0076e020();
    pcStack_6c = (char *)0x76e5e3;
    FUN_00732df0();
  }
  local_8 = local_8 & 0xffffff00;
  pcStack_6c = (char *)0x76e5f1;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  pcStack_6c = (char *)0x76e600;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

