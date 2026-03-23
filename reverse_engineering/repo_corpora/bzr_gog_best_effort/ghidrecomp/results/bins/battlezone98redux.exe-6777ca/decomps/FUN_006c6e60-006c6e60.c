
/* WARNING: Removing unreachable block (ram,0x006c72e5) */
/* WARNING: Removing unreachable block (ram,0x006c7324) */

void __thiscall FUN_006c6e60(int param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  ushort uVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  undefined4 *puVar5;
  int iVar6;
  code *pcVar7;
  undefined1 *puVar8;
  ushort uVar9;
  undefined *puVar10;
  undefined4 uVar11;
  basic_ostream<char,struct_std::char_traits<char>_> local_a9c [176];
  undefined1 auStack_9ec [176];
  undefined1 auStack_93c [176];
  undefined1 auStack_88c [176];
  undefined1 auStack_7dc [176];
  undefined1 auStack_72c [176];
  undefined1 auStack_67c [160];
  undefined1 local_5dc [16];
  undefined1 local_5cc [8];
  undefined1 local_5c4 [8];
  undefined1 local_5bc [8];
  undefined1 local_5b4 [8];
  undefined1 local_5ac [36];
  undefined1 local_588 [4];
  undefined1 local_584 [8];
  undefined1 local_57c [4];
  undefined1 local_578 [4];
  undefined1 local_574 [8];
  undefined4 local_56c;
  undefined4 local_568;
  undefined4 local_564;
  undefined4 local_560;
  undefined4 local_55c;
  undefined4 local_558;
  undefined4 local_554;
  undefined4 local_550;
  undefined4 local_54c;
  undefined4 local_548;
  undefined4 local_544;
  undefined4 local_540;
  undefined4 local_53c;
  undefined4 local_538;
  undefined4 local_534;
  undefined4 local_530;
  undefined4 local_52c;
  undefined4 local_528;
  undefined1 local_524 [4];
  undefined4 local_520;
  undefined8 local_51c;
  undefined4 local_514;
  undefined4 local_510;
  undefined4 local_50c;
  undefined4 local_508;
  undefined4 local_504;
  undefined4 local_500;
  undefined4 local_4fc;
  undefined1 local_4f8 [4];
  undefined4 local_4f4;
  undefined4 local_4f0;
  undefined4 local_4ec;
  undefined4 local_4e8;
  undefined4 local_4e4;
  undefined4 local_4e0;
  undefined4 local_4dc;
  undefined4 local_4d8;
  undefined4 local_4d4;
  undefined4 local_4d0;
  undefined4 local_4cc;
  int local_4c8;
  int local_4c4;
  undefined4 local_4c0;
  undefined4 local_4bc;
  undefined4 local_4b8;
  undefined4 local_4b4;
  char *local_4b0;
  undefined4 local_4ac;
  undefined4 local_4a8;
  undefined4 local_4a4;
  undefined1 local_4a0 [16];
  undefined1 *local_490;
  undefined4 local_48c;
  undefined1 *local_488;
  undefined1 local_484 [8];
  undefined1 *local_47c;
  undefined4 local_478;
  undefined4 local_474;
  undefined1 *local_470;
  undefined1 *local_46c;
  int local_468;
  undefined1 *local_464;
  undefined1 local_460 [4];
  undefined2 local_45c;
  undefined1 local_455;
  uint local_454;
  int local_450;
  uint local_44c;
  undefined8 local_448;
  ushort local_440 [2];
  uint local_43c;
  byte local_435;
  undefined1 local_434;
  char local_433;
  char local_432;
  undefined1 local_431;
  undefined4 local_430;
  char local_42a;
  char local_429;
  int local_428;
  undefined1 local_424 [28];
  undefined1 local_408 [48];
  undefined1 local_3d8 [48];
  undefined1 local_3a8 [24];
  undefined1 local_390 [48];
  undefined1 local_360 [24];
  undefined1 local_348 [72];
  undefined1 local_300 [48];
  undefined1 local_2d0 [24];
  undefined1 local_2b8 [48];
  undefined1 local_288 [48];
  undefined1 local_258 [48];
  undefined1 local_228 [24];
  SchedulingNode local_210 [32];
  undefined1 local_1f0 [24];
  undefined1 local_1d8 [24];
  undefined1 local_1c0 [24];
  undefined1 local_1a8 [24];
  undefined1 local_190 [24];
  undefined1 local_178 [24];
  undefined1 local_160 [24];
  undefined1 local_148 [24];
  undefined1 local_130 [24];
  undefined1 local_118 [24];
  undefined1 local_100 [24];
  undefined1 local_e8 [24];
  undefined1 local_d0 [16];
  undefined1 local_c0 [24];
  undefined1 local_a8 [24];
  undefined1 local_90 [24];
  undefined1 local_78 [24];
  undefined1 local_60 [24];
  undefined1 local_48 [24];
  undefined1 local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852642;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_428 = param_1;
  local_448 = CONCAT44(local_448._4_4_,(undefined4)local_448);
  local_51c = CONCAT44(local_51c._4_4_,(undefined4)local_51c);
  if ((param_3 < 0x12) ||
     (local_448 = CONCAT44(local_448._4_4_,(undefined4)local_448),
     local_51c = CONCAT44(local_51c._4_4_,(undefined4)local_51c), 0x800 < param_3))
  goto LAB_006c83d3;
  cVar1 = FUN_006ab7d0(local_14);
  local_448 = CONCAT44(local_448._4_4_,(undefined4)local_448);
  local_51c = CONCAT44(local_51c._4_4_,(undefined4)local_51c);
  if (cVar1 == '\0') goto LAB_006c83d3;
  local_434 = (*(byte *)(local_428 + 0x344) & 0x80) != 0;
  local_433 = (*(byte *)(local_428 + 0x344) & 0x40) != 0;
  local_435 = *(byte *)(local_428 + 0x345) & 0xf;
  local_431 = local_433;
  local_429 = local_434;
  if ((!(bool)local_434) &&
     (local_448 = CONCAT44(local_448._4_4_,(undefined4)local_448),
     local_51c = CONCAT44(local_51c._4_4_,(undefined4)local_51c), !(bool)local_433))
  goto LAB_006c83d3;
  puVar10 = &DAT_0260b068;
  puVar8 = local_5b4;
  FUN_006c9bd0(local_5ac,puVar8,&DAT_0260b068);
  FUN_006c9b60(puVar8,puVar10);
  local_448 = FUN_006c9a10();
  FUN_006dc3e0(&local_454,local_428 + 0x346,0,0);
  FUN_006dc460(&local_468,local_428 + 0x34e,0,0);
  FUN_006dc460(&local_4d0,local_428 + 0x352,0,0);
  if ((2 < DAT_008eda28) || ((1 < DAT_008eda28 && ((local_468 == 0 || (local_429 != '\0')))))) {
    local_48c = 0;
    local_478 = 0;
    if (*(int *)(local_428 + 0xc3c) != 0) {
      FUN_0075f550(&local_48c,&local_478);
    }
    FUN_00574400(3,1);
    local_8 = 0;
    FUN_00574400(3,1);
    local_8 = CONCAT31(local_8._1_3_,1);
    if (&stack0x00000000 == (undefined1 *)0x89c) {
      local_464 = (undefined1 *)0x0;
    }
    else {
      local_464 = auStack_88c;
    }
    FUN_006da360(local_464,local_428 + 0xc18);
    for (local_44c = 0; local_44c < param_3; local_44c = local_44c + 1) {
      uVar9 = (ushort)*(byte *)(local_428 + local_44c + 0x344);
      uVar3 = std::setw(CONCAT44(2,local_5dc));
      pcVar7 = FUN_006ab840;
      uVar3 = FUN_006dc270(&local_455,0x30,FUN_006ab840,uVar3);
      pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                         (local_a9c,FUN_00574a10);
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006dc290(pbVar4,uVar3);
      pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar7);
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar4);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar9);
    }
    local_560 = GetPolicy(local_288);
    local_8._0_1_ = 2;
    local_544 = local_560;
    local_4bc = GetPolicy(local_228);
    local_8._0_1_ = 3;
    local_4b4 = local_4bc;
    uVar3 = FUN_0041f870();
    uVar3 = FUN_0041f870(local_454,local_450,local_448,local_448 - CONCAT44(local_450,local_454),
                         uVar3);
    FUN_007d6a70("BZRNet P2P Received Packet (%u,%u) expecting (%u,%u) from %s sent at %llu, received at %llu, diff %lld: %s\n"
                 ,local_468,local_4d0,local_48c,local_478,uVar3);
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  cVar1 = operator==<>(local_428 + 0x328,local_428 + 0xc18);
  if (cVar1 == '\0') {
    local_51c = CONCAT44(local_51c._4_4_,(undefined4)local_51c);
    if (*(int *)(local_428 + 0xc3c) != 0) {
      FUN_0075d800(local_448,param_3,param_4);
      local_51c = CONCAT44(local_51c._4_4_,(undefined4)local_51c);
    }
    goto LAB_006c83d3;
  }
  local_51c = local_448 + 60000;
  if (local_51c < CONCAT44(local_450,local_454)) goto LAB_006c83d3;
  local_4c8 = local_454 + 60000;
  local_4c4 = local_450 + (uint)(0xffff159f < local_454);
  if ((((CONCAT44(local_4c4,local_4c8) < local_448) || (local_433 == '\0')) || (local_435 != 2)) ||
     (local_429 != '\0')) goto LAB_006c83d3;
  FUN_006b3160();
  local_43c = (uint)*(byte *)(local_428 + 0x356);
  if (param_3 != local_43c + 0x15) {
    FUN_007d6b70("BZRNet P2P Network Server IP Data Error, received invalid IP data\n");
    goto LAB_006c83d3;
  }
  if (local_43c == 4) {
    puVar5 = (undefined4 *)FUN_006ca020(local_588);
    FUN_006dc4c0(local_578,local_428 + 0x357,local_428 + 0x357 + local_43c,*puVar5);
    uVar3 = FUN_006b2de0(local_524);
    FUN_006b3210(uVar3);
  }
  else {
    if ((local_43c != 0x10) || (param_3 != 0x24)) {
      FUN_007d6b70("BZRNet P2P Network Server IP Data Error, received invalid IP data\n");
      goto LAB_006c83d3;
    }
    puVar5 = (undefined4 *)FUN_006ca020(local_57c);
    FUN_006dc4c0(local_584,local_428 + 0x357,local_428 + 0x357 + local_43c,*puVar5);
    uVar3 = FUN_006b2f30(local_d0,0);
    FUN_006b3270(uVar3);
  }
  FUN_006dc510(local_440,local_428 + 0x357 + local_43c,0,0);
  uVar3 = FUN_006cac80(local_424);
  cVar1 = operator!=<>(local_30,uVar3);
  uVar9 = local_440[0];
  if (cVar1 == '\0') {
    uVar2 = FUN_006cac60();
    if (uVar9 != uVar2) goto LAB_006c7520;
    local_474 = 0;
  }
  else {
LAB_006c7520:
    local_474 = 1;
  }
  local_432 = (char)local_474;
  FUN_006cb500(local_30);
  FUN_006cb4e0(local_440[0]);
  FUN_004fbb60();
  FUN_006cb3e0(local_408,local_574);
  local_45c = FUN_006cac60();
  iVar6 = FUN_00667170();
  if (iVar6 == 0) {
    FUN_006cc0e0();
    local_8 = 4;
    basic_string<>("content");
    local_8._0_1_ = 5;
    uVar3 = FUN_006cc0e0();
    local_8._0_1_ = 6;
    local_54c = uVar3;
    local_4d8 = uVar3;
    FUN_006cc100(local_178);
    uVar3 = FUN_006dc0c0(uVar3);
    local_430 = FUN_006db8f0(uVar3);
    local_8._0_1_ = 5;
    FUN_006c3d30();
    local_8._0_1_ = 4;
    ~basic_string<>();
    basic_string<>(&DAT_00897b9c);
    local_8._0_1_ = 7;
    puVar8 = local_348;
    FUN_007647a0(puVar8);
    FUN_00583e30();
    uVar3 = FUN_0073a9f0(puVar8);
    local_8._0_1_ = 8;
    local_52c = uVar3;
    local_4e0 = uVar3;
    FUN_006cc100(local_100);
    FUN_006dc070(uVar3);
    local_8._0_1_ = 7;
    ~basic_string<>();
    local_8._0_1_ = 4;
    ~basic_string<>();
    FUN_00574400(3,1);
    local_8._0_1_ = 9;
    if (&stack0x00000000 == (undefined1 *)0x9fc) {
      local_47c = (undefined1 *)0x0;
    }
    else {
      local_47c = auStack_9ec;
    }
    FUN_006da360(local_47c,local_428 + 0xb44);
    basic_string<>("wanAddress");
    local_8._0_1_ = 10;
    uVar3 = GetPolicy(local_2b8);
    local_8._0_1_ = 0xb;
    local_55c = uVar3;
    local_4e8 = uVar3;
    FUN_006cc100(local_1d8);
    FUN_006dc070(uVar3);
    local_8._0_1_ = 10;
    ~basic_string<>();
    local_8._0_1_ = 9;
    ~basic_string<>();
    local_8._0_1_ = 4;
    FUN_00417f10();
    local_42a = 0;
    basic_string<>("lanAddresses");
    local_8._0_1_ = 0xc;
    uVar3 = FUN_006cc690();
    local_8._0_1_ = 0xd;
    local_534 = uVar3;
    local_4f0 = uVar3;
    FUN_006cc100(local_48);
    uVar3 = FUN_006dc570(uVar3);
    local_53c = FUN_006db970(uVar3);
    local_8._0_1_ = 0xc;
    FUN_006cc6b0();
    local_8._0_1_ = 4;
    ~basic_string<>();
    FUN_00818cf0(local_484,local_45c,1,0);
    local_8 = CONCAT31(local_8._1_3_,0xe);
    local_42a = operator!=<>(local_428 + 0xb60,local_484);
    FUN_006cc0c0(local_484);
    FUN_00424640(local_460);
    FID_conflict_begin(local_4f8);
    while( true ) {
      cVar1 = FUN_00420f10(local_4f8);
      if (cVar1 == '\0') break;
      FUN_00574400(3,1);
      local_8._0_1_ = 0xf;
      if (&stack0x00000000 == (undefined1 *)0x94c) {
        local_488 = (undefined1 *)0x0;
      }
      else {
        local_488 = auStack_93c;
      }
      uVar3 = FUN_004237d0();
      FUN_006da360(local_488,uVar3);
      local_554 = GetPolicy(local_3a8);
      local_8._0_1_ = 0x10;
      local_500 = local_554;
      FUN_006dbff0(local_554,0,0);
      local_8._0_1_ = 0x11;
      FUN_006cc750(local_210);
      local_8._0_1_ = 0x10;
      Concurrency::details::SchedulingNode::~SchedulingNode(local_210);
      local_8._0_1_ = 0xf;
      ~basic_string<>();
      FUN_00422190();
      local_8 = CONCAT31(local_8._1_3_,0xe);
      FUN_00417f10();
    }
    local_8._0_1_ = 4;
    FUN_0045c7d0();
    if (*(int *)(local_428 + 4) == 1) {
      *(undefined4 *)(local_428 + 4) = 2;
      FUN_00574400(3,1);
      local_8._0_1_ = 0x12;
      basic_string<>(&DAT_0087d178);
      local_8._0_1_ = 0x13;
      uVar3 = basic_string<>("Authorization");
      local_8._0_1_ = 0x14;
      local_568 = uVar3;
      local_508 = uVar3;
      FUN_006cc100(local_60);
      FUN_006dc070(uVar3);
      local_8._0_1_ = 0x13;
      ~basic_string<>();
      local_8._0_1_ = 0x12;
      ~basic_string<>();
      basic_string<>("inLounge");
      local_8._0_1_ = 0x15;
      iVar6 = local_428 + 0xc34;
      FUN_006cc100(local_78);
      FUN_006dc140(iVar6);
      local_8._0_1_ = 0x12;
      ~basic_string<>();
      basic_string<>("apiVer");
      local_8._0_1_ = 0x16;
      uVar3 = basic_string<>(&DAT_008985a0);
      local_8._0_1_ = 0x17;
      local_4ac = uVar3;
      local_4a8 = uVar3;
      FUN_006cc100(local_130);
      FUN_006dc070(uVar3);
      local_8._0_1_ = 0x16;
      ~basic_string<>();
      local_8._0_1_ = 0x12;
      ~basic_string<>();
      local_4b0 = "2.2.301";
      basic_string<>("clientVersion");
      local_8._0_1_ = 0x18;
      uVar3 = basic_string<>(local_4b0);
      local_8._0_1_ = 0x19;
      local_4c0 = uVar3;
      local_4b8 = uVar3;
      FUN_006cc100(local_1a8);
      FUN_006dc070(uVar3);
      local_8._0_1_ = 0x18;
      ~basic_string<>();
      local_8._0_1_ = 0x12;
      ~basic_string<>();
      if (*(char *)(local_428 + 0x2e8) == '\0') {
        basic_string<>("authtype");
        local_8._0_1_ = 0x1e;
        uVar3 = basic_string<>(&DAT_008985e8);
        local_8._0_1_ = 0x1f;
        local_4e4 = uVar3;
        local_4dc = uVar3;
        FUN_006cc100(local_160);
        FUN_006dc070(uVar3);
        local_8._0_1_ = 0x1e;
        ~basic_string<>();
        local_8._0_1_ = 0x12;
        ~basic_string<>();
        basic_string<>("realname");
        local_8._0_1_ = 0x20;
        iVar6 = local_428 + 0x304;
        FUN_006cc100(local_190);
        FUN_006dc0a0(iVar6);
        local_8 = CONCAT31(local_8._1_3_,0x12);
        ~basic_string<>();
      }
      else {
        basic_string<>("authtype");
        local_8._0_1_ = 0x1a;
        uVar3 = basic_string<>("steam");
        local_8._0_1_ = 0x1b;
        local_4d4 = uVar3;
        local_4cc = uVar3;
        FUN_006cc100(local_c0);
        FUN_006dc070(uVar3);
        local_8._0_1_ = 0x1a;
        ~basic_string<>();
        local_8._0_1_ = 0x12;
        ~basic_string<>();
        basic_string<>("steamAppTicket");
        local_8._0_1_ = 0x1c;
        iVar6 = local_428 + 0x2ec;
        FUN_006cc100(local_e8);
        FUN_006dc0a0(iVar6);
        local_8._0_1_ = 0x12;
        ~basic_string<>();
        basic_string<>("realname");
        local_8._0_1_ = 0x1d;
        iVar6 = local_428 + 0x304;
        FUN_006cc100(local_118);
        FUN_006dc0a0(iVar6);
        local_8 = CONCAT31(local_8._1_3_,0x12);
        ~basic_string<>();
      }
      if (DAT_009453e0 == '\0') {
        basic_string<>("realname");
        local_8._0_1_ = 0x23;
        basic_string<>(&DAT_00879d2c);
        local_8._0_1_ = 0x24;
        uVar3 = FUN_006cc100(local_148);
        FUN_006cc100(local_1f0);
        FUN_006cc460(uVar3);
        local_8._0_1_ = 0x23;
        ~basic_string<>();
        local_8 = CONCAT31(local_8._1_3_,0x12);
        ~basic_string<>();
      }
      else {
        basic_string<>(&DAT_00879d2c);
        local_8._0_1_ = 0x21;
        uVar3 = basic_string<>(&DAT_009453e0);
        local_8._0_1_ = 0x22;
        local_4f4 = uVar3;
        local_4ec = uVar3;
        FUN_006cc100(local_1c0);
        FUN_006dc070(uVar3);
        local_8._0_1_ = 0x21;
        ~basic_string<>();
        local_8 = CONCAT31(local_8._1_3_,0x12);
        ~basic_string<>();
      }
      if (&stack0x00000000 == (undefined1 *)0x68c) {
        local_490 = (undefined1 *)0x0;
      }
      else {
        local_490 = auStack_67c;
      }
      FUN_007d7970(local_490,local_4a0,0,2);
      if (2 < DAT_008eda28) {
        local_504 = GetPolicy(local_2d0);
        local_8._0_1_ = 0x25;
        pcVar7 = FUN_004bc8c0;
        local_4fc = local_504;
        FUN_0081e820("WebSocket Message Sent:\n",local_504);
        uVar3 = FUN_0081e660();
        uVar3 = FUN_004bc590(uVar3);
        pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar3);
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar7);
        local_8 = CONCAT31(local_8._1_3_,0x12);
        ~basic_string<>();
      }
      uVar3 = GetPolicy(local_300);
      local_8._0_1_ = 0x26;
      uVar11 = 1;
      puVar8 = local_5cc;
      local_514 = uVar3;
      local_50c = uVar3;
      FUN_00421ec0(puVar8,uVar3,1);
      FUN_006da6b0(puVar8,uVar3,uVar11);
      local_8._0_1_ = 0x12;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,4);
      FUN_00417f10();
    }
    else if (*(int *)(local_428 + 0xc3c) != 0) {
      cVar1 = FUN_0073a900();
      if (cVar1 != '\0') {
        if (local_42a != '\0') {
          FUN_00574400(3,1);
          local_8._0_1_ = 0x27;
          basic_string<>(&DAT_0087d178);
          local_8._0_1_ = 0x28;
          uVar3 = basic_string<>("DoUpdateLAN");
          local_8._0_1_ = 0x29;
          local_528 = uVar3;
          local_520 = uVar3;
          FUN_006cc100(local_a8);
          FUN_006dc070(uVar3);
          local_8._0_1_ = 0x28;
          ~basic_string<>();
          local_8._0_1_ = 0x27;
          ~basic_string<>();
          if (&stack0x00000000 == (undefined1 *)0x73c) {
            local_470 = (undefined1 *)0x0;
          }
          else {
            local_470 = auStack_72c;
          }
          FUN_007d7970(local_470,local_4a0,0,2);
          if (2 < DAT_008eda28) {
            local_538 = GetPolicy(local_360);
            local_8._0_1_ = 0x2a;
            pcVar7 = FUN_004bc8c0;
            local_530 = local_538;
            FUN_0081e820("WebSocket Message Sent:\n",local_538);
            uVar3 = FUN_0081e660();
            uVar3 = FUN_004bc590(uVar3);
            pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar3);
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar7);
            local_8._0_1_ = 0x27;
            ~basic_string<>();
          }
          uVar3 = GetPolicy(local_390);
          local_8._0_1_ = 0x2b;
          uVar11 = 1;
          puVar8 = local_5c4;
          local_548 = uVar3;
          local_540 = uVar3;
          FUN_00421ec0(puVar8,uVar3,1);
          FUN_006da6b0(puVar8,uVar3,uVar11);
          local_8._0_1_ = 0x27;
          ~basic_string<>();
          local_8._0_1_ = 4;
          FUN_00417f10();
        }
        if (local_432 != '\0') {
          FUN_00574400(3,1);
          local_8._0_1_ = 0x2c;
          basic_string<>(&DAT_0087d178);
          local_8._0_1_ = 0x2d;
          uVar3 = basic_string<>("DoUpdateWAN");
          local_8._0_1_ = 0x2e;
          local_558 = uVar3;
          local_550 = uVar3;
          FUN_006cc100(local_90);
          FUN_006dc070(uVar3);
          local_8._0_1_ = 0x2d;
          ~basic_string<>();
          local_8._0_1_ = 0x2c;
          ~basic_string<>();
          if (&stack0x00000000 == (undefined1 *)0x7ec) {
            local_46c = (undefined1 *)0x0;
          }
          else {
            local_46c = auStack_7dc;
          }
          FUN_007d7970(local_46c,local_4a0,0,2);
          if (2 < DAT_008eda28) {
            local_56c = GetPolicy(local_3d8);
            local_8._0_1_ = 0x2f;
            pcVar7 = FUN_004bc8c0;
            local_564 = local_56c;
            FUN_0081e820("WebSocket Message Sent:\n",local_56c);
            uVar3 = FUN_0081e660();
            uVar3 = FUN_004bc590(uVar3);
            pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar3);
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar7);
            local_8._0_1_ = 0x2c;
            ~basic_string<>();
          }
          uVar3 = GetPolicy(local_258);
          local_8._0_1_ = 0x30;
          uVar11 = 1;
          puVar8 = local_5bc;
          local_510 = uVar3;
          local_4a4 = uVar3;
          FUN_00421ec0(puVar8,uVar3,1);
          FUN_006da6b0(puVar8,uVar3,uVar11);
          local_8._0_1_ = 0x2c;
          ~basic_string<>();
          local_8._0_1_ = 4;
          FUN_00417f10();
        }
        if ((local_432 != '\0') || (local_42a != '\0')) {
          FUN_0075ca90(*(int *)(local_428 + 0xc3c) + 0x48);
        }
      }
    }
    local_8 = 0xffffffff;
    FUN_006c3d30();
  }
  else {
    FUN_007d6b70("BZRNet P2P Network Server IP Data Error, no local endpoint\n");
  }
LAB_006c83d3:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

