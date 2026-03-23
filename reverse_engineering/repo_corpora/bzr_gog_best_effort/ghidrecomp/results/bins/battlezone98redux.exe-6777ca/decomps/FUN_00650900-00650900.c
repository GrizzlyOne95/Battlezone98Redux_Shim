
void FUN_00650900(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_48 [11];
  allocator<char> local_3d;
  undefined4 *local_3c;
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
  
  puStack_c = &LAB_0084d7d6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  if ((DAT_02cc3280 & 1) == 0) {
    DAT_02cc3280 = DAT_02cc3280 | 1;
    local_8 = 0;
    local_3c = &DAT_00878c18;
    local_38 = "svapcq";
    local_34 = "svapcr";
    local_30 = "svtank";
    local_2c = "svhraz";
    local_28 = "svfigh";
    local_24 = "cvmufa";
    local_20 = "cvslfa";
    local_1c = "cvscav";
    uVar2 = std::allocator<char>::allocator<char>(&local_3d);
    puVar3 = (undefined4 *)FUN_00416430(&local_3c,local_18);
    FUN_00631030(*puVar3,puVar3[1],uVar2);
    local_8._0_1_ = 1;
    FUN_0045c6e0(&DAT_02cc3284,local_48,uVar1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    FUN_0083e979(FUN_00867700);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

