
undefined4 * __fastcall FUN_0078a9f0(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 local_3c;
  undefined4 local_34;
  int *local_2c;
  undefined4 local_24;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e988;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_Invite::vftable;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_24 = 0;
  }
  else {
    local_24 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(1);
  FUN_007d2870("keyOptions_center.png");
  FUN_007d2110(local_24,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_2c = (int *)0x0;
  }
  else {
    local_2c = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_2c + 0x40))("topcrnhv.png");
  (**(code **)(*local_2c + 0x3c))("topcrnck.png");
  uVar2 = FUN_0081cb40("options",&DAT_008714b0);
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_0078a7c0);
  FUN_007d2110(local_2c,0);
  pvVar1 = operator_new(0x180);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_34 = 0;
  }
  else {
    local_34 = FUN_007c9de0("FriendList",0x43820000,0x43200000,0x44340000,0x44070000,FUN_0078a7a0,
                            FUN_0078a7b0,0,local_24,0xff00ff00,0x3f800000);
  }
  local_8._0_1_ = 0;
  DAT_009454f8 = local_34;
  FUN_007cb3e0(FUN_0078a7d0);
  FUN_007d2110(DAT_009454f8,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = FUN_007c2480("InviteFriendButton",0x43960000,0x44610000,0x43960000,0x42700000,0x20,
                            local_24,0,0x41000000);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x51] = local_3c;
  FUN_007d2870("multi_createGame_button_off.png");
  (**(code **)(*(int *)param_1[0x51] + 0x40))("multi_createGame_button_over.png");
  (**(code **)(*(int *)param_1[0x51] + 0x3c))("multi_createGame_button_on.png");
  uVar2 = FUN_0081cb40("multi_common","invite_friend");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_0078a790);
  FUN_007d2110(param_1[0x51],0);
  DAT_009454fc = param_1;
  piVar3 = (int *)FUN_007647a0();
  (**(code **)(*piVar3 + 0x14))();
  ExceptionList = local_10;
  return param_1;
}

