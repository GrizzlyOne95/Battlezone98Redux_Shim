
void FUN_0065fe30(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_60 [11];
  allocator<char> local_55;
  char *local_54;
  char *local_50;
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
  
  puStack_c = &LAB_0084d956;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  if ((DAT_02cc32c8 & 1) == 0) {
    DAT_02cc32c8 = DAT_02cc32c8 | 1;
    local_8 = 0;
    local_54 = "aprepaa";
    local_50 = "apammoa";
    local_4c = "apbolt";
    local_48 = "apflsh";
    local_44 = "apmini";
    local_40 = "apstabapsstb";
    local_3c = "cspilo";
    local_38 = "cssolda";
    local_34 = "cssold";
    local_30 = "csuserb";
    local_2c = "cvfighcvltnk";
    local_28 = "cvtnk";
    local_24 = "cvhraz";
    local_20 = "cvwalk";
    local_1c = "cvhtnk";
    uVar2 = std::allocator<char>::allocator<char>(&local_55);
    puVar3 = (undefined4 *)FUN_00416430(&local_54,local_18);
    FUN_00631030(*puVar3,puVar3[1],uVar2);
    local_8._0_1_ = 1;
    FUN_0045c6e0(&DAT_02cc32cc,local_60,uVar1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    FUN_0083e979(FUN_00867760);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

