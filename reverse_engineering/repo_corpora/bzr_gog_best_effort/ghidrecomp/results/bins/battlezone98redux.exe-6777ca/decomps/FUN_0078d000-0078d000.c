
void __thiscall FUN_0078d000(int param_1,char param_2)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  int *local_9c;
  int *local_98;
  int *local_94;
  int *local_8c;
  int *local_88;
  undefined4 local_84;
  int *local_78;
  undefined4 local_68;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_50;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ec12;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d2870("bckground_1920x1080.png");
  pvVar1 = operator_new(0x144);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_5c = 0;
  }
  else {
    local_5c = FUN_007d1cc0("MainScreen_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x158) = local_5c;
  FUN_007d3f20(1);
  FUN_007d2870("mainCenterPanel.png");
  FUN_007d2110(*(undefined4 *)(param_1 + 0x158),0);
  uVar2 = FUN_0081cb40(&DAT_0089df3c,&DAT_0089df34);
  uVar3 = FUN_0081cb40(&DAT_0089df3c,"single_player");
  uVar4 = FUN_0081cb40(&DAT_0089df3c,"view_credits");
  uVar5 = FUN_0081cb40(&DAT_0089df3c,"replay_intro");
  uVar6 = FUN_0081cb40(&DAT_0089df3c,"options");
  uVar7 = FUN_0081cb40(&DAT_0089df3c,&DAT_0089e0e4);
  uVar8 = FUN_0081cb40(&DAT_0089df3c,"achievements");
  iVar9 = FUN_004344a0();
  if (iVar9 != 2) {
    pvVar1 = operator_new(0x1ec);
    local_8 = 1;
    if (pvVar1 == (void *)0x0) {
      local_98 = (int *)0x0;
    }
    else {
      local_98 = (int *)FUN_007c2480("ExitGame_MainScreen",0,0,0x43ab0000,0x429a0000,0x20,0,
                                     0x41e00000,0);
    }
    local_8 = 0xffffffff;
    FUN_007d2870("topcorner.png");
    (**(code **)(*local_98 + 0x40))("topcrnhv.png");
    (**(code **)(*local_98 + 0x3c))("topcrnck.png");
    FUN_007c2950(uVar2);
    FUN_007c23e0(FUN_0078c670);
    FUN_007d2110(local_98,0);
  }
  pvVar1 = operator_new(0x1ec);
  local_8 = 2;
  if (pvVar1 == (void *)0x0) {
    local_9c = (int *)0x0;
  }
  else {
    local_9c = (int *)FUN_007c2480("Options_MainScreen",0,0x447ac000,0x43ab0000,0x429a0000,0x24,0,
                                   0x41e00000,0x40a00000);
  }
  local_8 = 0xffffffff;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_9c + 0x40))("topcrnhv.png");
  (**(code **)(*local_9c + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar6);
  FUN_007c23e0(FUN_0078c5e0);
  FUN_007d2110(local_9c,0);
  pvVar1 = operator_new(0x1ec);
  local_8 = 3;
  if (pvVar1 == (void *)0x0) {
    local_84 = 0;
  }
  else {
    local_84 = FUN_007c2480("openAchievements",0,0,0x43ab0000,0x429a0000,0xa2,0,0xc2200000,0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x178) = local_84;
  FUN_007d2870("topcorner.png");
  (**(code **)(**(int **)(param_1 + 0x178) + 0x40))("topcrnhv.png");
  (**(code **)(**(int **)(param_1 + 0x178) + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar8);
  FUN_007c23e0(FUN_0078c610);
  (**(code **)(**(int **)(param_1 + 0x178) + 0x24))(0);
  FUN_007d2110(*(undefined4 *)(param_1 + 0x178),0);
  iVar9 = FUN_004344a0();
  if (iVar9 != 2) {
    pvVar1 = operator_new(0x1ec);
    local_8 = 4;
    if (pvVar1 == (void *)0x0) {
      local_94 = (int *)0x0;
    }
    else {
      local_94 = (int *)FUN_007c2480(&DAT_0089e0ac,0,0x447ac000,0x43ab0000,0x429a0000,0xa6,0,
                                     0xc2200000,0x40a00000);
    }
    local_8 = 0xffffffff;
    FUN_007d2870("topcorner.png");
    (**(code **)(*local_94 + 0x40))("topcrnhv.png");
    (**(code **)(*local_94 + 0x3c))("topcrnck.png");
    FUN_007c2950(uVar7);
    FUN_007c23e0(FUN_0078c640);
    FUN_007d2110(local_94,0);
  }
  pvVar1 = operator_new(0x1ec);
  local_8 = 5;
  if (pvVar1 == (void *)0x0) {
    local_8c = (int *)0x0;
  }
  else {
    local_8c = (int *)FUN_007c2480("SinglePlayer_MainScreen",0x43230000,0x43170000,0x43df0000,
                                   0x433d0000,0x20,*(undefined4 *)(param_1 + 0x158),0,0);
  }
  local_8 = 0xffffffff;
  FUN_007c2950(uVar3);
  FUN_007c30e0(0x3fc00000);
  (**(code **)(*local_8c + 0x40))("midhvr.png");
  (**(code **)(*local_8c + 0x3c))("midclk.png");
  FUN_007c2ff0("shmroll.wav");
  FUN_007c2fa0("shmclick.wav");
  FUN_007c23e0(FUN_0078c520);
  FUN_007d2110(local_8c,0);
  pvVar1 = operator_new(0x1ec);
  local_8 = 6;
  if (pvVar1 == (void *)0x0) {
    local_58 = 0;
  }
  else {
    local_58 = FUN_007c2480("MultiPlayer_MainScreen",0x444fc000,0x43170000,0x43df0000,0x433d0000,
                            0x22,*(undefined4 *)(param_1 + 0x158),0,0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x170) = local_58;
  FUN_007c30e0(0x3fc00000);
  (**(code **)(**(int **)(param_1 + 0x170) + 0x40))("midhvr.png");
  (**(code **)(**(int **)(param_1 + 0x170) + 0x3c))("midclk.png");
  FUN_007c2ff0("shmroll.wav");
  FUN_007c2fa0("shmclick.wav");
  FUN_007c23e0(FUN_0078c550);
  FUN_007d2110(*(undefined4 *)(param_1 + 0x170),0);
  pvVar1 = operator_new(0x930);
  local_8 = 7;
  if (pvVar1 == (void *)0x0) {
    local_68 = 0;
  }
  else {
    local_68 = FUN_007cc390("MPStatus",0x444fc000,0x437b0000,0x43df0000,0x42200000,0x20,
                            *(undefined4 *)(param_1 + 0x158),0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x174) = local_68;
  FUN_007cc710(2,2);
  (**(code **)(**(int **)(param_1 + 0x174) + 0x3c))(&DAT_008a1ad8);
  FUN_007d2110(*(undefined4 *)(param_1 + 0x174),0);
  pvVar1 = operator_new(0x1ec);
  local_8 = 8;
  if (pvVar1 == (void *)0x0) {
    local_78 = (int *)0x0;
  }
  else {
    local_78 = (int *)FUN_007c2480("ViewCredits_MainScreen",0x43230000,0x44390000,0x43df0000,
                                   0x433d0000,0x24,*(undefined4 *)(param_1 + 0x158),0,0);
  }
  local_8 = 0xffffffff;
  FUN_007c2950(uVar4);
  FUN_007c30e0(0x3fc00000);
  (**(code **)(*local_78 + 0x40))("midhvr.png");
  (**(code **)(*local_78 + 0x3c))("midclk.png");
  FUN_007c2ff0("shmroll.wav");
  FUN_007c2fa0("shmclick.wav");
  FUN_007c23e0(FUN_0078c580);
  FUN_007d2110(local_78,0);
  pvVar1 = operator_new(0x1ec);
  local_8 = 9;
  if (pvVar1 == (void *)0x0) {
    local_88 = (int *)0x0;
  }
  else {
    local_88 = (int *)FUN_007c2480("Replay Intro_MainScreen",0x444fc000,0x44390000,0x43df0000,
                                   0x433d0000,0x26,*(undefined4 *)(param_1 + 0x158),0,0);
  }
  local_8 = 0xffffffff;
  FUN_007c2950(uVar5);
  FUN_007c30e0(0x3fc00000);
  (**(code **)(*local_88 + 0x40))("midhvr.png");
  (**(code **)(*local_88 + 0x3c))("midclk.png");
  FUN_007c2ff0("shmroll.wav");
  FUN_007c2fa0("shmclick.wav");
  FUN_007c23e0(FUN_0078c5b0);
  FUN_007d2110(local_88,0);
  pvVar1 = operator_new(0x930);
  local_8 = 10;
  if (pvVar1 == (void *)0x0) {
    local_50 = 0;
  }
  else {
    local_50 = FUN_007cc390("VersionString",0,0x44820000,0x44b40000,0x42200000,0x20,
                            *(undefined4 *)(param_1 + 0x158),0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x168) = local_50;
  FUN_007cc710(2,2);
  basic_string<>("Version ");
  local_8 = 0xb;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"2.2.301");
  uVar2 = FUN_0041f870();
  (**(code **)(**(int **)(param_1 + 0x168) + 0x3c))(uVar2);
  FUN_007d2110(*(undefined4 *)(param_1 + 0x168),0);
  *(undefined4 *)(param_1 + 0x16c) = 0;
  if (param_2 != '\0') {
    FUN_0078dde0();
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

