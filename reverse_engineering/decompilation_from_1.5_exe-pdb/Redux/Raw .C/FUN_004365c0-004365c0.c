
void FUN_004365c0(int *param_1,char param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined *local_5c0;
  undefined *local_5bc;
  undefined *local_5b8;
  undefined1 local_5b4 [24];
  undefined1 local_59c [24];
  undefined1 local_584 [24];
  undefined1 local_56c [24];
  undefined1 local_554 [24];
  undefined1 local_53c [24];
  undefined1 local_524 [24];
  undefined1 local_50c [24];
  undefined1 local_4f4 [24];
  undefined1 local_4dc [24];
  undefined1 local_4c4 [24];
  undefined1 local_4ac [24];
  undefined1 local_494 [24];
  undefined1 local_47c [24];
  undefined1 local_464 [24];
  undefined1 local_44c [24];
  undefined1 local_434 [24];
  undefined1 local_41c [24];
  undefined1 local_404 [24];
  undefined1 local_3ec [24];
  undefined1 local_3d4 [24];
  undefined1 local_3bc [24];
  undefined1 local_3a4 [24];
  undefined1 local_38c [24];
  undefined1 local_374 [24];
  undefined1 local_35c [24];
  undefined1 local_344 [24];
  undefined1 local_32c [24];
  undefined1 local_314 [24];
  undefined1 local_2fc [24];
  undefined1 local_2e4 [24];
  undefined1 local_2cc [24];
  undefined1 local_2b4 [24];
  undefined1 local_29c [24];
  undefined1 local_284 [24];
  undefined1 local_26c [24];
  undefined1 local_254 [24];
  undefined1 local_23c [24];
  undefined1 local_224 [24];
  undefined1 local_20c [24];
  undefined1 local_1f4 [24];
  undefined1 local_1dc [24];
  undefined1 local_1c4 [24];
  undefined1 local_1ac [24];
  undefined1 local_194 [24];
  undefined1 local_17c [24];
  undefined1 local_164 [24];
  undefined1 local_14c [24];
  undefined1 local_134 [24];
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845e58;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = (**(code **)(*param_1 + 4))("Direct3D9 Rendering Subsystem",local_14);
  cVar1 = FUN_00427270(uVar2);
  if (cVar1 == '\0') {
    uVar2 = (**(code **)(*param_1 + 4))("Direct3D11 Rendering Subsystem");
    cVar1 = FUN_00427270(uVar2);
    if (cVar1 == '\0') {
      uVar2 = (**(code **)(*param_1 + 4))("OpenGL Rendering Subsystem");
      cVar1 = FUN_00427270(uVar2);
      if (cVar1 != '\0') {
        (**(code **)(*param_1 + 0xc))();
        basic_string<>(&DAT_00873f58);
        local_8 = 0x2a;
        basic_string<>("Colour Depth");
        local_8._0_1_ = 0x2b;
        (**(code **)(*param_1 + 0x10))(local_29c,local_2cc);
        local_8 = CONCAT31(local_8._1_3_,0x2a);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        basic_string<>(&DAT_00873c74);
        local_8 = 0x2c;
        basic_string<>(&DAT_00873e08);
        local_8._0_1_ = 0x2d;
        (**(code **)(*param_1 + 0x10))(local_2fc,local_32c);
        local_8 = CONCAT31(local_8._1_3_,0x2c);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        basic_string<>(&DAT_00873e10);
        local_8 = 0x2e;
        basic_string<>("Fixed Pipeline Enabled");
        local_8._0_1_ = 0x2f;
        (**(code **)(*param_1 + 0x10))(local_35c,local_38c);
        local_8 = CONCAT31(local_8._1_3_,0x2e);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        if (param_2 == '\0') {
          local_5c0 = &DAT_00873de0;
        }
        else {
          local_5c0 = &DAT_00873e10;
        }
        basic_string<>(local_5c0);
        local_8 = 0x30;
        basic_string<>("Full Screen");
        local_8._0_1_ = 0x31;
        (**(code **)(*param_1 + 0x10))(local_3bc,local_3ec);
        local_8 = CONCAT31(local_8._1_3_,0x30);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        basic_string<>("Video Mode");
        local_8 = 0x32;
        uVar2 = FUN_006662a0(local_584,param_1);
        local_8._0_1_ = 0x33;
        (**(code **)(*param_1 + 0x10))(local_41c,uVar2);
        local_8 = CONCAT31(local_8._1_3_,0x32);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        basic_string<>(&DAT_00873e10);
        local_8 = 0x34;
        basic_string<>("VSync");
        local_8._0_1_ = 0x35;
        (**(code **)(*param_1 + 0x10))(local_44c,local_47c);
        local_8 = CONCAT31(local_8._1_3_,0x34);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        basic_string<>(&DAT_00873ef0);
        local_8 = 0x36;
        basic_string<>("VSync Interval");
        local_8._0_1_ = 0x37;
        (**(code **)(*param_1 + 0x10))(local_4ac,local_4dc);
        local_8 = CONCAT31(local_8._1_3_,0x36);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        basic_string<>(&DAT_00873de0);
        local_8 = 0x38;
        basic_string<>("sRGB Gamma Conversion");
        local_8._0_1_ = 0x39;
        (**(code **)(*param_1 + 0x10))(local_50c,local_53c);
        local_8 = CONCAT31(local_8._1_3_,0x38);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        basic_string<>(&DAT_00873f6c);
        local_8 = 0x3a;
        basic_string<>("RTT Preferred Mode");
        local_8._0_1_ = 0x3b;
        (**(code **)(*param_1 + 0x10))(local_56c,local_74);
        local_8 = CONCAT31(local_8._1_3_,0x3a);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
    else {
      basic_string<>(&DAT_00873de0);
      local_8 = 0x1a;
      basic_string<>("Allow NVPerfHUD");
      local_8._0_1_ = 0x1b;
      (**(code **)(*param_1 + 0x10))(local_2b4,local_4c4);
      local_8 = CONCAT31(local_8._1_3_,0x1a);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      basic_string<>(&DAT_00873c74);
      local_8 = 0x1c;
      basic_string<>(&DAT_00873e08);
      local_8._0_1_ = 0x1d;
      (**(code **)(*param_1 + 0x10))(local_2e4,local_5c);
      local_8 = CONCAT31(local_8._1_3_,0x1c);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      basic_string<>("Consistent");
      local_8 = 0x1e;
      basic_string<>("Floating-point mode");
      local_8._0_1_ = 0x1f;
      (**(code **)(*param_1 + 0x10))(local_44,local_bc);
      local_8 = CONCAT31(local_8._1_3_,0x1e);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      if (param_2 == '\0') {
        local_5bc = &DAT_00873de0;
      }
      else {
        local_5bc = &DAT_00873e10;
      }
      basic_string<>(local_5bc);
      local_8 = 0x20;
      basic_string<>("Full Screen");
      local_8._0_1_ = 0x21;
      (**(code **)(*param_1 + 0x10))(local_ec,local_11c);
      local_8 = CONCAT31(local_8._1_3_,0x20);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      basic_string<>("Video Mode");
      local_8 = 0x22;
      uVar2 = FUN_006662a0(local_5b4,param_1);
      local_8._0_1_ = 0x23;
      (**(code **)(*param_1 + 0x10))(local_14c,uVar2);
      local_8 = CONCAT31(local_8._1_3_,0x22);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      basic_string<>(&DAT_00873e10);
      local_8 = 0x24;
      basic_string<>("VSync");
      local_8._0_1_ = 0x25;
      (**(code **)(*param_1 + 0x10))(local_17c,local_1ac);
      local_8 = CONCAT31(local_8._1_3_,0x24);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      basic_string<>(&DAT_00873ef0);
      local_8 = 0x26;
      basic_string<>("VSync Interval");
      local_8._0_1_ = 0x27;
      (**(code **)(*param_1 + 0x10))(local_1dc,local_20c);
      local_8 = CONCAT31(local_8._1_3_,0x26);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      basic_string<>(&DAT_00873de0);
      local_8 = 0x28;
      basic_string<>("sRGB Gamma Conversion");
      local_8._0_1_ = 0x29;
      (**(code **)(*param_1 + 0x10))(local_23c,local_26c);
      local_8 = CONCAT31(local_8._1_3_,0x28);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  else {
    basic_string<>(&DAT_00873de0);
    local_8 = 0;
    basic_string<>("Allow DirectX9Ex");
    local_8._0_1_ = 1;
    (**(code **)(*param_1 + 0x10))(local_8c,local_434);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>(&DAT_00873de0);
    local_8 = 2;
    basic_string<>("Allow NVPerfHUD");
    local_8._0_1_ = 3;
    (**(code **)(*param_1 + 0x10))(local_a4,local_314);
    local_8 = CONCAT31(local_8._1_3_,2);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>(&DAT_00873c74);
    local_8 = 4;
    basic_string<>(&DAT_00873e08);
    local_8._0_1_ = 5;
    (**(code **)(*param_1 + 0x10))(local_d4,local_524);
    local_8 = CONCAT31(local_8._1_3_,4);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>(&DAT_00873e10);
    local_8 = 6;
    basic_string<>("Fixed Pipeline Enabled");
    local_8._0_1_ = 7;
    (**(code **)(*param_1 + 0x10))(local_104,local_344);
    local_8 = CONCAT31(local_8._1_3_,6);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("Consistent");
    local_8 = 8;
    basic_string<>("Floating-point mode");
    local_8._0_1_ = 9;
    (**(code **)(*param_1 + 0x10))(local_134,local_464);
    local_8 = CONCAT31(local_8._1_3_,8);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    if (param_2 == '\0') {
      local_5b8 = &DAT_00873de0;
    }
    else {
      local_5b8 = &DAT_00873e10;
    }
    basic_string<>(local_5b8);
    local_8 = 10;
    basic_string<>("Full Screen");
    local_8._0_1_ = 0xb;
    (**(code **)(*param_1 + 0x10))(local_164,local_374);
    local_8 = CONCAT31(local_8._1_3_,10);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("Video Mode");
    local_8 = 0xc;
    uVar2 = FUN_006662a0(local_59c,param_1);
    local_8._0_1_ = 0xd;
    (**(code **)(*param_1 + 0x10))(local_194,uVar2);
    local_8 = CONCAT31(local_8._1_3_,0xc);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("Auto hardware buffers management");
    local_8 = 0xe;
    basic_string<>("Multi device memory hint");
    local_8._0_1_ = 0xf;
    (**(code **)(*param_1 + 0x10))(local_4f4,local_1c4);
    local_8 = CONCAT31(local_8._1_3_,0xe);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("Create on all devices");
    local_8 = 0x10;
    basic_string<>("Resource Creation Policy");
    local_8._0_1_ = 0x11;
    (**(code **)(*param_1 + 0x10))(local_3a4,local_1f4);
    local_8 = CONCAT31(local_8._1_3_,0x10);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>(&DAT_00873e10);
    local_8 = 0x12;
    basic_string<>("Use Multihead");
    local_8._0_1_ = 0x13;
    (**(code **)(*param_1 + 0x10))(local_494,local_224);
    local_8 = CONCAT31(local_8._1_3_,0x12);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>(&DAT_00873e10);
    local_8 = 0x14;
    basic_string<>("VSync");
    local_8._0_1_ = 0x15;
    (**(code **)(*param_1 + 0x10))(local_3d4,local_254);
    local_8 = CONCAT31(local_8._1_3_,0x14);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>(&DAT_00873ef0);
    local_8 = 0x16;
    basic_string<>("VSync Interval");
    local_8._0_1_ = 0x17;
    (**(code **)(*param_1 + 0x10))(local_554,local_284);
    local_8 = CONCAT31(local_8._1_3_,0x16);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>(&DAT_00873de0);
    local_8 = 0x18;
    basic_string<>("sRGB Gamma Conversion");
    local_8._0_1_ = 0x19;
    (**(code **)(*param_1 + 0x10))(local_404,local_2c);
    local_8 = CONCAT31(local_8._1_3_,0x18);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

