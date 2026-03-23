
undefined1 FUN_00767fe0(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_38 [12];
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d430;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004bb540(local_2c);
  local_8 = 0;
  while( true ) {
    local_20 = FUN_004bb570(local_38);
    local_8._0_1_ = 1;
    local_1c = local_20;
    local_11 = FID_conflict_operator<(local_20);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004bb3b0(uVar2);
    if (local_11 == '\0') {
      local_8 = 0xffffffff;
      FUN_004bb3b0();
      ExceptionList = local_10;
      return 0;
    }
    iVar3 = FUN_00752f10(&DAT_00873c74);
    cVar1 = operator!=<>(iVar3 + 0x3c);
    if (cVar1 != '\0') break;
    FUN_00732df0();
  }
  local_12 = 1;
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return local_12;
}

