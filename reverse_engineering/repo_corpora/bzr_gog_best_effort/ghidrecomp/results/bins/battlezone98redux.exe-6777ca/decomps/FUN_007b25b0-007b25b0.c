
undefined4 * __fastcall FUN_007b25b0(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 local_110;
  int *local_100;
  undefined4 local_f4;
  undefined4 local_f0;
  int *local_ec;
  undefined4 local_e4;
  int *local_e0;
  int *local_dc;
  undefined4 local_d4;
  int *local_cc;
  undefined4 local_c4;
  int *local_c0;
  int *local_bc;
  undefined4 local_b4;
  undefined4 local_b0;
  int *local_ac;
  undefined4 local_a4;
  int *local_a0;
  int *local_9c;
  int *local_94;
  undefined4 local_90;
  int *local_8c;
  int *local_84;
  int *local_80;
  undefined4 local_7c;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_64;
  int *local_60;
  undefined4 local_5c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861273;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_OptionsInput::vftable;
  DAT_009455b8 = param_1;
  pvVar1 = operator_new(0xc994);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_64 = 0;
  }
  else {
    local_64 = FUN_0081bfb0();
  }
  local_8._0_1_ = 0;
  param_1[0x62] = local_64;
  param_1[0x61] = 0;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_6c = 0;
  }
  else {
    local_6c = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(1);
  FUN_007d2870("ioptions_center.png");
  FUN_007d2110(local_6c,0);
  uVar2 = FUN_0081cb40("input_config","back_exit");
  uVar3 = FUN_0081cb40("input_config",&DAT_0089fa80);
  uVar4 = FUN_0081cb40("input_config",&DAT_008714b0);
  uVar5 = FUN_0081cb40("input_config","strafe_right");
  uVar6 = FUN_0081cb40("input_config","strafe_left");
  uVar7 = FUN_0081cb40("input_config","forward");
  uVar8 = FUN_0081cb40("input_config",&DAT_008857d0);
  uVar9 = FUN_0081cb40("input_config","pitch_up");
  uVar10 = FUN_0081cb40("input_config","pitch_down");
  uVar11 = FUN_0081cb40("input_config","turn_right");
  uVar12 = FUN_0081cb40("input_config","turn_left");
  uVar13 = FUN_0081cb40("input_config",&DAT_0089faa4);
  uVar14 = FUN_0081cb40("input_config","shift_weapon");
  uVar15 = FUN_0081cb40("input_config","default_settings");
  uVar16 = FUN_0081cb40("input_config","joystick");
  uVar17 = FUN_0081cb40("input_config","message_one");
  uVar18 = FUN_0081cb40("input_config","message_two");
  param_1[0x5f] = uVar18;
  uVar18 = FUN_0081cb40("input_config","reserved_key");
  param_1[0x60] = uVar18;
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_74 = 0;
  }
  else {
    local_74 = FUN_007cc390("hitTheKey",0x43b40000,0x43e10000,0x43480000,0x42200000,0x20,local_6c,0)
    ;
  }
  local_8._0_1_ = 0;
  param_1[0x5d] = local_74;
  (**(code **)(*(int *)param_1[0x5d] + 0x3c))(uVar17);
  FUN_007cc6b0(0x3fa00000);
  FUN_007cc5c0(0);
  FUN_007d2110(param_1[0x5d],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_7c = 0;
  }
  else {
    local_7c = FUN_007cc390("alreadyBound",0x43960000,0x440e8000,0x43480000,0x42200000,0x20,local_6c
                            ,0);
  }
  local_8._0_1_ = 0;
  param_1[0x5e] = local_7c;
  (**(code **)(*(int *)param_1[0x5e] + 0x3c))(param_1[0x5f]);
  FUN_007cc6b0(0x3fc00000);
  FUN_007cc5c0(0);
  FUN_007d2110(param_1[0x5e],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_84 = (int *)0x0;
  }
  else {
    local_84 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_84 + 0x40))("topcrnhv.png");
  (**(code **)(*local_84 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007b2210);
  FUN_007d2110(local_84,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (pvVar1 == (void *)0x0) {
    local_8c = (int *)0x0;
  }
  else {
    local_8c = (int *)FUN_007c2480("Joystick",0,0x447ac000,0x43ab0000,0x429a0000,0xa6,0,0xc2200000,
                                   0x40a00000);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_8c + 0x40))("topcrnhv.png");
  (**(code **)(*local_8c + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar16);
  FUN_007c23e0(FUN_007b2220);
  FUN_007d2110(local_8c,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 7;
  if (pvVar1 == (void *)0x0) {
    local_94 = (int *)0x0;
  }
  else {
    local_94 = (int *)FUN_007c2480("Default",0x43d60000,0x41100000,0x44100000,0x42080000,0x20,
                                   local_6c,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007c2950(uVar15);
  FUN_007d2870("defaoff.png");
  (**(code **)(*local_94 + 0x40))("defaon.png");
  (**(code **)(*local_94 + 0x3c))("defaclk.png");
  FUN_007c23e0(FUN_007b2230);
  FUN_007c30e0(0x3f333333);
  FUN_007d2110(local_94,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 8;
  if (pvVar1 == (void *)0x0) {
    local_9c = (int *)0x0;
  }
  else {
    local_9c = (int *)FUN_007c2480("Forward",0x436d0000,0x44558000,0x437a0000,0x431d0000,0x24,
                                   local_6c,0x41700000,0x41e00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar3);
  (**(code **)(*local_9c + 0x40))("coulon.png");
  (**(code **)(*local_9c + 0x3c))("coulclk.png");
  FUN_007c23e0(FUN_007b2250);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_9c,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 9;
  if (pvVar1 == (void *)0x0) {
    local_a4 = 0;
  }
  else {
    local_a4 = FUN_007cc390("keyBindForward",0x42cc0000,0x41000000,0x42480000,0x42200000,0x20,
                            local_9c,0);
  }
  local_8._0_1_ = 0;
  param_1[0x52] = local_a4;
  (**(code **)(*(int *)param_1[0x52] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x52],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 10;
  if (pvVar1 == (void *)0x0) {
    local_ac = (int *)0x0;
  }
  else {
    local_ac = (int *)FUN_007c2480("Backward",0x44118000,0x44598000,0x43838000,0x434a0000,0x24,
                                   local_6c,0x41900000,0x425c0000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar4);
  (**(code **)(*local_ac + 0x40))("coumon.png");
  (**(code **)(*local_ac + 0x3c))("coumclk.png");
  FUN_007c23e0(FUN_007b2240);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_ac,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0xb;
  if (pvVar1 == (void *)0x0) {
    local_b4 = 0;
  }
  else {
    local_b4 = FUN_007cc390("keyBindBack",0x42dc0000,0x42500000,0x42480000,0x42200000,0x20,local_ac,
                            0);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_b4;
  (**(code **)(*(int *)param_1[0x51] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x51],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0xc;
  if (pvVar1 == (void *)0x0) {
    local_bc = (int *)0x0;
  }
  else {
    local_bc = (int *)FUN_007c2480("StrafeRight",0x44826000,0x43e60000,0x43a78000,0x43200000,0x22,
                                   local_6c,0x42040000,0xc1f00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar5);
  (**(code **)(*local_bc + 0x40))("comlon.png");
  (**(code **)(*local_bc + 0x3c))("comlclk.png");
  FUN_007c23e0(FUN_007b2290);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_bc,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0xd;
  if (pvVar1 == (void *)0x0) {
    local_c4 = 0;
  }
  else {
    local_c4 = FUN_007cc390("keyBindStrafeRight",0x432a0000,0x42b40000,0x42480000,0x42200000,0x20,
                            local_bc,0);
  }
  local_8._0_1_ = 0;
  param_1[0x56] = local_c4;
  (**(code **)(*(int *)param_1[0x56] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x56],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0xe;
  if (pvVar1 == (void *)0x0) {
    local_cc = (int *)0x0;
  }
  else {
    local_cc = (int *)FUN_007c2480("StrafeLeft",0x42700000,0x43e60000,0x43a78000,0x43200000,0x20,
                                   local_6c,0xc1a00000,0xc1f00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar6);
  (**(code **)(*local_cc + 0x40))("comlon.png");
  (**(code **)(*local_cc + 0x3c))("comlclk.png");
  FUN_007c23e0(FUN_007b2280);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_cc,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0xf;
  if (pvVar1 == (void *)0x0) {
    local_d4 = 0;
  }
  else {
    local_d4 = FUN_007cc390("keyBindStrafeLeft",0x42c00000,0x42b40000,0x42480000,0x42200000,0x20,
                            local_cc,0);
  }
  local_8._0_1_ = 0;
  param_1[0x55] = local_d4;
  (**(code **)(*(int *)param_1[0x55] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x55],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x10;
  if (pvVar1 == (void *)0x0) {
    local_dc = (int *)0x0;
  }
  else {
    local_dc = (int *)FUN_007c2480("Turbo",0x44118000,0x42700000,0x43838000,0x434a0000,0x20,local_6c
                                   ,0x41a00000,0xc2480000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar7);
  (**(code **)(*local_dc + 0x40))("coumon.png");
  (**(code **)(*local_dc + 0x3c))("coumclk.png");
  FUN_007c23e0(FUN_007b22a0);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_dc,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0x11;
  if (pvVar1 == (void *)0x0) {
    local_e4 = 0;
  }
  else {
    local_e4 = FUN_007cc390("keyBindTurbo",0x42dc0000,0x42b40000,0x42480000,0x42200000,0x1020,
                            local_dc,0);
  }
  local_8._0_1_ = 0;
  param_1[0x57] = local_e4;
  (**(code **)(*(int *)param_1[0x57] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x57],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x12;
  if (pvVar1 == (void *)0x0) {
    local_ec = (int *)0x0;
  }
  else {
    local_ec = (int *)FUN_007c2480(&DAT_0089faec,0x446dc000,0x44558000,0x437a0000,0x431d0000,0x26,
                                   local_6c,0xc1880000,0x41e00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar8);
  (**(code **)(*local_ec + 0x40))("coulon.png");
  (**(code **)(*local_ec + 0x3c))("coulclk.png");
  FUN_007c23e0(FUN_007b22b0);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_ec,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0x13;
  if (pvVar1 == (void *)0x0) {
    local_f4 = 0;
  }
  else {
    local_f4 = FUN_007cc390("keyBindJump",0x42b40000,0x41000000,0x42480000,0x42200000,0x20,local_ec,
                            0);
  }
  local_8._0_1_ = 0;
  param_1[0x58] = local_f4;
  (**(code **)(*(int *)param_1[0x58] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x58],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x14;
  if (pvVar1 == (void *)0x0) {
    local_a0 = (int *)0x0;
  }
  else {
    local_a0 = (int *)FUN_007c2480(&DAT_0089fb04,0x436d0000,0x429e0000,0x437a0000,0x431d0000,0x20,
                                   local_6c,0x41a00000,0xc1c80000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar9);
  (**(code **)(*local_a0 + 0x40))("coulon.png");
  (**(code **)(*local_a0 + 0x3c))("coulclk.png");
  FUN_007c23e0(FUN_007b2260);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_a0,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0x15;
  if (pvVar1 == (void *)0x0) {
    local_b0 = 0;
  }
  else {
    local_b0 = FUN_007cc390("keyBindUp",0x42c80000,0x42b40000,0x42480000,0x42200000,0x20,local_a0,0)
    ;
  }
  local_8._0_1_ = 0;
  param_1[0x53] = local_b0;
  (**(code **)(*(int *)param_1[0x53] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x53],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x16;
  if (pvVar1 == (void *)0x0) {
    local_c0 = (int *)0x0;
  }
  else {
    local_c0 = (int *)FUN_007c2480(&DAT_0089fb7c,0x446dc000,0x429e0000,0x437a0000,0x431d0000,0x22,
                                   local_6c,0xc1200000,0xc1c80000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar10);
  (**(code **)(*local_c0 + 0x40))("coulon.png");
  (**(code **)(*local_c0 + 0x3c))("coulclk.png");
  FUN_007c23e0(FUN_007b2270);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_c0,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0x17;
  if (pvVar1 == (void *)0x0) {
    local_5c = 0;
  }
  else {
    local_5c = FUN_007cc390("keyBindDown",0x42b40000,0x42b40000,0x42480000,0x42200000,0x20,local_c0,
                            0);
  }
  local_8._0_1_ = 0;
  param_1[0x54] = local_5c;
  (**(code **)(*(int *)param_1[0x54] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x54],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x18;
  if (pvVar1 == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_007c2480("Right",0x448a4000,0x43710000,0x437a0000,0x431d0000,0x22,local_6c
                                   ,0xc0e00000,0xc1a00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar11);
  (**(code **)(*local_e0 + 0x40))("coulon.png");
  (**(code **)(*local_e0 + 0x3c))("coulclk.png");
  FUN_007c23e0(FUN_007b22c0);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_e0,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0x19;
  if (pvVar1 == (void *)0x0) {
    local_f0 = 0;
  }
  else {
    local_f0 = FUN_007cc390("keyBindRight",0x42b40000,0x42b40000,0x42480000,0x42200000,0x20,local_e0
                            ,0);
  }
  local_8._0_1_ = 0;
  param_1[0x59] = local_f0;
  (**(code **)(*(int *)param_1[0x59] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x59],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x1a;
  if (pvVar1 == (void *)0x0) {
    local_100 = (int *)0x0;
  }
  else {
    local_100 = (int *)FUN_007c2480(&DAT_0089fb50,0x42a40000,0x43710000,0x437a0000,0x431d0000,0x20,
                                    local_6c,0x41a00000,0xc1b00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar12);
  (**(code **)(*local_100 + 0x40))("coulon.png");
  (**(code **)(*local_100 + 0x3c))("coulclk.png");
  FUN_007c23e0(FUN_007b22d0);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_100,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0x1b;
  if (pvVar1 == (void *)0x0) {
    local_110 = 0;
  }
  else {
    local_110 = FUN_007cc390("keyBindLeft",0x42c80000,0x42b40000,0x42480000,0x42200000,0x20,
                             local_100,0);
  }
  local_8._0_1_ = 0;
  param_1[0x5a] = local_110;
  (**(code **)(*(int *)param_1[0x5a] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x5a],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x1c;
  if (pvVar1 == (void *)0x0) {
    local_60 = (int *)0x0;
  }
  else {
    local_60 = (int *)FUN_007c2480(&DAT_0089fb68,0x42a40000,0x442d0000,0x437a0000,0x431d0000,0x24,
                                   local_6c,0x41a00000,0x41f00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar13);
  (**(code **)(*local_60 + 0x40))("coulon.png");
  (**(code **)(*local_60 + 0x3c))("coulclk.png");
  FUN_007c23e0(FUN_007b22e0);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_60,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0x1d;
  if (pvVar1 == (void *)0x0) {
    local_70 = 0;
  }
  else {
    local_70 = FUN_007cc390("keyBindFire",0x42cc0000,0x41000000,0x42480000,0x42200000,0x20,local_60,
                            0);
  }
  local_8._0_1_ = 0;
  param_1[0x5b] = local_70;
  (**(code **)(*(int *)param_1[0x5b] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x5b],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x1e;
  if (pvVar1 == (void *)0x0) {
    local_80 = (int *)0x0;
  }
  else {
    local_80 = (int *)FUN_007c2480("Weapon",0x448a4000,0x442d0000,0x437a0000,0x431d0000,0x26,
                                   local_6c,0xc1a00000,0x41f00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007c2950(uVar14);
  (**(code **)(*local_80 + 0x40))("coulon.png");
  (**(code **)(*local_80 + 0x3c))("coulclk.png");
  FUN_007c23e0(FUN_007b22f0);
  FUN_007c30e0(0x3f400000);
  FUN_007d2110(local_80,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0x1f;
  if (pvVar1 == (void *)0x0) {
    local_90 = 0;
  }
  else {
    local_90 = FUN_007cc390("keyBindWeapon",0x42cc0000,0x41000000,0x42480000,0x42200000,0x20,
                            local_80,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x5c] = local_90;
  (**(code **)(*(int *)param_1[0x5c] + 0x3c))(&DAT_0088d940);
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3f400000);
  FUN_007d2110(param_1[0x5c],0);
  FUN_007b5480();
  ExceptionList = local_10;
  return param_1;
}

