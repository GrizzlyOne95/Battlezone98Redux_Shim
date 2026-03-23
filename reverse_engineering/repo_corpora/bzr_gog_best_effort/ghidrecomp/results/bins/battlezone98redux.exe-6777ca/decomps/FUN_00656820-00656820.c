
void FUN_00656820(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_5c [11];
  allocator<char> local_51;
  undefined4 *local_50;
  char *local_4c;
  char *local_48;
  char *local_44;
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
  
  puStack_c = &LAB_0084d856;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  if ((DAT_02cc32a0 & 1) == 0) {
    DAT_02cc32a0 = DAT_02cc32a0 | 1;
    local_8 = 0;
    local_50 = &DAT_00878c18;
    local_4c = "apwrck";
    local_48 = "cvcnst";
    local_44 = "cvfigh";
    local_40 = "cvfighh";
    local_3c = "cvmuf";
    local_38 = "sssold";
    local_34 = "ssuser";
    local_30 = "svartl";
    local_2c = "svfigh";
    local_28 = "svhraz";
    local_24 = "svltnksvrckt";
    local_20 = "svtank";
    local_1c = "svwalk";
    uVar2 = std::allocator<char>::allocator<char>(&local_51);
    puVar3 = (undefined4 *)FUN_00416430(&local_50,local_18);
    FUN_00631030(*puVar3,puVar3[1],uVar2);
    local_8._0_1_ = 1;
    FUN_0045c6e0(&DAT_02cc3298,local_5c,uVar1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    FUN_0083e979(FUN_00867720);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

