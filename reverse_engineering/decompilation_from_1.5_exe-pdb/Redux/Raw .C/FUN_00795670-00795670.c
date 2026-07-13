
void FUN_00795670(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined1 local_5c [12];
  undefined1 local_50 [12];
  undefined1 local_44 [12];
  undefined1 local_38 [12];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_18;
  char local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f1e0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = 0;
  puVar4 = local_38;
  FUN_00764790(puVar4,uVar1);
  FUN_004bb540(puVar4);
  local_8 = 0;
  while( true ) {
    puVar4 = local_50;
    FUN_00764790(puVar4,uVar1);
    local_24 = FUN_004bb570(puVar4);
    local_8._0_1_ = 1;
    local_20 = local_24;
    local_11 = FID_conflict_operator<(local_24);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004bb3b0();
    if (local_11 == '\0') break;
    uVar5 = 0;
    iVar3 = local_18;
    FUN_0076f9f0(local_18,0);
    uVar2 = FUN_0041f870();
    FUN_007cabf0(uVar2,iVar3,uVar5);
    iVar3 = FUN_0076f9f0();
    if (*(char *)(iVar3 + 0x90) == '\x01') {
      FUN_007caba0(local_18,3);
    }
    else {
      FUN_007caba0(local_18,2);
    }
    local_18 = local_18 + 1;
    FUN_00732df0();
  }
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  local_18 = 0;
  puVar4 = local_44;
  FUN_00764790(puVar4);
  FUN_004bb540(puVar4);
  local_8 = 2;
  while( true ) {
    puVar4 = local_5c;
    FUN_00764790(puVar4);
    local_2c = FUN_004bb570(puVar4);
    local_8._0_1_ = 3;
    local_28 = local_2c;
    local_12 = FID_conflict_operator<(local_2c);
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_004bb3b0();
    if (local_12 == '\0') break;
    uVar5 = 0;
    iVar3 = local_18;
    FUN_0076f9f0(local_18,0);
    uVar2 = FUN_0041f870();
    FUN_007cabf0(uVar2,iVar3,uVar5);
    iVar3 = FUN_0076f9f0();
    if (*(char *)(iVar3 + 0x90) == '\x01') {
      FUN_007caba0(local_18,3);
    }
    else {
      FUN_007caba0(local_18,2);
    }
    local_18 = local_18 + 1;
    FUN_00732df0();
  }
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

