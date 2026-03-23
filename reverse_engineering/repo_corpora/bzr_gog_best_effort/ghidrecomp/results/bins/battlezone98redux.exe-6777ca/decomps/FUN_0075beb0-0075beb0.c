
void __thiscall
FUN_0075beb0(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar6;
  int iVar7;
  int *piVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  code *pcVar13;
  undefined4 uVar14;
  ushort uVar15;
  undefined *puVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  basic_ostream<char,struct_std::char_traits<char>_> local_4bc [176];
  basic_ostream<char,struct_std::char_traits<char>_> local_40c [176];
  undefined1 auStack_35c [176];
  undefined1 auStack_2ac [192];
  undefined1 local_1ec [16];
  undefined1 local_1dc [16];
  undefined1 local_1cc [8];
  undefined1 local_1c4 [8];
  undefined1 local_1bc [8];
  undefined1 local_1b4 [8];
  undefined1 local_1ac [8];
  undefined1 local_1a4 [8];
  undefined1 local_19c [8];
  undefined1 local_194 [4];
  undefined1 local_190 [4];
  undefined1 local_18c [4];
  undefined1 local_188 [4];
  undefined1 local_184 [4];
  undefined1 local_180 [4];
  undefined1 local_17c [4];
  undefined1 local_178 [4];
  undefined1 local_174 [4];
  undefined1 local_170 [4];
  undefined1 local_16c [4];
  undefined1 local_168 [4];
  undefined1 local_164 [4];
  undefined1 local_160 [4];
  undefined1 local_15c [4];
  undefined1 local_158 [4];
  undefined1 local_154 [4];
  undefined1 local_150 [4];
  undefined1 local_14c [4];
  undefined1 local_148 [4];
  undefined1 local_144 [4];
  undefined1 local_140 [4];
  undefined1 local_13c [4];
  undefined1 local_138 [4];
  undefined1 local_134 [8];
  undefined1 local_12c [4];
  undefined1 local_128 [8];
  undefined1 local_120 [4];
  undefined1 local_11c [4];
  undefined1 local_118 [4];
  undefined1 local_114 [4];
  undefined1 local_110 [4];
  undefined1 local_10c [4];
  undefined1 local_108 [8];
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined1 local_e4 [4];
  undefined4 local_e0;
  undefined8 local_dc;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined1 local_cc [4];
  undefined1 *local_c8;
  byte *local_c4;
  undefined4 local_c0;
  undefined1 *local_bc;
  byte *local_b8;
  byte *local_b4;
  undefined1 local_ae;
  undefined1 local_ad;
  int local_ac;
  undefined1 local_a8 [12];
  uint local_9c;
  undefined1 local_98 [4];
  uint local_94;
  int local_90;
  char local_8a;
  undefined1 local_89;
  undefined4 local_88;
  undefined1 local_82;
  undefined1 local_81;
  int *local_80;
  int *local_7c;
  char local_75;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cb92;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_88 = param_1;
  local_14 = uVar2;
  if (param_4 != 0) {
    local_75 = '\x01';
    local_7c = (int *)0x0;
    FUN_00578c20(local_cc,param_2);
    uVar3 = FID_conflict_begin(local_154);
    cVar1 = FUN_004221b0(uVar3);
    if (cVar1 == '\0') {
      iVar7 = FUN_00422150(uVar2);
      local_7c = *(int **)(iVar7 + 0x10);
    }
    else {
      FUN_0075eea0(param_2,0);
      FUN_0042d8c0(local_98);
      FID_conflict_begin(local_e4);
      while (cVar1 = FUN_00420f10(local_e4), cVar1 != '\0') {
        uVar3 = param_2;
        FUN_0042da60(param_2);
        cVar1 = FUN_0056f780(uVar3);
        if (cVar1 != '\0') {
          local_7c = (int *)FUN_0042de50();
          local_75 = '\0';
          break;
        }
        FUN_0042da80();
      }
      if (local_7c == (int *)0x0) goto LAB_0075ca1d;
    }
    get();
    puVar16 = &DAT_0260b068;
    puVar12 = local_19c;
    FUN_006c9bd0(local_1c4,puVar12,&DAT_0260b068);
    FUN_006c9b60(puVar12,puVar16);
    local_dc = FUN_006c9a10();
    if (param_5 == 0) {
      vector<>();
      local_8 = 0;
      FUN_0075f640(param_4 + 0x12);
      local_b8 = (byte *)FUN_006cf0f0(0);
      *local_b8 = *local_b8 | 0x40;
      uVar17 = 0;
      uVar14 = 0;
      uVar3 = 2;
      puVar12 = local_114;
      FID_conflict_begin(local_11c);
      puVar4 = (undefined4 *)FID_conflict_operator_(puVar12,uVar3);
      FUN_00760670(&local_dc,*puVar4,uVar14,uVar17);
      uVar18 = 0;
      uVar17 = 0;
      uVar14 = 8;
      puVar12 = local_17c;
      uVar3 = 2;
      puVar11 = local_184;
      FID_conflict_begin(local_18c);
      FID_conflict_operator_(puVar11,uVar3);
      puVar4 = (undefined4 *)FID_conflict_operator_(puVar12,uVar14);
      FUN_007606d0(local_7c + 0x22,*puVar4,uVar17,uVar18);
      uVar19 = 0;
      uVar18 = 0;
      uVar17 = 4;
      puVar12 = local_194;
      uVar14 = 8;
      puVar11 = local_140;
      uVar3 = 2;
      puVar9 = local_14c;
      FID_conflict_begin(local_118);
      FID_conflict_operator_(puVar9,uVar3);
      FID_conflict_operator_(puVar11,uVar14);
      puVar4 = (undefined4 *)FID_conflict_operator_(puVar12,uVar17);
      FUN_007606d0(local_7c + 0x21,*puVar4,uVar18,uVar19);
      uVar18 = 4;
      puVar12 = local_10c;
      uVar17 = 4;
      puVar11 = local_120;
      uVar14 = 8;
      puVar9 = local_15c;
      uVar3 = 2;
      puVar10 = local_12c;
      FID_conflict_begin(local_164);
      FID_conflict_operator_(puVar10,uVar3);
      FID_conflict_operator_(puVar9,uVar14);
      FID_conflict_operator_(puVar11,uVar17);
      puVar4 = (undefined4 *)FID_conflict_operator_(puVar12,uVar18);
      FUN_00760730(local_138,param_3,param_3 + param_4,*puVar4);
      FUN_004fbb60();
      if (*local_7c == 8) {
        if (local_75 != '\0') {
          if (2 < DAT_008eda28) {
            FUN_00574400(3,1);
            local_8._0_1_ = 1;
            local_9c = 0;
            while( true ) {
              uVar2 = FUN_004bb390();
              if (uVar2 <= local_9c) break;
              pbVar5 = (byte *)FUN_006cf0f0(local_9c);
              uVar15 = (ushort)*pbVar5;
              uVar3 = std::setw(CONCAT44(2,local_1dc));
              pcVar13 = FUN_006ab840;
              uVar3 = FUN_006dc270(&local_ae,0x30,FUN_006ab840,uVar3);
              pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                                 (local_40c,FUN_00574a10);
              pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                       FUN_006dc290(pbVar6,uVar3);
              pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                                 (pbVar6,pcVar13);
              pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar6);
              std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar15);
              local_9c = local_9c + 1;
            }
            FUN_00574400(3,1);
            local_8._0_1_ = 2;
            if (&stack0x00000000 == (undefined1 *)0x2bc) {
              local_bc = (undefined1 *)0x0;
            }
            else {
              local_bc = auStack_2ac;
            }
            FUN_006da360(local_bc,local_7c + 10);
            local_f8 = GetPolicy(local_2c);
            local_8._0_1_ = 3;
            local_d4 = local_f8;
            local_100 = GetPolicy(local_5c);
            local_8._0_1_ = 4;
            local_f0 = local_100;
            uVar3 = FUN_0041f870();
            uVar3 = FUN_0041f870(uVar3);
            FUN_007d6a70("BZRNet P2P UNR Sent Packet (%u,%u) to %s: %s\n",local_7c[0x22],
                         local_7c[0x21],uVar3);
            local_8._0_1_ = 3;
            ~basic_string<>();
            local_8._0_1_ = 2;
            ~basic_string<>();
            local_8._0_1_ = 1;
            FUN_00417f10();
            local_8 = (uint)local_8._1_3_ << 8;
            FUN_00417f10();
          }
          puVar12 = local_128;
          uVar14 = 0;
          piVar8 = local_7c + 10;
          uVar3 = FUN_00760590(local_1bc,local_a8,piVar8,0,puVar12);
          get(uVar3);
          iVar7 = FUN_006dc2e0(uVar3,piVar8,uVar14,puVar12);
          local_81 = iVar7 != 0;
          local_75 = local_81;
        }
        local_8a = local_75;
        local_8 = 0xffffffff;
        FUN_00579000();
      }
      else {
        local_89 = 0;
        local_8 = 0xffffffff;
        FUN_00579000();
      }
    }
    else {
      local_90 = param_4;
      while (local_90 != 0) {
        local_ac = local_90;
        if (0x5aa < local_90) {
          local_ac = 0x5aa;
        }
        local_90 = local_90 - local_ac;
        local_fc = FUN_0075ca40();
        local_8 = 5;
        local_f4 = local_fc;
        FUN_0075f980(local_fc);
        local_8 = 0xffffffff;
        FUN_0075ca70();
        local_80 = (int *)FUN_0045e220();
        *local_80 = local_7c[0x22];
        piVar8 = (int *)FUN_006c9bd0(local_1cc);
        iVar7 = piVar8[1];
        local_80[2] = *piVar8;
        local_80[3] = iVar7;
        FUN_0075f640(param_4 + 0x12);
        local_c4 = (byte *)FUN_006cf0f0(0);
        *local_c4 = *local_c4 | 0x80;
        if (local_90 == 0) {
          local_b4 = (byte *)FUN_006cf0f0(0);
          *local_b4 = *local_b4 | 0x40;
        }
        uVar17 = 0;
        uVar14 = 0;
        uVar3 = 2;
        puVar12 = local_16c;
        FID_conflict_begin(local_174);
        puVar4 = (undefined4 *)FID_conflict_operator_(puVar12,uVar3);
        FUN_00760670(&local_dc,*puVar4,uVar14,uVar17);
        uVar18 = 0;
        uVar17 = 0;
        uVar14 = 8;
        puVar12 = local_180;
        uVar3 = 2;
        puVar11 = local_148;
        FID_conflict_begin(local_170);
        FID_conflict_operator_(puVar11,uVar3);
        puVar4 = (undefined4 *)FID_conflict_operator_(puVar12,uVar14);
        FUN_007606d0(local_7c + 0x22,*puVar4,uVar17,uVar18);
        uVar19 = 0;
        uVar18 = 0;
        uVar17 = 4;
        puVar12 = local_150;
        uVar14 = 8;
        puVar11 = local_190;
        uVar3 = 2;
        puVar9 = local_158;
        FID_conflict_begin(local_178);
        FID_conflict_operator_(puVar9,uVar3);
        FID_conflict_operator_(puVar11,uVar14);
        puVar4 = (undefined4 *)FID_conflict_operator_(puVar12,uVar17);
        FUN_007606d0(local_7c + 0x21,*puVar4,uVar18,uVar19);
        uVar18 = 4;
        puVar12 = local_160;
        uVar17 = 4;
        puVar11 = local_188;
        uVar14 = 8;
        puVar9 = local_168;
        uVar3 = 2;
        puVar10 = local_13c;
        FID_conflict_begin(local_144);
        FID_conflict_operator_(puVar10,uVar3);
        FID_conflict_operator_(puVar9,uVar14);
        FID_conflict_operator_(puVar11,uVar17);
        puVar4 = (undefined4 *)FID_conflict_operator_(puVar12,uVar18);
        FUN_00760730(local_110,param_3,param_3 + param_4,*puVar4);
        FUN_004fbb60();
        if ((*local_7c == 8) && (*(char *)((int)local_7c + 0x1a) == '\0')) {
          if (local_75 != '\0') {
            if (1 < DAT_008eda28) {
              FUN_00574400(3,1);
              local_8 = 6;
              local_94 = 0;
              while( true ) {
                uVar2 = FUN_004bb390();
                if (uVar2 <= local_94) break;
                pbVar5 = (byte *)FUN_006cf0f0(local_94);
                uVar15 = (ushort)*pbVar5;
                uVar3 = std::setw(CONCAT44(2,local_1ec));
                pcVar13 = FUN_006ab840;
                uVar3 = FUN_006dc270(&local_ad,0x30,FUN_006ab840,uVar3);
                pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                                   (local_4bc,FUN_00574a10);
                pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                         FUN_006dc290(pbVar6,uVar3);
                pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                                   (pbVar6,pcVar13);
                pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar6);
                std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar15);
                local_94 = local_94 + 1;
              }
              FUN_00574400(3,1);
              local_8._0_1_ = 7;
              if (&stack0x00000000 == (undefined1 *)0x36c) {
                local_c8 = (undefined1 *)0x0;
              }
              else {
                local_c8 = auStack_35c;
              }
              FUN_006da360(local_c8,local_7c + 10);
              local_e8 = GetPolicy(local_74);
              local_8._0_1_ = 8;
              local_e0 = local_e8;
              local_ec = GetPolicy(local_44);
              local_8._0_1_ = 9;
              local_d0 = local_ec;
              uVar3 = FUN_0041f870();
              uVar3 = FUN_0041f870(uVar3);
              FUN_007d6a70("BZRNet P2P REL Sent Packet (%u,%u) to %s: %s\n",local_7c[0x22],
                           local_7c[0x21],uVar3);
              local_8._0_1_ = 8;
              ~basic_string<>();
              local_8._0_1_ = 7;
              ~basic_string<>();
              local_8 = CONCAT31(local_8._1_3_,6);
              FUN_00417f10();
              local_8 = 0xffffffff;
              FUN_00417f10();
            }
            puVar12 = local_134;
            uVar14 = 0;
            piVar8 = local_7c + 10;
            uVar3 = FUN_00760590(local_1a4,local_80 + 4,piVar8,0,puVar12);
            get(uVar3);
            iVar7 = FUN_006dc2e0(uVar3,piVar8,uVar14,puVar12);
            local_82 = iVar7 != 0;
            local_75 = local_82;
          }
        }
        else {
          local_75 = '\0';
        }
        local_7c[0x22] = local_7c[0x22] + 1;
      }
      local_c0 = FUN_0045e220();
      FUN_0075fe50(1000,0);
      uVar3 = FUN_006c9b90(local_1b4,local_108);
      cVar1 = FUN_0075f5f0(local_7c + 8,uVar3);
      if (cVar1 != '\0') {
        *(undefined1 *)((int)local_7c + 0x19) = 0;
        piVar8 = (int *)FUN_006c9b90(local_1ac,local_108);
        iVar7 = piVar8[1];
        local_7c[8] = *piVar8;
        local_7c[9] = iVar7;
      }
    }
  }
LAB_0075ca1d:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

