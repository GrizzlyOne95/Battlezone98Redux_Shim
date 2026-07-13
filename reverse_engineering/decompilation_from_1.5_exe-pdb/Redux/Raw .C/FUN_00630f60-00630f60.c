
undefined * FUN_00630f60(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *local_34;
  char *local_30;
  undefined1 local_2c [12];
  undefined1 local_20 [15];
  allocator<char> local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084d346;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((DAT_02cc31b4 & 1) == 0) {
    DAT_02cc31b4 = DAT_02cc31b4 | 1;
    local_8 = 0;
    local_34 = &DAT_00878c18;
    local_30 = "cvfigh";
    uVar2 = std::allocator<char>::allocator<char>(&local_11);
    puVar3 = (undefined4 *)FUN_00416430(&local_34,local_2c);
    FUN_00631030(*puVar3,puVar3[1],uVar2);
    local_8._0_1_ = 1;
    FUN_0045c6e0(&DAT_02cc31b8,local_20,uVar1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    FUN_0083e979(FUN_008675f0);
  }
  ExceptionList = local_10;
  return &DAT_02cc31b8;
}

