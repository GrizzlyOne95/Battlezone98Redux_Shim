
void FUN_007bc1e0(undefined4 param_1,char param_2)

{
  char cVar1;
  undefined4 *puVar2;
  allocator<char> *paVar3;
  code *local_1b4;
  code *local_1ac;
  int *piStack_1a8;
  undefined1 local_198 [20];
  undefined1 local_184 [8];
  undefined1 local_17c [4];
  undefined1 local_178 [4];
  undefined1 *local_174;
  undefined1 *local_170;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_13c;
  undefined4 local_138;
  code *local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  int *local_11c;
  int *local_118;
  void *local_10c;
  void *local_108;
  int *local_104;
  undefined4 local_100;
  void *local_fc;
  float local_f8;
  code *local_f4;
  undefined4 local_f0;
  void *local_ec;
  undefined4 local_e8;
  float local_e4;
  int *local_e0;
  code *local_dc;
  void *local_d8;
  void *local_d4;
  undefined4 local_d0;
  void *local_cc;
  void *local_c8;
  undefined4 local_c4;
  float local_c0;
  undefined4 local_bc;
  float local_b8;
  int local_b4;
  undefined1 *local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  undefined4 local_a0;
  float local_9c;
  int *local_98;
  int *local_94;
  undefined4 *local_90;
  undefined1 local_8c [48];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008619af;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0();
  local_8 = 0;
  *local_90 = cUI_SaveLoadEdit::vftable;
  local_90[0x54] = 0;
  DAT_009455d8 = local_90;
  local_ec = operator_new(0x144);
  local_8._0_1_ = 1;
  if (local_ec == (void *)0x0) {
    local_e8 = 0;
  }
  else {
    piStack_1a8 = (int *)0x60;
    local_1ac = (code *)0x44870000;
    local_1b4 = (code *)0x0;
    local_e8 = FUN_007d1cc0("Middle_Overlay",0);
  }
  local_130 = local_e8;
  local_8._0_1_ = 0;
  local_90[0x51] = local_e8;
  FUN_007d3f20();
  piStack_1a8 = (int *)0x7bc327;
  FUN_007d2110();
  local_fc = operator_new(0x930);
  local_8._0_1_ = 2;
  if (local_fc == (void *)0x0) {
    local_104 = (int *)0x0;
  }
  else {
    piStack_1a8 = (int *)0x9020;
    local_1ac = (code *)0x42a00000;
    local_1b4 = (code *)0x42c80000;
    local_104 = (int *)FUN_007cc390("prompt",0);
  }
  local_118 = local_104;
  local_8 = (uint)local_8._1_3_ << 8;
  local_98 = local_104;
  FUN_007cc6b0();
  if (param_2 == '\0') {
    (**(code **)(*local_98 + 0x3c))();
  }
  else {
    (**(code **)(*local_98 + 0x3c))();
  }
  piStack_1a8 = local_98;
  local_1ac = (code *)0x7bc44b;
  FUN_007d2110();
  local_a4 = 50.0;
  local_a8 = 230.0;
  local_ac = 400.0;
  local_9c = 440.0;
  piStack_1a8 = (int *)0x7bc496;
  local_10c = operator_new(0x144);
  local_8._0_1_ = 3;
  if (local_10c == (void *)0x0) {
    local_100 = 0;
  }
  else {
    piStack_1a8 = (int *)local_90[0x51];
    local_1ac = (code *)0x20;
    local_1b4 = (code *)(local_ac + 40.0);
    local_100 = FUN_007d1cc0("Mission_List_Files",local_a4,local_a8);
  }
  local_144 = local_100;
  local_8._0_1_ = 0;
  local_bc = local_100;
  piStack_1a8 = (int *)0x7bc55f;
  FUN_007d2870();
  piStack_1a8 = (int *)local_bc;
  local_1ac = (code *)0x7bc579;
  FUN_007d2110();
  piStack_1a8 = (int *)0x7bc584;
  local_108 = operator_new(0x180);
  local_8._0_1_ = 4;
  if (local_108 == (void *)0x0) {
    local_c4 = 0;
  }
  else {
    piStack_1a8 = (int *)0xff00ff00;
    local_1ac = (code *)local_90[0x51];
    local_1b4 = FUN_007bc040;
    local_c4 = FUN_007c9de0("Mission_List",local_a4 + 30.0,local_a8 + 50.0,local_ac,local_9c,
                            FUN_007bc030);
  }
  local_14c = local_c4;
  local_8._0_1_ = 0;
  local_90[0x52] = local_c4;
  DAT_009455d4 = local_90[0x52];
  piStack_1a8 = (int *)0x7bc67d;
  FUN_007cb3e0();
  piStack_1a8 = (int *)local_90[0x52];
  local_1ac = (code *)0x7bc69d;
  FUN_007d2110();
  piStack_1a8 = &DAT_02cf3000;
  local_1ac = (code *)0x7bc6ac;
  FUN_00426a60();
  local_8._0_1_ = 5;
  vector<>();
  local_8._0_1_ = 6;
  piStack_1a8 = (int *)local_178;
  local_1ac = (code *)0x7bc6d2;
  FUN_006dd0e0();
  local_174 = (undefined1 *)&local_1ac;
  local_168 = FUN_00667590();
  local_8._0_1_ = 7;
  local_170 = (undefined1 *)&local_1b4;
  local_154 = local_168;
  local_164 = FUN_007bbca0(local_5c);
  local_8._0_1_ = 6;
  FUN_007bd7a0(local_184);
  local_b0 = (undefined1 *)0x0;
  FUN_00422260();
  local_8 = CONCAT31(local_8._1_3_,8);
  piStack_1a8 = (int *)0x7bc756;
  puVar2 = (undefined4 *)FID_conflict_begin();
  local_a0 = *puVar2;
  do {
    piStack_1a8 = (int *)0x7bc77d;
    FID_conflict_end();
    piStack_1a8 = (int *)0x7bc789;
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') {
      piStack_1a8 = (int *)0x7bc9a5;
      local_cc = operator_new(0x1ec);
      local_8._0_1_ = 0xe;
      if (local_cc == (void *)0x0) {
        local_f0 = 0;
      }
      else {
        piStack_1a8 = (int *)0x0;
        local_1ac = (code *)local_90[0x51];
        local_1b4 = (code *)0x42980000;
        local_f0 = FUN_007c2480("loadBtn",local_a4 + local_ac + 80.0,local_9c / 2.0 + local_a8,
                                0x435c0000);
      }
      local_150 = local_f0;
      local_8 = CONCAT31(local_8._1_3_,8);
      local_90[0x53] = local_f0;
      piStack_1a8 = (int *)0x7bca99;
      FUN_007d3f20();
      piStack_1a8 = (int *)0x7bcaaf;
      FUN_007d2870();
      piStack_1a8 = (int *)0x7bcad3;
      (**(code **)(*(int *)local_90[0x53] + 0x40))();
      piStack_1a8 = (int *)0x89f288;
      local_1ac = (code *)0x7bcaf7;
      (**(code **)(*(int *)local_90[0x53] + 0x3c))();
      if (param_2 == '\0') {
        local_1ac = (code *)&DAT_0087d1e8;
        FUN_007c2950();
      }
      else {
        local_1ac = (code *)&DAT_0087d2a8;
        FUN_007c2950();
      }
      local_1ac = FUN_007bbe50;
      FUN_007c23e0();
      local_1ac = (code *)0x0;
      (**(code **)(*(int *)local_90[0x53] + 0x24))();
      local_1b4 = (code *)local_90[0x53];
      FUN_007d2110();
      local_c0 = local_a4 + local_ac + 80.0;
      local_b8 = (local_9c / 2.0 + local_a8) - 70.0;
      local_e4 = 300.0;
      local_f8 = 40.0;
      if (param_2 != '\0') {
        local_1b4 = (code *)0x7bcc03;
        local_d4 = operator_new(0x144);
        local_8._0_1_ = 0xf;
        if (local_d4 == (void *)0x0) {
          local_f4 = (code *)0x0;
        }
        else {
          local_1b4 = (code *)local_90[0x51];
          local_f4 = (code *)FUN_007d1cc0("input_background",local_c0,local_b8,local_e4 + 190.0,
                                          local_f8 + 20.0,0x20);
        }
        local_134 = local_f4;
        local_8._0_1_ = 8;
        local_dc = local_f4;
        local_1b4 = (code *)0x7bcccc;
        FUN_007d2870();
        local_1b4 = local_dc;
        FUN_007d2110();
        local_1b4 = (code *)0x7bccf1;
        local_c8 = operator_new(0x968);
        local_8._0_1_ = 0x10;
        if (local_c8 == (void *)0x0) {
          local_d0 = 0;
        }
        else {
          local_1b4 = (code *)0x8020;
          local_d0 = FUN_007cf410(0,1,0x24,"chatEntry",local_c0 + 10.0,local_b8 + 7.0,local_e4 / 2.0
                                  ,local_f8);
        }
        local_138 = local_d0;
        local_8 = CONCAT31(local_8._1_3_,8);
        local_90[0x54] = local_d0;
        local_1b4 = (code *)0x7bcdcd;
        FUN_007cf940();
        local_1b4 = (code *)local_90[0x54];
        FUN_007d2110();
      }
      local_1b4 = (code *)0x89d780;
      local_120 = FUN_0081cb40();
      local_1b4 = (code *)0x7bce10;
      local_d8 = operator_new(0x1ec);
      local_8._0_1_ = 0x11;
      if (local_d8 == (void *)0x0) {
        local_e0 = (int *)0x0;
      }
      else {
        local_1b4 = (code *)0x41e00000;
        local_e0 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0);
      }
      local_11c = local_e0;
      local_8._0_1_ = 8;
      local_94 = local_e0;
      local_1b4 = (code *)0x7bcecc;
      FUN_007d2870();
      local_1b4 = (code *)0x7bcee4;
      (**(code **)(*local_94 + 0x40))();
      local_1b4 = (code *)0x89d7e4;
      (**(code **)(*local_94 + 0x3c))();
      FUN_007c2950(local_120);
      FUN_007c23e0(FUN_007bbe40);
      FUN_007d2110(local_94,0);
      local_8._0_1_ = 6;
      FUN_0041eb50();
      local_8._0_1_ = 5;
      FUN_007bd0d0();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004180b0();
      local_8 = 0xffffffff;
      ExceptionList = local_10;
      local_1b4 = (code *)0x7bcf84;
      FUN_0083e885();
      return;
    }
    FUN_004fbb60();
    piStack_1a8 = (int *)0x7bc7b1;
    paVar3 = (allocator<char> *)FUN_00422220();
    piStack_1a8 = (int *)0x7bc7b8;
    piStack_1a8 = (int *)std::allocator<char>::allocator<char>(paVar3);
    local_1ac = (code *)0x7bc7be;
    cVar1 = FUN_00767a00();
    if (cVar1 == '\0') {
      piStack_1a8 = (int *)0x7bc7db;
      paVar3 = (allocator<char> *)FUN_00422220();
      piStack_1a8 = (int *)0x7bc7e2;
      std::allocator<char>::allocator<char>(paVar3);
      piStack_1a8 = (int *)0x7bc7e9;
      local_148 = FUN_008405e0();
      local_8._0_1_ = 9;
      piStack_1a8 = (int *)0x7bc80e;
      local_13c = local_148;
      FUN_00417fd0();
      local_8._0_1_ = 0xb;
      FUN_004180b0();
      local_128 = FUN_006ab6b0();
      local_8._0_1_ = 0xc;
      piStack_1a8 = (int *)local_2c;
      local_1ac = (code *)0x7bc84b;
      local_124 = local_128;
      FUN_00756750();
      local_8._0_1_ = 0xb;
      FUN_00417b50();
      piStack_1a8 = (int *)&DAT_008752b0;
      local_1ac = (code *)0x7bc871;
      local_b4 = FUN_0045e1a0();
      basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,0xd);
      if (local_b4 != -1) {
        piStack_1a8 = (int *)local_b4;
        local_1ac = (code *)local_8c;
        local_12c = FUN_0045e1d0();
        piStack_1a8 = (int *)0x7bc8c3;
        FUN_0045e0f0();
        ~basic_string<>();
      }
      piStack_1a8 = (int *)0x7bc8e0;
      FID_conflict_begin();
      piStack_1a8 = (int *)local_2c;
      local_1ac = (code *)local_17c;
      FUN_00421e00();
      piStack_1a8 = (int *)0x7bc8fe;
      cVar1 = FUN_004221b0();
      if (cVar1 != '\0') {
        piStack_1a8 = (int *)local_44;
        local_1ac = (code *)0x7bc913;
        cVar1 = FUN_00427270();
        if (cVar1 == '\0') {
          piStack_1a8 = (int *)local_44;
          local_1ac = (code *)0x7bc92b;
          cVar1 = FUN_00427270();
          if (cVar1 == '\0') goto LAB_007bc97d;
        }
        piStack_1a8 = (int *)local_198;
        local_1ac = (code *)0x7bc94b;
        FUN_004222f0();
        piStack_1a8 = (int *)local_b0;
        local_1ac = (code *)0x7bc95c;
        local_1ac = (code *)FUN_0041f870();
        FUN_007cabf0();
        local_b0 = local_b0 + 1;
      }
LAB_007bc97d:
      local_8._0_1_ = 0xb;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,8);
      ~basic_string<>();
    }
    FUN_007bd0f0();
  } while( true );
}

