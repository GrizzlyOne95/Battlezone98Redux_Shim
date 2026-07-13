
void __fastcall FUN_00796880(undefined4 *param_1)

{
  undefined1 uVar1;
  char cVar2;
  undefined4 uVar3;
  void *pvVar4;
  int *piVar5;
  int iVar6;
  char *_Str;
  uint uVar7;
  longlong lVar8;
  undefined4 uVar9;
  undefined1 *puVar10;
  int *local_1f8;
  int *local_1e8;
  int *local_1e4;
  undefined4 local_1d8;
  undefined4 local_1d4;
  int *local_1d0;
  undefined4 local_1c8;
  undefined4 local_1b8;
  undefined4 local_1a8;
  undefined4 local_198;
  undefined4 local_188;
  undefined4 local_16c;
  undefined4 local_168;
  int *local_164;
  undefined4 local_158;
  int *local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_fc;
  undefined4 local_f8;
  int *local_f4;
  int *local_ec;
  undefined4 local_e8;
  int *local_d8;
  int *local_c4;
  uint local_b8;
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [48];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f578;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0();
  local_8 = 0;
  *param_1 = cUI_Multiplayer_Create::vftable;
  vector<>();
  local_8._0_1_ = 1;
  FUN_005df1f0();
  lVar8 = FUN_00822ea0();
  *(longlong *)(param_1 + 0x52) = lVar8 + 500;
  uVar3 = FUN_00764760();
  param_1[0x6f] = uVar3;
  uVar1 = FUN_00742cf0();
  *(undefined1 *)(param_1 + 0x75) = uVar1;
  *(undefined1 *)((int)param_1 + 0x1d5) = 0;
  DAT_0094555c = param_1;
  pvVar4 = operator_new(0x144);
  local_8._0_1_ = 2;
  if (pvVar4 == (void *)0x0) {
    local_1d8 = 0;
  }
  else {
    local_1d8 = FUN_007d1cc0();
  }
  local_8._0_1_ = 1;
  param_1[0x54] = local_1d8;
  FUN_007d2870();
  FUN_007d2110();
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 3;
  if (pvVar4 == (void *)0x0) {
    local_1e8 = (int *)0x0;
  }
  else {
    local_1e8 = (int *)FUN_007cc390();
  }
  local_8._0_1_ = 1;
  FUN_0081cb40();
  (**(code **)(*local_1e8 + 0x3c))();
  FUN_007d2110();
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 4;
  if (pvVar4 == (void *)0x0) {
    local_1f8 = (int *)0x0;
  }
  else {
    local_1f8 = (int *)FUN_007cc390();
  }
  local_8._0_1_ = 1;
  FUN_0081cb40();
  (**(code **)(*local_1f8 + 0x3c))();
  FUN_007d2110();
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 5;
  if (pvVar4 == (void *)0x0) {
    local_1d0 = (int *)0x0;
  }
  else {
    local_1d0 = (int *)FUN_007cc390();
  }
  local_8._0_1_ = 1;
  FUN_0081cb40();
  (**(code **)(*local_1d0 + 0x3c))();
  FUN_007d2110();
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 6;
  if (pvVar4 == (void *)0x0) {
    local_164 = (int *)0x0;
  }
  else {
    local_164 = (int *)FUN_007cc390();
  }
  local_8._0_1_ = 1;
  FUN_0081cb40();
  (**(code **)(*local_164 + 0x3c))();
  (**(code **)(*local_164 + 0x24))();
  FUN_007d2110();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 7;
  if (pvVar4 == (void *)0x0) {
    local_1d4 = 0;
  }
  else {
    basic_string<>();
    local_1d4 = FUN_007c3e30("SyncJoinButton",0x42480000,0x43ff0000,0x43960000);
  }
  local_8._0_1_ = 1;
  param_1[0x61] = local_1d4;
  FUN_007d2110();
  FUN_0041fe40();
  pvVar4 = operator_new(0x1ec);
  local_8._0_1_ = 8;
  if (pvVar4 == (void *)0x0) {
    local_16c = 0;
  }
  else {
    local_16c = FUN_007c2480();
  }
  local_8 = CONCAT31(local_8._1_3_,1);
  param_1[0x58] = local_16c;
  FUN_007d2870();
  (**(code **)(*(int *)param_1[0x58] + 0x40))();
  (**(code **)(*(int *)param_1[0x58] + 0x3c))();
  FUN_0081cb40();
  FUN_007c2950();
  FUN_007c23e0();
  piVar5 = (int *)FUN_007647a0();
  cVar2 = (**(code **)(*piVar5 + 8))();
  if (cVar2 == '\0') {
    (**(code **)(*(int *)param_1[0x58] + 0x24))();
  }
  FUN_007d2110();
  iVar6 = FUN_00764980();
  if (iVar6 != 0) {
    pvVar4 = operator_new(0x1ec);
    local_8._0_1_ = 9;
    if (pvVar4 == (void *)0x0) {
      local_ec = (int *)0x0;
    }
    else {
      local_ec = (int *)FUN_007c2480();
    }
    local_8._0_1_ = 1;
    FUN_007d2870();
    (**(code **)(*local_ec + 0x40))();
    (**(code **)(*local_ec + 0x3c))();
    FUN_0081cb40();
    FUN_007c2950();
    FUN_007c23e0();
    FUN_007d2110();
    pvVar4 = operator_new(0x1ec);
    local_8._0_1_ = 10;
    if (pvVar4 == (void *)0x0) {
      local_f4 = (int *)0x0;
    }
    else {
      local_f4 = (int *)FUN_007c2480("RefreshButton");
    }
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_007d2870();
    (**(code **)(*local_f4 + 0x40))();
    (**(code **)(*local_f4 + 0x3c))();
    FUN_0081cb40();
    FUN_007c2950();
    FUN_007c23e0();
    FUN_007d2110();
  }
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0xb;
  if (pvVar4 == (void *)0x0) {
    local_fc = 0;
  }
  else {
    basic_string<>();
    local_fc = FUN_007c3e30("TeamButton",0x42480000,0x440fc000,0x43960000,0x42700000,0x20);
  }
  local_8._0_1_ = 1;
  param_1[0x62] = local_fc;
  FUN_007d2110();
  FUN_0041fe40();
  (**(code **)(*(int *)param_1[0x62] + 0x24))();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0xc;
  if (pvVar4 == (void *)0x0) {
    local_104 = 0;
  }
  else {
    basic_string<>();
    local_104 = FUN_007c3e30("CommSatButton",0x43c80000,0x43ff0000,0x43960000,0x42700000,0x20,
                             param_1[0x54]);
  }
  local_8._0_1_ = 1;
  param_1[99] = local_104;
  FUN_007d2110();
  FUN_0041fe40();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0xd;
  if (pvVar4 == (void *)0x0) {
    local_10c = 0;
  }
  else {
    basic_string<>();
    local_10c = FUN_007c3e30("BarracksButton",0x43c80000,0x440fc000,0x43960000,0x42700000,0x20,
                             param_1[0x54]);
  }
  local_8._0_1_ = 1;
  param_1[100] = local_10c;
  FUN_007d2110();
  FUN_0041fe40();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0xe;
  if (pvVar4 == (void *)0x0) {
    local_114 = 0;
  }
  else {
    basic_string<>();
    local_114 = FUN_007c3e30("TimeLimitButton",0x443e0000,0x43eb0000,0x43960000,0x42700000,0x20,
                             param_1[0x54]);
  }
  local_8._0_1_ = 1;
  param_1[0x65] = local_114;
  FUN_007d2110();
  FUN_0041fe40();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0xf;
  if (pvVar4 == (void *)0x0) {
    local_11c = 0;
  }
  else {
    basic_string<>();
    local_11c = FUN_007c3e30("PlayerLivesButton",0x443e0000,0x43eb0000,0x43960000,0x42700000,0x20,
                             param_1[0x54]);
  }
  local_8._0_1_ = 1;
  param_1[0x66] = local_11c;
  FUN_007d2110();
  FUN_0041fe40();
  (**(code **)(*(int *)param_1[0x66] + 0x24))();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0x10;
  if (pvVar4 == (void *)0x0) {
    local_124 = 0;
  }
  else {
    basic_string<>();
    local_124 = FUN_007c3e30("PlayerLimitButton",0x443e0000,0x44034000,0x43960000,0x42700000,0x20,
                             param_1[0x54],FUN_00795e10);
  }
  local_8._0_1_ = 1;
  param_1[0x67] = local_124;
  FUN_007d2110();
  FUN_0041fe40();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0x11;
  if (pvVar4 == (void *)0x0) {
    local_12c = 0;
  }
  else {
    basic_string<>();
    local_12c = FUN_007c3e30("AnyNationButton",0x443e0000,0x44110000,0x43960000,0x42700000,0x20,
                             param_1[0x54],FUN_00795d70);
  }
  local_8._0_1_ = 1;
  param_1[0x68] = local_12c;
  FUN_007d2110();
  FUN_0041fe40();
  (**(code **)(*(int *)param_1[0x68] + 0x24))();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0x12;
  if (pvVar4 == (void *)0x0) {
    local_134 = 0;
  }
  else {
    basic_string<>("Sniper");
    local_134 = FUN_007c3e30("SniperButton",0x44848000,0x43eb0000,0x43960000,0x42700000,0x20,
                             param_1[0x54],FUN_00795ed0,FUN_00795ed0);
  }
  local_8._0_1_ = 1;
  param_1[0x69] = local_134;
  FUN_007d2110();
  FUN_0041fe40();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0x13;
  if (pvVar4 == (void *)0x0) {
    local_13c = 0;
  }
  else {
    basic_string<>("Kill_Limit");
    local_13c = FUN_007c3e30("KillLimitButton",0x44848000,0x44034000,0x43960000,0x42700000,0x20,
                             param_1[0x54],FUN_00795e30,FUN_00795eb0);
  }
  local_8._0_1_ = 1;
  param_1[0x6a] = local_13c;
  FUN_007d2110();
  FUN_0041fe40();
  pvVar4 = operator_new(0x158);
  local_8._0_1_ = 0x14;
  if (pvVar4 == (void *)0x0) {
    local_144 = 0;
  }
  else {
    basic_string<>("Splinter");
    local_144 = FUN_007c3e30("SplinterButton",0x44848000,0x44034000,0x43960000,0x42700000,0x20,
                             param_1[0x54],FUN_00795ef0,FUN_00795ef0);
  }
  local_8._0_1_ = 1;
  param_1[0x6b] = local_144;
  FUN_007d2110();
  FUN_0041fe40();
  (**(code **)(*(int *)param_1[0x6b] + 0x24))();
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 0x15;
  if (pvVar4 == (void *)0x0) {
    local_14c = (int *)0x0;
  }
  else {
    local_14c = (int *)FUN_007cc390("Lobby",0x43020000);
  }
  local_8._0_1_ = 1;
  FUN_0081cb40();
  (**(code **)(*local_14c + 0x3c))();
  FUN_007d2110();
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 0x16;
  if (pvVar4 == (void *)0x0) {
    local_1e4 = (int *)0x0;
  }
  else {
    local_1e4 = (int *)FUN_007cc390("Lobby",0x444a8000,0x44244000);
  }
  local_8._0_1_ = 1;
  FUN_0081cb40();
  (**(code **)(*local_1e4 + 0x3c))();
  FUN_007d2110();
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 0x17;
  if (pvVar4 == (void *)0x0) {
    local_c4 = (int *)0x0;
  }
  else {
    local_c4 = (int *)FUN_007cc390("Lobby",0x43020000,0x442d4000,0x43960000);
  }
  local_8._0_1_ = 1;
  FUN_0081cb40();
  (**(code **)(*local_c4 + 0x3c))();
  FUN_007d2110();
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 0x18;
  if (pvVar4 == (void *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_007cc390("Lobby",0x43e10000,0x442d4000,0x43480000,0x422c0000);
  }
  local_8._0_1_ = 1;
  FUN_0081cb40();
  (**(code **)(*local_d8 + 0x3c))();
  FUN_007d2110();
  pvVar4 = operator_new(0x4c);
  local_8._0_1_ = 0x19;
  if (pvVar4 == (void *)0x0) {
    local_e8 = 0;
  }
  else {
    local_e8 = FUN_007a3160();
  }
  local_8._0_1_ = 1;
  param_1[0x72] = local_e8;
  pvVar4 = operator_new(0x34);
  local_8._0_1_ = 0x1a;
  if (pvVar4 == (void *)0x0) {
    local_f8 = 0;
  }
  else {
    local_f8 = FUN_007a9590();
  }
  local_8._0_1_ = 1;
  param_1[0x73] = local_f8;
  pvVar4 = operator_new(0x1ec);
  local_8._0_1_ = 0x1b;
  if (pvVar4 == (void *)0x0) {
    local_108 = 0;
  }
  else {
    local_108 = FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0);
  }
  local_8._0_1_ = 1;
  param_1[0x55] = local_108;
  FUN_007d2870();
  (**(code **)(*(int *)param_1[0x55] + 0x40))();
  (**(code **)(*(int *)param_1[0x55] + 0x3c))();
  uVar3 = FUN_0081cb40("multi_common",&DAT_008714b0);
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_00795bf0);
  FUN_007d2110(param_1[0x55],0);
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 0x1c;
  if (pvVar4 == (void *)0x0) {
    local_118 = 0;
  }
  else {
    local_118 = FUN_007cc390("RoomName",0,0,0x44b40000,0x41f00000,0x9020,param_1[0x54],0);
  }
  local_8._0_1_ = 1;
  param_1[0x5d] = local_118;
  FUN_007d2110(param_1[0x5d],0);
  param_1[0x5c] = 0;
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 0x1d;
  if (pvVar4 == (void *)0x0) {
    local_128 = 0;
  }
  else {
    local_128 = FUN_007cc390("RoomType",0x42fa0000,0x4480c000,0x437a0000,0x41f00000,0x8020,0,0);
  }
  local_8._0_1_ = 1;
  param_1[0x5e] = local_128;
  FUN_007cc6b0(0x3fa00000);
  FUN_007d2110(param_1[0x5e],0);
  pvVar4 = operator_new(0x1ec);
  local_8._0_1_ = 0x1e;
  if (pvVar4 == (void *)0x0) {
    local_138 = 0;
  }
  else {
    local_138 = FUN_007c2480("Create",0,0,0x43ab0000,0x429a0000,0xa2,0,0xc2200000,0);
  }
  local_8._0_1_ = 1;
  param_1[0x56] = local_138;
  FUN_007d2870("topcorner.png");
  (**(code **)(*(int *)param_1[0x56] + 0x40))("topcrnhv.png");
  (**(code **)(*(int *)param_1[0x56] + 0x3c))("topcrnck.png");
  uVar3 = FUN_0081cb40("multi_common","launch");
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_00795c10);
  (**(code **)(*(int *)param_1[0x56] + 0x24))(0);
  FUN_007d2110(param_1[0x56],0);
  pvVar4 = operator_new(0x295c);
  local_8._0_1_ = 0x1f;
  if (pvVar4 == (void *)0x0) {
    local_148 = 0;
  }
  else {
    local_148 = FUN_007ce140(0,"chatText",0x443b8000,0x442f0000,0x44110000,0x435c0000,FUN_00795c50,
                             FUN_00795c60,0x8020,param_1[0x54]);
  }
  local_8._0_1_ = 1;
  param_1[0x70] = local_148;
  FUN_007d3f20(1);
  FUN_007d2110(param_1[0x70],0);
  DAT_00945558 = param_1[0x70];
  pvVar4 = operator_new(0x968);
  local_8._0_1_ = 0x20;
  if (pvVar4 == (void *)0x0) {
    local_158 = 0;
  }
  else {
    local_158 = FUN_007cf410(1,1,0x2a,"CreateTextEntry",0x443e0000,0x446c4000,0x44110000,0x42200000,
                             0x8020,param_1[0x54]);
  }
  local_8._0_1_ = 1;
  param_1[0x74] = local_158;
  CMFCToolBarsListPropertyPage::EnableUserDefinedToolbars
            ((CMFCToolBarsListPropertyPage *)param_1[0x74],0xfa);
  FUN_007cf940(FUN_00795f50);
  FUN_007d2110(param_1[0x74],0);
  pvVar4 = operator_new(0x50);
  local_8._0_1_ = 0x21;
  if (pvVar4 == (void *)0x0) {
    local_168 = 0;
  }
  else {
    local_168 = FUN_007a8160(param_1[0x54],param_1[0x74],0x43020000,0x44390000,0x440c0000,0x437a0000
                             ,0);
  }
  local_8._0_1_ = 1;
  param_1[0x71] = local_168;
  basic_string<>("netveh.odf");
  local_8._0_1_ = 0x22;
  puVar10 = local_74;
  FUN_00764780(puVar10);
  FUN_00766900(puVar10);
  FUN_00426b10(0,0,0);
  local_8._0_1_ = 0x23;
  FUN_00426a60(&DAT_02cf2000,0);
  local_8._0_1_ = 0x24;
  FUN_00426af0("multi.ini");
  FUN_00417fd0(local_a4);
  local_8._0_1_ = 0x25;
  uVar3 = FUN_0041f870();
  FUN_00426c30(uVar3);
  local_8._0_1_ = 0x24;
  ~basic_string<>();
  iVar6 = FUN_00426cf0("multi","vehicle",0,0);
  _Str = (char *)FUN_00426cf0("multi","faction",0,0);
  if ((iVar6 != 0) && (_Str != (char *)0x0)) {
    basic_string<>(iVar6);
    local_8._0_1_ = 0x26;
    puVar10 = local_8c;
    iVar6 = atoi(_Str);
    FUN_00764780(iVar6,puVar10);
    FUN_00766410(iVar6,puVar10);
    local_8._0_1_ = 0x24;
    ~basic_string<>();
  }
  pvVar4 = operator_new(0x1ec);
  local_8._0_1_ = 0x27;
  if (pvVar4 == (void *)0x0) {
    local_188 = 0;
  }
  else {
    local_188 = FUN_007c2480("mapFilterToggle",0x43600000,0x42c00000,0x43580000,0x42080000,0x20,
                             param_1[0x54],0,0);
  }
  local_8._0_1_ = 0x24;
  param_1[0x59] = local_188;
  FUN_007d2870("dropover.png");
  (**(code **)(*(int *)param_1[0x59] + 0x40))("dropon.png");
  (**(code **)(*(int *)param_1[0x59] + 0x3c))("dropon.png");
  FUN_007c23e0(FUN_00795f10);
  FUN_007d2110(param_1[0x59],0);
  pvVar4 = operator_new(0x1ec);
  local_8._0_1_ = 0x28;
  if (pvVar4 == (void *)0x0) {
    local_198 = 0;
  }
  else {
    local_198 = FUN_007c2480("mapFilterBG",0x432e0000,0x43080000,0x43898000,0x43520000,0x20,
                             param_1[0x54],0,0);
  }
  local_8._0_1_ = 0x24;
  param_1[0x5a] = local_198;
  FUN_007d2870("Filterdn2.png");
  (**(code **)(*(int *)param_1[0x5a] + 0x40))("Filterdn2.png");
  (**(code **)(*(int *)param_1[0x5a] + 0x3c))("Filterdn2.png");
  (**(code **)(*(int *)param_1[0x5a] + 0x24))(0);
  FUN_007c23e0(FUN_00795f10);
  FUN_007d2110(param_1[0x5a],0);
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 0x29;
  if (pvVar4 == (void *)0x0) {
    local_1a8 = 0;
  }
  else {
    local_1a8 = FUN_007cc390("currentFilter",0x437f0000,0x42ce0000,0x43160000,0x41b80000,0x20,
                             param_1[0x54],0);
  }
  local_8._0_1_ = 0x24;
  param_1[0x5b] = local_1a8;
  (**(code **)(*(int *)param_1[0x5b] + 0x3c))(&DAT_008a1ad8);
  FUN_007d2110(param_1[0x5b],0);
  pvVar4 = operator_new(0x180);
  local_8._0_1_ = 0x2a;
  if (pvVar4 == (void *)0x0) {
    local_1b8 = 0;
  }
  else {
    local_1b8 = FUN_007c9de0("filterList",0x433a0000,0x43120000,0x43820000,0x434d0000,0,0,0x20,
                             param_1[0x54],0xff00ff00,0x3f800000);
  }
  local_8 = CONCAT31(local_8._1_3_,0x24);
  param_1[0x5f] = local_1b8;
  FUN_007d3f20(2);
  FUN_007cb3e0(FUN_00795f30);
  FUN_007d2110(param_1[0x5f],0);
  for (local_b8 = 0; uVar7 = FUN_007cb5a0(), local_b8 < uVar7; local_b8 = local_b8 + 1) {
    uVar9 = 0;
    uVar7 = local_b8;
    FUN_006cf480(local_b8);
    uVar3 = FUN_0041f870(uVar7,uVar9);
    FUN_007cabf0(uVar3,uVar7,uVar9);
    iVar6 = FUN_0048a830();
    if (iVar6 - 1U == local_b8) break;
  }
  FUN_007cafa0(0);
  (**(code **)(*(int *)param_1[0x5f] + 0x24))(0);
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,0x2b);
  iVar6 = FUN_0056f900();
  if ((iVar6 != 0) && (cVar2 = FUN_0041f890(), cVar2 == '\0')) {
    FID_conflict_operator_(iVar6 + 0xdc);
  }
  uVar3 = FUN_007cb0c0();
  basic_string<>(uVar3);
  local_8._0_1_ = 0x2c;
  FUN_007a4460(local_5c,local_2c);
  local_8._0_1_ = 0x2b;
  ~basic_string<>();
  uVar3 = FUN_007cb0c0();
  (**(code **)(*(int *)param_1[0x5b] + 0x3c))(uVar3);
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 0x2d;
  if (pvVar4 == (void *)0x0) {
    local_1c8 = 0;
  }
  else {
    local_1c8 = FUN_007cc390("errorConditionLabel",0,0x41a00000,0x44b40000,0x422c0000,0x9020,
                             param_1[0x54],0);
  }
  local_8._0_1_ = 0x2b;
  param_1[0x60] = local_1c8;
  FUN_007cc710(2,0xffffffff);
  uVar3 = FUN_0081cb40("multi_message","rebuilding_room");
  param_1[0x51] = uVar3;
  (**(code **)(*(int *)param_1[0x60] + 0x3c))(param_1[0x51]);
  FUN_007cca20(0xffff2222);
  FUN_007d2110(param_1[0x60],0);
  FUN_00799d70();
  local_8._0_1_ = 0x24;
  ~basic_string<>();
  local_8._0_1_ = 0x23;
  FUN_004180b0();
  local_8._0_1_ = 0x22;
  FUN_00426bc0();
  local_8 = CONCAT31(local_8._1_3_,1);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

