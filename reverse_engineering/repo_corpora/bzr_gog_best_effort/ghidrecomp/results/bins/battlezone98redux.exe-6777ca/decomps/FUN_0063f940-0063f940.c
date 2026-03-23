
void FUN_0063f940(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_40 [11];
  allocator<char> local_35;
  undefined4 *local_34;
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
  
  puStack_c = &LAB_0084d596;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  if ((DAT_02cc3214 & 1) == 0) {
    DAT_02cc3214 = DAT_02cc3214 | 1;
    local_8 = 0;
    local_34 = &DAT_00878c18;
    local_30 = "cvfigh";
    local_2c = "cvltnk";
    local_28 = "cvtnk";
    local_24 = "cvhtnk";
    local_20 = "cvrckt";
    local_1c = "cvtnkb";
    uVar2 = std::allocator<char>::allocator<char>(&local_35);
    puVar3 = (undefined4 *)FUN_00416430(&local_34,local_18);
    FUN_00631030(*puVar3,puVar3[1],uVar2);
    local_8._0_1_ = 1;
    FUN_0045c6e0(&DAT_02cc3218,local_40,uVar1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    FUN_0083e979(FUN_00867670);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

