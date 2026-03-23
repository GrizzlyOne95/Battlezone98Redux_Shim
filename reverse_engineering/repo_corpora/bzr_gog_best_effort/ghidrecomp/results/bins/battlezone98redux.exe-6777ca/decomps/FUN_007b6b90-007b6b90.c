
undefined4 * __fastcall FUN_007b6b90(undefined4 *param_1)

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
  int iVar16;
  undefined4 local_f4;
  undefined4 local_f0;
  int *local_e4;
  int *local_e0;
  undefined4 local_d8;
  int *local_d0;
  undefined4 local_cc;
  int *local_bc;
  int *local_b8;
  int *local_b0;
  undefined4 local_ac;
  int *local_9c;
  undefined4 local_98;
  int *local_90;
  undefined4 local_84;
  int *local_74;
  undefined4 local_5c;
  undefined4 local_58;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086147e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_OptionsPlay::vftable;
  DAT_009455c8 = param_1;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_f4 = 0;
  }
  else {
    local_f4 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(1);
  FUN_007d2870("poptions_center.png");
  FUN_007d2110(local_f4,0);
  uVar2 = FUN_0081cb40("play_options",&DAT_008714b0);
  uVar3 = FUN_0081cb40("play_options","game_difficulty");
  uVar4 = FUN_0081cb40("play_options","special_item_trigger");
  uVar5 = FUN_0081cb40("play_options","automatic_leveling");
  uVar6 = FUN_0081cb40("play_options","target_lead_position");
  uVar7 = FUN_0081cb40("play_options","reverse_mouse");
  uVar8 = FUN_0081cb40("play_options","mouse_sensitivity");
  uVar9 = FUN_0081cb40("play_options","strategy_help");
  uVar10 = FUN_0081cb40("play_options","language");
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_d0 + 0x40))("topcrnhv.png");
  (**(code **)(*local_d0 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007b6870);
  FUN_007d2110(local_d0,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_b0 = (int *)0x0;
  }
  else {
    local_b0 = (int *)FUN_007cc390("Difficulty",0x43ac0000,0x43700000,0x43a90000,0x421c0000,0x8020,
                                   local_f4,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_b0 + 0x3c))(uVar3);
  FUN_007d2110(local_b0,0);
  uVar2 = FUN_0081cb40("option_box","VERY_EASY");
  uVar3 = FUN_0081cb40("option_box",&DAT_0089f354);
  uVar11 = FUN_0081cb40("option_box","MEDIUM");
  uVar12 = FUN_0081cb40("option_box",&DAT_0089f368);
  uVar13 = FUN_0081cb40("option_box","VERY_HARD");
  uVar14 = FUN_0081cb40("option_box",&DAT_0089e9fc);
  uVar15 = FUN_0081cb40("option_box",&DAT_008712f4);
  pvVar1 = operator_new(500);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_f0 = 0;
  }
  else {
    local_f0 = FUN_007c3150("DiffChecklist",0x44244000,0x43700000,0x43010000,0x421c0000,0,local_f4);
  }
  local_8._0_1_ = 0;
  param_1[0x57] = local_f0;
  FUN_007c3ac0(uVar2,0);
  FUN_007c3ac0(uVar3,1);
  FUN_007c3ac0(uVar11,2);
  FUN_007c3ac0(uVar12,3);
  FUN_007c3ac0(uVar13,4);
  FUN_007c3c10(*(undefined4 *)(DAT_0094672c + 0x40));
  FUN_007c3cf0(FUN_007b68b0);
  FUN_007d2110(param_1[0x57],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_b8 = (int *)0x0;
  }
  else {
    local_b8 = (int *)FUN_007cc390("Special",0x43ac0000,0x439e8000,0x43a90000,0x421c0000,0x8020,
                                   local_f4,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_b8 + 0x3c))(uVar4);
  FUN_007d2110(local_b8,0);
  pvVar1 = operator_new(500);
  local_8._0_1_ = 6;
  if (pvVar1 == (void *)0x0) {
    local_d8 = 0;
  }
  else {
    local_d8 = FUN_007c3150("SpecialChecklist",0x44244000,0x439e8000,0x43010000,0x421c0000,0,
                            local_f4);
  }
  local_8._0_1_ = 0;
  param_1[0x56] = local_d8;
  FUN_007c3ac0(uVar14,0);
  FUN_007c3ac0(uVar15,1);
  FUN_007c3cf0(FUN_007b68d0);
  FUN_007c3c10((*(uint *)(DAT_0094672c + 0x30) & 0x400) != 0);
  FUN_007d2110(param_1[0x56],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 7;
  if (pvVar1 == (void *)0x0) {
    local_90 = (int *)0x0;
  }
  else {
    local_90 = (int *)FUN_007cc390(&DAT_008740b4,0x43ac0000,0x43c50000,0x43a90000,0x421c0000,0x8020,
                                   local_f4,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_90 + 0x3c))(uVar5);
  FUN_007d2110(local_90,0);
  pvVar1 = operator_new(500);
  local_8._0_1_ = 8;
  if (pvVar1 == (void *)0x0) {
    local_98 = 0;
  }
  else {
    local_98 = FUN_007c3150("AutoChecklist",0x44244000,0x43c50000,0x43010000,0x421c0000,0,local_f4);
  }
  local_8._0_1_ = 0;
  param_1[0x55] = local_98;
  FUN_007c3ac0(uVar14,0);
  FUN_007c3ac0(uVar15,1);
  FUN_007c3cf0(FUN_007b68a0);
  FUN_007c3c10((*(uint *)(DAT_0094672c + 0x30) & 0x10) != 0);
  FUN_007d2110(param_1[0x55],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 9;
  if (pvVar1 == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_007cc390("Target",0x43ac0000,0x43eb8000,0x43a90000,0x422c0000,0x20,
                                   local_f4,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_e0 + 0x3c))(uVar6);
  FUN_007d2110(local_e0,0);
  pvVar1 = operator_new(500);
  local_8._0_1_ = 10;
  if (pvVar1 == (void *)0x0) {
    local_5c = 0;
  }
  else {
    local_5c = FUN_007c3150("TargetChecklist",0x44244000,0x43eb8000,0x43010000,0x421c0000,0,local_f4
                           );
  }
  local_8._0_1_ = 0;
  param_1[0x54] = local_5c;
  FUN_007c3ac0(uVar14,0);
  FUN_007c3ac0(uVar15,1);
  FUN_007c3cf0(FUN_007b68c0);
  FUN_007c3c10((*(uint *)(DAT_0094672c + 0x30) & 0x20) != 0);
  FUN_007d2110(param_1[0x54],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0xb;
  if (pvVar1 == (void *)0x0) {
    local_74 = (int *)0x0;
  }
  else {
    local_74 = (int *)FUN_007cc390("Reverse",0x43ac0000,0x44090000,0x43a90000,0x421c0000,0x8020,
                                   local_f4,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_74 + 0x3c))(uVar7);
  FUN_007d2110(local_74,0);
  pvVar1 = operator_new(500);
  local_8._0_1_ = 0xc;
  if (pvVar1 == (void *)0x0) {
    local_84 = 0;
  }
  else {
    local_84 = FUN_007c3150("ReverseChecklist",0x44244000,0x44090000,0x43010000,0x421c0000,0,
                            local_f4);
  }
  local_8._0_1_ = 0;
  param_1[0x53] = local_84;
  FUN_007c3ac0(uVar14,0);
  FUN_007c3ac0(uVar15,1);
  FUN_007c3cf0(FUN_007b6890);
  FUN_007c3c10((*(uint *)(DAT_0094672c + 0x30) & 0x40) == 0);
  FUN_007d2110(param_1[0x53],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0xd;
  if (pvVar1 == (void *)0x0) {
    local_9c = (int *)0x0;
  }
  else {
    local_9c = (int *)FUN_007cc390("Sensitivity",0x43ac0000,0x441c4000,0x43a90000,0x422c0000,0x20,
                                   local_f4,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_9c + 0x3c))(uVar8);
  FUN_007d2110(local_9c,0);
  pvVar1 = operator_new(0x164);
  local_8._0_1_ = 0xe;
  if (pvVar1 == (void *)0x0) {
    local_ac = 0;
  }
  else {
    local_ac = FUN_007cbd60("MouseSlider",0x44244000,0x44190000,0x43ca8000,0x429e0000,0x20,local_f4)
    ;
  }
  local_8._0_1_ = 0;
  param_1[0x52] = local_ac;
  FUN_007cc200(0x40c00000);
  FUN_007cc2d0((float)*(int *)(DAT_0094672c + 0x38));
  FUN_007cc340(FUN_007b68e0);
  FUN_007d2110(param_1[0x52],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0xf;
  if (pvVar1 == (void *)0x0) {
    local_bc = (int *)0x0;
  }
  else {
    local_bc = (int *)FUN_007cc390(&DAT_0089fcb0,0x43ac0000,0x442f8000,0x43a90000,0x421c0000,0x8020,
                                   local_f4,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_bc + 0x3c))(uVar9);
  FUN_007d2110(local_bc,0);
  pvVar1 = operator_new(500);
  local_8._0_1_ = 0x10;
  if (pvVar1 == (void *)0x0) {
    local_cc = 0;
  }
  else {
    local_cc = FUN_007c3150("HelpChecklist",0x44244000,0x442f8000,0x43010000,0x421c0000,0,local_f4);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_cc;
  FUN_007c3ac0(uVar14,0);
  FUN_007c3ac0(uVar15,1);
  FUN_007c3cf0(FUN_007b6880);
  FUN_007c3c10((*(uint *)(DAT_0094672c + 0x30) & 0x80) != 0);
  FUN_007d2110(param_1[0x51],0);
  iVar16 = FUN_00434160();
  if (iVar16 != 5) {
    pvVar1 = operator_new(0x930);
    local_8._0_1_ = 0x11;
    if (pvVar1 == (void *)0x0) {
      local_e4 = (int *)0x0;
    }
    else {
      local_e4 = (int *)FUN_007cc390(&DAT_0089fcb0,0x43ac0000,0x4442c000,0x43a90000,0x421c0000,
                                     0x8020,local_f4,0);
    }
    local_8._0_1_ = 0;
    (**(code **)(*local_e4 + 0x3c))(uVar10);
    FUN_007d2110(local_e4,0);
    uVar2 = FUN_0081cb40("languages",&DAT_00871354);
    uVar3 = FUN_0081cb40("languages","ENGLISH");
    uVar4 = FUN_0081cb40("languages","FRENCH");
    uVar5 = FUN_0081cb40("languages","GERMAN");
    uVar6 = FUN_0081cb40("languages","SPANISH");
    uVar7 = FUN_0081cb40("languages","ITALIAN");
    uVar8 = FUN_0081cb40("languages","PORTUGUESE");
    uVar9 = FUN_0081cb40("languages","RUSSIAN");
    pvVar1 = operator_new(500);
    local_8._0_1_ = 0x12;
    if (pvVar1 == (void *)0x0) {
      local_58 = 0;
    }
    else {
      local_58 = FUN_007c3150("LangChecklist",0x44244000,0x4442c000,0x43010000,0x421c0000,0,local_f4
                             );
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x58] = local_58;
    FUN_007c3ac0(uVar2,0);
    FUN_007c3ac0(uVar3,1);
    FUN_007c3ac0(uVar4,2);
    FUN_007c3ac0(uVar5,3);
    FUN_007c3ac0(uVar6,4);
    FUN_007c3ac0(uVar7,5);
    FUN_007c3ac0(uVar8,6);
    FUN_007c3ac0(uVar9,7);
    FUN_007c3cf0(FUN_007b68f0);
    FUN_007c3c10(*(undefined4 *)(DAT_0094672c + 0x4c));
    FUN_007d2110(param_1[0x58],0);
  }
  param_1[0x59] = *(undefined4 *)(DAT_0094672c + 0x4c);
  ExceptionList = local_10;
  return param_1;
}

