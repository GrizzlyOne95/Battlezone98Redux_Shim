
void FUN_007abee0(void)

{
  char cVar1;
  int iVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  undefined4 uVar4;
  undefined1 local_2c4 [8];
  undefined4 local_2bc;
  int *local_2b8;
  int *local_2b4;
  int *local_2b0;
  undefined4 local_2ac;
  undefined4 local_2a8;
  undefined4 local_2a4;
  int *local_2a0;
  int *local_29c;
  undefined4 local_298;
  undefined4 local_294;
  int *local_290;
  int *local_28c;
  undefined4 local_288;
  int *local_284;
  int *local_280;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  int *local_26c;
  undefined4 local_268;
  int *local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined1 local_24c [4];
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  float local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined4 local_218;
  undefined4 local_214;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined4 local_1fc;
  undefined4 local_1f8;
  undefined4 local_1f4;
  void *local_1f0;
  void *local_1ec;
  int *local_1e8;
  void *local_1e4;
  undefined4 local_1e0;
  void *local_1dc;
  int *local_1d8;
  void *local_1d4;
  undefined4 local_1d0;
  void *local_1cc;
  int *local_1c8;
  void *local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  int *local_1b8;
  void *local_1b4;
  undefined4 local_1b0;
  void *local_1ac;
  int *local_1a8;
  void *local_1a4;
  undefined4 local_1a0;
  void *local_19c;
  int *local_198;
  void *local_194;
  int *local_190;
  void *local_18c;
  void *local_188;
  undefined4 local_184;
  undefined4 local_180;
  void *local_17c;
  int *local_178;
  undefined4 local_174;
  void *local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  void *local_160;
  undefined4 local_15c;
  float local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  void *local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  void *local_138;
  undefined4 local_134;
  undefined4 local_130;
  int *local_12c;
  void *local_128;
  int local_124;
  undefined4 local_120;
  undefined4 local_11c;
  void *local_118;
  void *local_114;
  undefined4 local_110;
  void *local_10c;
  void *local_108;
  void *local_104;
  undefined4 local_100;
  void *local_fc;
  int *local_f8;
  void *local_f4;
  void *local_f0;
  void *local_ec;
  float local_e8;
  void *local_e4;
  undefined4 local_e0;
  void *local_dc;
  void *local_d8;
  void *local_d4;
  undefined4 local_d0;
  void *local_cc;
  int *local_c8;
  void *local_c4;
  void *local_c0;
  void *local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  int *local_b0;
  int *local_ac;
  undefined4 local_a8;
  int *local_a4;
  int *local_a0;
  int *local_9c;
  undefined4 local_98;
  undefined4 local_94;
  int *local_90;
  undefined4 local_8c;
  int *local_88;
  int *local_84;
  float local_80;
  int *local_7c;
  float local_78;
  int *local_74;
  float local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  undefined1 local_58 [4];
  float local_54;
  float local_50;
  int *local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860d04;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(local_14);
  local_8 = 0;
  *local_30 = cUI_OptionsAudio::vftable;
  local_30[0x51] = 0;
  local_30[0x52] = 0;
  local_30[0x53] = 0;
  vector<>();
  local_8._0_1_ = 1;
  DAT_009455a0 = local_30;
  local_17c = operator_new(0x144);
  local_8._0_1_ = 2;
  if (local_17c == (void *)0x0) {
    local_11c = 0;
  }
  else {
    local_11c = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_1f4 = local_11c;
  local_8._0_1_ = 1;
  local_34 = local_11c;
  FUN_007d3f20(1);
  FUN_007d2870("keyOptions_center.png");
  FUN_007d2110(local_34,0);
  local_1fc = FUN_0081cb40("audio_options",&DAT_008714b0);
  local_180 = FUN_0081cb40("audio_options","music_volume");
  local_d0 = FUN_0081cb40("audio_options","effects_volume");
  local_100 = FUN_0081cb40("audio_options","voice_volume");
  local_bc = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (local_bc == (void *)0x0) {
    local_190 = (int *)0x0;
  }
  else {
    local_190 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_2b4 = local_190;
  local_8._0_1_ = 1;
  local_4c = local_190;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_4c + 0x40))("topcrnhv.png");
  (**(code **)(*local_4c + 0x3c))("topcrnck.png");
  FUN_007c2950(local_1fc);
  FUN_007c23e0(FUN_007ab7c0);
  FUN_007d2110(local_4c,0);
  iVar2 = FUN_004344a0();
  if (iVar2 == 2) {
    local_21c = FUN_0081cb40("joystick","sensitivity");
    local_3c = 229.0;
    local_60 = 100.0;
    local_94 = 0x447e4000;
    local_8c = 0x4429c000;
    local_64 = 0x43700000;
    local_48 = 0x43ca8000;
    local_68 = 0x429e0000;
    local_6c = 0x43700000;
    local_70 = -30.0;
    local_224 = 229.0;
    local_c4 = operator_new(0x930);
    local_8._0_1_ = 4;
    if (local_c4 == (void *)0x0) {
      local_198 = (int *)0x0;
    }
    else {
      local_198 = (int *)FUN_007cc390("Music",local_6c,local_3c + local_70,local_48,0x429e0000,
                                      0x9020,local_34,0);
    }
    local_264 = local_198;
    local_8._0_1_ = 1;
    local_ac = local_198;
    (**(code **)(*local_198 + 0x3c))(local_180);
    FUN_007d2110(local_ac,0);
    local_cc = operator_new(0x164);
    local_8._0_1_ = 5;
    if (local_cc == (void *)0x0) {
      local_1a0 = 0;
    }
    else {
      local_1a0 = FUN_007cbd60("MusicSlider",local_64,local_3c,local_48,local_68,0x20,local_34);
    }
    local_204 = local_1a0;
    local_8._0_1_ = 1;
    local_30[0x53] = local_1a0;
    FUN_007cc2d0((float)*(byte *)(DAT_0094672c + 0x2a));
    FUN_007cc340(FUN_007ab7e0);
    FUN_007d2110(local_30[0x53],0);
    local_3c = local_3c + local_60;
    local_d4 = operator_new(0x930);
    local_8._0_1_ = 6;
    if (local_d4 == (void *)0x0) {
      local_1a8 = (int *)0x0;
    }
    else {
      local_1a8 = (int *)FUN_007cc390("Effects",local_6c,local_3c + local_70,local_48,0x429e0000,
                                      0x9020,local_34,0);
    }
    local_2b0 = local_1a8;
    local_8._0_1_ = 1;
    local_b0 = local_1a8;
    (**(code **)(*local_1a8 + 0x3c))(local_d0);
    FUN_007d2110(local_b0,0);
    local_dc = operator_new(0x164);
    local_8._0_1_ = 7;
    if (local_dc == (void *)0x0) {
      local_1b0 = 0;
    }
    else {
      local_1b0 = FUN_007cbd60("EffectSlider",local_64,local_3c,local_48,local_68,0x20,local_34);
    }
    local_20c = local_1b0;
    local_8._0_1_ = 1;
    local_30[0x52] = local_1b0;
    FUN_007cc2d0((float)*(byte *)(DAT_0094672c + 0x2b));
    FUN_007cc340(FUN_007ab7f0);
    FUN_007d2110(local_30[0x52],0);
    local_3c = local_3c + local_60;
    local_e4 = operator_new(0x930);
    local_8._0_1_ = 8;
    if (local_e4 == (void *)0x0) {
      local_1b8 = (int *)0x0;
    }
    else {
      local_1b8 = (int *)FUN_007cc390("Voice",local_6c,local_3c + local_70,local_48,0x429e0000,
                                      0x9020,local_34,0);
    }
    local_26c = local_1b8;
    local_8._0_1_ = 1;
    local_7c = local_1b8;
    (**(code **)(*local_1b8 + 0x3c))(local_100);
    FUN_007d2110(local_7c,0);
    local_ec = operator_new(0x164);
    local_8._0_1_ = 9;
    if (local_ec == (void *)0x0) {
      local_1c0 = 0;
    }
    else {
      local_1c0 = FUN_007cbd60("VoiceSlider",local_64,local_3c,local_48,local_68,0x20,local_34);
    }
    local_214 = local_1c0;
    local_8._0_1_ = 1;
    local_30[0x51] = local_1c0;
    FUN_007cc2d0((float)*(byte *)(DAT_0094672c + 0x2c));
    FUN_007cc340(FUN_007ab7d0);
    FUN_007d2110(local_30[0x51],0);
    local_3c = local_3c + local_60;
    local_f4 = operator_new(0x930);
    local_8._0_1_ = 10;
    if (local_f4 == (void *)0x0) {
      local_1c8 = (int *)0x0;
    }
    else {
      local_1c8 = (int *)FUN_007cc390("Sensitivity",local_6c,local_3c + local_70,local_48,0x429e0000
                                      ,0x9020,local_34,0);
    }
    local_29c = local_1c8;
    local_8._0_1_ = 1;
    local_a4 = local_1c8;
    (**(code **)(*local_1c8 + 0x3c))(local_21c);
    FUN_007d2110(local_a4,0);
    local_fc = operator_new(0x164);
    local_8._0_1_ = 0xb;
    if (local_fc == (void *)0x0) {
      local_1d0 = 0;
    }
    else {
      local_1d0 = FUN_007cbd60("JoystickSlider",local_64,local_3c,local_48,local_68,0x20,local_34);
    }
    local_274 = local_1d0;
    local_8._0_1_ = 1;
    local_30[0x54] = local_1d0;
    FUN_007cc2d0((float)*(int *)(DAT_0094672c + 0x3c));
    FUN_007cc340(FUN_007ab800);
    FUN_007d2110(local_30[0x54],0);
    local_3c = local_224 + 11.0;
    local_22c = FUN_0081cb40("play_options","game_difficulty");
    local_104 = operator_new(0x930);
    local_8._0_1_ = 0xc;
    if (local_104 == (void *)0x0) {
      local_1d8 = (int *)0x0;
    }
    else {
      local_1d8 = (int *)FUN_007cc390("Difficulty",local_8c,local_3c,0x43a90000,0x421c0000,0xa020,
                                      local_34,0);
    }
    local_2b8 = local_1d8;
    local_8._0_1_ = 1;
    local_84 = local_1d8;
    (**(code **)(*local_1d8 + 0x3c))(local_22c);
    FUN_007d2110(local_84,0);
    FUN_0081cb40("option_box","VERY_EASY");
    local_234 = FUN_0081cb40("option_box",&DAT_0089f354);
    local_2a4 = FUN_0081cb40("option_box","MEDIUM");
    local_23c = FUN_0081cb40("option_box",&DAT_0089f368);
    FUN_0081cb40("option_box","VERY_HARD");
    local_10c = operator_new(500);
    local_8._0_1_ = 0xd;
    if (local_10c == (void *)0x0) {
      local_1e0 = 0;
    }
    else {
      local_1e0 = FUN_007c3150("DiffChecklist",local_94,local_3c,0x43010000,0x421c0000,0,local_34);
    }
    local_27c = local_1e0;
    local_8._0_1_ = 1;
    local_30[0x55] = local_1e0;
    FUN_007c3ac0(local_234,0);
    FUN_007c3ac0(local_2a4,1);
    FUN_007c3ac0(local_23c,2);
    FUN_007c3c10(*(undefined4 *)(DAT_0094672c + 0x40));
    FUN_007c3cf0(FUN_007ab9f0);
    FUN_007d2110(local_30[0x55],0);
    local_3c = local_3c + local_60;
    local_244 = FUN_0081cb40("control_setting","label");
    local_114 = operator_new(0x930);
    local_8._0_1_ = 0xe;
    if (local_114 == (void *)0x0) {
      local_1e8 = (int *)0x0;
    }
    else {
      local_1e8 = (int *)FUN_007cc390("control_setting_label",local_8c,local_3c,0x43a90000,
                                      0x421c0000,0xa020,local_34,0);
    }
    local_284 = local_1e8;
    local_8._0_1_ = 1;
    local_9c = local_1e8;
    (**(code **)(*local_1e8 + 0x3c))(local_244);
    FUN_007d2110(local_9c,0);
    local_1f0 = operator_new(500);
    local_8._0_1_ = 0xf;
    if (local_1f0 == (void *)0x0) {
      local_1bc = 0;
    }
    else {
      local_1bc = FUN_007c3150("ioscontrolsetting",local_94,local_3c,0x43010000,0x421c0000,0,
                               local_34);
    }
    local_2bc = local_1bc;
    local_8._0_1_ = 1;
    local_30[0x59] = local_1bc;
    FUN_0041ea20(local_2c4);
    local_8._0_1_ = 0x10;
    pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_0041e9f0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar3);
    local_8 = CONCAT31(local_8._1_3_,0x11);
    FUN_00424640(local_58);
    FID_conflict_begin(local_24c);
    while( true ) {
      cVar1 = FUN_00420f10(local_24c);
      if (cVar1 == '\0') break;
      uVar4 = FUN_004237d0();
      local_124 = FUN_0041eb70(uVar4);
      if (local_124 != 0) {
        uVar4 = FUN_0048a830();
        FUN_007c3ac0(local_124,uVar4);
        uVar4 = FUN_004237d0(local_2c);
        cVar1 = FUN_00427310(uVar4);
        if (cVar1 != '\0') {
          uVar4 = FUN_0048a830();
          FUN_007c3c10(uVar4);
        }
      }
      uVar4 = FUN_004237d0();
      FUN_006cae50(uVar4);
      FUN_00422190();
    }
    FUN_007c3cf0(FUN_007aba30);
    FUN_007d2110(local_30[0x59],0);
    local_3c = local_3c + local_60;
    local_254 = FUN_0081cb40("control_swap","label");
    local_18c = operator_new(0x930);
    local_8._0_1_ = 0x12;
    if (local_18c == (void *)0x0) {
      local_12c = (int *)0x0;
    }
    else {
      local_12c = (int *)FUN_007cc390("control_swap_label",local_8c,local_3c,0x43a90000,0x422c0000,
                                      0xa020,local_34,0);
    }
    local_28c = local_12c;
    local_8._0_1_ = 0x11;
    local_74 = local_12c;
    (**(code **)(*local_12c + 0x3c))(local_254);
    FUN_007d2110(local_74,0);
    local_25c = FUN_0081cb40("control_swap",&DAT_00889e90);
    local_294 = FUN_0081cb40("control_swap","right");
    local_1e4 = operator_new(500);
    local_8._0_1_ = 0x13;
    if (local_1e4 == (void *)0x0) {
      local_134 = 0;
    }
    else {
      local_134 = FUN_007c3150("ioscontrolswap",local_94,local_3c,0x43010000,0x421c0000,0,local_34);
    }
    local_2ac = local_134;
    local_8._0_1_ = 0x11;
    local_30[0x5a] = local_134;
    FUN_007c3ac0(local_25c,0);
    FUN_007c3ac0(local_294,1);
    uVar4 = FUN_0041c1d0();
    FUN_007c3c10(uVar4);
    FUN_007c3cf0(FUN_007aba80);
    FUN_007d2110(local_30[0x5a],0);
    local_38 = 100.0;
    local_5c = 200.0;
    local_210 = 0x430f0000;
    local_50 = 320.0;
    local_80 = 625.0;
    local_1f8 = 0x44250000;
    local_54 = 980.0;
    local_40 = 680.0;
    local_78 = 745.0;
    local_158 = 60.0;
    local_194 = operator_new(0x144);
    local_8._0_1_ = 0x14;
    if (local_194 == (void *)0x0) {
      local_13c = 0;
    }
    else {
      local_13c = FUN_007d1cc0("leftthumb",local_50,local_40,local_38,local_38,0x20,local_34,0);
    }
    local_200 = local_13c;
    local_8._0_1_ = 0x11;
    local_30[0x5b] = local_13c;
    FUN_007d2870("ui_thumb_1.png");
    FUN_007d2110(local_30[0x5b],0);
    local_1c4 = operator_new(0x144);
    local_8._0_1_ = 0x15;
    if (local_1c4 == (void *)0x0) {
      local_144 = 0;
    }
    else {
      local_144 = FUN_007d1cc0("rightthumb",local_54,local_40,local_38,local_38,0x20,local_34,0);
    }
    local_208 = local_144;
    local_8._0_1_ = 0x11;
    local_30[0x61] = local_144;
    FUN_007d2870("ui_thumb_1.png");
    FUN_007d2110(local_30[0x61],0);
    local_19c = operator_new(0x144);
    local_8._0_1_ = 0x16;
    if (local_19c == (void *)0x0) {
      local_14c = 0;
    }
    else {
      local_14c = FUN_007d1cc0("tiltDevice",local_80,local_78,local_5c,local_210,0x20,local_34,0);
    }
    local_218 = local_14c;
    local_8._0_1_ = 0x11;
    local_30[0x67] = local_14c;
    FUN_007d2870("ipadRotate.png");
    FUN_007d2110(local_30[0x67],0);
    local_1dc = operator_new(0x930);
    local_8._0_1_ = 0x17;
    if (local_1dc == (void *)0x0) {
      local_154 = 0;
    }
    else {
      local_154 = FUN_007cc390("leftthumbhold",local_50,local_40 - 40.0,local_38,0x41a00000,0x11020,
                               local_34,0);
    }
    local_220 = local_154;
    local_8._0_1_ = 0x11;
    local_30[0x5c] = local_154;
    FUN_007d2110(local_30[0x5c],0);
    local_1a4 = operator_new(0x930);
    local_8._0_1_ = 0x18;
    if (local_1a4 == (void *)0x0) {
      local_15c = 0;
    }
    else {
      local_15c = FUN_007cc390("leftthumbup",local_50,local_40 - 20.0,local_38,0x41a00000,0x11020,
                               local_34,0);
    }
    local_228 = local_15c;
    local_8._0_1_ = 0x11;
    local_30[0x5d] = local_15c;
    FUN_007d2110(local_30[0x5d],0);
    local_1cc = operator_new(0x930);
    local_8._0_1_ = 0x19;
    if (local_1cc == (void *)0x0) {
      local_164 = 0;
    }
    else {
      local_164 = FUN_007cc390("leftthumbdown",local_50,local_40 + local_38,local_38,0x41a00000,
                               0x5020,local_34,0);
    }
    local_230 = local_164;
    local_8._0_1_ = 0x11;
    local_30[0x5e] = local_164;
    FUN_007d2110(local_30[0x5e],0);
    local_1ac = operator_new(0x930);
    local_8._0_1_ = 0x1a;
    if (local_1ac == (void *)0x0) {
      local_16c = 0;
    }
    else {
      local_16c = FUN_007cc390("leftthumbleft",local_50 - local_38,local_40,local_38,local_38,0xa020
                               ,local_34,0);
    }
    local_238 = local_16c;
    local_8._0_1_ = 0x11;
    local_30[0x5f] = local_16c;
    FUN_007d2110(local_30[0x5f],0);
    local_1ec = operator_new(0x930);
    local_8._0_1_ = 0x1b;
    if (local_1ec == (void *)0x0) {
      local_174 = 0;
    }
    else {
      local_174 = FUN_007cc390("leftthumbright",local_50 + local_38,local_40,local_38,local_38,
                               0x8820,local_34,0);
    }
    local_240 = local_174;
    local_8._0_1_ = 0x11;
    local_30[0x60] = local_174;
    FUN_007d2110(local_30[0x60],0);
    local_1b4 = operator_new(0x930);
    local_8._0_1_ = 0x1c;
    if (local_1b4 == (void *)0x0) {
      local_b4 = 0;
    }
    else {
      local_b4 = FUN_007cc390("rightthumbhold",local_54,local_40 - 40.0,local_38,0x41a00000,0x11020,
                              local_34,0);
    }
    local_248 = local_b4;
    local_8._0_1_ = 0x11;
    local_30[0x62] = local_b4;
    FUN_007d2110(local_30[0x62],0);
    local_1d4 = operator_new(0x930);
    local_8._0_1_ = 0x1d;
    if (local_1d4 == (void *)0x0) {
      local_184 = 0;
    }
    else {
      local_184 = FUN_007cc390("rightThumbUp",local_54,local_40 - 20.0,local_38,0x41a00000,0x11020,
                               local_34,0);
    }
    local_250 = local_184;
    local_8._0_1_ = 0x11;
    local_30[99] = local_184;
    FUN_007d2110(local_30[99],0);
    local_118 = operator_new(0x930);
    local_8._0_1_ = 0x1e;
    if (local_118 == (void *)0x0) {
      local_120 = 0;
    }
    else {
      local_120 = FUN_007cc390("rightThumbDown",local_54,local_40 + local_38,local_38,0x41a00000,
                               0x5020,local_34,0);
    }
    local_258 = local_120;
    local_8._0_1_ = 0x11;
    local_30[100] = local_120;
    FUN_007d2110(local_30[100],0);
    local_128 = operator_new(0x930);
    local_8._0_1_ = 0x1f;
    if (local_128 == (void *)0x0) {
      local_130 = 0;
    }
    else {
      local_130 = FUN_007cc390("rightThumbLeft",local_54 - local_38,local_40,local_38,local_38,
                               0xa020,local_34,0);
    }
    local_260 = local_130;
    local_8._0_1_ = 0x11;
    local_30[0x65] = local_130;
    FUN_007d2110(local_30[0x65],0);
    local_138 = operator_new(0x930);
    local_8._0_1_ = 0x20;
    if (local_138 == (void *)0x0) {
      local_140 = 0;
    }
    else {
      local_140 = FUN_007cc390("rightThumbRight",local_54 + local_38,local_40,local_38,local_38,
                               0x8820,local_34,0);
    }
    local_268 = local_140;
    local_8._0_1_ = 0x11;
    local_30[0x66] = local_140;
    FUN_007d2110(local_30[0x66],0);
    local_148 = operator_new(0x930);
    local_8._0_1_ = 0x21;
    if (local_148 == (void *)0x0) {
      local_150 = 0;
    }
    else {
      local_150 = FUN_007cc390("tiltDeviceCounter",local_80 - local_5c,local_78 + local_158,local_5c
                               ,local_38,0xa020,local_34,0);
    }
    local_270 = local_150;
    local_8._0_1_ = 0x11;
    local_30[0x68] = local_150;
    FUN_007d2110(local_30[0x68],0);
    local_160 = operator_new(0x930);
    local_8._0_1_ = 0x22;
    if (local_160 == (void *)0x0) {
      local_168 = 0;
    }
    else {
      local_168 = FUN_007cc390("tiltDeviceClock",local_80 + local_5c,local_78 + local_158,local_5c,
                               local_38,0x8820,local_34,0);
    }
    local_278 = local_168;
    local_8._0_1_ = 0x11;
    local_30[0x69] = local_168;
    FUN_007d2110(local_30[0x69],0);
    FUN_007abd00();
    local_8._0_1_ = 0x10;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_0041eb50();
  }
  else {
    local_44 = 240.0;
    local_e8 = 100.0;
    local_98 = 0x43d68000;
    local_a8 = 0x4428c000;
    local_30[0x5b] = 0;
    local_30[0x5c] = 0;
    local_30[0x5d] = 0;
    local_30[0x5e] = 0;
    local_30[0x5f] = 0;
    local_30[0x60] = 0;
    local_30[0x61] = 0;
    local_30[0x62] = 0;
    local_30[99] = 0;
    local_30[100] = 0;
    local_30[0x65] = 0;
    local_30[0x66] = 0;
    local_30[0x67] = 0;
    local_30[0x68] = 0;
    local_30[0x69] = 0;
    local_170 = operator_new(0x930);
    local_8._0_1_ = 0x23;
    if (local_170 == (void *)0x0) {
      local_178 = (int *)0x0;
    }
    else {
      local_178 = (int *)FUN_007cc390("Music",local_98,local_44 - 11.0,0x43a90000,0x429e0000,0x8020,
                                      local_34,0);
    }
    local_280 = local_178;
    local_8._0_1_ = 1;
    local_88 = local_178;
    (**(code **)(*local_178 + 0x3c))(local_180);
    FUN_007d2110(local_88,0);
    local_188 = operator_new(0x164);
    local_8._0_1_ = 0x24;
    if (local_188 == (void *)0x0) {
      local_b8 = 0;
    }
    else {
      local_b8 = FUN_007cbd60("MusicSlider",local_a8,local_44 - 11.0,0x43ca8000,0x429e0000,0x20,
                              local_34);
    }
    local_288 = local_b8;
    local_8._0_1_ = 1;
    local_30[0x53] = local_b8;
    FUN_007cc2d0((float)*(byte *)(DAT_0094672c + 0x2a));
    FUN_007cc340(FUN_007ab7e0);
    FUN_007d2110(local_30[0x53],0);
    local_44 = local_44 + local_e8;
    local_c0 = operator_new(0x930);
    local_8._0_1_ = 0x25;
    if (local_c0 == (void *)0x0) {
      local_c8 = (int *)0x0;
    }
    else {
      local_c8 = (int *)FUN_007cc390("Effects",local_98,local_44 - 11.0,0x43a90000,0x429e0000,0x8020
                                     ,local_34,0);
    }
    local_290 = local_c8;
    local_8._0_1_ = 1;
    local_90 = local_c8;
    (**(code **)(*local_c8 + 0x3c))(local_d0);
    FUN_007d2110(local_90,0);
    local_d8 = operator_new(0x164);
    local_8._0_1_ = 0x26;
    if (local_d8 == (void *)0x0) {
      local_e0 = 0;
    }
    else {
      local_e0 = FUN_007cbd60("EffectSlider",local_a8,local_44 - 11.0,0x43ca8000,0x429e0000,0x20,
                              local_34);
    }
    local_298 = local_e0;
    local_8._0_1_ = 1;
    local_30[0x52] = local_e0;
    FUN_007cc2d0((float)*(byte *)(DAT_0094672c + 0x2b));
    FUN_007cc340(FUN_007ab7f0);
    FUN_007d2110(local_30[0x52],0);
    local_44 = local_44 + local_e8;
    local_f0 = operator_new(0x930);
    local_8._0_1_ = 0x27;
    if (local_f0 == (void *)0x0) {
      local_f8 = (int *)0x0;
    }
    else {
      local_f8 = (int *)FUN_007cc390("Voice",local_98,local_44 - 11.0,0x43a90000,0x429e0000,0x8020,
                                     local_34,0);
    }
    local_2a0 = local_f8;
    local_8._0_1_ = 1;
    local_a0 = local_f8;
    (**(code **)(*local_f8 + 0x3c))(local_100);
    FUN_007d2110(local_a0,0);
    local_108 = operator_new(0x164);
    local_8._0_1_ = 0x28;
    if (local_108 == (void *)0x0) {
      local_110 = 0;
    }
    else {
      local_110 = FUN_007cbd60("VoiceSlider",local_a8,local_44 - 11.0,0x43ca8000,0x429e0000,0x20,
                               local_34);
    }
    local_2a8 = local_110;
    local_8 = CONCAT31(local_8._1_3_,1);
    local_30[0x51] = local_110;
    FUN_007cc2d0((float)*(byte *)(DAT_0094672c + 0x2c));
    FUN_007cc340(FUN_007ab7d0);
    FUN_007d2110(local_30[0x51],0);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

