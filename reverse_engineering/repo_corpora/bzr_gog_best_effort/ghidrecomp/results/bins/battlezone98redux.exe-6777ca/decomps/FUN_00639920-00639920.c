
void FUN_00639920(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  undefined4 uVar5;
  undefined1 local_108 [4];
  undefined1 local_104 [4];
  float local_100;
  undefined8 local_fc;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c0;
  float local_bc;
  uint local_b8;
  uint local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  uint local_98;
  float local_94;
  float local_90;
  float local_88;
  float local_84;
  float local_80;
  float local_78;
  float local_74;
  float local_70;
  float local_68;
  float local_64;
  float local_60;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  int *local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined *local_30;
  int local_2c;
  undefined1 local_28 [4];
  float local_24;
  int local_20;
  float local_1c;
  int *local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_2c = 0;
  local_fc = FUN_0045c0c0("bvapc");
  FUN_005ccfa0(*(undefined4 *)(local_8 + 0x78),0);
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(local_8 + 0x70) = uVar2;
  if (*(char *)(local_8 + 0x54) == '\0') {
    if ((*(char *)(local_8 + 0x55) == '\0') && (*(int *)(local_8 + 0x74) != 0)) {
      local_30 = &DAT_0094e2d4;
      FID_conflict_begin(local_28);
      while( true ) {
        uVar2 = FID_conflict_end(local_108);
        cVar1 = FID_conflict_operator__(uVar2);
        if (cVar1 == '\0') break;
        local_18 = (int *)FUN_00421ec0();
        local_18 = (int *)*local_18;
        local_3c = (**(code **)local_18[6])();
        if ((*(int *)(local_3c + 0x30) == (int)local_fc) &&
           (*(int *)(local_3c + 0x34) == local_fc._4_4_)) {
          cVar1 = (**(code **)(*local_18 + 0x38))();
          if (cVar1 != '\0') {
            local_14 = FUN_00462380();
            fVar4 = (float10)FUN_005c9800(local_14,"apc_in",0);
            local_88 = (float)fVar4;
            if (local_88 < 100.0) {
              FUN_005ccfd0(local_14,0x461c4000);
              FUN_005cb960(local_14,"apc_in",1);
              FUN_005caff0(local_14,1);
              *(undefined4 *)(local_8 + 0x10c) = local_14;
              *(undefined1 *)(local_8 + 0x55) = 1;
              *(undefined4 *)(local_8 + 0x118) = 0;
              FUN_00639680();
              local_10 = FUN_005c8250("cvartl",2,"portal_attack_1",0,0);
              FUN_005cb820(local_10,*(undefined4 *)(local_8 + 0x78),1);
              local_10 = FUN_005c8250("cvartl",2,"portal_attack_1",0,0);
              FUN_005cb820(local_10,*(undefined4 *)(local_8 + 0x78),1);
              local_10 = FUN_005c8250("cvartl",2,"portal_attack_1",0,0);
              FUN_005cb820(local_10,*(undefined4 *)(local_8 + 0x78),1);
              *(undefined4 *)(local_8 + 0x114) = 0x11;
              *(undefined4 *)(local_8 + 0x5c) = 0;
              FUN_005cd2a0();
              break;
            }
            fVar4 = (float10)FUN_005c9800(local_14,"apc_in",0);
            local_a8 = (float)fVar4;
            if (local_a8 < 200.0) {
              FUN_005ccfd0(local_14,0x461c4000);
            }
            local_2c = local_2c + 1;
          }
        }
        FUN_0046b260(local_104,0);
      }
      if ((*(char *)(local_8 + 0x55) == '\0') && (local_2c == 0)) {
        cVar1 = FUN_005c84d0(local_8 + 0x74);
        if (cVar1 == '\0') {
          *(undefined4 *)(local_8 + 0x114) = 0x17;
          uVar2 = FUN_00437d30("bd06006.wav");
          *(undefined4 *)(local_8 + 0x118) = uVar2;
        }
      }
    }
    cVar1 = FUN_005c84d0(local_8 + 0x78);
    if (cVar1 == '\0') {
      fVar4 = (float10)FUN_004b1670("bd06lseb.des");
      local_50 = (float)fVar4;
      FUN_0045c0f0(local_50 + 2.0);
      *(undefined1 *)(local_8 + 0x54) = 1;
    }
  }
  else if (*(char *)(local_8 + 0x54) != '\0') {
    return;
  }
  if (*(float *)(local_8 + 0x68) != 0.0) {
    fVar4 = (float10)FUN_004b1670();
    local_d8 = (float)fVar4;
    if (*(float *)(local_8 + 0x68) <= local_d8 && local_d8 != *(float *)(local_8 + 0x68)) {
      for (local_c = 0; local_c < 2; local_c = local_c + 1) {
        fVar4 = (float10)FUN_004b1670();
        local_58 = (float)fVar4;
        local_1c = local_58 - *(float *)(local_8 + 0x68);
        if (1.0 <= local_1c) {
          cVar1 = FUN_005c8490(local_8 + 0xe4 + local_c * 4);
          if (cVar1 == '\0') {
            FUN_005cdbb0(*(undefined4 *)(local_8 + 0x78),local_1c - 1.0);
            fVar4 = (float10)FUN_004a7890();
            local_24 = (float)fVar4;
            if (0.33 <= local_24) {
              if (0.66 <= local_24) {
                uVar2 = FUN_005cdcd0("cvrckt",2,*(undefined4 *)(local_8 + 0x78));
                *(undefined4 *)(local_8 + 0xe4 + local_c * 4) = uVar2;
              }
              else {
                uVar2 = FUN_005cdcd0("cvtnk",2,*(undefined4 *)(local_8 + 0x78));
                *(undefined4 *)(local_8 + 0xe4 + local_c * 4) = uVar2;
              }
            }
            else {
              uVar2 = FUN_005cdcd0("cvfigh",2,*(undefined4 *)(local_8 + 0x78));
              *(undefined4 *)(local_8 + 0xe4 + local_c * 4) = uVar2;
            }
            FUN_005cb960(*(undefined4 *)(local_8 + 0xe4 + local_c * 4),"camera_go",1);
          }
          else if (2.0 <= local_1c) {
            fVar4 = (float10)FUN_004b1670();
            local_b0 = (float)fVar4;
            *(float *)(local_8 + 0x68) = local_b0 + 80.0;
            *(undefined4 *)(local_8 + 0xe8) = 0;
            *(undefined4 *)(local_8 + 0xe4) = 0;
          }
          else {
            FUN_005cdbb0(*(undefined4 *)(local_8 + 0x78),local_1c - 1.0);
          }
        }
        else {
          FUN_005cdbb0(*(undefined4 *)(local_8 + 0x78),1.0 - local_1c);
        }
      }
    }
  }
  if (*(float *)(local_8 + 100) != 0.0) {
    fVar4 = (float10)FUN_004b1670();
    local_60 = (float)fVar4;
    if (*(float *)(local_8 + 100) <= local_60 && local_60 != *(float *)(local_8 + 100)) {
      for (local_c = 0; local_c < 4; local_c = local_c + 1) {
        cVar1 = FUN_005c8490(local_8 + 0xec + local_c * 4);
        if (cVar1 == '\0') {
          fVar4 = (float10)FUN_004a7890();
          local_24 = (float)fVar4;
          if (0.5 <= local_24) {
            uVar2 = FUN_005c8250("cvtnk",2,"attack_always",0,0);
            *(undefined4 *)(local_8 + 0xec + local_c * 4) = uVar2;
          }
          else {
            uVar2 = FUN_005c8250("cvfigh",2,"attack_always",0,0);
            *(undefined4 *)(local_8 + 0xec + local_c * 4) = uVar2;
          }
          FUN_005cdb20(*(undefined4 *)(local_8 + 0xec + local_c * 4),1);
        }
      }
      fVar4 = (float10)FUN_004b1670();
      local_f0 = (float)fVar4;
      *(float *)(local_8 + 100) = local_f0 + 120.0;
    }
  }
  local_34 = *(undefined4 *)(local_8 + 0x114);
  switch(local_34) {
  case 0:
    FUN_005cadd0(1,0x4b);
    FUN_005cacb0(1,10);
    FUN_00639680();
    *(undefined4 *)(local_8 + 0x114) = 1;
    fVar4 = (float10)FUN_004b1670();
    local_68 = (float)fVar4;
    *(float *)(local_8 + 0x5c) = local_68 + 2.0;
    *(undefined4 *)(local_8 + 0x118) = 0;
    FUN_005cd2a0();
  case 1:
    local_b8 = FUN_005cd300("camera_start",1000,0x9c4,*(undefined4 *)(local_8 + 0x78));
    local_b8 = local_b8 & 0xff;
    if (local_b8 == 0) {
      cVar1 = FUN_005cd560();
      if (cVar1 != '\0') goto LAB_0063a07e;
    }
    else {
LAB_0063a07e:
      FUN_005cd4e0();
      *(undefined4 *)(local_8 + 0x114) = 2;
      FUN_00639680();
      fVar4 = (float10)FUN_004b1670();
      local_70 = (float)fVar4;
      *(float *)(local_8 + 0x5c) = local_70 + 20.0;
      fVar4 = (float10)FUN_004b1670();
      local_e0 = (float)fVar4;
      *(float *)(local_8 + 0x60) = local_e0 + 660.0;
    }
    fVar4 = (float10)FUN_004b1670();
    local_78 = (float)fVar4;
    if ((*(float *)(local_8 + 0x5c) <= local_78 && local_78 != *(float *)(local_8 + 0x5c)) &&
       (*(int *)(local_8 + 0x118) == 0)) {
      uVar2 = FUN_00437d30("bd06001.wav");
      *(undefined4 *)(local_8 + 0x118) = uVar2;
    }
    break;
  case 2:
    fVar4 = (float10)FUN_004b1670();
    local_c0 = (float)fVar4;
    if (local_c0 < *(float *)(local_8 + 0x5c) || local_c0 == *(float *)(local_8 + 0x5c)) {
      for (local_c = 0; local_c < 10; local_c = local_c + 1) {
        local_38 = FUN_00462630(*(undefined4 *)(local_8 + 0xa4 + local_c * 4));
        fVar4 = (float10)FUN_0046fbd0();
        local_f4 = (float)fVar4;
        local_80 = local_f4;
        fVar4 = (float10)FUN_004624f0();
        local_44 = (float)fVar4;
        if (local_f4 != local_44) {
          *(undefined4 *)(local_8 + 0x114) = 0x18;
          uVar2 = FUN_00437d30("bd06007.wav");
          *(undefined4 *)(local_8 + 0x118) = uVar2;
        }
      }
    }
    else {
      uVar2 = FUN_00437d30("bd06002.wav");
      *(undefined4 *)(local_8 + 0x118) = uVar2;
      for (local_c = 0; local_c < 10; local_c = local_c + 1) {
        FUN_005cb960(*(undefined4 *)(local_8 + 0xa4 + local_c * 4),"fake_attack",1);
      }
      *(undefined4 *)(local_8 + 0x114) = 3;
    }
    break;
  case 3:
    cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 0x118));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_8 + 0x114) = 4;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(local_8 + 0x5c) = (float)fVar4 + 1.0;
    }
    break;
  case 4:
    fVar4 = (float10)FUN_004b1670();
    local_90 = (float)fVar4;
    if (local_90 < *(float *)(local_8 + 0x5c) || local_90 == *(float *)(local_8 + 0x5c)) {
      return;
    }
    *(undefined4 *)(local_8 + 0x114) = 5;
    fVar4 = (float10)FUN_004b1670();
    local_e8 = (float)fVar4;
    *(float *)(local_8 + 0x5c) = local_e8 + 10.0;
    FUN_005cd2a0();
  case 5:
    local_98 = FUN_005cd300("camera_go",2000,2000,*(undefined4 *)(local_8 + 0xb0));
    local_98 = local_98 & 0xff;
    if (local_98 == 0) {
      cVar1 = FUN_005cd560();
      if (cVar1 == '\0') {
        fVar4 = (float10)FUN_004b1670();
        local_d0 = (float)fVar4;
        if (local_d0 < *(float *)(local_8 + 0x5c) || local_d0 == *(float *)(local_8 + 0x5c)) {
          return;
        }
      }
    }
    for (local_c = 0; local_c < 10; local_c = local_c + 1) {
      FUN_005c83e0(*(undefined4 *)(local_8 + 0xa4 + local_c * 4));
    }
    FUN_005cd4e0();
    *(undefined4 *)(local_8 + 0x60) = 0x44160000;
    *(undefined4 *)(local_8 + 0x114) = 6;
    break;
  case 6:
    fVar4 = (float10)FUN_004b1670();
    local_a0 = (float)fVar4;
    if (local_a0 < *(float *)(local_8 + 0x60) || local_a0 == *(float *)(local_8 + 0x60)) {
      cVar1 = FUN_0049a000();
      if (cVar1 == '\0') {
        uVar5 = 0x80000000;
        uVar2 = 0x80000000;
        fVar4 = (float10)FUN_004b1670(0x80000000,0x80000000);
        local_48 = (float)fVar4;
        FUN_004f6a10((int)(*(float *)(local_8 + 0x60) - local_48),uVar2,uVar5);
        FUN_0049a020();
      }
      for (local_c = 0; local_c < 6; local_c = local_c + 1) {
        cVar1 = FUN_005c84d0(local_8 + 0xcc + local_c * 4);
        if (cVar1 != '\0') break;
      }
      if (5 < local_c) {
        FUN_0049a080();
        *(undefined4 *)(local_8 + 0x114) = 7;
        FUN_00639680();
        fVar4 = (float10)FUN_004b1670();
        local_4c = (float)fVar4;
        *(float *)(local_8 + 0x5c) = local_4c + 90.0;
        fVar4 = (float10)FUN_004b1670();
        local_54 = (float)fVar4;
        *(float *)(local_8 + 100) = local_54 + 60.0 + 50.0;
        fVar4 = (float10)FUN_004b1670();
        *(float *)(local_8 + 0x68) = (float)fVar4 + 80.0;
        *(undefined4 *)(local_8 + 0xe8) = 0;
        *(undefined4 *)(local_8 + 0xe4) = 0;
        *(undefined4 *)(local_8 + 0xec) = 0;
        *(undefined4 *)(local_8 + 0xf0) = 0;
        *(undefined4 *)(local_8 + 0xf4) = 0;
        *(undefined4 *)(local_8 + 0xf8) = 0;
        *(undefined4 *)(local_8 + 0xfc) = 0;
        *(undefined4 *)(local_8 + 0x118) = 0;
        *(undefined1 *)(local_8 + 0x56) = 0;
      }
    }
    else {
      fVar4 = (float10)FUN_004b1670("bd06lsed.des");
      local_100 = (float)fVar4;
      FUN_0045c0f0(local_100 + 2.0);
      *(undefined1 *)(local_8 + 0x54) = 1;
    }
    break;
  case 7:
    fVar4 = (float10)FUN_004b1670();
    local_64 = (float)fVar4;
    if (*(float *)(local_8 + 0x5c) <= local_64 && local_64 != *(float *)(local_8 + 0x5c)) {
      local_20 = 0;
      local_c = 0;
      while ((local_c < 10 || (local_20 == 5))) {
        cVar1 = FUN_005c84d0(local_8 + 0x7c + local_c * 4);
        if (cVar1 == '\0') {
          local_20 = local_20 + 1;
        }
        local_c = local_c + 1;
      }
      for (local_c = 0; local_c < local_20; local_c = local_c + 1) {
        local_10 = FUN_005c8250("bvrdeva",1,"backup_1",0,0);
        FUN_005cb960(local_10,"backup_path",1);
      }
      fVar4 = (float10)FUN_004b1670();
      *(float *)(local_8 + 0x5c) = (float)fVar4 + 60.0 + 30.0;
      *(undefined4 *)(local_8 + 0x114) = 8;
    }
    break;
  case 8:
    fVar4 = (float10)FUN_004b1670();
    local_74 = (float)fVar4;
    if (*(float *)(local_8 + 0x5c) <= local_74 && local_74 != *(float *)(local_8 + 0x5c)) {
      uVar2 = FUN_005c8250("cvtnk",2,"attack_1",0,0);
      *(undefined4 *)(local_8 + 0x100) = uVar2;
      FUN_005cb820(*(undefined4 *)(local_8 + 0x100),*(undefined4 *)(local_8 + 0x70),1);
      uVar2 = FUN_005c8250("cvtnk",2,"attack_1",0,0);
      *(undefined4 *)(local_8 + 0x104) = uVar2;
      FUN_005cb820(*(undefined4 *)(local_8 + 0x104),*(undefined4 *)(local_8 + 0x70),1);
      *(undefined4 *)(local_8 + 0x114) = 9;
    }
    break;
  case 9:
    cVar1 = FUN_005c84d0(local_8 + 0x100);
    if (cVar1 == '\0') {
      fVar4 = (float10)FUN_004b1670();
      *(float *)(local_8 + 0x5c) = (float)fVar4 + 180.0;
      *(undefined4 *)(local_8 + 0x114) = 10;
    }
    break;
  case 10:
    fVar4 = (float10)FUN_004b1670();
    local_84 = (float)fVar4;
    if (*(float *)(local_8 + 0x5c) <= local_84 && local_84 != *(float *)(local_8 + 0x5c)) {
      uVar2 = FUN_005c8250("cvtnk",2,"attack_2",0,0);
      *(undefined4 *)(local_8 + 0x100) = uVar2;
      FUN_005cb820(*(undefined4 *)(local_8 + 0x100),*(undefined4 *)(local_8 + 0x70),1);
      uVar2 = FUN_005c8250("cvtnk",2,"attack_2",0,0);
      *(undefined4 *)(local_8 + 0x104) = uVar2;
      FUN_005cb820(*(undefined4 *)(local_8 + 0x104),*(undefined4 *)(local_8 + 0x70),1);
      uVar2 = FUN_005c8250("cvtnk",2,"attack_2",0,0);
      *(undefined4 *)(local_8 + 0x108) = uVar2;
      FUN_005cb820(*(undefined4 *)(local_8 + 0x108),*(undefined4 *)(local_8 + 0x70),1);
      *(undefined4 *)(local_8 + 0x114) = 0xb;
    }
    break;
  case 0xb:
    cVar1 = FUN_005c84d0(local_8 + 0x100);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_8 + 0x104);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(local_8 + 0x108);
        if (cVar1 == '\0') {
          *(undefined4 *)(local_8 + 0x114) = 0xc;
          FUN_00639680();
          uVar2 = FUN_00437d30("bd06003.wav");
          *(undefined4 *)(local_8 + 0x118) = uVar2;
        }
      }
    }
    break;
  case 0xc:
    cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 0x118));
    if (cVar1 != '\0') {
      uVar2 = FUN_005c8250("bvrecy",1,"recycler_spawn",0,0);
      *(undefined4 *)(local_8 + 0x74) = uVar2;
      FUN_005cb960(*(undefined4 *)(local_8 + 0x74),"recycler_path",1);
      local_10 = FUN_005c8250("bvrdeva",1,"recycler_spawn",0,0);
      FUN_005cbc20(local_10,*(undefined4 *)(local_8 + 0x74),1);
      local_10 = FUN_005c8250("bvrdeva",1,"recycler_spawn",0,0);
      FUN_005cbc20(local_10,*(undefined4 *)(local_8 + 0x74),1);
      fVar4 = (float10)FUN_004b1670();
      *(float *)(local_8 + 0x5c) = (float)fVar4 + 30.0;
      *(undefined4 *)(local_8 + 0x114) = 0xd;
    }
    break;
  case 0xd:
    fVar4 = (float10)FUN_004b1670();
    local_94 = (float)fVar4;
    if (*(float *)(local_8 + 0x5c) <= local_94 && local_94 != *(float *)(local_8 + 0x5c)) {
      *(undefined4 *)(local_8 + 0x114) = 0xe;
      FUN_00639680();
    }
    break;
  case 0xe:
    iVar3 = FUN_005cb5c0(*(undefined4 *)(local_8 + 0x74));
    if (iVar3 == 0) {
      local_40 = (int *)FUN_00462630(*(undefined4 *)(local_8 + 0x74));
      (**(code **)(*local_40 + 0x60))();
      FUN_00437d30("bd06004.wav");
      *(undefined4 *)(local_8 + 0x114) = 0xf;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(local_8 + 0x5c) = (float)fVar4 + 60.0;
    }
    break;
  case 0xf:
    local_10 = FUN_005c8250("cvtnk",2,"attack_3",0,0);
    FUN_005cdb20(local_10,1);
    local_10 = FUN_005c8250("cvtnk",2,"attack_3",0,0);
    FUN_005cdb20(local_10,1);
    local_10 = FUN_005c8250("cvtnk",2,"attack_3",0,0);
    FUN_005cdb20(local_10,1);
    local_10 = FUN_005c8250("cvtnk",2,"attack_3",0,0);
    FUN_005cdb20(local_10,1);
    local_10 = FUN_005c8250("cvtnk",2,"attack_3",0,0);
    FUN_005cdb20(local_10,1);
    *(undefined4 *)(local_8 + 0x114) = 0x10;
    break;
  case 0x11:
    if (*(int *)(local_8 + 0x10c) != 0) {
      iVar3 = FUN_005cb5c0(*(undefined4 *)(local_8 + 0x10c));
      if (iVar3 == 0) {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0x10c));
        *(undefined4 *)(local_8 + 0x10c) = 0;
        uVar2 = FUN_00437d30("bd06009.wav");
        *(undefined4 *)(local_8 + 0x118) = uVar2;
        fVar4 = (float10)FUN_004b1670();
        local_a4 = (float)fVar4;
        *(float *)(local_8 + 0x60) = local_a4 + 60.0;
      }
    }
    if (*(int *)(local_8 + 0x118) != 0) {
      cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 0x118));
      if (cVar1 != '\0') {
        *(undefined4 *)(local_8 + 0x118) = 0;
        for (local_c = 0; local_c < 7; local_c = local_c + 1) {
          local_10 = FUN_005c8250("cvtnk",2,"dummy_1",0,0);
          FUN_005cb960(local_10,"dummy_1_path",1);
        }
        fVar4 = (float10)FUN_004b1670();
        local_ac = (float)fVar4;
        *(float *)(local_8 + 0x5c) = local_ac + 3.0;
      }
    }
    local_b4 = FUN_005cd300("camera_end_scene",2000,0,*(undefined4 *)(local_8 + 0x10c));
    local_b4 = local_b4 & 0xff;
    if (local_b4 == 0) {
      if (*(float *)(local_8 + 0x5c) == 0.0) {
        return;
      }
      cVar1 = FUN_005cd560();
      if (cVar1 == '\0') {
        fVar4 = (float10)FUN_004b1670();
        local_bc = (float)fVar4;
        if (local_bc < *(float *)(local_8 + 0x5c) || local_bc == *(float *)(local_8 + 0x5c)) {
          return;
        }
      }
    }
    FUN_005cd4e0();
    *(undefined4 *)(local_8 + 0x114) = 0x12;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(local_8 + 0x5c) = (float)fVar4 + 5.0;
    break;
  case 0x12:
    fVar4 = (float10)FUN_004b1670();
    local_cc = (float)fVar4;
    if (*(float *)(local_8 + 0x5c) <= local_cc && local_cc != *(float *)(local_8 + 0x5c)) {
      for (local_c = 0; local_c < 7; local_c = local_c + 1) {
        local_10 = FUN_005c8250("cvfigh",2,"portal_attack_2",0,0);
        FUN_005cb820(local_10,*(undefined4 *)(local_8 + 0x78),1);
      }
      *(undefined4 *)(local_8 + 0x114) = 0x13;
    }
    break;
  case 0x13:
    fVar4 = (float10)FUN_004b1670();
    local_d4 = (float)fVar4;
    if (*(float *)(local_8 + 0x60) <= local_d4 && local_d4 != *(float *)(local_8 + 0x60)) {
      uVar2 = FUN_005c8250("bvapc",1,"portal",0,0);
      *(undefined4 *)(local_8 + 0x10c) = uVar2;
      FUN_005cb960(*(undefined4 *)(local_8 + 0x10c),"apc_out",1);
      *(undefined4 *)(local_8 + 0x114) = 0x14;
    }
    break;
  case 0x14:
    iVar3 = FUN_005cb5c0(*(undefined4 *)(local_8 + 0x10c));
    if (iVar3 == 0) {
      fVar4 = (float10)FUN_004b1670("bd06wina.des");
      local_dc = (float)fVar4;
      FUN_0045c110(local_dc + 10.0);
      *(undefined1 *)(local_8 + 0x54) = 1;
    }
    break;
  case 0x17:
    cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 0x118));
    if (cVar1 != '\0') {
      fVar4 = (float10)FUN_004b1670("bd06lsec.des");
      local_e4 = (float)fVar4;
      FUN_0045c0f0(local_e4 + 2.0);
      *(undefined1 *)(local_8 + 0x54) = 1;
    }
    break;
  case 0x18:
    cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 0x118));
    if (cVar1 != '\0') {
      fVar4 = (float10)FUN_004b1670("bd06lsea.des");
      local_ec = (float)fVar4;
      FUN_0045c0f0(local_ec + 2.0);
      *(undefined1 *)(local_8 + 0x54) = 1;
    }
  }
  return;
}

