
void FUN_007a4b60(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  float fVar11;
  code *pcVar12;
  float fVar13;
  code *pcVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  int *local_21c;
  undefined4 local_218;
  int *local_214;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined4 local_1fc;
  float local_1f8;
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4;
  int *local_1d0;
  void *local_1cc;
  void *local_1c8;
  int *local_1c4;
  undefined4 local_1c0;
  void *local_1bc;
  int *local_1b8;
  int *local_1b4;
  int *local_1b0;
  void *local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  void *local_19c;
  undefined4 local_198;
  undefined4 local_194;
  float local_190;
  void *local_18c;
  undefined4 local_188;
  void *local_184;
  undefined4 local_180;
  void *local_17c;
  int *local_178;
  int *local_174;
  void *local_170;
  void *local_16c;
  void *local_168;
  int *local_164;
  void *local_160;
  void *local_15c;
  void *local_158;
  undefined4 local_154;
  int *local_150;
  void *local_14c;
  uint local_148;
  undefined4 local_144;
  void *local_140;
  void *local_13c;
  void *local_138;
  undefined4 local_134;
  void *local_130;
  void *local_12c;
  void *local_128;
  undefined4 local_124;
  int *local_120;
  void *local_11c;
  undefined4 local_118;
  float local_108;
  undefined4 local_104;
  undefined4 local_100;
  uint local_fc;
  float local_f8;
  int *local_f4;
  int *local_f0;
  uint local_ec;
  float local_e8;
  int *local_e4;
  int *local_e0;
  undefined4 local_dc;
  undefined4 *local_d8;
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
  puStack_c = &LAB_00860574;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(local_14);
  local_8 = 0;
  *local_d8 = cUI_Multiplayer_Status::vftable;
  vector<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  vector<>();
  local_8._0_1_ = 3;
  FUN_0073a6b0();
  DAT_00945549 = 1;
  DAT_0094557c = local_d8;
  *(undefined1 *)(local_d8 + 0x51) = 0;
  local_184 = operator_new(0x144);
  local_8._0_1_ = 4;
  if (local_184 == (void *)0x0) {
    local_194 = 0;
  }
  else {
    local_194 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 3;
  local_dc = local_194;
  FUN_007d3f20(1);
  FUN_007d2870("multipe_center.png");
  FUN_007d2110(local_dc,0);
  uVar1 = FUN_0081cb40("escape","return_to_game");
  uVar2 = FUN_0081cb40("multi_common","options");
  uVar3 = FUN_0081cb40("multi_common","leave_game");
  uVar4 = FUN_0081cb40("multi_common","game_stats");
  local_1d8 = FUN_0081cb40("multi_common","player_status");
  local_1e0 = FUN_0081cb40("multi_common",&DAT_0089e97c);
  local_19c = operator_new(0x1ec);
  local_8._0_1_ = 5;
  if (local_19c == (void *)0x0) {
    local_1a4 = 0;
  }
  else {
    local_1a4 = FUN_007c2480(&DAT_00877f98,0x3f800000,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 3;
  local_d8[0x53] = local_1a4;
  FUN_007d2870("topcorner.png");
  (**(code **)(*(int *)local_d8[0x53] + 0x40))("topcrnhv.png");
  (**(code **)(*(int *)local_d8[0x53] + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar1);
  FUN_007c23e0(FUN_007a4920);
  FUN_007d2110(local_d8[0x53],0);
  local_1ac = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (local_1ac == (void *)0x0) {
    local_1b4 = (int *)0x0;
  }
  else {
    local_1b4 = (int *)FUN_007c2480("Options_EscScreen",0,0x447ac000,0x43ab0000,0x429a0000,0x24,0,
                                    0x41e00000,0x40a00000);
  }
  local_8._0_1_ = 3;
  local_f4 = local_1b4;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_f4 + 0x40))("topcrnhv.png");
  (**(code **)(*local_f4 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007a4930);
  FUN_007d2110(local_f4,0);
  local_1bc = operator_new(0x1ec);
  local_8._0_1_ = 7;
  if (local_1bc == (void *)0x0) {
    local_1c4 = (int *)0x0;
  }
  else {
    local_1c4 = (int *)FUN_007c2480(&DAT_0089ecdc,0,0x447ac000,0x43ab0000,0x429a0000,0xa6,0,
                                    0xc2200000,0x40a00000);
  }
  local_8._0_1_ = 3;
  local_f0 = local_1c4;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_f0 + 0x40))("topcrnhv.png");
  (**(code **)(*local_f0 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_007a4940);
  FUN_007d2110(local_f0,0);
  local_1cc = operator_new(0x930);
  local_8._0_1_ = 8;
  if (local_1cc == (void *)0x0) {
    local_120 = (int *)0x0;
  }
  else {
    local_120 = (int *)FUN_007cc390("Lobby",0x43160000,0x42b40000,0x44898000,0x41b80000,0x9020,
                                    local_dc,0);
  }
  local_8._0_1_ = 3;
  local_e0 = local_120;
  (**(code **)(*local_120 + 0x3c))(uVar4);
  FUN_007d2110(local_e0,0);
  local_18c = operator_new(0x930);
  local_8._0_1_ = 9;
  if (local_18c == (void *)0x0) {
    local_178 = (int *)0x0;
  }
  else {
    local_178 = (int *)FUN_007cc390("Lobby",0x43160000,0x44160000,0x43a90000,0x41b80000,0x8020,
                                    local_dc,0);
  }
  local_8._0_1_ = 3;
  local_e0 = local_178;
  (**(code **)(*local_178 + 0x3c))(local_1d8);
  FUN_007d2110(local_e0,0);
  local_128 = operator_new(0x930);
  local_8._0_1_ = 10;
  if (local_128 == (void *)0x0) {
    local_1b8 = (int *)0x0;
  }
  else {
    local_1b8 = (int *)FUN_007cc390("Lobby",0x44520000,0x44160000,0x43a90000,0x41b80000,0x8020,
                                    local_dc,0);
  }
  local_1d0 = local_1b8;
  local_8._0_1_ = 3;
  local_e0 = local_1b8;
  (**(code **)(*local_1b8 + 0x3c))(local_1e0);
  FUN_007d2110(local_e0,0);
  local_130 = operator_new(0x294c);
  local_8._0_1_ = 0xb;
  if (local_130 == (void *)0x0) {
    local_180 = 0;
  }
  else {
    local_180 = FUN_007ccb70("chatText",0x443b8000,0x44228000,0x44110000,0x43820000,0,local_dc);
  }
  local_23c = local_180;
  local_8._0_1_ = 3;
  local_d8[0x57] = local_180;
  (**(code **)(*(int *)local_d8[0x57] + 0x3c))(&DAT_008a1ad8,3);
  FUN_007d2110(local_d8[0x57],0);
  local_138 = operator_new(0x968);
  local_8._0_1_ = 0xc;
  if (local_138 == (void *)0x0) {
    local_1a8 = 0;
  }
  else {
    local_1a8 = FUN_007cf410(1,1,0x2a,"CreateTextEntry",0x443b8000,0x446c4000,0x44110000,0x42200000,
                             0x8020,local_dc);
  }
  local_1e8 = local_1a8;
  local_8._0_1_ = 3;
  local_d8[0x58] = local_1a8;
  FUN_007cf940(FUN_007a48b0);
  FUN_007d2110(local_d8[0x58],0);
  local_140 = operator_new(0x180);
  local_8._0_1_ = 0xd;
  if (local_140 == (void *)0x0) {
    local_188 = 0;
  }
  else {
    local_188 = FUN_007c9de0("ChatUserList2",0x430c0000,0x442b4000,0x440c0000,0x43988000,
                             FUN_007a4840,FUN_007a4860,0,local_dc,0xff00ff00,0x3f800000);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  local_d8[0x65] = local_188;
  FUN_007cb3e0(FUN_007a69c0);
  FUN_007d2110(local_d8[0x65],0);
  local_ec = 0;
  while( true ) {
    uVar5 = FUN_007cb5a0();
    if (uVar5 <= local_ec) break;
    basic_string<>("chatUser");
    local_8._0_1_ = 0xe;
    local_1f0 = FUN_007d4300(local_bc,local_ec,0);
    local_8._0_1_ = 0xf;
    FUN_00449810(local_1f0);
    local_8._0_1_ = 0xe;
    ~basic_string<>();
    FUN_007cabf0(&DAT_008a1ad8,local_ec,0);
    local_f8 = 14.0;
    fVar7 = (float10)FUN_007ca800();
    local_1f8 = (float)fVar7;
    local_148 = local_ec;
    local_190 = (float)((double)(int)local_ec + (double)(&DAT_008a2fd0)[-((int)local_ec >> 0x1f)]) *
                local_1f8;
    local_200 = FUN_007d4300(local_a4,local_ec,0);
    local_8._0_1_ = 0x10;
    FUN_006dd7f0(local_2c,"StatusMuteIcon",local_200);
    local_8._0_1_ = 0x12;
    ~basic_string<>();
    local_1c8 = operator_new(0x144);
    local_8._0_1_ = 0x13;
    if (local_1c8 == (void *)0x0) {
      local_150 = (int *)0x0;
    }
    else {
      uVar17 = 0;
      uVar4 = 0x20;
      fVar8 = local_190 + 685.0;
      uVar3 = 0x42c80000;
      fVar11 = local_f8;
      fVar13 = local_f8;
      uVar1 = local_dc;
      uVar2 = FUN_0041f870(0x42c80000,fVar8,local_f8,local_f8,0x20,local_dc,0);
      local_150 = (int *)FUN_007d1cc0(uVar2,uVar3,fVar8,fVar11,fVar13,uVar4,uVar1,uVar17);
    }
    local_8._0_1_ = 0x12;
    local_e4 = local_150;
    FUN_007d2110(local_150,0);
    FUN_007d2870("mute.png");
    (**(code **)(*local_e4 + 0x24))(0);
    FUN_0041fe40(&local_e4);
    local_208 = FUN_007d4300(local_74,local_ec,0);
    local_8._0_1_ = 0x14;
    local_210 = FUN_006dd7f0(local_8c,"StatusHostIcon",local_208);
    FUN_0045e0f0(local_210);
    ~basic_string<>();
    local_8._0_1_ = 0x12;
    ~basic_string<>();
    local_158 = operator_new(0x144);
    local_8._0_1_ = 0x15;
    if (local_158 == (void *)0x0) {
      local_1b0 = (int *)0x0;
    }
    else {
      uVar4 = 0;
      uVar3 = 0x20;
      fVar8 = local_190 + 685.0;
      fVar9 = (100.0 - local_f8) - 2.0;
      fVar11 = local_f8;
      fVar13 = local_f8;
      uVar1 = local_dc;
      uVar2 = FUN_0041f870(fVar9,fVar8,local_f8,local_f8,0x20,local_dc,0);
      local_1b0 = (int *)FUN_007d1cc0(uVar2,fVar9,fVar8,fVar11,fVar13,uVar3,uVar1,uVar4);
    }
    local_8._0_1_ = 0x12;
    local_e4 = local_1b0;
    FUN_007d2110(local_1b0,0);
    FUN_007d2870("host.png");
    (**(code **)(*local_e4 + 0x24))(0);
    FUN_0041fe40(&local_e4);
    local_8._0_1_ = 0xe;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
    local_ec = local_ec + 1;
  }
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,0x16);
  local_218 = 0x43160000;
  FUN_0041ff90(&local_218);
  local_22c = 0x437a0000;
  FUN_0041ff90(&local_22c);
  local_220 = 0x44354000;
  FUN_0041ff90(&local_220);
  local_230 = 0x44480000;
  FUN_0041ff90(&local_230);
  local_228 = 0x44610000;
  FUN_0041ff90(&local_228);
  local_238 = 0x447a0000;
  FUN_0041ff90(&local_238);
  local_240 = 0x44898000;
  FUN_0041ff90(&local_240);
  local_fc = 0;
  while( true ) {
    uVar5 = size();
    if (uVar5 <= local_fc) break;
    local_234 = FUN_0073b940(local_d4,local_fc);
    local_8._0_1_ = 0x17;
    local_1d4 = local_234;
    FUN_006dd7f0(local_44,"ScoreList",local_234);
    local_8._0_1_ = 0x19;
    ~basic_string<>();
    local_160 = operator_new(0x180);
    local_8._0_1_ = 0x1a;
    if (local_160 == (void *)0x0) {
      local_198 = 0;
    }
    else {
      uVar18 = 0x3f800000;
      uVar16 = 0xff00ff00;
      uVar15 = 0x20;
      pcVar14 = FUN_007a48a0;
      pcVar12 = FUN_007a48a0;
      uVar10 = 0x43ca0000;
      uVar17 = 0x449b0000;
      uVar4 = 0x43000000;
      uVar2 = local_dc;
      puVar6 = (undefined4 *)FUN_004200d0(local_fc);
      uVar1 = *puVar6;
      uVar3 = FUN_0041f870(uVar1,uVar4,uVar17,uVar10,pcVar12,pcVar14,uVar15,uVar2,uVar16,uVar18);
      local_198 = FUN_007c9de0(uVar3,uVar1,uVar4,uVar17,uVar10,pcVar12,pcVar14,uVar15,uVar2,uVar16,
                               uVar18);
    }
    local_1dc = local_198;
    local_8._0_1_ = 0x19;
    local_100 = local_198;
    FUN_007cb380(0);
    FUN_007d2110(local_100,0);
    FUN_0041fe40(&local_100);
    local_8 = CONCAT31(local_8._1_3_,0x16);
    ~basic_string<>();
    local_fc = local_fc + 1;
  }
  local_e8 = 48.0;
  local_104 = 0x41700000;
  local_108 = 990.0;
  local_168 = operator_new(0x1ec);
  local_8._0_1_ = 0x1b;
  if (local_168 == (void *)0x0) {
    local_1c0 = 0;
  }
  else {
    local_1c0 = FUN_007c2480("Whisper User",local_104,local_108 - local_e8 * 3.0,local_e8,local_e8,0
                             ,local_dc,0,0);
  }
  local_1e4 = local_1c0;
  local_8._0_1_ = 0x16;
  local_d8[0x59] = local_1c0;
  FUN_007d2870("MultiplayerModeButton_off.png");
  (**(code **)(*(int *)local_d8[0x59] + 0x40))("MultiplayerModeButton_over.png");
  (**(code **)(*(int *)local_d8[0x59] + 0x3c))("MultiplayerModeButton_on.png");
  uVar1 = FUN_0081cb40("first_letter","whisper");
  FUN_007c2950(uVar1);
  FUN_007c23e0(FUN_007a4950);
  FUN_007c23c0(FUN_007a4b00);
  FUN_007d2110(local_d8[0x59],0);
  local_170 = operator_new(0x1ec);
  local_8._0_1_ = 0x1c;
  if (local_170 == (void *)0x0) {
    local_1a0 = 0;
  }
  else {
    local_1a0 = FUN_007c2480("Mute User",local_104,local_108 - local_e8 * 2.0,local_e8,local_e8,0,
                             local_dc,0,0);
  }
  local_1ec = local_1a0;
  local_8._0_1_ = 0x16;
  local_d8[0x5a] = local_1a0;
  FUN_007d2870("MultiplayerModeButton_off.png");
  (**(code **)(*(int *)local_d8[0x5a] + 0x40))("MultiplayerModeButton_over.png");
  (**(code **)(*(int *)local_d8[0x5a] + 0x3c))("MultiplayerModeButton_on.png");
  uVar1 = FUN_0081cb40("first_letter",&DAT_0089ef88);
  FUN_007c2950(uVar1);
  FUN_007c23e0(FUN_007a4a80);
  FUN_007c23c0(FUN_007a4b20);
  FUN_007d2110(local_d8[0x5a],0);
  local_11c = operator_new(0x1ec);
  local_8._0_1_ = 0x1d;
  if (local_11c == (void *)0x0) {
    local_124 = 0;
  }
  else {
    local_124 = FUN_007c2480("Kick User",local_104,local_108 - local_e8,local_e8,local_e8,0,local_dc
                             ,0,0);
  }
  local_1f4 = local_124;
  local_8._0_1_ = 0x16;
  local_d8[0x5b] = local_124;
  FUN_007d2870("MultiplayerModeButton_off.png");
  (**(code **)(*(int *)local_d8[0x5b] + 0x40))("MultiplayerModeButton_over.png");
  (**(code **)(*(int *)local_d8[0x5b] + 0x3c))("MultiplayerModeButton_on.png");
  uVar1 = FUN_0081cb40("first_letter",&DAT_0089f02c);
  FUN_007c2950(uVar1);
  FUN_007c23e0(FUN_007a4a20);
  FUN_007c23c0(FUN_007a4b40);
  FUN_007d2110(local_d8[0x5b],0);
  local_12c = operator_new(0x930);
  local_8._0_1_ = 0x1e;
  if (local_12c == (void *)0x0) {
    local_134 = 0;
  }
  else {
    local_134 = FUN_007cc390("Lobby",0x43870000,0x447a0000,0x43a90000,0x422c0000,0x20,local_dc,0);
  }
  local_1fc = local_134;
  local_8._0_1_ = 0x16;
  local_d8[0x5c] = local_134;
  uVar1 = FUN_0081cb40("multi_help","whisper");
  (**(code **)(*(int *)local_d8[0x5c] + 0x3c))(uVar1);
  FUN_007cc5c0(0);
  FUN_007d2110(local_d8[0x5c],0);
  local_13c = operator_new(0x930);
  local_8._0_1_ = 0x1f;
  if (local_13c == (void *)0x0) {
    local_144 = 0;
  }
  else {
    local_144 = FUN_007cc390("Lobby",0x43870000,0x447a0000,0x43a90000,0x422c0000,0x20,local_dc,0);
  }
  local_204 = local_144;
  local_8._0_1_ = 0x16;
  local_d8[0x5d] = local_144;
  uVar1 = FUN_0081cb40("multi_help",&DAT_0089ef88);
  (**(code **)(*(int *)local_d8[0x5d] + 0x3c))(uVar1);
  FUN_007cc5c0(0);
  FUN_007d2110(local_d8[0x5d],0);
  local_14c = operator_new(0x930);
  local_8._0_1_ = 0x20;
  if (local_14c == (void *)0x0) {
    local_154 = 0;
  }
  else {
    local_154 = FUN_007cc390("Lobby",0x43870000,0x447a0000,0x43a90000,0x422c0000,0x20,local_dc,0);
  }
  local_20c = local_154;
  local_8._0_1_ = 0x16;
  local_d8[0x5e] = local_154;
  uVar1 = FUN_0081cb40("multi_help",&DAT_0089f02c);
  (**(code **)(*(int *)local_d8[0x5e] + 0x3c))(uVar1);
  FUN_007cc5c0(0);
  FUN_007d2110(local_d8[0x5e],0);
  local_15c = operator_new(0x930);
  local_8._0_1_ = 0x21;
  if (local_15c == (void *)0x0) {
    local_164 = (int *)0x0;
  }
  else {
    local_164 = (int *)FUN_007cc390("Lobby",0x43160000,0x44214000,0x43960000,0x41b80000,0x8020,
                                    local_dc,0);
  }
  local_214 = local_164;
  local_8._0_1_ = 0x16;
  local_e0 = local_164;
  uVar1 = FUN_0081cb40("multi_common","player");
  (**(code **)(*local_e0 + 0x3c))(uVar1);
  FUN_007d2110(local_e0,0);
  local_16c = operator_new(0x930);
  local_8._0_1_ = 0x22;
  if (local_16c == (void *)0x0) {
    local_174 = (int *)0x0;
  }
  else {
    local_174 = (int *)FUN_007cc390("Lobby",0x43ed8000,0x44214000,0x43960000,0x41b80000,0x8020,
                                    local_dc,0);
  }
  local_21c = local_174;
  local_8._0_1_ = 0x16;
  local_e0 = local_174;
  uVar1 = FUN_0081cb40("multi_common","vehicle");
  (**(code **)(*local_e0 + 0x3c))(uVar1);
  FUN_007d2110(local_e0,0);
  local_17c = operator_new(0x930);
  local_8._0_1_ = 0x23;
  if (local_17c == (void *)0x0) {
    local_118 = 0;
  }
  else {
    local_118 = FUN_007cc390("errorConditionLabel",0,0,0x44b40000,0x422c0000,0x9020,local_dc,0);
  }
  local_224 = local_118;
  local_8._0_1_ = 0x16;
  local_d8[0x52] = local_118;
  FUN_007cc6b0(0x3fa00000);
  uVar1 = FUN_0081cb40("multi_message","game_over");
  (**(code **)(*(int *)local_d8[0x52] + 0x3c))(uVar1);
  FUN_007d2110(local_d8[0x52],0);
  FUN_007cc5c0(0);
  FUN_007a6b70();
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_0041fe20();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

