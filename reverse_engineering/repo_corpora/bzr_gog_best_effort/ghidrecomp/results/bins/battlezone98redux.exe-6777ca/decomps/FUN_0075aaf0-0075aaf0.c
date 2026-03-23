
void FUN_0075aaf0(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar6;
  int iVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  undefined1 *puVar14;
  undefined4 uVar15;
  code *pcVar16;
  ushort uVar17;
  basic_ostream<char,struct_std::char_traits<char>_> local_6c0 [176];
  undefined1 auStack_610 [176];
  undefined1 auStack_560 [176];
  undefined1 auStack_4b0 [176];
  undefined1 auStack_400 [160];
  undefined1 local_360 [16];
  undefined1 local_350 [8];
  undefined1 local_348 [8];
  undefined1 local_340 [8];
  undefined1 local_338 [8];
  undefined1 local_330 [8];
  undefined1 local_328 [8];
  undefined1 local_320 [32];
  undefined1 local_300 [8];
  undefined1 local_2f8 [8];
  undefined1 local_2f0 [24];
  undefined1 local_2d8 [8];
  undefined1 local_2d0 [16];
  undefined1 local_2c0 [8];
  undefined1 local_2b8 [16];
  undefined1 local_2a8 [8];
  undefined1 local_2a0 [8];
  undefined1 local_298 [8];
  undefined1 local_290 [4];
  undefined1 local_28c [8];
  undefined1 local_284 [4];
  undefined1 local_280 [4];
  undefined1 local_27c [4];
  undefined1 local_278 [4];
  undefined1 local_274 [4];
  undefined8 local_270;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  uint local_248;
  uint local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  uint local_224;
  uint local_220;
  undefined4 local_21c;
  undefined4 local_218;
  undefined1 local_214 [4];
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined1 local_1fc [4];
  uint local_1f8;
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined1 local_1e4 [4];
  uint local_1e0;
  undefined8 local_1dc;
  undefined4 local_1d4;
  undefined8 local_1d0;
  uint local_1c8;
  undefined8 local_1c4;
  undefined4 local_1bc;
  undefined8 local_1b8;
  undefined4 local_1b0;
  undefined8 local_1ac;
  undefined4 local_1a4;
  undefined8 local_1a0;
  undefined8 local_198;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined1 *local_184;
  undefined1 *local_180;
  undefined1 *local_17c;
  undefined1 *local_178;
  ushort *local_174;
  ushort *local_170;
  ushort *local_16c;
  undefined1 local_165;
  ushort *local_164;
  undefined1 local_160 [4];
  ushort *local_15c;
  ushort *local_158;
  uint local_154;
  int local_150;
  undefined1 local_14c [8];
  undefined1 local_144 [4];
  int local_140;
  undefined1 local_13c [32];
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
  puStack_c = &LAB_0085cb04;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_0042d8c0(local_13c);
  FID_conflict_begin(local_1fc);
  FUN_006c9bd0(local_14c,uVar2);
  do {
    cVar1 = FUN_00420f10(local_1fc);
    if (cVar1 == '\0') {
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    iVar3 = FUN_0042da60(local_14c);
    cVar1 = FUN_0075f610(iVar3 + 0x20);
    if (cVar1 != '\0') {
      puVar4 = (undefined4 *)FUN_0042da60();
      local_188 = *puVar4;
      switch(local_188) {
      case 0:
        FUN_006b29f0(2);
        iVar3 = FUN_0042da60();
        *(undefined4 *)(iVar3 + 0x20) = local_250;
        *(undefined4 *)(iVar3 + 0x24) = local_24c;
        break;
      case 1:
        iVar3 = FUN_0042da60();
        local_158 = (ushort *)(iVar3 + 0x1c);
        local_224 = (uint)*local_158;
        *local_158 = *local_158 - 1;
        if (local_224 == 0) {
          FUN_00574400(3,1);
          local_8 = 0;
          if (&stack0x00000000 == (undefined1 *)0x410) {
            local_17c = (undefined1 *)0x0;
          }
          else {
            local_17c = auStack_400;
          }
          iVar3 = FUN_0042da60();
          FUN_006da360(local_17c,iVar3 + 0x44);
          local_210 = GetPolicy(local_d4);
          local_8._0_1_ = 1;
          puVar14 = local_74;
          local_200 = local_210;
          FUN_0042da60(puVar14);
          local_218 = FUN_0073a9f0(puVar14);
          local_8._0_1_ = 2;
          local_208 = local_218;
          uVar8 = FUN_0041f870();
          uVar8 = FUN_0041f870(uVar8);
          FUN_007d6a70("BZRNet P2P Starting WAN Connect For Client %s (IP %s)\n",uVar8);
          local_8._0_1_ = 1;
          ~basic_string<>();
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          iVar3 = FUN_0042da60();
          *(undefined2 *)(iVar3 + 0x1c) = 0x1e;
          puVar4 = (undefined4 *)FUN_0042da60();
          *puVar4 = 3;
          local_8 = 0xffffffff;
          FUN_00417f10();
        }
        else {
          FUN_006cb470();
          puVar14 = local_160;
          FUN_0042da60(puVar14);
          FUN_00424640(puVar14);
          puVar14 = local_1e4;
          FUN_0042da60(puVar14);
          FID_conflict_begin(puVar14);
          FUN_006c9b60(local_2a0,&DAT_0260b068);
          uVar9 = FUN_006c9a10();
          local_1a0 = uVar9;
          while( true ) {
            cVar1 = FUN_00420f10(local_1e4);
            if (cVar1 == '\0') break;
            iVar3 = FUN_0042da60(local_140 + 0x38);
            iVar3 = FUN_0042da60(*(undefined4 *)(iVar3 + 0x84));
            uVar8 = FUN_004237d0(local_1a0,3,*(undefined4 *)(iVar3 + 0x88));
            iVar3 = get(uVar8);
            FUN_0075a710(iVar3 + 0xb8);
            FUN_00422190();
          }
          uVar8 = FUN_006b2a40(1);
          puVar4 = (undefined4 *)FUN_006c9b90(local_350,uVar8);
          uVar8 = *puVar4;
          uVar13 = puVar4[1];
          iVar3 = FUN_0042da60();
          *(undefined4 *)(iVar3 + 0x20) = uVar8;
          *(undefined4 *)(iVar3 + 0x24) = uVar13;
        }
        break;
      case 2:
        iVar3 = FUN_0042da60();
        local_15c = (ushort *)(iVar3 + 0x1c);
        local_220 = (uint)*local_15c;
        *local_15c = *local_15c - 1;
        if (local_220 == 0) {
          FUN_00574400(3,1);
          local_8 = 3;
          if (&stack0x00000000 == (undefined1 *)0x620) {
            local_180 = (undefined1 *)0x0;
          }
          else {
            local_180 = auStack_610;
          }
          iVar3 = FUN_0042da60();
          FUN_006da360(local_180,iVar3 + 0x44);
          local_238 = GetPolicy(local_2c);
          local_8._0_1_ = 4;
          puVar14 = local_a4;
          local_228 = local_238;
          FUN_0042da60(puVar14);
          local_240 = FUN_0073a9f0(puVar14);
          local_8._0_1_ = 5;
          local_230 = local_240;
          uVar8 = FUN_0041f870();
          uVar8 = FUN_0041f870(uVar8);
          FUN_007d6a70("BZRNet P2P Starting WAN Connect For Client %s (IP %s)\n",uVar8);
          local_8._0_1_ = 4;
          ~basic_string<>();
          local_8 = CONCAT31(local_8._1_3_,3);
          ~basic_string<>();
          iVar3 = FUN_0042da60();
          *(undefined2 *)(iVar3 + 0x1c) = 0x1e;
          puVar4 = (undefined4 *)FUN_0042da60();
          *puVar4 = 3;
          local_8 = 0xffffffff;
          FUN_00417f10();
        }
        else {
          FUN_006c9b60(local_2a8,&DAT_0260b068);
          uVar9 = FUN_006c9a10();
          local_1ac = uVar9;
          iVar3 = FUN_0042da60(local_140 + 0x38);
          iVar3 = FUN_0042da60(*(undefined4 *)(iVar3 + 0x84));
          iVar3 = FUN_0042da60(local_1ac,4,*(undefined4 *)(iVar3 + 0x88));
          iVar3 = get(iVar3 + 0x28);
          FUN_0075a710(iVar3 + 0xb8);
          uVar8 = FUN_006b2a40(1);
          puVar4 = (undefined4 *)FUN_006c9b90(local_2c0,uVar8);
          uVar8 = *puVar4;
          uVar13 = puVar4[1];
          iVar3 = FUN_0042da60();
          *(undefined4 *)(iVar3 + 0x20) = uVar8;
          *(undefined4 *)(iVar3 + 0x24) = uVar13;
        }
        break;
      case 3:
        iVar3 = FUN_0042da60();
        local_164 = (ushort *)(iVar3 + 0x1c);
        local_248 = (uint)*local_164;
        *local_164 = *local_164 - 1;
        if (local_248 == 0) {
          puVar14 = local_44;
          FUN_0042da60(puVar14);
          local_21c = FUN_0073a9f0(puVar14);
          local_8 = 6;
          local_1a4 = local_21c;
          uVar8 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P FAILED WAN Connect For Client %s, ATTEMPTING RELAY\n",uVar8);
          local_8 = 0xffffffff;
          ~basic_string<>();
          uVar8 = FUN_0042de50();
          FUN_0075aa90(uVar8);
        }
        else {
          FUN_006c9b60(local_2d0,&DAT_0260b068);
          uVar9 = FUN_006c9a10();
          local_1b8 = uVar9;
          iVar3 = FUN_0042da60(local_140 + 0x38);
          iVar3 = FUN_0042da60(*(undefined4 *)(iVar3 + 0x84));
          iVar3 = FUN_0042da60(local_1b8,3,*(undefined4 *)(iVar3 + 0x88));
          iVar3 = get(iVar3 + 0x44);
          FUN_0075a710(iVar3 + 0xb8);
          uVar8 = FUN_006b2a40(1);
          puVar4 = (undefined4 *)FUN_006c9b90(local_2f0,uVar8);
          uVar8 = *puVar4;
          uVar13 = puVar4[1];
          iVar3 = FUN_0042da60();
          *(undefined4 *)(iVar3 + 0x20) = uVar8;
          *(undefined4 *)(iVar3 + 0x24) = uVar13;
        }
        break;
      case 4:
        iVar3 = FUN_0042da60();
        local_16c = (ushort *)(iVar3 + 0x1c);
        local_1f8 = (uint)*local_16c;
        *local_16c = *local_16c - 1;
        if (local_1f8 == 0) {
          puVar14 = local_5c;
          FUN_0042da60(puVar14);
          local_204 = FUN_0073a9f0(puVar14);
          local_8 = 7;
          local_1b0 = local_204;
          uVar8 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P FAILED WAN Connect For Client %s, ATTEMPTING RELAY\n",uVar8);
          local_8 = 0xffffffff;
          ~basic_string<>();
          uVar8 = FUN_0042de50();
          FUN_0075aa90(uVar8);
        }
        else {
          FUN_006c9b60(local_300,&DAT_0260b068);
          uVar9 = FUN_006c9a10();
          local_1c4 = uVar9;
          iVar3 = FUN_0042da60(local_140 + 0x38);
          iVar3 = FUN_0042da60(*(undefined4 *)(iVar3 + 0x84));
          iVar3 = FUN_0042da60(local_1c4,4,*(undefined4 *)(iVar3 + 0x88));
          iVar3 = get(iVar3 + 0x28);
          FUN_0075a710(iVar3 + 0xb8);
          uVar8 = FUN_006b2a40(1);
          puVar4 = (undefined4 *)FUN_006c9b90(local_320,uVar8);
          uVar8 = *puVar4;
          uVar13 = puVar4[1];
          iVar3 = FUN_0042da60();
          *(undefined4 *)(iVar3 + 0x20) = uVar8;
          *(undefined4 *)(iVar3 + 0x24) = uVar13;
        }
        break;
      case 6:
        iVar3 = FUN_0042da60();
        local_174 = (ushort *)(iVar3 + 0x1c);
        local_244 = (uint)*local_174;
        *local_174 = *local_174 - 1;
        if (local_244 == 0) {
          puVar14 = local_8c;
          FUN_0042da60(puVar14);
          local_20c = FUN_0073a9f0(puVar14);
          local_8 = 8;
          local_1bc = local_20c;
          uVar8 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P FAILED RELAY Connect For Client %s\n",uVar8);
          local_8 = 0xffffffff;
          ~basic_string<>();
          iVar3 = FUN_0042da60();
          *(undefined2 *)(iVar3 + 0x1c) = 0;
          FUN_006b29f0(2);
          iVar3 = FUN_0042da60();
          *(undefined4 *)(iVar3 + 0x20) = local_258;
          *(undefined4 *)(iVar3 + 0x24) = local_254;
          puVar4 = (undefined4 *)FUN_0042da60();
          *puVar4 = 0;
        }
        else {
          FUN_006c9b60(local_330,&DAT_0260b068);
          uVar9 = FUN_006c9a10();
          local_1d0 = uVar9;
          iVar3 = FUN_0042da60(local_140 + 0x38);
          iVar3 = FUN_0042da60(*(undefined4 *)(iVar3 + 0x84));
          iVar3 = FUN_0042da60(local_1d0,3,*(undefined4 *)(iVar3 + 0x88));
          iVar3 = get(iVar3 + 0x60);
          FUN_0075a710(iVar3 + 0xb8);
          uVar8 = FUN_006b2a40(1);
          puVar4 = (undefined4 *)FUN_006c9b90(local_2b8,uVar8);
          uVar8 = *puVar4;
          uVar13 = puVar4[1];
          iVar3 = FUN_0042da60();
          *(undefined4 *)(iVar3 + 0x20) = uVar8;
          *(undefined4 *)(iVar3 + 0x24) = uVar13;
        }
        break;
      case 7:
        iVar3 = FUN_0042da60();
        local_170 = (ushort *)(iVar3 + 0x1c);
        local_1c8 = (uint)*local_170;
        *local_170 = *local_170 - 1;
        if (local_1c8 == 0) {
          puVar14 = local_bc;
          FUN_0042da60(puVar14);
          local_22c = FUN_0073a9f0(puVar14);
          local_8 = 9;
          local_1d4 = local_22c;
          uVar8 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P FAILED RELAY Connect For Client %s\n",uVar8);
          local_8 = 0xffffffff;
          ~basic_string<>();
          iVar3 = FUN_0042da60();
          *(undefined2 *)(iVar3 + 0x1c) = 0;
          FUN_006b29f0(2);
          iVar3 = FUN_0042da60();
          *(undefined4 *)(iVar3 + 0x20) = local_260;
          *(undefined4 *)(iVar3 + 0x24) = local_25c;
          puVar4 = (undefined4 *)FUN_0042da60();
          *puVar4 = 0;
        }
        else {
          FUN_006c9b60(local_340,&DAT_0260b068);
          uVar9 = FUN_006c9a10();
          local_1dc = uVar9;
          iVar3 = FUN_0042da60(local_140 + 0x38);
          iVar3 = FUN_0042da60(*(undefined4 *)(iVar3 + 0x84));
          iVar3 = FUN_0042da60(local_1dc,4,*(undefined4 *)(iVar3 + 0x88));
          iVar3 = get(iVar3 + 0x60);
          FUN_0075a710(iVar3 + 0xb8);
          uVar8 = FUN_006b2a40(1);
          puVar4 = (undefined4 *)FUN_006c9b90(local_328,uVar8);
          uVar8 = *puVar4;
          uVar13 = puVar4[1];
          iVar3 = FUN_0042da60();
          *(undefined4 *)(iVar3 + 0x20) = uVar8;
          *(undefined4 *)(iVar3 + 0x24) = uVar13;
        }
        break;
      case 8:
        iVar3 = FUN_0042da60();
        if (*(char *)(iVar3 + 0x19) != '\0') {
          FUN_0042da60();
          cVar1 = FUN_0042d8f0();
          if (cVar1 == '\0') {
            iVar3 = FUN_0042da60();
            *(undefined1 *)(iVar3 + 0x1a) = 1;
            local_150 = 0;
            uVar2 = FUN_00416410();
            local_1e0 = (uint)(5000 / (ulonglong)uVar2);
            FUN_006c9bd0(&local_190);
            get();
            FUN_006c9b60(local_2d8,&DAT_0260b068);
            uVar9 = FUN_006c9a10();
            puVar14 = local_144;
            local_270 = uVar9;
            FUN_0042da60(puVar14);
            FUN_0042d8c0(puVar14);
            puVar14 = local_214;
            FUN_0042da60(puVar14);
            FID_conflict_begin(puVar14);
            while( true ) {
              cVar1 = FUN_00420f10(local_214);
              if (cVar1 == '\0') break;
              FUN_0042da60();
              iVar3 = FUN_004bb390();
              if ((local_1e0 <= (uint)(iVar3 + local_150)) && (local_150 != 0)) break;
              FUN_0042da60();
              iVar3 = FUN_004bb390();
              local_150 = iVar3 + local_150;
              iVar3 = FUN_0042da60();
              *(undefined4 *)(iVar3 + 8) = local_190;
              *(undefined4 *)(iVar3 + 0xc) = local_18c;
              uVar8 = 2;
              puVar14 = local_284;
              puVar12 = local_278;
              FUN_0042da60(puVar12,puVar14,2,0,0);
              FID_conflict_begin(puVar12);
              puVar4 = (undefined4 *)FID_conflict_operator_(puVar14,uVar8);
              FUN_00760670(&local_270,*puVar4);
              uVar15 = 4;
              puVar14 = local_280;
              uVar13 = 8;
              puVar12 = local_274;
              uVar8 = 2;
              puVar11 = local_27c;
              puVar10 = local_290;
              FUN_0042da60(puVar10,puVar11,2,puVar12,8,puVar14,4,0,0);
              FID_conflict_begin(puVar10);
              FID_conflict_operator_(puVar11,uVar8);
              FID_conflict_operator_(puVar12,uVar13);
              puVar4 = (undefined4 *)FID_conflict_operator_(puVar14,uVar15);
              iVar3 = FUN_0042da60(*puVar4);
              FUN_007606d0(iVar3 + 0x84);
              if (DAT_008eda28 != 0) {
                FUN_00574400(3,1);
                local_8 = 10;
                local_154 = 0;
                while( true ) {
                  FUN_0042da60();
                  uVar2 = FUN_004bb390();
                  if (uVar2 <= local_154) break;
                  uVar2 = local_154;
                  FUN_0042da60(local_154);
                  pbVar5 = (byte *)FUN_006cf0f0(uVar2);
                  uVar17 = (ushort)*pbVar5;
                  uVar8 = std::setw(CONCAT44(2,local_360));
                  pcVar16 = FUN_006ab840;
                  uVar8 = FUN_006dc270(&local_165,0x30,FUN_006ab840,uVar8);
                  pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                                     (local_6c0,FUN_00574a10);
                  pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                           FUN_006dc290(pbVar6,uVar8);
                  pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                                     (pbVar6,pcVar16);
                  pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                           FUN_006db8a0(pbVar6);
                  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar17)
                  ;
                  local_154 = local_154 + 1;
                }
                FUN_00574400(3,1);
                local_8._0_1_ = 0xb;
                if (&stack0x00000000 == (undefined1 *)0x4c0) {
                  local_178 = (undefined1 *)0x0;
                }
                else {
                  local_178 = auStack_4b0;
                }
                iVar3 = FUN_0042da60();
                FUN_006da360(local_178,iVar3 + 0x28);
                local_23c = GetPolicy(local_11c);
                local_8._0_1_ = 0xc;
                local_1ec = local_23c;
                local_1f0 = GetPolicy(local_ec);
                local_8._0_1_ = 0xd;
                local_1e8 = local_1f0;
                uVar8 = FUN_0041f870();
                uVar8 = FUN_0041f870(uVar8);
                iVar3 = FUN_0042da60(uVar8);
                puVar4 = (undefined4 *)FUN_0042da60(*(undefined4 *)(iVar3 + 0x84));
                FUN_007d6a70("BZRNet P2P TRY Sent Packet (%u,%u) to %s: %s\n",*puVar4);
                local_8._0_1_ = 0xc;
                ~basic_string<>();
                local_8._0_1_ = 0xb;
                ~basic_string<>();
                local_8 = CONCAT31(local_8._1_3_,10);
                FUN_00417f10();
                local_8 = 0xffffffff;
                FUN_00417f10();
              }
              FUN_004fbb60();
              puVar14 = local_28c;
              uVar13 = 0;
              iVar3 = FUN_0042da60(0,puVar14);
              iVar3 = iVar3 + 0x28;
              iVar7 = FUN_0042da60(iVar3);
              uVar8 = FUN_00760590(local_348,iVar7 + 0x10);
              get(uVar8);
              FUN_006dc2e0(uVar8,iVar3,uVar13,puVar14);
              iVar3 = FUN_0042da60();
              *(undefined1 *)(iVar3 + 0x18) = 0;
              FUN_0042da80();
            }
            if (DAT_008eda28 != 0) {
              FUN_00574400(3,1);
              local_8 = 0xe;
              if (&stack0x00000000 == (undefined1 *)0x570) {
                local_184 = (undefined1 *)0x0;
              }
              else {
                local_184 = auStack_560;
              }
              iVar3 = FUN_0042da60();
              FUN_006da360(local_184,iVar3 + 0x28);
              local_234 = GetPolicy(local_104);
              local_8._0_1_ = 0xf;
              local_1f4 = local_234;
              uVar8 = FUN_0041f870();
              FUN_007d6a70("BZRNet P2P TRY Sent %u to %s\n",local_150,uVar8);
              local_8 = CONCAT31(local_8._1_3_,0xe);
              ~basic_string<>();
              local_8 = 0xffffffff;
              FUN_00417f10();
            }
            iVar3 = FUN_0042da60();
            *(undefined1 *)(iVar3 + 0x19) = 0;
            uVar8 = FUN_0075fe50(0x9c4,0);
            puVar4 = (undefined4 *)FUN_006c9b90(local_338,uVar8);
            uVar8 = *puVar4;
            uVar13 = puVar4[1];
            iVar3 = FUN_0042da60();
            *(undefined4 *)(iVar3 + 0x20) = uVar8;
            *(undefined4 *)(iVar3 + 0x24) = uVar13;
            break;
          }
        }
        iVar3 = FUN_0042da60();
        *(undefined1 *)(iVar3 + 0x1a) = 0;
        FUN_006b29f0(2);
        iVar3 = FUN_0042da60();
        *(undefined4 *)(iVar3 + 0x20) = local_268;
        *(undefined4 *)(iVar3 + 0x24) = local_264;
      }
    }
    iVar3 = FUN_0042da60();
    if (*(char *)(iVar3 + 0x18) != '\0') {
      FUN_006c9bd0(local_298);
      get();
      FUN_006c9b60(local_2f8,&DAT_0260b068);
      uVar9 = FUN_006c9a10();
      local_198 = uVar9;
      iVar3 = FUN_0042da60();
      iVar3 = FUN_0042da60(*(undefined4 *)(iVar3 + 0x84));
      iVar3 = FUN_0042da60(local_198,7,*(undefined4 *)(iVar3 + 0x88));
      iVar3 = get(iVar3 + 0x28);
      FUN_0075a490(iVar3 + 0xb8);
      iVar3 = FUN_0042da60();
      *(undefined1 *)(iVar3 + 0x18) = 0;
    }
    FUN_0042da80();
  } while( true );
}

