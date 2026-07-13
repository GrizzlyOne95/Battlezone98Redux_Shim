
/* WARNING: Removing unreachable block (ram,0x007bfad7) */

void __thiscall FUN_007bf440(undefined4 *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  char cVar2;
  void *pvVar3;
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
  char *_Source;
  int iVar15;
  size_t _Count;
  int *local_4d4;
  undefined4 local_4d0;
  int *local_4cc;
  int *local_4c8;
  undefined4 local_4c4;
  int *local_4c0;
  undefined4 local_4bc;
  int *local_4b4;
  undefined4 local_4b0;
  undefined4 local_4ac;
  int *local_4a4;
  undefined4 local_4a0;
  undefined4 local_490;
  undefined4 local_480;
  undefined4 local_470;
  int *local_464;
  undefined4 local_45c;
  undefined4 local_44c;
  char *local_440;
  char *local_430;
  char local_414 [1023];
  undefined1 uStack_15;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861cf9;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(local_14);
  local_8 = 0;
  *param_1 = cUI_SinglePlayer::vftable;
  param_1[0x4e] = param_2;
  param_1[0x51] = 0;
  param_1[0x52] = 0;
  DAT_009455e0 = param_1;
  uVar1 = FUN_004894f0();
  *(undefined1 *)(param_1 + 0x5f) = uVar1;
  if (DAT_009455dd != '\0') {
    *(undefined1 *)(param_1 + 0x5f) = 0;
  }
  pvVar3 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar3 == (void *)0x0) {
    local_4bc = 0;
  }
  else {
    local_4bc = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x53] = local_4bc;
  FUN_007d3f20(1);
  FUN_007d2870("singlep_center.png");
  FUN_007d2110(local_4bc,0);
  uVar4 = FUN_0081cb40("single",&DAT_008714b0);
  uVar5 = FUN_0041f870();
  uVar5 = FUN_0081cb40("single",uVar5);
  uVar6 = FUN_0041f870();
  uVar6 = FUN_0081cb40("single",uVar6);
  uVar7 = FUN_0081cb40("single","blackdog");
  uVar8 = FUN_0041f870();
  uVar8 = FUN_0081cb40("single",uVar8);
  uVar9 = FUN_0041f870();
  uVar9 = FUN_0081cb40("single",uVar9);
  uVar10 = FUN_0081cb40("single","load_saved_game");
  uVar11 = FUN_0081cb40("single","options");
  uVar12 = FUN_0081cb40("single","instant");
  uVar13 = FUN_0081cb40("campaign","campaign");
  param_1[0x5c] = "Red Odyssey";
  uVar14 = FUN_0081cb40("campaign","standard");
  param_1[0x5d] = uVar14;
  pvVar3 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar3 == (void *)0x0) {
    local_4c0 = (int *)0x0;
  }
  else {
    local_4c0 = (int *)FUN_007c2480("Back_SinglePlayer",0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,
                                    0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_4c0 + 0x40))("topcrnhv.png");
  (**(code **)(*local_4c0 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar4);
  FUN_007c23e0(FUN_007bed10);
  FUN_007d2110(local_4c0,0);
  pvVar3 = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (pvVar3 == (void *)0x0) {
    local_4c8 = (int *)0x0;
  }
  else {
    local_4c8 = (int *)FUN_007c2480("Options_SinglePlayer",0,0x447ac000,0x43ab0000,0x429a0000,0x24,0
                                    ,0x41e00000,0x40a00000);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(3);
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_4c8 + 0x40))("topcrnhv.png");
  (**(code **)(*local_4c8 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar11);
  FUN_007c23e0(FUN_007bed20);
  FUN_007d2110(local_4c8,0);
  if (*(char *)(param_1 + 0x5f) == '\0') {
    iVar15 = FUN_004344a0();
    if (iVar15 != 2) {
      pvVar3 = operator_new(0x1ec);
      local_8._0_1_ = 10;
      if (pvVar3 == (void *)0x0) {
        local_4d4 = (int *)0x0;
      }
      else {
        local_4d4 = (int *)FUN_007c2480("CampaignLaunch",0,0,0x43ab0000,0x429a0000,0xa2,0,0xc2200000
                                        ,0);
      }
      local_8._0_1_ = 0;
      FUN_007d2870("topcorner.png");
      (**(code **)(*local_4d4 + 0x40))("topcrnhv.png");
      (**(code **)(*local_4d4 + 0x3c))("topcrnck.png");
      FUN_007c2950(uVar13);
      FUN_007c23e0(FUN_007bee80);
      FUN_007d2110(local_4d4,0);
    }
    iVar15 = FUN_004344a0();
    if (iVar15 != 2) {
      pvVar3 = operator_new(0x1ec);
      local_8._0_1_ = 0xb;
      if (pvVar3 == (void *)0x0) {
        local_464 = (int *)0x0;
      }
      else {
        local_464 = (int *)FUN_007c2480("Instant",0,0x447ac000,0x43ab0000,0x429a0000,0xa6,0,
                                        0xc2200000,0x40a00000);
      }
      local_8._0_1_ = 0;
      FUN_007d3f20(3);
      FUN_007d2870("topcorner.png");
      (**(code **)(*local_464 + 0x40))("topcrnhv.png");
      (**(code **)(*local_464 + 0x3c))("topcrnck.png");
      FUN_007c2950(uVar12);
      FUN_007c30e0(0x3f666666);
      FUN_007c23e0(FUN_007bee10);
      FUN_007d2110(local_464,0);
    }
    uVar4 = 1;
    FUN_007647a0(1);
    cVar2 = FUN_007537a0(uVar4);
    if (cVar2 != '\0') {
      pvVar3 = operator_new(0x1ec);
      local_8._0_1_ = 0xc;
      if (pvVar3 == (void *)0x0) {
        local_470 = 0;
      }
      else {
        local_470 = FUN_007c2480(&PTR_PTR_0089cd2c,0,0x447d0000,0x43b88000,0x42880000,100,0,0,
                                 0xc0e00000);
      }
      local_8._0_1_ = 0;
      param_1[0x5b] = local_470;
      FUN_007d2870("tomnoff.png");
      (**(code **)(*(int *)param_1[0x5b] + 0x40))("tomnon.png");
      (**(code **)(*(int *)param_1[0x5b] + 0x3c))("tomnclk.png");
      FUN_007c2950(param_1[0x5c]);
      FUN_007c23e0(FUN_007bee20);
      FUN_007d2110(param_1[0x5b],0);
    }
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 0xd;
    if (pvVar3 == (void *)0x0) {
      local_480 = 0;
    }
    else {
      local_480 = FUN_007c2480("USAMission_SinglePlayer",0x430b0000,0x43000000,0x43838000,0x43de8000
                               ,0x20,local_4bc,0,0x43750000);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x57] = local_480;
    FUN_007d3f20(3);
    FUN_007c2950(uVar5);
    FUN_007c30e0(0x3fa00000);
    FUN_007d2870("aflagon.png");
    (**(code **)(*(int *)param_1[0x57] + 0x40))("aflagclk.png");
    (**(code **)(*(int *)param_1[0x57] + 0x3c))("aflagclk.png");
    FUN_007c2ff0("shmroll.wav");
    FUN_007c2fa0("shmclick.wav");
    FUN_007c23e0(FUN_007bed30);
    iVar15 = FUN_004344a0();
    if (iVar15 != 2) {
      FUN_007c23c0(FUN_007bed50);
    }
    FUN_007d2110(param_1[0x57],0);
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 0xe;
    if (pvVar3 == (void *)0x0) {
      local_490 = 0;
    }
    else {
      local_490 = FUN_007c2480("BDMission_SinglePlayer",0x430b0000,0x43000000,0x43838000,0x43de8000,
                               0x20,local_4bc,0,0x43750000);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x58] = local_490;
    FUN_007d3f20(3);
    FUN_007c2950(uVar7);
    FUN_007c30e0(0x3fa00000);
    FUN_007d2870("aflagon_2.png");
    (**(code **)(*(int *)param_1[0x58] + 0x40))("aflagclk_2.png");
    (**(code **)(*(int *)param_1[0x58] + 0x3c))("aflagclk_2.png");
    FUN_007c2ff0("shmroll.wav");
    FUN_007c2fa0("shmclick.wav");
    FUN_007c23e0(FUN_007bed40);
    iVar15 = FUN_004344a0();
    if (iVar15 != 2) {
      FUN_007c23c0(FUN_007bed70);
    }
    FUN_007d2110(param_1[0x58],0);
    (**(code **)(*(int *)param_1[0x58] + 0x24))(0);
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 0xf;
    if (pvVar3 == (void *)0x0) {
      local_4a0 = 0;
    }
    else {
      local_4a0 = FUN_007c2480("USSRMission_SinglePlayer",0x44828000,0x43000000,0x43838000,
                               0x43de8000,0x20,local_4bc,0,0x43750000);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x59] = local_4a0;
    FUN_007d3f20(3);
    FUN_007c2950(uVar6);
    FUN_007c30e0(0x3fa00000);
    FUN_007d2870("rflagon.png");
    (**(code **)(*(int *)param_1[0x59] + 0x40))("rflagclk.png");
    (**(code **)(*(int *)param_1[0x59] + 0x3c))("rflagclk.png");
    FUN_007c2ff0("shmroll.wav");
    FUN_007c2fa0("shmclick.wav");
    FUN_007c23e0(FUN_007bed90);
    iVar15 = FUN_004344a0();
    if (iVar15 != 2) {
      FUN_007c23c0(FUN_007beda0);
    }
    FUN_007d2110(param_1[0x59],0);
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 0x10;
    if (pvVar3 == (void *)0x0) {
      local_4b0 = 0;
    }
    else {
      local_4b0 = FUN_007c2480("CHMission_SinglePlayer",0x44828000,0x43000000,0x43838000,0x43de8000,
                               0x20,local_4bc,0,0x43750000);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x5a] = local_4b0;
    FUN_007d3f20(3);
    FUN_007c2950(uVar8);
    FUN_007c30e0(0x3fa00000);
    FUN_007d2870("rflagon_2.png");
    (**(code **)(*(int *)param_1[0x5a] + 0x40))("rflagclk_2.png");
    (**(code **)(*(int *)param_1[0x5a] + 0x3c))("rflagclk_2.png");
    FUN_007c2ff0("shmroll.wav");
    FUN_007c2fa0("shmclick.wav");
    FUN_007c23e0(FUN_007bedc0);
    iVar15 = FUN_004344a0();
    if (iVar15 != 2) {
      FUN_007c23c0(FUN_007bedd0);
    }
    FUN_007d2110(param_1[0x5a],0);
    (**(code **)(*(int *)param_1[0x5a] + 0x24))(0);
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 0x11;
    if (pvVar3 == (void *)0x0) {
      local_44c = 0;
    }
    else {
      local_44c = FUN_007c2480("trainingMission_SinglePlayer",0x43020000,0x44228000,0x439d8000,
                               0x43780000,0x20,local_4bc,0x432f0000,0);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x55] = local_44c;
    FUN_007d3f20(10);
    FUN_007d3850("train1.ogv",0);
    FUN_007c23e0(FUN_007bedf0);
    FUN_007c2ff0("shmroll.wav");
    FUN_007c2fa0("shmclick.wav");
    iVar15 = FUN_004344a0();
    if (iVar15 != 2) {
      FUN_007c23c0(FUN_007bee50);
    }
    FUN_007c2950(uVar9);
    FUN_007c30e0(0x3fa00000);
    FUN_007d2110(param_1[0x55],0);
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 0x12;
    if (pvVar3 == (void *)0x0) {
      local_45c = 0;
    }
    else {
      local_45c = FUN_007c2480("LoadMission_SinglePlayer",0x447a0000,0x44228000,0x439d8000,
                               0x43780000,0x20,local_4bc,0xc32f0000,0);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x56] = local_45c;
    FUN_007d3f20(10);
    FUN_007d3850("load1.ogv",0);
    FUN_007c23e0(FUN_007bee00);
    FUN_007c2ff0("shmroll.wav");
    FUN_007c2fa0("shmclick.wav");
    iVar15 = FUN_004344a0();
    if (iVar15 != 2) {
      FUN_007c23c0(FUN_007bee30);
    }
    FUN_007c2950(uVar10);
    FUN_007c30e0(0x3fa00000);
    FUN_007d3f20(3);
    FUN_007d2110(param_1[0x56],0);
    param_1[0x54] = 0;
    FUN_007c1780();
    FUN_007d3dd0(0);
    FUN_007d3dd0(0);
    if (DAT_009455dc == '\0') {
      FUN_007d3e80(0,0x1d,0);
    }
    else {
      FUN_007befd0();
    }
  }
  else {
    pvVar3 = operator_new(0x144);
    local_8._0_1_ = 4;
    if (pvVar3 == (void *)0x0) {
      local_4d0 = 0;
    }
    else {
      local_4d0 = FUN_007d1cc0("PopupBG",0,0x42700000,0x44a56000,0x44148000,0x60,0,0);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x5e] = local_4d0;
    FUN_007d3f20(8);
    FUN_007d2870("tutorial_popup.png");
    FUN_007d2110(param_1[0x5e],0);
    _Count = 0x400;
    _Source = (char *)FUN_0081cb40("single","prompt_training");
    strncpy(local_414,_Source,_Count);
    uStack_15 = 0;
    local_440 = local_414;
    do {
      cVar2 = *local_440;
      local_440 = local_440 + 1;
    } while (cVar2 != '\0');
    for (local_430 = local_414 + ((uint)((int)local_440 - (int)(local_414 + 1)) >> 1);
        (*local_430 != '\0' && (*local_430 != ' ')); local_430 = local_430 + 1) {
    }
    if (*local_430 != '\0') {
      *local_430 = '\0';
      local_430 = local_430 + 1;
    }
    pvVar3 = operator_new(0x930);
    local_8._0_1_ = 5;
    if (pvVar3 == (void *)0x0) {
      local_4a4 = (int *)0x0;
    }
    else {
      local_4a4 = (int *)FUN_007cc390("Lobby",0,0x43200000,0x44068000,0x422c0000,0x60,param_1,0);
    }
    local_8._0_1_ = 0;
    FUN_007d3f20(10);
    FUN_007cc6b0(0x3fc00000);
    FUN_007cc710(2,0xffffffff);
    (**(code **)(*local_4a4 + 0x3c))(local_414);
    FUN_007d2110(local_4a4,0);
    pvVar3 = operator_new(0x930);
    local_8._0_1_ = 6;
    if (pvVar3 == (void *)0x0) {
      local_4cc = (int *)0x0;
    }
    else {
      local_4cc = (int *)FUN_007cc390("Lobby",0,0x43480000,0x44068000,0x422c0000,0x60,param_1,0);
    }
    local_8._0_1_ = 0;
    FUN_007d3f20(10);
    FUN_007cc6b0(0x3fc00000);
    FUN_007cc710(2,0xffffffff);
    (**(code **)(*local_4cc + 0x3c))(local_430);
    FUN_007d2110(local_4cc,0);
    iVar15 = FUN_004344a0();
    if (iVar15 == 2) {
      pvVar3 = operator_new(0x1ec);
      local_8._0_1_ = 8;
      if (pvVar3 == (void *)0x0) {
        local_4c4 = 0;
      }
      else {
        local_4c4 = FUN_007c2480("trainingMission_SinglePlayer",0x43ee0000,0x439d0000,0x43b88000,
                                 0x42880000,0x24,param_1[0x5e],0,0xc0e00000);
      }
      local_8 = (uint)local_8._1_3_ << 8;
      param_1[0x55] = local_4c4;
      FUN_007d2870("tomnoff.png");
      (**(code **)(*(int *)param_1[0x55] + 0x40))("tomnon.png");
      (**(code **)(*(int *)param_1[0x55] + 0x3c))("tomnclk.png");
      FUN_007c2950(uVar9);
      FUN_007c23e0(FUN_007bedf0);
      FUN_007c2fa0("shmclick.wav");
      FUN_007c30e0(0x3fa00000);
      FUN_007d2110(param_1[0x55],0);
    }
    else {
      pvVar3 = operator_new(0x1ec);
      local_8._0_1_ = 7;
      if (pvVar3 == (void *)0x0) {
        local_4ac = 0;
      }
      else {
        local_4ac = FUN_007c2480("trainingMission_SinglePlayer",0x44160000,0x438c0000,0x439d8000,
                                 0x43780000,0x20,local_4bc,0x432f0000,0);
      }
      local_8 = (uint)local_8._1_3_ << 8;
      param_1[0x55] = local_4ac;
      FUN_007d3f20(10);
      FUN_007d3850("train1.ogv",0);
      FUN_007c23e0(FUN_007bedf0);
      FUN_007c2ff0("shmroll.wav");
      FUN_007c2fa0("shmclick.wav");
      FUN_007c23c0(FUN_007bee50);
      FUN_007c2950(uVar9);
      FUN_007c30e0(0x3fa00000);
      FUN_007d2110(param_1[0x55],0);
    }
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 9;
    if (pvVar3 == (void *)0x0) {
      local_4b4 = (int *)0x0;
    }
    else {
      local_4b4 = (int *)FUN_007c2480("skiptraining",0x43ee0000,0x44008000,0x43b88000,0x42880000,
                                      0x24,param_1[0x5e],0,0xc0e00000);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_007d2870("tomnoff.png");
    (**(code **)(*local_4b4 + 0x40))("tomnon.png");
    (**(code **)(*local_4b4 + 0x3c))("tomnclk.png");
    uVar4 = FUN_0081cb40("single","skip_training");
    FUN_007c2950(uVar4);
    FUN_007c23e0(FUN_007bee70);
    FUN_007d2110(local_4b4,0);
    FUN_007d3dd0(0);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

