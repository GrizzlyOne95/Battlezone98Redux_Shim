
void FUN_0075d800(undefined4 param_1,undefined4 param_2,uint param_3,undefined1 *param_4)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  undefined1 auStack_380 [160];
  int local_2e0 [44];
  undefined1 local_230 [8];
  undefined1 local_228 [16];
  undefined1 local_218 [4];
  undefined1 local_214 [4];
  undefined1 local_210 [4];
  undefined1 local_20c [4];
  undefined1 local_208 [4];
  undefined1 local_204 [16];
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined1 local_1d8 [4];
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  uint *local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  uint *local_1bc;
  undefined4 local_1b8;
  undefined1 local_1b4 [4];
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  int local_198;
  int local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  int local_17c;
  uint local_178;
  char *local_174;
  uint local_170;
  char *local_16c;
  undefined1 local_168 [4];
  undefined1 *local_164;
  int local_160;
  undefined4 local_15c;
  char local_155;
  byte *local_154;
  undefined1 local_14e;
  undefined1 local_14d;
  undefined1 local_14c [4];
  undefined8 local_148;
  char local_13e;
  byte local_13d;
  int local_13c;
  int *local_138;
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
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cce9;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  iVar4 = get(uVar3);
  local_154 = (byte *)(iVar4 + 0x344);
  local_14d = (*local_154 & 0x80) != 0;
  local_155 = (*local_154 & 0x40) != 0;
  local_13d = *(byte *)(iVar4 + 0x345) & 0xf;
  local_14e = local_155;
  local_13e = local_14d;
  FUN_006dc460(&local_160,iVar4 + 0x34e,0,0);
  FUN_006dc460(&local_178,local_154 + 0xe,0,0);
  local_138 = (int *)0x0;
  FUN_006c9bd0(&local_198);
  get(uVar3);
  FUN_006c9b60(local_230,&DAT_0260b068);
  local_148 = FUN_006c9a10();
  iVar4 = get();
  FUN_0075fd00(local_168,iVar4 + 0xc18);
  uVar5 = FID_conflict_begin(local_218);
  cVar1 = FUN_00420f10(uVar5);
  if (cVar1 == '\0') {
    if (((local_13d != 3) && (local_13d != 4)) && (local_13d != 5)) {
      if (DAT_008eda28 != 0) {
        FUN_007d6a70("BZRNet P2P Dropping Packet (Not a connected client or a connection packet)\n")
        ;
      }
      goto switchD_0075df65_caseD_1;
    }
    if (param_3 < 0x15) {
      if (DAT_008eda28 != 0) {
        FUN_007d6a70("BZRNet P2P Dropping Packet (Packet Too Small for connecting)\n");
      }
      goto switchD_0075df65_caseD_1;
    }
    if (local_154[param_3 - 1] != 0) {
      if (DAT_008eda28 != 0) {
        FUN_007d6a70("BZRNet P2P Dropping Packet (Packet Not Null Terminated)\n");
      }
      goto switchD_0075df65_caseD_1;
    }
    FUN_0073a6b0();
    basic_string<>(local_154 + 0x12);
    local_8 = 1;
    FUN_004203f0(local_2c,3,1);
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
    FUN_0073ba90(local_2e0,local_228);
    bVar2 = std::ios_base::operator!((ios_base *)((int)local_2e0 + *(int *)(local_2e0[0] + 4)));
    if (!bVar2) {
      bVar2 = std::ios_base::eof((ios_base *)((int)local_2e0 + *(int *)(local_2e0[0] + 4)));
      if (bVar2) {
        FUN_0042d8c0(local_14c);
        FID_conflict_begin(local_1b4);
        while( true ) {
          cVar1 = FUN_00420f10(local_1b4);
          if (cVar1 == '\0') break;
          puVar9 = local_228;
          FUN_0042de50(puVar9);
          cVar1 = FUN_0056f780(puVar9);
          if (cVar1 != '\0') {
            iVar4 = get();
            piVar6 = (int *)FUN_0042de50(iVar4 + 0xc18);
            cVar1 = operator==<>(*piVar6 + 0x60);
            if (cVar1 != '\0') {
              puVar7 = (undefined4 *)FUN_0042de50();
              local_138 = (int *)*puVar7;
              break;
            }
            if (DAT_00946708 == 0) {
              iVar4 = get();
              piVar6 = (int *)FUN_0042de50(iVar4 + 0xc18);
              cVar1 = operator==<>(*piVar6 + 0x44);
              if (cVar1 != '\0') {
                puVar7 = (undefined4 *)FUN_0042de50();
                local_138 = (int *)*puVar7;
                break;
              }
              puVar9 = local_208;
              FUN_0042de50(puVar9);
              uVar5 = FID_conflict_begin(puVar9);
              iVar4 = get(uVar5);
              iVar4 = iVar4 + 0xc18;
              puVar9 = local_210;
              FUN_0042de50(puVar9,iVar4);
              FUN_0075f8b0(puVar9,iVar4);
              cVar1 = FUN_00420f10(uVar5);
              if (cVar1 != '\0') {
                puVar7 = (undefined4 *)FUN_0042de50();
                local_138 = (int *)*puVar7;
                break;
              }
              puVar7 = (undefined4 *)FUN_0042de50();
              local_138 = (int *)*puVar7;
            }
          }
          FUN_0042da80();
        }
        if (local_138 == (int *)0x0) {
          FUN_007d6a70("BZRNet P2P Dropping Packet (Source IP doesn\'t match any known player)\n");
          local_8 = 0xffffffff;
          FUN_00417f10();
          goto switchD_0075df65_caseD_1;
        }
        local_8 = 0xffffffff;
        FUN_00417f10();
        goto LAB_0075deef;
      }
    }
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  else {
    iVar4 = FUN_00422150();
    local_138 = *(int **)(iVar4 + 0x1c);
    if (local_138 == (int *)0x0) {
      FUN_007d6a70("BZRNet P2P Failure with bzrinmap detected\n");
      goto switchD_0075df65_caseD_1;
    }
    if ((((local_160 != 0) || (local_13d < 3)) || (5 < local_13d)) && (local_160 != local_138[0x21])
       ) {
      while( true ) {
        cVar1 = FUN_0042d8f0();
        if (cVar1 != '\0') break;
        local_1c8 = (uint *)FUN_00438b60();
        if (local_178 <= *local_1c8) break;
        FUN_0075f9e0();
      }
      if ((local_13d != 6) && (local_13d != 7)) {
        if (DAT_008eda28 != 0) {
          if (local_13e == '\0') {
            local_17c = 0;
          }
          else {
            local_17c = local_138[0x21];
          }
          local_1ac = FUN_0073a9f0(local_11c);
          local_8 = 0;
          local_18c = local_1ac;
          uVar5 = FUN_0041f870(local_160,local_17c);
          FUN_007d6a70("BZRNet P2P Dropping Packet Type %u For Client %s (Packet #%ld received, #%ld expected)\n"
                       ,local_13d,uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        iVar4 = get(local_138 + 10,local_148,6,local_138[0x22],local_138[0x21]);
        FUN_0075a490(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
        *(undefined1 *)((int)local_138 + 0x19) = 1;
      }
      goto switchD_0075df65_caseD_1;
    }
    if (local_13e != '\0') {
      local_138[0x21] = local_160 + 1;
      *(undefined1 *)(local_138 + 6) = 1;
    }
    *(undefined1 *)((int)local_138 + 0x19) = 1;
LAB_0075deef:
    while( true ) {
      cVar1 = FUN_0042d8f0();
      if (cVar1 != '\0') break;
      local_1bc = (uint *)FUN_00438b60();
      if (local_178 <= *local_1bc) break;
      FUN_0075f9e0();
    }
    local_170 = (uint)local_13d;
    switch(local_170) {
    case 0:
      if (local_13e == '\0') {
        cVar1 = FUN_0041fc90();
        if (cVar1 == '\0') break;
      }
      iVar4 = FUN_004bb390();
      FUN_00579020(iVar4 + -0x12 + param_3);
      puVar7 = (undefined4 *)FID_conflict_end(local_20c);
      local_1c4 = *puVar7;
      FUN_0057b140(local_214,local_1c4,local_154 + 0x12,local_154 + param_3);
      if (local_155 != '\0') {
        vector<>();
        local_8 = 4;
        FUN_0075f750(local_138 + 0x26);
        FUN_0041ff50();
        get();
        FUN_006c6df0();
        *param_4 = 0;
        piVar6 = local_138 + 2;
        uVar5 = FUN_004bb390(piVar6);
        uVar8 = get(uVar5);
        FUN_00758c90(uVar8,uVar5,piVar6);
        local_8 = 0xffffffff;
        FUN_00579000();
      }
      break;
    case 3:
      if (*local_138 == 0) {
        if (1 < DAT_008eda28) {
          local_1d4 = FUN_0073a9f0(local_5c);
          local_8 = 5;
          local_1cc = local_1d4;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Completing WAN Connect For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_138 = 4;
        *(undefined2 *)(local_138 + 7) = 10;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,4,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (*local_138 == 1) {
        if (1 < DAT_008eda28) {
          local_1e4 = FUN_0073a9f0(local_74);
          local_8 = 6;
          local_1dc = local_1e4;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Completing LAN Connect For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_138 = 2;
        *(undefined2 *)(local_138 + 7) = 10;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,4,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (*local_138 == 3) {
        if (1 < DAT_008eda28) {
          local_1f4 = FUN_0073a9f0(local_a4);
          local_8 = 7;
          local_1ec = local_1f4;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Completing WAN Connect For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_138 = 4;
        *(undefined2 *)(local_138 + 7) = 10;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,4,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (*local_138 == 6) {
        if (1 < DAT_008eda28) {
          local_1e0 = FUN_0073a9f0(local_d4);
          local_8 = 8;
          local_188 = local_1e0;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Completing RELAY Connect For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_138 = 7;
        *(undefined2 *)(local_138 + 7) = 10;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,4,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (((*local_138 == 2) || (*local_138 == 4)) || (*local_138 == 7)) {
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,4,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (*local_138 == 8) {
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,4,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      break;
    case 4:
      if (*local_138 == 0) {
        if (1 < DAT_008eda28) {
          local_1e8 = FUN_0073a9f0(local_104);
          local_8 = 9;
          local_184 = local_1e8;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Completing WAN Connect For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_138 = 4;
        *(undefined2 *)(local_138 + 7) = 10;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,4,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (*local_138 == 1) {
        if (1 < DAT_008eda28) {
          local_190 = FUN_0073a9f0(local_134);
          local_8 = 10;
          local_180 = local_190;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Completing LAN Connect For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_138 = 2;
        *(undefined2 *)(local_138 + 7) = 10;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,5,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (*local_138 == 3) {
        if (1 < DAT_008eda28) {
          local_1a0 = FUN_0073a9f0(local_ec);
          local_8 = 0xb;
          local_19c = local_1a0;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Completing WAN Connect For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_138 = 4;
        *(undefined2 *)(local_138 + 7) = 10;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,5,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (*local_138 == 6) {
        if (1 < DAT_008eda28) {
          local_1a8 = FUN_0073a9f0(local_8c);
          local_8 = 0xc;
          local_1a4 = local_1a8;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Completing RELAY Connect For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_138 = 7;
        *(undefined2 *)(local_138 + 7) = 10;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,5,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (((*local_138 == 2) || (*local_138 == 4)) || (*local_138 == 7)) {
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        iVar4 = get(local_138 + 10,local_148,5,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      else if (*local_138 == 8) {
        iVar4 = get(local_138 + 10,local_148,5,local_138[0x22],local_138[0x21],local_13c + 0x38);
        FUN_0075a710(iVar4 + 0xb8);
        *(undefined1 *)(local_138 + 6) = 0;
      }
      break;
    case 5:
      if (((*local_138 == 2) || (*local_138 == 4)) || (*local_138 == 7)) {
        if (0 < DAT_008eda28) {
          FUN_00574400(3,1);
          local_8 = 0xd;
          if (&stack0x00000000 == (undefined1 *)0x390) {
            local_164 = (undefined1 *)0x0;
          }
          else {
            local_164 = auStack_380;
          }
          iVar4 = get();
          FUN_006da360(local_164,iVar4 + 0xc18);
          if (*local_138 == 2) {
            local_174 = "LAN";
          }
          else {
            if (*local_138 == 4) {
              local_16c = "WAN";
            }
            else {
              local_16c = "RELAY";
            }
            local_174 = local_16c;
          }
          local_1f0 = GetPolicy(local_44);
          local_8._0_1_ = 0xe;
          local_1d0 = local_1f0;
          local_1b8 = FUN_0073a9f0(local_bc);
          local_8._0_1_ = 0xf;
          local_1b0 = local_1b8;
          uVar5 = FUN_0041f870();
          uVar5 = FUN_0041f870(uVar5);
          FUN_007d6a70("BZRNet P2P Completed %s Connect For Client %s, using address %s\n",local_174
                       ,uVar5);
          local_8._0_1_ = 0xe;
          ~basic_string<>();
          local_8 = CONCAT31(local_8._1_3_,0xd);
          ~basic_string<>();
          local_8 = 0xffffffff;
          FUN_00417f10();
        }
        *local_138 = 8;
        iVar4 = get();
        FUN_006cb4c0(iVar4 + 0xc18);
        puVar7 = (undefined4 *)FUN_0075fc50(local_138 + 10);
        *puVar7 = local_138;
        puVar7 = (undefined4 *)FUN_0075fda0(local_138 + 2);
        *puVar7 = local_138;
        FUN_0042d8c0(&local_15c);
        FID_conflict_begin(local_1d8);
        while( true ) {
          cVar1 = FUN_00420f10(local_1d8);
          if (cVar1 == '\0') break;
          puVar7 = (undefined4 *)FUN_0042de50();
          if ((int *)*puVar7 == local_138) {
            local_1c0 = local_15c;
            FUN_0042d920(local_204,local_15c);
            break;
          }
          FUN_0042da80();
        }
      }
      break;
    case 6:
      local_138[8] = local_198;
      local_138[9] = local_194;
    }
  }
switchD_0075df65_caseD_1:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

