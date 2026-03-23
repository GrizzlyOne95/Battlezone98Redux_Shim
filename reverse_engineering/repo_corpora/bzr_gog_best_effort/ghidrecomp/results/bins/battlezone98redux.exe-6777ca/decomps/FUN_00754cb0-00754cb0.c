
void FUN_00754cb0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined1 local_95;
  undefined4 *local_94;
  uint local_90;
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c33a;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_90 = 0;
  FUN_007536b0(local_14);
  local_8 = 0;
  FUN_00755cb0(0);
  local_8._0_1_ = 1;
  FUN_00755e20(0);
  local_8._0_1_ = 2;
  FUN_00755f90(0);
  local_8._0_1_ = 3;
  FUN_00756100(0);
  local_8._0_1_ = 4;
  *local_94 = cNetFriendsGog::vftable;
  local_94[0xc] = cNetFriendsGog::vftable;
  local_94[0xe] = cNetFriendsGog::vftable;
  local_94[0x10] = cNetFriendsGog::vftable;
  local_94[0x12] = cNetFriendsGog::vftable;
  FUN_00426a60(&DAT_02cf0000,0);
  local_8._0_1_ = 5;
  FUN_00426a60("tro_cam.zfs",0);
  local_8 = CONCAT31(local_8._1_3_,6);
  local_90 = local_90 | 1;
  uVar2 = FUN_00662ec0(local_74,local_2c,local_44);
  local_8 = 7;
  local_90 = local_90 | 2;
  cVar1 = FUN_00667410(uVar2);
  if (cVar1 == '\0') {
    FUN_00426a60("tro_cam",0);
    local_8 = 8;
    local_90 = local_90 | 4;
    local_a4 = FUN_00662ec0(local_8c,local_2c,local_5c);
    local_8 = 9;
    local_90 = local_90 | 8;
    local_a0 = local_a4;
    cVar1 = FUN_00667410(local_a4);
    if (cVar1 == '\0') {
      local_9c = 0;
      goto LAB_00754ea8;
    }
  }
  local_9c = 1;
LAB_00754ea8:
  local_95 = (undefined1)local_9c;
  local_8 = 8;
  if ((local_90 & 8) != 0) {
    local_90 = local_90 & 0xfffffff7;
    FUN_004180b0();
  }
  local_8 = 7;
  if ((local_90 & 4) != 0) {
    local_90 = local_90 & 0xfffffffb;
    FUN_004180b0();
  }
  local_8 = 6;
  if ((local_90 & 2) != 0) {
    local_90 = local_90 & 0xfffffffd;
    FUN_004180b0();
  }
  local_8 = 5;
  if ((local_90 & 1) != 0) {
    local_90 = local_90 & 0xfffffffe;
    FUN_004180b0();
  }
  local_a8 = 1;
  puVar3 = (undefined1 *)FUN_00753940(&local_a8);
  *puVar3 = local_95;
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_004180b0();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

