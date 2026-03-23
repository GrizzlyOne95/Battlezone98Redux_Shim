
void FUN_0041e880(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_5c [24];
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844fe3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_004202c0(local_14);
  if (cVar1 != '\0') {
    FUN_0041c580();
  }
  FID_conflict_operator_(param_1);
  FUN_00426a60(&DAT_02cf2000,0);
  local_8 = 0;
  FUN_00426af0("config.ini");
  FUN_00426b10(0,0,0);
  local_8._0_1_ = 1;
  FUN_00417fd0(local_5c);
  local_8._0_1_ = 2;
  uVar2 = FUN_0041f870();
  FUN_00426c30(uVar2);
  local_8._0_1_ = 1;
  ~basic_string<>();
  uVar4 = 0;
  uVar3 = 0;
  uVar2 = FUN_0041f870(0,0);
  FUN_00421f90("buttonsystem","config",uVar2,uVar3,uVar4);
  FUN_00417fd0(local_44);
  local_8._0_1_ = 3;
  uVar3 = 1;
  uVar2 = FUN_0041f870(1);
  FUN_00426c90(uVar2,uVar3);
  local_8._0_1_ = 1;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00426bc0();
  local_8 = 0xffffffff;
  FUN_004180b0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

