
void FUN_0041ea20(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined4 local_44;
  undefined1 local_40 [8];
  uint local_38;
  undefined4 local_34;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845020;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_38 = 0;
  cVar1 = FUN_004202c0(local_14);
  if (cVar1 != '\0') {
    FUN_0041c580();
  }
  FUN_00422260();
  local_8 = 0;
  puVar2 = (undefined4 *)FUN_00420260(local_48);
  local_34 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_4c);
  local_44 = *puVar2;
  while( true ) {
    cVar1 = FUN_00420f10(&local_44);
    if (cVar1 == '\0') break;
    uVar3 = FUN_00421ea0();
    FUN_004222f0(local_5c,uVar3);
    FUN_00422190();
  }
  basic_string<>("default");
  local_8._0_1_ = 1;
  FUN_004222c0(local_54,local_2c);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  FUN_00422290(local_40);
  local_38 = local_38 | 1;
  local_8 = 0xffffffff;
  FUN_0041eb50();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

