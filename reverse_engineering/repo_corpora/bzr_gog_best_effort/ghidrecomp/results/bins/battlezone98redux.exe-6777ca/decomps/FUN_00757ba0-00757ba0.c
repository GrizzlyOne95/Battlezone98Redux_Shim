
undefined4 * FUN_00757ba0(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 local_20;
  undefined4 local_1c;
  int *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c5f9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007536b0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *local_14 = cNetFriendsSteam::vftable;
  FUN_007586a0(local_14,FUN_00757e00);
  local_8._0_1_ = 1;
  FUN_00758730(local_14,FUN_00757f60);
  local_8._0_1_ = 2;
  FUN_007587c0(local_14,FUN_00757fa0);
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_00757da0();
  iVar2 = FUN_00757b80();
  if (iVar2 == 0) {
    local_20 = 1;
    puVar3 = (undefined1 *)FUN_00753940(&local_20);
    *puVar3 = 0;
  }
  else {
    local_1c = 1;
    local_18 = (int *)FUN_00757b80();
    uVar1 = (**(code **)(*local_18 + 0x1c))(0x72ede);
    puVar3 = (undefined1 *)FUN_00753940(&local_1c);
    *puVar3 = uVar1;
  }
  ExceptionList = local_10;
  return local_14;
}

