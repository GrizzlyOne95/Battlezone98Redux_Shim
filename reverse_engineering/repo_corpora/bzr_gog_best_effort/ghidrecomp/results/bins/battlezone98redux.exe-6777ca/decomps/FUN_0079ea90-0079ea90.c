
void FUN_0079ea90(undefined4 param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  float10 fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined4 local_25c;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_23c;
  int *local_238;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_21c;
  undefined4 local_218;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined4 local_1f8;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e0;
  undefined4 local_1d4;
  undefined4 local_1c4;
  int *local_1c0;
  undefined4 local_1b4;
  undefined4 local_1a4;
  undefined4 local_194;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_174;
  undefined4 local_168;
  undefined4 local_164;
  float local_160;
  undefined4 local_15c;
  float local_158;
  undefined4 local_154;
  float local_150;
  uint local_14c;
  float local_148;
  uint local_144;
  int *local_140;
  undefined4 local_13c;
  undefined4 *local_138;
  undefined1 local_134 [24];
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [48];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ff50;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(local_14);
  local_8 = 0;
  *local_138 = cUI_MultiPlayer_Lobby::vftable;
  vector<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  vector<>();
  local_8._0_1_ = 3;
  vector<>();
  local_8._0_1_ = 4;
  FUN_0073a6b0();
  vector<>();
  local_8._0_1_ = 5;
  vector<>();
  local_8._0_1_ = 6;
  vector<>();
  local_8._0_1_ = 7;
  basic_string<>();
  local_8._0_1_ = 8;
  basic_string<>();
  local_8._0_1_ = 9;
  FUN_0073cc40();
  local_8._0_1_ = 10;
  local_138[0xe0] = 0;
  FUN_005df1f0(param_1);
  *(undefined1 *)((int)local_138 + 0x1ff) = 0;
  uVar1 = FUN_00764760();
  local_138[0x71] = uVar1;
  FUN_0056f7e0();
  DAT_00945564 = local_138;
  *(undefined1 *)(local_138 + 0x7f) = 0;
  *(undefined1 *)((int)local_138 + 0x1fe) = 0;
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 0xb;
  if (pvVar2 == (void *)0x0) {
    local_20c = 0;
  }
  else {
    local_20c = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 10;
  local_13c = local_20c;
  FUN_007d3f20(1);
  FUN_007d2870("multi2_center.png");
  FUN_007d2110(local_13c,0);
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 0xc;
  if (pvVar2 == (void *)0x0) {
    local_21c = 0;
  }
  else {
    local_21c = FUN_007c6180("please_wait",0,0,0x45340000,0x44870000,0x60,0);
  }
  local_8._0_1_ = 10;
  local_138[0x51] = local_21c;
  FUN_007d3f20(0xe);
  FUN_007d2870("blackui.png");
  FUN_007d2db0(0x3f4ccccd);
  FUN_007d2110(local_138[0x51],0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 0xd;
  if (pvVar2 == (void *)0x0) {
    local_22c = 0;
  }
  else {
    local_22c = FUN_007cc390("overlaymsg",0,0x43fa0000,0x44160000,0x422c0000,0x60,local_138,0);
  }
  local_8._0_1_ = 10;
  local_138[0x52] = local_22c;
  FUN_007d3f20(0x10);
  FUN_007cc710(2,0xffffffff);
  uVar1 = FUN_0081cb40("multi_message","rebuilding_room");
  (**(code **)(*(int *)local_138[0x52] + 0x3c))(uVar1);
  FUN_007cc6b0(0x3fb33333);
  FUN_007d2110(local_138[0x52],0);
  uVar1 = FUN_0081cb40("multi_common",&DAT_008714b0);
  uVar3 = FUN_0081cb40("multi_common","options");
  uVar4 = FUN_0081cb40("multi_two","create_game");
  uVar5 = FUN_0081cb40("multi_two","create_room");
  uVar6 = FUN_0081cb40("multi_two","join_game");
  uVar7 = FUN_0081cb40("multi_common",&DAT_0089e97c);
  uVar8 = FUN_0081cb40("multi_two","rooms");
  uVar9 = FUN_0081cb40("multi_two","games");
  uVar10 = FUN_0081cb40("multi_two","p_in_room");
  uVar11 = FUN_0081cb40("multi_two","p_in_game");
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 0xe;
  if (pvVar2 == (void *)0x0) {
    local_23c = 0;
  }
  else {
    local_23c = FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 10;
  local_138[0x53] = local_23c;
  FUN_007d3f20(0x10);
  FUN_007d2870("topcorner.png");
  (**(code **)(*(int *)local_138[0x53] + 0x40))("topcrnhv.png");
  (**(code **)(*(int *)local_138[0x53] + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar1);
  FUN_007c23e0(FUN_0079d670);
  FUN_007d2110(local_138[0x53],0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 0xf;
  if (pvVar2 == (void *)0x0) {
    local_24c = 0;
  }
  else {
    local_24c = FUN_007c2480("Options",0,0x447ac000,0x43ab0000,0x429a0000,0x24,0,0x41e00000,
                             0x40a00000);
  }
  local_8._0_1_ = 10;
  local_138[0x55] = local_24c;
  FUN_007d2870("topcorner.png");
  (**(code **)(*(int *)local_138[0x55] + 0x40))("topcrnhv.png");
  (**(code **)(*(int *)local_138[0x55] + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_0079d680);
  FUN_007d2110(local_138[0x55],0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 0x10;
  if (pvVar2 == (void *)0x0) {
    local_25c = 0;
  }
  else {
    local_25c = FUN_007c2480("Create",0,0,0x43ab0000,0x429a0000,0xa2,0,0xc2200000,0);
  }
  local_8._0_1_ = 10;
  local_138[0x56] = local_25c;
  FUN_007d2870("topcorner.png");
  (**(code **)(*(int *)local_138[0x56] + 0x40))("topcrnhv.png");
  (**(code **)(*(int *)local_138[0x56] + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar4);
  FUN_007c23e0(FUN_0079d6b0);
  FUN_007d2110(local_138[0x56],0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 0x11;
  if (pvVar2 == (void *)0x0) {
    local_204 = 0;
  }
  else {
    local_204 = FUN_007c2480(&DAT_0089ecdc,0,0x447ac000,0x43ab0000,0x429a0000,0xa6,0,0xc2200000,
                             0x40a00000);
  }
  local_8._0_1_ = 10;
  local_138[0x57] = local_204;
  FUN_007d2870("topcorner.png");
  (**(code **)(*(int *)local_138[0x57] + 0x40))("topcrnhv.png");
  (**(code **)(*(int *)local_138[0x57] + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar6);
  FUN_007c23e0(FUN_0079d690);
  FUN_007d2110(local_138[0x57],0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 0x12;
  if (pvVar2 == (void *)0x0) {
    local_1e8 = 0;
  }
  else {
    local_1e8 = FUN_007cc390("Lobby",0x42b40000,0x42ba0000,0x43a00000,0x42040000,0x9020,local_13c,0)
    ;
  }
  local_8._0_1_ = 10;
  local_138[0x58] = local_1e8;
  (**(code **)(*(int *)local_138[0x58] + 0x3c))(uVar8);
  FUN_007d2110(local_138[0x58],0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 0x13;
  if (pvVar2 == (void *)0x0) {
    local_180 = 0;
  }
  else {
    local_180 = FUN_007cc390("Lobby",0x43ff0000,0x42ba0000,0x44548000,0x42040000,0x9020,local_13c,0)
    ;
  }
  local_8._0_1_ = 10;
  local_138[0x5b] = local_180;
  (**(code **)(*(int *)local_138[0x5b] + 0x3c))(uVar9);
  FUN_007d2110(local_138[0x5b],0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 0x14;
  if (pvVar2 == (void *)0x0) {
    local_188 = 0;
  }
  else {
    local_188 = FUN_007cc390("Lobby",0x44048000,0x43db8000,0x43c80000,0x42040000,0x9020,local_13c,0)
    ;
  }
  local_8._0_1_ = 10;
  local_138[0x5a] = local_188;
  FUN_007d3f20(1);
  (**(code **)(*(int *)local_138[0x5a] + 0x3c))(uVar7);
  FUN_007d2110(local_138[0x5a],0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 0x15;
  if (pvVar2 == (void *)0x0) {
    local_1f8 = 0;
  }
  else {
    local_1f8 = FUN_007cc390("Lobby",0x4480c000,0x43db8000,0x43a90000,0x42040000,0x9020,local_13c,0)
    ;
  }
  local_8._0_1_ = 10;
  local_138[0x5c] = local_1f8;
  (**(code **)(*(int *)local_138[0x5c] + 0x3c))(uVar11);
  FUN_007d2110(local_138[0x5c],0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 0x16;
  if (pvVar2 == (void *)0x0) {
    local_250 = 0;
  }
  else {
    local_250 = FUN_007cc390("Lobby",0x42b40000,0x44138000,0x43a00000,0x42040000,0x9020,local_13c,0)
    ;
  }
  local_8._0_1_ = 10;
  local_138[0x59] = local_250;
  (**(code **)(*(int *)local_138[0x59] + 0x3c))(uVar10);
  FUN_007d2110(local_138[0x59],0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 0x17;
  if (pvVar2 == (void *)0x0) {
    local_200 = 0;
  }
  else {
    local_200 = FUN_007c2480("Create Room",0x42be0000,0x43f60000,0x439b0000,0x429a0000,0x20,
                             local_13c,0,0x41000000);
  }
  local_8._0_1_ = 10;
  local_138[0x54] = local_200;
  FUN_007d3f20(4);
  FUN_007d2870("multi_createGame_button_off.png");
  (**(code **)(*(int *)local_138[0x54] + 0x40))("multi_createGame_button_over.png");
  (**(code **)(*(int *)local_138[0x54] + 0x3c))("multi_createGame_button_on.png");
  FUN_007c2950(uVar5);
  FUN_007c23e0(FUN_0079d6a0);
  FUN_007d2110(local_138[0x54],0);
  pvVar2 = operator_new(0x180);
  local_8._0_1_ = 0x18;
  if (pvVar2 == (void *)0x0) {
    local_230 = 0;
  }
  else {
    local_230 = FUN_007c9de0("ChatRoomList",0x42b40000,0x43060000,0x43a00000,0x43af0000,FUN_0079d570
                             ,FUN_0079d580,0x20,local_13c,0xff00ff00,0x3f800000);
  }
  local_8._0_1_ = 10;
  local_138[0x5d] = local_230;
  DAT_00945568 = local_138[0x5d];
  FUN_007cb3e0(FUN_0079d6c0);
  FUN_007d2110(local_138[0x5d],0);
  pvVar2 = operator_new(0x180);
  local_8._0_1_ = 0x19;
  if (pvVar2 == (void *)0x0) {
    local_208 = 0;
  }
  else {
    local_208 = FUN_007c9de0("ChatUserList",0x42ea0000,0x441d8000,0x43968000,0x43af0000,FUN_0079d590
                             ,FUN_0079d5a0,0x20,local_13c,0xff00ff00,0x3f800000);
  }
  local_8 = CONCAT31(local_8._1_3_,10);
  local_138[0x6b] = local_208;
  DAT_0094556c = local_138[0x6b];
  FUN_007cb3e0(FUN_0079d6e0);
  FUN_007d2110(local_138[0x6b],0);
  local_144 = 0;
  while( true ) {
    uVar12 = FUN_007cb5a0();
    if (uVar12 <= local_144) break;
    basic_string<>("chatUser");
    local_8._0_1_ = 0x1a;
    uVar1 = FUN_007d4300(local_74,local_144,0);
    local_8._0_1_ = 0x1b;
    FUN_00449810(uVar1);
    local_8._0_1_ = 0x1a;
    ~basic_string<>();
    FUN_007cabf0(&DAT_008a1ad8,local_144,0);
    local_150 = 14.0;
    fVar14 = (float10)FUN_007ca800();
    fVar15 = (float)((double)(int)local_144 + (double)(&DAT_008a2fd0)[-((int)local_144 >> 0x1f)]) *
             (float)fVar14;
    uVar1 = FUN_007d4300(local_11c,local_144,0);
    local_8._0_1_ = 0x1c;
    FUN_006dd7f0(local_44,"LobbyMuteIcon",uVar1);
    local_8._0_1_ = 0x1e;
    ~basic_string<>();
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 0x1f;
    if (pvVar2 == (void *)0x0) {
      local_1c0 = (int *)0x0;
    }
    else {
      uVar6 = 0;
      uVar5 = 0x20;
      fVar16 = fVar15 + 632.0;
      uVar4 = 0x42c80000;
      fVar17 = local_150;
      fVar18 = local_150;
      uVar1 = local_13c;
      uVar3 = FUN_0041f870(0x42c80000,fVar16,local_150,local_150,0x20,local_13c,0);
      local_1c0 = (int *)FUN_007d1cc0(uVar3,uVar4,fVar16,fVar17,fVar18,uVar5,uVar1,uVar6);
    }
    local_8._0_1_ = 0x1e;
    local_140 = local_1c0;
    FUN_007d2110(local_1c0,0);
    FUN_007d2870("mute.png");
    (**(code **)(*local_140 + 0x24))(0);
    FUN_0041fe40(&local_140);
    uVar1 = FUN_007d4300(local_a4,local_144,0);
    local_8._0_1_ = 0x20;
    uVar1 = FUN_006dd7f0(local_8c,"LobbyHostIcon",uVar1);
    FUN_0045e0f0(uVar1);
    ~basic_string<>();
    local_8._0_1_ = 0x1e;
    ~basic_string<>();
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 0x21;
    if (pvVar2 == (void *)0x0) {
      local_238 = (int *)0x0;
    }
    else {
      uVar5 = 0;
      uVar4 = 0x20;
      fVar15 = fVar15 + 632.0;
      fVar16 = (100.0 - local_150) - 2.0;
      fVar17 = local_150;
      fVar18 = local_150;
      uVar1 = local_13c;
      uVar3 = FUN_0041f870(fVar16,fVar15,local_150,local_150,0x20,local_13c,0);
      local_238 = (int *)FUN_007d1cc0(uVar3,fVar16,fVar15,fVar17,fVar18,uVar4,uVar1,uVar5);
    }
    local_8._0_1_ = 0x1e;
    local_140 = local_238;
    FUN_007d2110(local_238,0);
    FUN_007d2870("host.png");
    (**(code **)(*local_140 + 0x24))(0);
    FUN_0041fe40(&local_140);
    local_8._0_1_ = 0x1a;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,10);
    ~basic_string<>();
    local_144 = local_144 + 1;
  }
  pvVar2 = operator_new(0x180);
  local_8._0_1_ = 0x22;
  if (pvVar2 == (void *)0x0) {
    local_218 = 0;
  }
  else {
    local_218 = FUN_007c9de0("GameRoomList",0x44048000,0x43060000,0x4450c000,0x43870000,FUN_0079d5b0
                             ,FUN_0079d5d0,0x20,local_13c,0xff00ff00,0x3f800000);
  }
  local_8 = CONCAT31(local_8._1_3_,10);
  local_138[100] = local_218;
  DAT_00945560 = local_138[100];
  FUN_007cb3e0(FUN_0079d6d0);
  FUN_007d2110(local_138[100],0);
  local_14c = 0;
  while( true ) {
    uVar12 = FUN_007cb5a0();
    if (uVar12 <= local_14c) break;
    uVar1 = FUN_007d4300(local_d4,local_14c,0);
    local_8._0_1_ = 0x23;
    FUN_006dd7f0(local_2c,"MapIcon",uVar1);
    local_8._0_1_ = 0x25;
    ~basic_string<>();
    fVar14 = (float10)FUN_007ca800();
    local_148 = 14.0;
    local_158 = -44.0;
    local_160 = (float)((double)(int)local_14c + (double)(&DAT_008a2fd0)[-((int)local_14c >> 0x1f)])
                * (float)fVar14 + 4.0;
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 0x26;
    if (pvVar2 == (void *)0x0) {
      local_1e0 = 0;
    }
    else {
      uVar5 = 0;
      uVar1 = local_138[100];
      uVar4 = 0x20;
      fVar15 = local_158;
      fVar17 = local_160;
      fVar18 = local_148;
      fVar16 = local_148;
      uVar3 = FUN_0041f870(local_158,local_160,local_148,local_148,0x20,uVar1,0);
      local_1e0 = FUN_007d1cc0(uVar3,fVar15,fVar17,fVar18,fVar16,uVar4,uVar1,uVar5);
    }
    local_8._0_1_ = 0x25;
    local_168 = local_1e0;
    FUN_007d2110(local_1e0,0);
    FUN_0041fe40(&local_168);
    uVar1 = FUN_007d4300(local_134,local_14c,0);
    local_8._0_1_ = 0x27;
    uVar1 = FUN_006dd7f0(local_104,"PrivIcon",uVar1);
    FUN_0045e0f0(uVar1);
    ~basic_string<>();
    local_8._0_1_ = 0x25;
    ~basic_string<>();
    fVar15 = local_158 + 20.0;
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 0x28;
    if (pvVar2 == (void *)0x0) {
      local_174 = 0;
    }
    else {
      uVar5 = 0;
      uVar1 = local_138[100];
      uVar4 = 0x20;
      fVar17 = local_160;
      fVar18 = local_148;
      fVar16 = local_148;
      uVar3 = FUN_0041f870(fVar15,local_160,local_148,local_148,0x20,uVar1,0);
      local_174 = FUN_007d1cc0(uVar3,fVar15,fVar17,fVar18,fVar16,uVar4,uVar1,uVar5);
    }
    local_8._0_1_ = 0x25;
    local_154 = local_174;
    FUN_007d2870("private.png");
    FUN_007d2110(local_154,0);
    FUN_0041fe40(&local_154);
    uVar1 = FUN_007d4300(local_ec,local_14c,0);
    local_8._0_1_ = 0x29;
    uVar1 = FUN_006dd7f0(local_bc,"LobbyLockIcon",uVar1);
    FUN_0045e0f0(uVar1);
    ~basic_string<>();
    local_8._0_1_ = 0x25;
    ~basic_string<>();
    fVar15 = (local_158 - local_148) - 4.0;
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 0x2a;
    if (pvVar2 == (void *)0x0) {
      local_184 = 0;
    }
    else {
      uVar5 = 0;
      uVar1 = local_138[100];
      uVar4 = 0x20;
      fVar17 = local_160;
      fVar18 = local_148;
      fVar16 = local_148;
      uVar3 = FUN_0041f870(fVar15,local_160,local_148,local_148,0x20,uVar1,0);
      local_184 = FUN_007d1cc0(uVar3,fVar15,fVar17,fVar18,fVar16,uVar4,uVar1,uVar5);
    }
    local_8._0_1_ = 0x25;
    local_15c = local_184;
    FUN_007d2870("lock.png");
    FUN_007d2110(local_15c,0);
    FUN_0041fe40(&local_15c);
    local_8 = CONCAT31(local_8._1_3_,10);
    ~basic_string<>();
    local_14c = local_14c + 1;
  }
  pvVar2 = operator_new(0x180);
  local_8._0_1_ = 0x2b;
  if (pvVar2 == (void *)0x0) {
    local_194 = 0;
  }
  else {
    local_194 = FUN_007c9de0("GameUserList",0x44810000,0x43fa0000,0x43a00000,0x43f00000,0,0,0x20,
                             local_13c,0xff00ff00,0x3f800000);
  }
  local_8._0_1_ = 10;
  local_138[0x6c] = local_194;
  FUN_007cb380(0);
  FUN_007d2110(local_138[0x6c],0);
  pvVar2 = operator_new(0x295c);
  local_8._0_1_ = 0x2c;
  if (pvVar2 == (void *)0x0) {
    local_1a4 = 0;
  }
  else {
    local_1a4 = FUN_007ce140(1,"chatText",0x43eb0000,0x43fa0000,0x44020000,0x43cd0000,FUN_0079d550,
                             FUN_0079d560,0x20,local_13c);
  }
  local_8._0_1_ = 10;
  local_138[0x6e] = local_1a4;
  FUN_007d3f20(1);
  FUN_007d2110(local_138[0x6e],0);
  DAT_00945570 = local_138[0x6e];
  pvVar2 = operator_new(0x968);
  local_8._0_1_ = 0x2d;
  if (pvVar2 == (void *)0x0) {
    local_1b4 = 0;
  }
  else {
    local_1b4 = FUN_007cf410(1,1,0x24,"chatEntry",0x43eb0000,0x446c4000,0x44020000,0x42200000,0x8020
                             ,local_13c);
  }
  local_8._0_1_ = 10;
  local_138[0x6f] = local_1b4;
  CMFCToolBarsListPropertyPage::EnableUserDefinedToolbars
            ((CMFCToolBarsListPropertyPage *)local_138[0x6f],0xfa);
  FUN_007cf940(FUN_0079d5f0);
  FUN_007d2110(local_138[0x6f],0);
  pvVar2 = operator_new(0x24);
  local_8._0_1_ = 0x2e;
  if (pvVar2 == (void *)0x0) {
    local_1c4 = 0;
  }
  else {
    local_1c4 = FUN_007d0770(local_13c,0x41f00000,0x44548000,local_138[0x6b],local_138[0x6f],
                             FUN_0079d660,0);
  }
  local_8._0_1_ = 10;
  local_138[0x6d] = local_1c4;
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 0x2f;
  if (pvVar2 == (void *)0x0) {
    local_1d4 = 0;
  }
  else {
    local_1d4 = FUN_007d1cc0("totalUserBackground",0x43d10000,0x41800000,0x44150000,0x422c0000,0x20,
                             local_13c,0);
  }
  local_8._0_1_ = 10;
  FUN_007d2870("defaoff.png");
  FUN_007d2110(local_1d4,0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 0x30;
  if (pvVar2 == (void *)0x0) {
    local_1ec = 0;
  }
  else {
    local_1ec = FUN_007cc390("totalUserCount",0x44070000,0x41c00000,0x43a90000,0x41b80000,0x20,
                             local_13c,0);
  }
  local_8._0_1_ = 10;
  local_138[0xe1] = local_1ec;
  FUN_007cc710(2,0xffffffff);
  FUN_007cc6b0(0x3fa00000);
  FUN_007d2110(local_138[0xe1],0);
  pvVar2 = operator_new(0x158);
  local_8._0_1_ = 0x31;
  if (pvVar2 == (void *)0x0) {
    local_164 = 0;
  }
  else {
    local_164 = FUN_007cfdd0("NameRoom",0x43e30000,0x43af0000,0x4404c000,0x43620000,0x20,local_13c);
  }
  local_8 = CONCAT31(local_8._1_3_,10);
  local_138[0x70] = local_164;
  FUN_007d2110(local_138[0x70],0);
  (**(code **)(*(int *)local_138[0x70] + 0x24))(0);
  iVar13 = FUN_0056f900();
  if (iVar13 == 0) {
    FUN_0073dd40();
  }
  else {
    FUN_007a21e0();
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

