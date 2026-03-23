
void FUN_00634d10(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_4c [11];
  allocator<char> local_41;
  char *local_40;
  char *local_3c;
  char *local_38;
  char *local_34;
  char *local_30;
  char *local_2c;
  char *local_28;
  char *local_24;
  char *local_20;
  char *local_1c;
  undefined1 local_18 [4];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084d416;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  if ((DAT_02cc31d4 & 1) == 0) {
    DAT_02cc31d4 = DAT_02cc31d4 | 1;
    local_8 = 0;
    local_40 = "cvturr";
    local_3c = "cvfigh";
    local_38 = "cvtnk";
    local_34 = "cvltnk";
    local_30 = "cvrckt";
    local_2c = "bvscav";
    local_28 = "bvturr";
    local_24 = "bvapcb";
    local_20 = "bvraz";
    local_1c = "cvfighf";
    uVar2 = std::allocator<char>::allocator<char>(&local_41);
    puVar3 = (undefined4 *)FUN_00416430(&local_40,local_18);
    FUN_00631030(*puVar3,puVar3[1],uVar2);
    local_8._0_1_ = 1;
    FUN_0045c6e0(&DAT_02cc31cc,local_4c,uVar1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    FUN_0083e979(FUN_00867610);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

