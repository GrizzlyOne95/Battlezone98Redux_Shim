
undefined * FUN_0076ea20(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_5c [12];
  undefined1 local_50 [12];
  undefined1 local_44 [24];
  undefined *local_2c;
  undefined *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085dd1e;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = FUN_004bb540(local_50);
  local_8 = 0;
  local_18 = local_1c;
  _String_const_iterator<>(local_1c);
  local_8._0_1_ = 2;
  FUN_004bb3b0(uVar2);
  local_24 = FUN_004bb570(local_5c);
  local_8._0_1_ = 3;
  local_20 = local_24;
  _String_const_iterator<>(local_24);
  local_8 = CONCAT31(local_8._1_3_,5);
  FUN_004bb3b0();
  while( true ) {
    cVar1 = FID_conflict_operator__(local_44);
    if (cVar1 == '\0') {
      if ((DAT_02cc38dc & 1) == 0) {
        DAT_02cc38dc = DAT_02cc38dc | 1;
        local_8._0_1_ = 6;
        FUN_00482690();
        FUN_0083e979(FUN_00867d70);
        local_8 = (uint)local_8._1_3_ << 8;
      }
      local_2c = &DAT_02cc38e0;
      local_8 = CONCAT31(local_8._1_3_,2);
      FUN_004bb3d0();
      local_8 = 0xffffffff;
      FUN_004bb3d0();
      ExceptionList = local_10;
      return local_2c;
    }
    iVar3 = FUN_0076f990(param_1);
    cVar1 = FUN_00427310(iVar3 + 0x34);
    if (cVar1 != '\0') break;
    FUN_007332d0();
  }
  local_28 = (undefined *)FUN_0076f930();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_004bb3d0();
  local_8 = 0xffffffff;
  FUN_004bb3d0();
  ExceptionList = local_10;
  return local_28;
}

