
void FUN_0065b130(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_7c [11];
  allocator<char> local_71;
  undefined4 *local_70;
  char *local_6c;
  char *local_68;
  char *local_64;
  char *local_60;
  char *local_5c;
  char *local_58;
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
  
  puStack_c = &LAB_0084d8d6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  if ((DAT_02cc32b8 & 1) == 0) {
    DAT_02cc32b8 = DAT_02cc32b8 | 1;
    local_8 = 0;
    local_70 = &DAT_00878c18;
    local_6c = "cspilo";
    local_68 = "sssold";
    local_64 = " ssusera";
    local_60 = "svapca";
    local_5c = "svapcb";
    local_58 = "svfighsvturr";
    local_54 = "svapcc";
    local_50 = "svapcd";
    local_4c = "svapce";
    local_48 = "svapcf";
    local_44 = "svapcg";
    local_40 = "svapch";
    local_3c = "svapci";
    local_38 = "svapcj";
    local_34 = "svapck";
    local_30 = "svapcl";
    local_2c = "svapcm";
    local_28 = "svapcn";
    local_24 = "svapco";
    local_20 = "svapcp";
    local_1c = "svapcs";
    uVar2 = std::allocator<char>::allocator<char>(&local_71);
    puVar3 = (undefined4 *)FUN_00416430(&local_70,local_18);
    FUN_00631030(*puVar3,puVar3[1],uVar2);
    local_8._0_1_ = 1;
    FUN_0045c6e0(&DAT_02cc32b0,local_7c,uVar1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    FUN_0083e979(FUN_00867740);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

