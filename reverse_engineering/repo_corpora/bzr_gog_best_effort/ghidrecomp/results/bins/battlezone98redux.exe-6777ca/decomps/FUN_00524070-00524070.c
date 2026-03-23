
void __fastcall FUN_00524070(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_1a4 [12];
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
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
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = param_1;
  if (*(char *)(param_1 + 0x54) == '\x01') {
    uVar2 = FUN_00437d30("misn0601.wav");
    *(undefined4 *)(local_24 + 0x35c) = uVar2;
    *(undefined1 *)(local_24 + 0x54) = 0;
    uVar2 = FUN_005c7fb0();
    *(undefined4 *)(local_24 + 0x1a0) = uVar2;
    uVar2 = FUN_005c7e90("eggeizr1-1_geyser");
    *(undefined4 *)(local_24 + 0x1a8) = uVar2;
    FUN_005c9640(*(undefined4 *)(local_24 + 0x1a8),"5th Platoon");
    uVar2 = FUN_005c7e90("obheph0_i76building");
    *(undefined4 *)(local_24 + 0x144) = uVar2;
    puVar3 = (undefined4 *)FUN_005c8b10(local_1a4,*(undefined4 *)(local_24 + 0x144));
    local_20 = *puVar3;
    local_1c = (float)puVar3[1];
    local_18 = puVar3[2];
    local_10 = local_1c - 4.0;
    local_14 = local_20;
    local_c = local_18;
    FUN_005c8c80(*(undefined4 *)(local_24 + 0x144),&local_14);
    uVar2 = FUN_005c7e90("avrecy-1_recycler");
    *(undefined4 *)(local_24 + 0x1b0) = uVar2;
    uVar2 = FUN_005c7e90("svrecy-1_recycler");
    *(undefined4 *)(local_24 + 0x1b4) = uVar2;
    uVar2 = FUN_005c7e90("sblpad0_i76building");
    *(undefined4 *)(local_24 + 0x1b8) = uVar2;
    uVar2 = FUN_005c7e90("svfigh568_wingman");
    *(undefined4 *)(local_24 + 0x210) = uVar2;
    uVar2 = FUN_005c7e90("svfigh566_wingman");
    *(undefined4 *)(local_24 + 0x214) = uVar2;
    uVar2 = FUN_005c7e90("turret");
    *(undefined4 *)(local_24 + 0x220) = uVar2;
    uVar2 = FUN_005c7e90("obstp25_i76building");
    *(undefined4 *)(local_24 + 0x22c) = uVar2;
    uVar2 = FUN_005c7e90("obstp10_i76building");
    *(undefined4 *)(local_24 + 0x23c) = uVar2;
    uVar2 = FUN_005c7e90("obstp33_i76building");
    *(undefined4 *)(local_24 + 0x244) = uVar2;
    uVar2 = FUN_005c7e90("svturr649_turrettank");
    *(undefined4 *)(local_24 + 0x1ac) = uVar2;
    uVar2 = FUN_005c7e90(&DAT_0087ee34);
    *(undefined4 *)(local_24 + 0x2d0) = uVar2;
    uVar2 = FUN_005c7e90(&DAT_0087ee2c);
    *(undefined4 *)(local_24 + 0x2d4) = uVar2;
    uVar2 = FUN_005c7e90(&DAT_0087eefc);
    *(undefined4 *)(local_24 + 0x2d8) = uVar2;
    uVar2 = FUN_005c7e90(&DAT_0087eef4);
    *(undefined4 *)(local_24 + 0x2dc) = uVar2;
    uVar2 = FUN_005c7e90("avtank13_wingman");
    *(undefined4 *)(local_24 + 600) = uVar2;
    uVar2 = FUN_005c7e90("avtank11_wingman");
    *(undefined4 *)(local_24 + 0x25c) = uVar2;
    uVar2 = FUN_005c7e90("avtank12_wingman");
    *(undefined4 *)(local_24 + 0x264) = uVar2;
    uVar2 = FUN_005c7e90("avfigh7_wingman");
    *(undefined4 *)(local_24 + 0x270) = uVar2;
    uVar2 = FUN_005c7e90("avfigh10_wingman");
    *(undefined4 *)(local_24 + 0x27c) = uVar2;
    fVar5 = (float10)FUN_004b1670();
    local_e0 = (float)fVar5;
    *(float *)(local_24 + 0x10c) = local_e0 + 30.0;
    fVar5 = (float10)FUN_004b1670();
    local_18c = (float)fVar5;
    *(float *)(local_24 + 0x110) = local_18c + 30.0;
    fVar5 = (float10)FUN_004b1670();
    local_194 = (float)fVar5;
    *(float *)(local_24 + 0x114) = local_194 + 30.0;
    FUN_005c95e0(*(undefined4 *)(local_24 + 0x1a8));
    FUN_004f6ab0("misn0600.otf",DAT_0091755c,0x41000000,0);
    FUN_005cd2a0();
    fVar5 = (float10)FUN_004b1670();
    local_40 = (float)fVar5;
    *(float *)(local_24 + 0xf0) = local_40 + 30.0;
    *(undefined1 *)(local_24 + 0x82) = 1;
    *(undefined1 *)(local_24 + 0x6c) = 1;
    FUN_005cadd0(1,5);
    uVar2 = FUN_005c7e90("svartl648_howitzer");
    *(undefined4 *)(local_24 + 0x1c4) = uVar2;
    FUN_005cbc80(*(undefined4 *)(local_24 + 0x1c4),1);
    fVar5 = (float10)FUN_004b1670();
    local_f0 = (float)fVar5;
    *(float *)(local_24 + 0xe4) = local_f0 + 20.0;
  }
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(local_24 + 0x1a0) = uVar2;
  cVar1 = FUN_005c84d0(local_24 + 0x22c);
  if (cVar1 != '\0') {
    FUN_005ccfd0(*(undefined4 *)(local_24 + 0x22c),0x461c4000);
  }
  cVar1 = FUN_005c84d0(local_24 + 0x23c);
  if (cVar1 != '\0') {
    FUN_005ccfd0(*(undefined4 *)(local_24 + 0x23c),0x461c4000);
  }
  cVar1 = FUN_005c84d0(local_24 + 0x244);
  if (cVar1 != '\0') {
    FUN_005ccfd0(*(undefined4 *)(local_24 + 0x244),0x461c4000);
  }
  cVar1 = FUN_005c84d0(local_24 + 0x144);
  if (cVar1 != '\0') {
    FUN_005ccfd0(*(undefined4 *)(local_24 + 0x144),0x461c4000);
  }
  if (*(char *)(local_24 + 0x9c) == '\0') {
    uVar2 = FUN_005ca150(*(undefined4 *)(local_24 + 0x220));
    *(undefined4 *)(local_24 + 0x224) = uVar2;
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x224),
                                  *(undefined4 *)(local_24 + 0x220));
    local_48 = (float)fVar5;
    if ((local_48 < 200.0) || (cVar1 = FUN_005c84d0(local_24 + 0x220), cVar1 == '\0')) {
      if (*(char *)(local_24 + 0x85) == '\0') {
        local_34 = *(undefined4 *)(local_24 + 0x328);
        switch(local_34) {
        case 0:
          uVar2 = FUN_005c8250("svfigh",2,"pat1sp1",0,0);
          *(undefined4 *)(local_24 + 0x288) = uVar2;
          break;
        case 1:
          uVar2 = FUN_005c8250("svfigh",2,"pat1sp2",0,0);
          *(undefined4 *)(local_24 + 0x288) = uVar2;
          break;
        case 2:
          uVar2 = FUN_005c8250("svtank",2,"pat1sp3",0,0);
          *(undefined4 *)(local_24 + 0x288) = uVar2;
          break;
        case 3:
          uVar2 = FUN_005c8250("svfigh",2,"pat1sp4",0,0);
          *(undefined4 *)(local_24 + 0x288) = uVar2;
        }
        *(undefined1 *)(local_24 + 0x85) = 1;
      }
      if (*(char *)(local_24 + 0x86) == '\0') {
        local_2c = *(undefined4 *)(local_24 + 0x32c);
        switch(local_2c) {
        case 0:
          uVar2 = FUN_005c8250("svfigh",2,"pat2sp1",0,0);
          *(undefined4 *)(local_24 + 0x298) = uVar2;
          break;
        case 1:
          uVar2 = FUN_005c8250("svfigh",2,"pat2sp2",0,0);
          *(undefined4 *)(local_24 + 0x298) = uVar2;
          break;
        case 2:
          uVar2 = FUN_005c8250("svtank",2,"pat2sp3",0,0);
          *(undefined4 *)(local_24 + 0x298) = uVar2;
          break;
        case 3:
          uVar2 = FUN_005c8250("svfigh",2,"pat2sp4",0,0);
          *(undefined4 *)(local_24 + 0x298) = uVar2;
        }
        *(undefined1 *)(local_24 + 0x86) = 1;
      }
      if (*(char *)(local_24 + 0x87) == '\0') {
        local_28 = *(undefined4 *)(local_24 + 0x330);
        switch(local_28) {
        case 0:
          uVar2 = FUN_005c8250("svfigh",2,"pat3sp1",0,0);
          *(undefined4 *)(local_24 + 0x2a8) = uVar2;
          break;
        case 1:
          uVar2 = FUN_005c8250("svfigh",2,"pat3sp2",0,0);
          *(undefined4 *)(local_24 + 0x2a8) = uVar2;
          break;
        case 2:
          uVar2 = FUN_005c8250("svtank",2,"pat3sp3",0,0);
          *(undefined4 *)(local_24 + 0x2a8) = uVar2;
          break;
        case 3:
          uVar2 = FUN_005c8250("svfigh",2,"pat3sp4",0,0);
          *(undefined4 *)(local_24 + 0x2a8) = uVar2;
        }
        *(undefined1 *)(local_24 + 0x87) = 1;
      }
      if ((*(char *)(local_24 + 0x85) == '\x01') && (*(char *)(local_24 + 0x88) == '\0')) {
        FUN_005cc0c0(*(undefined4 *)(local_24 + 0x288),"patrol1",1);
        *(undefined1 *)(local_24 + 0x88) = 1;
      }
      if ((*(char *)(local_24 + 0x86) == '\x01') && (*(char *)(local_24 + 0x89) == '\0')) {
        FUN_005cc0c0(*(undefined4 *)(local_24 + 0x298),"patrol2",1);
        *(undefined1 *)(local_24 + 0x89) = 1;
      }
      if ((*(char *)(local_24 + 0x87) == '\x01') && (*(char *)(local_24 + 0x8a) == '\0')) {
        FUN_005cc0c0(*(undefined4 *)(local_24 + 0x2a8),"patrol3",1);
        *(undefined1 *)(local_24 + 0x8a) = 1;
      }
      if (*(char *)(local_24 + 0x8b) == '\0') {
        FUN_005cc0c0(*(undefined4 *)(local_24 + 0x2b8),"patrol4",1);
        FUN_005cc0c0(*(undefined4 *)(local_24 + 700),"patrol4",1);
        FUN_005cc0c0(*(undefined4 *)(local_24 + 0x2c0),"patrol4",1);
        *(undefined1 *)(local_24 + 0x8b) = 1;
      }
      *(undefined1 *)(local_24 + 0x9c) = 1;
    }
  }
  if (*(char *)(local_24 + 0x9c) == '\x01') {
    fVar5 = (float10)FUN_004b1670();
    local_148 = (float)fVar5;
    if ((*(float *)(local_24 + 0x10c) <= local_148 && local_148 != *(float *)(local_24 + 0x10c)) &&
       (*(char *)(local_24 + 0x90) == '\0')) {
      fVar5 = (float10)FUN_004b1670();
      local_50 = (float)fVar5;
      *(float *)(local_24 + 0x10c) = local_50 + 2.0;
      cVar1 = FUN_005c84d0(local_24 + 0x288);
      if ((cVar1 != '\0') &&
         (iVar4 = FUN_005ca150(*(undefined4 *)(local_24 + 0x288)), (float)iVar4 < 450.0)) {
        uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_24 + 0x288),0);
        *(undefined4 *)(local_24 + 0x28c) = uVar2;
        *(undefined1 *)(local_24 + 0x90) = 1;
        FUN_005cc0c0(*(undefined4 *)(local_24 + 0x28c),"patrol1",1);
      }
    }
    fVar5 = (float10)FUN_004b1670();
    local_f8 = (float)fVar5;
    if ((*(float *)(local_24 + 0x110) <= local_f8 && local_f8 != *(float *)(local_24 + 0x110)) &&
       (*(char *)(local_24 + 0x92) == '\0')) {
      fVar5 = (float10)FUN_004b1670();
      local_58 = (float)fVar5;
      *(float *)(local_24 + 0x110) = local_58 + 2.0;
      cVar1 = FUN_005c84d0(local_24 + 0x298);
      if ((cVar1 != '\0') &&
         (iVar4 = FUN_005ca150(*(undefined4 *)(local_24 + 0x298)), (float)iVar4 < 450.0)) {
        uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x298),0);
        *(undefined4 *)(local_24 + 0x29c) = uVar2;
        *(undefined1 *)(local_24 + 0x92) = 1;
        FUN_005cc0c0(*(undefined4 *)(local_24 + 0x29c),"patrol2",1);
      }
    }
    fVar5 = (float10)FUN_004b1670();
    local_188 = (float)fVar5;
    if ((*(float *)(local_24 + 0x114) <= local_188 && local_188 != *(float *)(local_24 + 0x114)) &&
       (*(char *)(local_24 + 0x93) == '\0')) {
      fVar5 = (float10)FUN_004b1670();
      local_60 = (float)fVar5;
      *(float *)(local_24 + 0x114) = local_60 + 2.0;
      iVar4 = FUN_005ca150(*(undefined4 *)(local_24 + 0x2a8));
      if ((float)iVar4 < 450.0) {
        uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x2a8),0);
        *(undefined4 *)(local_24 + 0x2ac) = uVar2;
        *(undefined1 *)(local_24 + 0x93) = 1;
        FUN_005cc0c0(*(undefined4 *)(local_24 + 0x2ac),"patrol3",1);
      }
    }
  }
  cVar1 = FUN_005c84d0(local_24 + 0x1b0);
  if ((cVar1 == '\0') && (*(char *)(local_24 + 0x6a) == '\0')) {
    uVar2 = FUN_00437d30("misn0653.wav");
    *(undefined4 *)(local_24 + 0x280) = uVar2;
    uVar2 = FUN_00437d30("misn0651.wav");
    *(undefined4 *)(local_24 + 0x284) = uVar2;
    *(undefined1 *)(local_24 + 0x6a) = 1;
  }
  if (((*(char *)(local_24 + 0x6a) == '\x01') &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x280)), cVar1 != '\0')) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x284)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("misn06l5.des");
    FUN_0045c0f0((float)fVar5);
  }
  if (*(char *)(local_24 + 0x82) == '\x01') {
    FUN_005cd300("openingcampath",1000,500,*(undefined4 *)(local_24 + 600));
    FUN_005ccfd0(*(undefined4 *)(local_24 + 600),0x42480000);
    FUN_005ccfd0(*(undefined4 *)(local_24 + 0x25c),0x42480000);
    FUN_005ccfd0(*(undefined4 *)(local_24 + 0x264),0x42480000);
    FUN_005ccfd0(*(undefined4 *)(local_24 + 0x270),0x42480000);
    FUN_005ccfd0(*(undefined4 *)(local_24 + 0x27c),0x42480000);
  }
  if (*(char *)(local_24 + 0x82) == '\x01') {
    fVar5 = (float10)FUN_004b1670();
    local_100 = (float)fVar5;
    if (((*(float *)(local_24 + 0xf0) <= local_100 && local_100 != *(float *)(local_24 + 0xf0)) &&
        (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x35c)), cVar1 != '\0')) ||
       (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
      FUN_00437d80(*(undefined4 *)(local_24 + 0x35c));
      *(undefined4 *)(local_24 + 0x35c) = 0;
      FUN_005cd4e0();
      *(undefined1 *)(local_24 + 0x82) = 0;
      cVar1 = FUN_005c84d0(local_24 + 0x2d0);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x2d0));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x2d4);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x2d4));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x2d8);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x2d8));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x2dc);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x2dc));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x21c);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x21c));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x254);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x254));
      }
      cVar1 = FUN_005c84d0(local_24 + 600);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 600));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x25c);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x25c));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x260);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x260));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x264);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x264));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x268);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x268));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x26c);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x26c));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x270);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x270));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x274);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x274));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x278);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x278));
      }
      cVar1 = FUN_005c84d0(local_24 + 0x27c);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_24 + 0x27c));
      }
    }
  }
  if (*(char *)(local_24 + 0x6c) == '\x01') {
    FUN_004f6aa0();
    if ((*(char *)(local_24 + 0x95) == '\x01') && (*(char *)(local_24 + 0x6b) == '\x01')) {
      FUN_004f6ab0("misn0606.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0605.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0604.otf",DAT_009175b0,0x41000000,0);
    }
    if ((*(char *)(local_24 + 0x95) == '\x01') && (*(char *)(local_24 + 0x6b) == '\0')) {
      FUN_004f6ab0("misn0606.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misn0605.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0604.otf",DAT_009175b0,0x41000000,0);
    }
    if ((*(char *)(local_24 + 0x77) == '\x01') && (*(char *)(local_24 + 0x95) == '\0')) {
      FUN_004f6ab0("misn0605.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misn0604.otf",DAT_009175b0,0x41000000,0);
    }
    if (((*(char *)(local_24 + 99) == '\x01') && (*(char *)(local_24 + 0x75) == '\0')) &&
       (*(char *)(local_24 + 0x70) == '\0')) {
      FUN_004f6ab0("misn0604.otf",DAT_0091755c,0x41000000,0);
    }
    if ((*(char *)(local_24 + 0x6f) == '\x01') && (*(char *)(local_24 + 99) == '\0')) {
      FUN_004f6ab0("misn0603.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misn0602.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0601.otf",DAT_009175b0,0x41000000,0);
    }
    if ((*(char *)(local_24 + 0x6d) == '\x01') && (*(char *)(local_24 + 0x6f) == '\0')) {
      FUN_004f6ab0("misn0602.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misn0601.otf",DAT_009175b0,0x41000000,0);
    }
    if (((*(char *)(local_24 + 0x66) == '\x01') && (*(char *)(local_24 + 0x6d) == '\0')) &&
       (*(char *)(local_24 + 0x98) == '\0')) {
      FUN_004f6ab0("misn0601.otf",DAT_0091755c,0x41000000,0);
    }
    if (*(char *)(local_24 + 0xaa) == '\x01') {
      FUN_004f6ab0("misn0600.otf",DAT_0091755c,0x41000000,0);
    }
    *(undefined1 *)(local_24 + 0x6c) = 0;
  }
  if (*(char *)(local_24 + 0x66) == '\0') {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x144),
                                  *(undefined4 *)(local_24 + 0x1a0));
    local_68 = (float)fVar5;
    if (local_68 < 1000.0) {
      uVar2 = FUN_00437d30("misn0602.wav");
      *(undefined4 *)(local_24 + 0x1d4) = uVar2;
      *(undefined1 *)(local_24 + 0x66) = 1;
    }
  }
  if (((*(char *)(local_24 + 0xb5) == '\0') && (*(char *)(local_24 + 0x66) == '\x01')) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x1d4)), cVar1 != '\0')) {
    FUN_005c95e0(*(undefined4 *)(local_24 + 0x144));
    FUN_005c9640(*(undefined4 *)(local_24 + 0x144),"Object");
    *(undefined1 *)(local_24 + 0x6c) = 1;
    *(undefined1 *)(local_24 + 0xb5) = 1;
    fVar5 = (float10)FUN_004b1670();
    local_150 = (float)fVar5;
    *(float *)(local_24 + 0x11c) = local_150 + 60.0;
  }
  if (((*(char *)(local_24 + 0x66) == '\x01') && (*(char *)(local_24 + 0x6d) == '\0')) &&
     (*(char *)(local_24 + 0x98) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    local_70 = (float)fVar5;
    if (*(float *)(local_24 + 0x11c) <= local_70 && local_70 != *(float *)(local_24 + 0x11c)) {
      if (*(int *)(local_24 + 0x338) < 2) {
        uVar2 = FUN_00437d30("misn0690.wav");
        *(undefined4 *)(local_24 + 0x358) = uVar2;
        fVar5 = (float10)FUN_004b1670();
        local_108 = (float)fVar5;
        *(float *)(local_24 + 0x11c) = local_108 + 20.0;
        *(int *)(local_24 + 0x338) = *(int *)(local_24 + 0x338) + 1;
      }
      else if (*(char *)(local_24 + 0xb2) == '\0') {
        uVar2 = FUN_00437d30("misn0694.wav");
        *(undefined4 *)(local_24 + 0x358) = uVar2;
        *(undefined1 *)(local_24 + 0xb2) = 1;
      }
    }
  }
  if ((*(char *)(local_24 + 0xb2) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x358)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("misn06l1.des");
    local_78 = (float)fVar5;
    FUN_0045c0f0(local_78 + 0.0);
  }
  if (*(char *)(local_24 + 0x6d) == '\0') {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x1a0),
                                  *(undefined4 *)(local_24 + 0x144));
    local_178 = (float)fVar5;
    if ((local_178 < 125.0) && (*(char *)(local_24 + 0x98) == '\0')) {
      FUN_00437d80(*(undefined4 *)(local_24 + 0x358));
      uVar2 = FUN_00437d30("misn0603.wav");
      *(undefined4 *)(local_24 + 0x184) = uVar2;
      uVar2 = FUN_00437d30("misn0604.wav");
      *(undefined4 *)(local_24 + 0x188) = uVar2;
      *(undefined1 *)(local_24 + 0x6d) = 1;
      FUN_005c9610(*(undefined4 *)(local_24 + 0x144));
      FUN_005cd2a0();
      fVar5 = (float10)FUN_004b1670();
      local_80 = (float)fVar5;
      *(float *)(local_24 + 0xf4) = local_80 + 12.0;
      *(undefined1 *)(local_24 + 0x83) = 1;
    }
  }
  fVar5 = (float10)FUN_004b1670();
  local_110 = (float)fVar5;
  if ((*(float *)(local_24 + 0x120) <= local_110 && local_110 != *(float *)(local_24 + 0x120)) &&
     (*(char *)(local_24 + 0x98) == '\0')) {
    if (*(int *)(local_24 + 0x33c) < 2) {
      uVar2 = FUN_00437d30("misn0691.wav");
      *(undefined4 *)(local_24 + 0x344) = uVar2;
      *(int *)(local_24 + 0x33c) = *(int *)(local_24 + 0x33c) + 1;
      fVar5 = (float10)FUN_004b1670();
      local_88 = (float)fVar5;
      *(float *)(local_24 + 0x120) = local_88 + 10.0;
    }
    else if (*(char *)(local_24 + 0x62) == '\0') {
      uVar2 = FUN_00437d30("misn0694.wav");
      *(undefined4 *)(local_24 + 0x344) = uVar2;
      *(undefined1 *)(local_24 + 0x62) = 1;
    }
  }
  if ((*(char *)(local_24 + 0x62) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x344)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("misn06l2.des");
    local_158 = (float)fVar5;
    FUN_0045c0f0(local_158 + 0.0);
  }
  cVar1 = FUN_005cd610("obheph");
  if ((cVar1 == '\x01') && (*(char *)(local_24 + 0x98) == '\0')) {
    FUN_00437d80(*(undefined4 *)(local_24 + 0x344));
    fVar5 = (float10)FUN_004b1670();
    local_90 = (float)fVar5;
    *(float *)(local_24 + 0xc0) = local_90 + 5.0;
    *(undefined1 *)(local_24 + 0x98) = 1;
    *(undefined1 *)(local_24 + 0x6d) = 1;
    FUN_005c9610(*(undefined4 *)(local_24 + 0x144));
    *(undefined1 *)(local_24 + 0x6c) = 1;
  }
  if (*(char *)(local_24 + 0x6f) == '\0') {
    fVar5 = (float10)FUN_004b1670();
    local_118 = (float)fVar5;
    if (*(float *)(local_24 + 0xc0) <= local_118 && local_118 != *(float *)(local_24 + 0xc0)) {
      uVar2 = FUN_00437d30("misn0605.wav");
      *(undefined4 *)(local_24 + 0x1d8) = uVar2;
      *(undefined1 *)(local_24 + 0xaa) = 0;
      *(undefined1 *)(local_24 + 0x6f) = 1;
      *(undefined1 *)(local_24 + 0x73) = 1;
      fVar5 = (float10)FUN_004b1670();
      local_98 = (float)fVar5;
      *(float *)(local_24 + 0x124) = local_98 + 80.0;
    }
  }
  if ((*(char *)(local_24 + 0x73) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x1d8)), cVar1 != '\0')) {
    FUN_005c9610(*(undefined4 *)(local_24 + 0x1a8));
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam1spawn",0,0);
    *(undefined4 *)(local_24 + 0x1bc) = uVar2;
    FUN_005c9640(*(undefined4 *)(local_24 + 0x1bc),"Starport");
    *(undefined1 *)(local_24 + 0x73) = 0;
    *(undefined1 *)(local_24 + 0x6c) = 1;
  }
  fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x1a0),*(undefined4 *)(local_24 + 0x1ac))
  ;
  local_198 = (float)fVar5;
  if ((local_198 < 420.0) && (*(char *)(local_24 + 0x67) == '\0')) {
    FUN_00437d30("misn0636.wav");
    *(undefined1 *)(local_24 + 0x67) = 1;
  }
  cVar1 = FUN_005cd610("obstp1");
  if ((cVar1 == '\x01') && (*(char *)(local_24 + 0x56) == '\0')) {
    *(undefined1 *)(local_24 + 0x56) = 1;
  }
  cVar1 = FUN_005cd610("obstp8");
  if ((cVar1 == '\x01') && (*(char *)(local_24 + 0x5a) == '\0')) {
    *(undefined1 *)(local_24 + 0x5a) = 1;
  }
  cVar1 = FUN_005cd610("obstp3");
  if ((cVar1 == '\x01') && (*(char *)(local_24 + 0x5c) == '\0')) {
    *(undefined1 *)(local_24 + 0x5c) = 1;
  }
  if ((*(char *)(local_24 + 0x9b) == '\0') && (*(float *)(local_24 + 0x134) == 4.0)) {
    *(undefined1 *)(local_24 + 0x9b) = 1;
    uVar2 = FUN_00437d30("misn0694.wav");
    *(undefined4 *)(local_24 + 0x2cc) = uVar2;
  }
  if ((*(char *)(local_24 + 0x9b) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x2cc)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("misn06l6.des");
    local_a0 = (float)fVar5;
    FUN_0045c0f0(local_a0 + 0.0);
  }
  if (*(char *)(local_24 + 99) == '\0') {
    fVar5 = (float10)FUN_004b1670();
    local_120 = (float)fVar5;
    if (((*(float *)(local_24 + 0x138) <= local_120 && local_120 != *(float *)(local_24 + 0x138)) &&
        (*(char *)(local_24 + 0x9b) == '\0')) &&
       (*(float *)(local_24 + 0x134) <= 4.0 && *(float *)(local_24 + 0x134) != 4.0)) {
      FUN_00437d30("misn0654.wav");
      fVar5 = (float10)FUN_004b1670();
      local_a8 = (float)fVar5;
      *(float *)(local_24 + 0x138) = local_a8 + 15.0;
      *(float *)(local_24 + 0x134) = *(float *)(local_24 + 0x134) + 1.0;
    }
  }
  if (((*(char *)(local_24 + 0x56) == '\x01') && (*(char *)(local_24 + 0x5a) == '\x01')) &&
     ((*(char *)(local_24 + 0x5c) == '\x01' && (*(char *)(local_24 + 99) == '\0')))) {
    uVar2 = FUN_00437d30("misn0650.wav");
    *(undefined4 *)(local_24 + 0x1dc) = uVar2;
    uVar2 = FUN_00437d30("misn0606.wav");
    *(undefined4 *)(local_24 + 0x1e0) = uVar2;
    uVar2 = FUN_00437d30("misn0607.wav");
    *(undefined4 *)(local_24 + 0x1e4) = uVar2;
    *(undefined1 *)(local_24 + 99) = 1;
    fVar5 = (float10)FUN_004b1670();
    local_160 = (float)fVar5;
    *(float *)(local_24 + 0x130) = local_160 + 15.0;
  }
  if (((*(char *)(local_24 + 0x59) == '\0') && (*(char *)(local_24 + 99) == '\x01')) &&
     ((cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x1dc)), cVar1 != '\0' &&
      ((cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x1e0)), cVar1 != '\0' &&
       (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x1e4)), cVar1 != '\0')))))) {
    *(undefined1 *)(local_24 + 0x6c) = 1;
    *(undefined1 *)(local_24 + 0x59) = 1;
  }
  if (*(char *)(local_24 + 0x55) == '\0') {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x244),
                                  *(undefined4 *)(local_24 + 0x1a0));
    local_b0 = (float)fVar5;
    if (local_b0 < 200.0) {
      FUN_00437d30("misn0608.wav");
      fVar5 = (float10)FUN_004b1670();
      local_128 = (float)fVar5;
      *(float *)(local_24 + 0xbc) = local_128 + 15.0;
      *(undefined1 *)(local_24 + 0x55) = 1;
      fVar5 = (float10)FUN_004b1670();
      local_b8 = (float)fVar5;
      *(float *)(local_24 + 0x138) = local_b8 + 20.0;
    }
  }
  if ((*(char *)(local_24 + 0x6f) == '\x01') && (*(char *)(local_24 + 0x55) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    local_180 = (float)fVar5;
    if ((*(float *)(local_24 + 0x124) <= local_180 && local_180 != *(float *)(local_24 + 0x124)) &&
       (*(int *)(local_24 + 0x340) < 3)) {
      FUN_00437d30("misn0695.wav");
      fVar5 = (float10)FUN_004b1670();
      local_c0 = (float)fVar5;
      *(float *)(local_24 + 0x124) = local_c0 + 40.0;
      *(int *)(local_24 + 0x340) = *(int *)(local_24 + 0x340) + 1;
    }
  }
  if (*(int *)(local_24 + 0x340) == 3) {
    fVar5 = (float10)FUN_004b1670();
    local_130 = (float)fVar5;
    if ((*(float *)(local_24 + 0x124) <= local_130 && local_130 != *(float *)(local_24 + 0x124)) &&
       (*(char *)(local_24 + 0xb1) == '\0')) {
      *(undefined1 *)(local_24 + 0xb1) = 1;
      uVar2 = FUN_00437d30("misn0694.wav");
      *(undefined4 *)(local_24 + 0x348) = uVar2;
    }
  }
  if ((*(char *)(local_24 + 0xb1) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x348)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("misn06l3.des");
    local_c8 = (float)fVar5;
    FUN_0045c0f0(local_c8 + 0.0);
  }
  if (*(char *)(local_24 + 0x71) == '\0') {
    fVar5 = (float10)FUN_004b1670();
    local_168 = (float)fVar5;
    if (*(float *)(local_24 + 0xe4) <= local_168 && local_168 != *(float *)(local_24 + 0xe4)) {
      uVar2 = FUN_005ca150(*(undefined4 *)(local_24 + 0x210));
      *(undefined4 *)(local_24 + 0x18c) = uVar2;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x18c),
                                    *(undefined4 *)(local_24 + 0x210));
      local_d0 = (float)fVar5;
      if (local_d0 < 410.0) {
        FUN_005cb820(*(undefined4 *)(local_24 + 0x210),*(undefined4 *)(local_24 + 0x18c),1);
        FUN_005cb820(*(undefined4 *)(local_24 + 0x214),*(undefined4 *)(local_24 + 0x18c),1);
        FUN_005cb620(*(undefined4 *)(local_24 + 0x214),1);
        *(undefined1 *)(local_24 + 0x71) = 1;
        fVar5 = (float10)FUN_004b1670();
        local_138 = (float)fVar5;
        *(float *)(local_24 + 0x130) = local_138 - 1.0;
      }
      fVar5 = (float10)FUN_004b1670();
      local_d8 = (float)fVar5;
      *(float *)(local_24 + 0xe4) = local_d8 + 1.5;
    }
  }
  if ((*(char *)(local_24 + 99) == '\x01') && (*(char *)(local_24 + 0x71) == '\0')) {
    FUN_005cb820(*(undefined4 *)(local_24 + 0x210),*(undefined4 *)(local_24 + 0x1a0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x214),*(undefined4 *)(local_24 + 0x1a0),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x210),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x214),1);
    *(undefined1 *)(local_24 + 0x71) = 1;
  }
  fVar5 = (float10)FUN_005c9800(*(undefined4 *)(local_24 + 0x210),"cam1spawn",0);
  local_190 = (float)fVar5;
  if (400.0 <= local_190) {
    fVar5 = (float10)FUN_005c9800(*(undefined4 *)(local_24 + 0x214),"cam1spawn",0);
    local_38 = (float)fVar5;
    if (400.0 <= local_38) goto LAB_005260b6;
  }
  if ((*(char *)(local_24 + 0x71) == '\x01') && (*(char *)(local_24 + 0x81) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    local_140 = (float)fVar5;
    if ((*(float *)(local_24 + 0x130) <= local_140 && local_140 != *(float *)(local_24 + 0x130)) &&
       (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x1e4)), cVar1 != '\0')) {
      uVar2 = FUN_00437d30("misn0611.wav");
      *(undefined4 *)(local_24 + 400) = uVar2;
      FUN_005cd2a0();
      fVar5 = (float10)FUN_004b1670();
      local_e8 = (float)fVar5;
      *(float *)(local_24 + 0xf8) = local_e8 + 5.0;
      *(undefined1 *)(local_24 + 0x84) = 1;
      *(undefined1 *)(local_24 + 0x71) = 0;
      *(undefined1 *)(local_24 + 0x81) = 1;
    }
  }
LAB_005260b6:
  if (*(char *)(local_24 + 0x83) == '\x01') {
    FUN_005cd300("cam1path",*(undefined4 *)(local_24 + 0x324),1000,*(undefined4 *)(local_24 + 0x144)
                );
    *(int *)(local_24 + 0x324) = *(int *)(local_24 + 0x324) + 0xf;
  }
  if ((*(char *)(local_24 + 0x83) == '\x01') &&
     (((cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x184)), cVar1 != '\0' &&
       (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x188)), cVar1 != '\0')) ||
      (cVar1 = FUN_005cd560(), cVar1 != '\0')))) {
    FUN_005cd4e0();
    *(undefined1 *)(local_24 + 0x83) = 0;
    FUN_00437d80(*(undefined4 *)(local_24 + 0x184));
    FUN_00437d80(*(undefined4 *)(local_24 + 0x188));
    *(undefined1 *)(local_24 + 0x6c) = 1;
    fVar5 = (float10)FUN_004b1670();
    local_170 = (float)fVar5;
    *(float *)(local_24 + 0x120) = local_170 + 20.0;
  }
  if (*(char *)(local_24 + 0x84) == '\x01') {
    FUN_005cd440(*(undefined4 *)(local_24 + 0x210),300,100,0xfffffc7c,
                 *(undefined4 *)(local_24 + 0x210));
  }
  if (((*(char *)(local_24 + 0x84) == '\x01') &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 400)), cVar1 != '\0')) ||
     (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
    FUN_005cd4e0();
    if (*(char *)(local_24 + 0x84) == '\0') {
      *(undefined1 *)(local_24 + 0xa4) = 0;
    }
    *(undefined1 *)(local_24 + 0x84) = 0;
  }
  if (*(char *)(local_24 + 0x74) == '\0') {
    FUN_005c84d0(local_24 + 0x210);
    FUN_005c84d0(local_24 + 0x210);
  }
  cVar1 = FUN_005c84d0(local_24 + 0x210);
  if (((cVar1 == '\0') && (cVar1 = FUN_005c84d0(local_24 + 0x214), cVar1 == '\0')) &&
     ((*(char *)(local_24 + 0x74) == '\0' && (*(char *)(local_24 + 99) == '\x01')))) {
    uVar2 = FUN_00437d30("misn0612.wav");
    *(undefined4 *)(local_24 + 0x2c4) = uVar2;
    uVar2 = FUN_00437d30("misn0613.wav");
    *(undefined4 *)(local_24 + 0x2c8) = uVar2;
    fVar5 = (float10)FUN_004b1670();
    local_3c = (float)fVar5;
    *(float *)(local_24 + 0xc4) = local_3c + 50.0;
    *(undefined1 *)(local_24 + 0x75) = 1;
    *(undefined1 *)(local_24 + 0x70) = 1;
    *(undefined1 *)(local_24 + 0x74) = 1;
    fVar5 = (float10)FUN_004b1670();
    local_44 = (float)fVar5;
    *(float *)(local_24 + 0xfc) = local_44 + 60.0;
    fVar5 = (float10)FUN_004b1670();
    local_4c = (float)fVar5;
    *(float *)(local_24 + 0x100) = local_4c + 180.0;
    fVar5 = (float10)FUN_004b1670();
    local_54 = (float)fVar5;
    *(float *)(local_24 + 0x104) = local_54 + 300.0;
  }
  if ((((*(char *)(local_24 + 0xab) == '\0') && (*(char *)(local_24 + 0x74) == '\x01')) &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x2c4)), cVar1 != '\0')) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x2c8)), cVar1 != '\0')) {
    *(undefined1 *)(local_24 + 0xab) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  local_5c = (float)fVar5;
  if (((*(float *)(local_24 + 0xfc) <= local_5c && local_5c != *(float *)(local_24 + 0xfc)) &&
      (*(char *)(local_24 + 0x8c) == '\0')) &&
     (cVar1 = FUN_005c84d0(local_24 + 0x1b4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x1c8) = uVar2;
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x1cc) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x1d0) = uVar2;
    FUN_005cb820(*(undefined4 *)(local_24 + 0x1c8),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x1cc),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x1d0),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x1c8),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x1cc),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x1d0),1);
    *(undefined1 *)(local_24 + 0x8c) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  local_64 = (float)fVar5;
  if (((*(float *)(local_24 + 0x100) <= local_64 && local_64 != *(float *)(local_24 + 0x100)) &&
      (*(char *)(local_24 + 0x8d) == '\0')) &&
     (cVar1 = FUN_005c84d0(local_24 + 0x1b4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x1f8) = uVar2;
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x1fc) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x200) = uVar2;
    FUN_005cb820(*(undefined4 *)(local_24 + 0x1f8),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x1fc),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x200),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x1f8),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x1fc),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x200),1);
    *(undefined1 *)(local_24 + 0x8d) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  local_6c = (float)fVar5;
  if (((*(float *)(local_24 + 0x104) <= local_6c && local_6c != *(float *)(local_24 + 0x104)) &&
      (*(char *)(local_24 + 0x8e) == '\0')) &&
     (cVar1 = FUN_005c84d0(local_24 + 0x1b4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x204) = uVar2;
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x208) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x1b4),0);
    *(undefined4 *)(local_24 + 0x20c) = uVar2;
    FUN_005cb820(*(undefined4 *)(local_24 + 0x204),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x208),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x20c),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x204),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x208),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x20c),1);
    *(undefined1 *)(local_24 + 0x8e) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  local_74 = (float)fVar5;
  if ((*(float *)(local_24 + 0xc4) <= local_74 && local_74 != *(float *)(local_24 + 0xc4)) &&
     (*(char *)(local_24 + 0x75) == '\x01')) {
    uVar2 = FUN_00437d30("misn0614.wav");
    *(undefined4 *)(local_24 + 0x1e8) = uVar2;
    uVar2 = FUN_00437d30("misn0628.wav");
    *(undefined4 *)(local_24 + 0x1ec) = uVar2;
    fVar5 = (float10)FUN_004b1670();
    local_7c = (float)fVar5;
    *(float *)(local_24 + 0x108) = local_7c + 60.0;
    fVar5 = (float10)FUN_004b1670();
    local_84 = (float)fVar5;
    *(float *)(local_24 + 200) = local_84 + 60.0;
    fVar5 = (float10)FUN_004b1670();
    local_8c = (float)fVar5;
    *(float *)(local_24 + 0xcc) = local_8c + 90.0;
    fVar5 = (float10)FUN_004b1670();
    local_94 = (float)fVar5;
    *(float *)(local_24 + 0xd0) = local_94 + 1410.0;
    fVar5 = (float10)FUN_004b1670();
    local_9c = (float)fVar5;
    *(float *)(local_24 + 0xdc) = local_9c + 390.0;
    fVar5 = (float10)FUN_004b1670();
    local_a4 = (float)fVar5;
    *(float *)(local_24 + 0xd8) = local_a4 + 810.0;
    fVar5 = (float10)FUN_004b1670();
    local_ac = (float)fVar5;
    *(float *)(local_24 + 0xe0) = local_ac + 1110.0;
    fVar5 = (float10)FUN_004b1670();
    local_b4 = (float)fVar5;
    *(float *)(local_24 + 0xec) = local_b4 + 1260.0;
    *(undefined1 *)(local_24 + 0x75) = 0;
    *(undefined1 *)(local_24 + 0x76) = 1;
    *(undefined1 *)(local_24 + 0x7b) = 1;
    *(undefined1 *)(local_24 + 0x7a) = 1;
    *(undefined1 *)(local_24 + 0x7c) = 1;
    *(undefined1 *)(local_24 + 0x7d) = 1;
    *(undefined1 *)(local_24 + 0x7e) = 1;
    *(undefined1 *)(local_24 + 0x6c) = 1;
    fVar5 = (float10)FUN_004b1670();
    local_bc = (float)fVar5;
    *(float *)(local_24 + 300) = local_bc + 27.42;
    *(undefined1 *)(local_24 + 0x80) = 1;
  }
  if (((*(char *)(local_24 + 0x77) == '\0') && (*(char *)(local_24 + 0x80) == '\x01')) &&
     ((cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x1e8)), cVar1 != '\0' &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x1ec)), cVar1 != '\0')))) {
    *(undefined1 *)(local_24 + 0x77) = 1;
    FUN_004f6ae0(0x21c,0x168,0xb4);
    FUN_005c95e0(*(undefined4 *)(local_24 + 0x1b8));
    *(undefined1 *)(local_24 + 0x6c) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  local_c4 = (float)fVar5;
  if (((*(float *)(local_24 + 0xdc) <= local_c4 && local_c4 != *(float *)(local_24 + 0xdc)) &&
      (*(char *)(local_24 + 0x7b) == '\x01')) && (*(char *)(local_24 + 0x8f) == '\0')) {
    uVar2 = FUN_005ca150(*(undefined4 *)(local_24 + 0x1a0));
    *(undefined4 *)(local_24 + 0x2e0) = uVar2;
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x2e0),
                                  *(undefined4 *)(local_24 + 0x1a0));
    local_cc = (float)fVar5;
    if (400.0 < local_cc) {
      uVar2 = FUN_005c8250("avtank",3,&DAT_0087f25c,0,0);
      *(undefined4 *)(local_24 + 0x148) = uVar2;
      uVar2 = FUN_005c8250("avtank",3,&DAT_0087f27c,0,0);
      *(undefined4 *)(local_24 + 0x14c) = uVar2;
      uVar2 = FUN_005c8250("avtank",3,&DAT_0087f274,0,0);
      *(undefined4 *)(local_24 + 0x150) = uVar2;
      uVar2 = FUN_005c8250("avtank",3,&DAT_0087f28c,0,0);
      *(undefined4 *)(local_24 + 0x154) = uVar2;
      uVar2 = FUN_005c8250("avtank",3,&DAT_0087f284,0,0);
      *(undefined4 *)(local_24 + 0x158) = uVar2;
      uVar2 = FUN_005c8250("avfigh",3,&DAT_0087f29c,0,0);
      *(undefined4 *)(local_24 + 0x15c) = uVar2;
      uVar2 = FUN_005c8250("avfigh",3,&DAT_0087f294,0,0);
      *(undefined4 *)(local_24 + 0x160) = uVar2;
      uVar2 = FUN_005c8250("avfigh",3,&DAT_0087f200,0,0);
      *(undefined4 *)(local_24 + 0x164) = uVar2;
      uVar2 = FUN_005c8250("avfigh",3,&DAT_0087f1f8,0,0);
      *(undefined4 *)(local_24 + 0x168) = uVar2;
      uVar2 = FUN_005c8250("avfigh",3,"sim10",0,0);
      *(undefined4 *)(local_24 + 0x16c) = uVar2;
      FUN_005cb960(*(undefined4 *)(local_24 + 0x148),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x14c),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x150),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x154),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x158),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x15c),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x160),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x164),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x168),"simpoint5",1);
      FUN_005cb960(*(undefined4 *)(local_24 + 0x16c),"simpoint5",1);
      FUN_005cd2a0();
      uVar2 = FUN_00437d30("misn0631.wav");
      *(undefined4 *)(local_24 + 0x170) = uVar2;
      uVar2 = FUN_00437d30("misn0642.wav");
      *(undefined4 *)(local_24 + 0x174) = uVar2;
      uVar2 = FUN_00437d30("misn0643.wav");
      *(undefined4 *)(local_24 + 0x178) = uVar2;
      uVar2 = FUN_00437d30("misn0644.wav");
      *(undefined4 *)(local_24 + 0x17c) = uVar2;
      uVar2 = FUN_00437d30("misn0645.wav");
      *(undefined4 *)(local_24 + 0x180) = uVar2;
      *(undefined1 *)(local_24 + 0xa4) = 1;
      *(undefined1 *)(local_24 + 0x7b) = 0;
      FUN_004ff160();
    }
  }
  if (((*(char *)(local_24 + 0xa4) == '\x01') &&
      (FUN_005cd440(*(undefined4 *)(local_24 + 0x158),0,1000,0xfffff060,
                    *(undefined4 *)(local_24 + 0x158)), *(char *)(local_24 + 0xa7) == '\0')) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x17c)), cVar1 != '\0')) {
    FUN_005cb960(*(undefined4 *)(local_24 + 0x148),"simpoint1",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x14c),"simpoint1",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x154),"simpoint1",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x160),"simpoint1",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x150),"simpoint3",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x15c),"simpoint3",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x16c),"simpoint3",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x158),"simpoint5",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x164),"simpoint5",1);
    FUN_005cb960(*(undefined4 *)(local_24 + 0x168),"simpoint5",1);
    *(undefined1 *)(local_24 + 0xa7) = 1;
  }
  if ((*(char *)(local_24 + 0xa4) == '\x01') && (*(char *)(local_24 + 0xa6) == '\0')) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x170));
    if (cVar1 != '\0') {
      *(undefined1 *)(local_24 + 0xad) = 1;
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x174));
    if (cVar1 != '\0') {
      *(undefined1 *)(local_24 + 0xae) = 1;
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x178));
    if (cVar1 != '\0') {
      *(undefined1 *)(local_24 + 0xb0) = 1;
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x17c));
    if (cVar1 != '\0') {
      *(undefined1 *)(local_24 + 0xb3) = 1;
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x180));
    if (cVar1 != '\0') {
      *(undefined1 *)(local_24 + 0xb4) = 1;
    }
    if (((((*(char *)(local_24 + 0xad) != '\0') && (*(char *)(local_24 + 0xae) != '\0')) &&
         (*(char *)(local_24 + 0xb0) != '\0')) &&
        ((*(char *)(local_24 + 0xb3) != '\0' && (*(char *)(local_24 + 0xb4) != '\0')))) ||
       (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
      FUN_005cd4e0();
      *(undefined1 *)(local_24 + 0xa6) = 1;
      *(undefined1 *)(local_24 + 0xa4) = 0;
      FUN_00437d80(*(undefined4 *)(local_24 + 0x170));
      FUN_00437d80(*(undefined4 *)(local_24 + 0x174));
      FUN_00437d80(*(undefined4 *)(local_24 + 0x178));
      FUN_00437d80(*(undefined4 *)(local_24 + 0x17c));
      FUN_00437d80(*(undefined4 *)(local_24 + 0x180));
    }
  }
  if ((*(char *)(local_24 + 0xa6) == '\x01') && (*(char *)(local_24 + 0xa5) == '\0')) {
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x148));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x14c));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x150));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x154));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x158));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x15c));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x160));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x164));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x168));
    FUN_005c83e0(*(undefined4 *)(local_24 + 0x16c));
    *(undefined1 *)(local_24 + 0xa5) = 1;
    FUN_004ff150();
    FUN_004ff160();
  }
  fVar5 = (float10)FUN_004b1670();
  local_d4 = (float)fVar5;
  if ((((*(float *)(local_24 + 0xd8) <= local_d4 && local_d4 != *(float *)(local_24 + 0xd8)) &&
       (*(char *)(local_24 + 0x7a) == '\x01')) && (*(char *)(local_24 + 0x8f) == '\0')) &&
     (*(char *)(local_24 + 0x99) == '\0')) {
    FUN_00437d30("misn0632.wav");
    *(undefined1 *)(local_24 + 0x7a) = 0;
  }
  fVar5 = (float10)FUN_004b1670();
  local_dc = (float)fVar5;
  if (((*(float *)(local_24 + 0xe0) <= local_dc && local_dc != *(float *)(local_24 + 0xe0)) &&
      (*(char *)(local_24 + 0x7c) == '\x01')) &&
     ((*(char *)(local_24 + 0x8f) == '\0' && (*(char *)(local_24 + 0x99) == '\0')))) {
    FUN_00437d30("misn0633.wav");
    *(undefined1 *)(local_24 + 0x7c) = 0;
  }
  fVar5 = (float10)FUN_004b1670();
  local_e4 = (float)fVar5;
  if (((*(float *)(local_24 + 0xec) <= local_e4 && local_e4 != *(float *)(local_24 + 0xec)) &&
      (*(char *)(local_24 + 0x7d) == '\x01')) &&
     ((*(char *)(local_24 + 0x8f) == '\0' && (*(char *)(local_24 + 0x99) == '\0')))) {
    FUN_00437d30("misn0634.wav");
    *(undefined1 *)(local_24 + 0x7d) = 0;
  }
  fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x1a0),*(undefined4 *)(local_24 + 0x1b4))
  ;
  local_ec = (float)fVar5;
  if (((local_ec < 250.0) && (*(char *)(local_24 + 0x99) == '\0')) &&
     (*(char *)(local_24 + 0x8f) == '\0')) {
    FUN_00437d30("misn0638.wav");
    *(undefined1 *)(local_24 + 0x99) = 1;
    fVar5 = (float10)FUN_004b1670();
    local_f4 = (float)fVar5;
    *(float *)(local_24 + 0x13c) = local_f4 + 120.0;
  }
  if (*(char *)(local_24 + 0x99) == '\x01') {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x1a0),
                                  *(undefined4 *)(local_24 + 0x1b8));
    local_fc = (float)fVar5;
    if ((400.0 < local_fc) && (*(char *)(local_24 + 0x8f) == '\0')) {
      fVar5 = (float10)FUN_004b1670();
      local_104 = (float)fVar5;
      if ((*(float *)(local_24 + 0x13c) <= local_104 && local_104 != *(float *)(local_24 + 0x13c))
         && (*(char *)(local_24 + 0xa8) == '\0')) {
        uVar2 = FUN_00437d30("misn0635.wav");
        *(undefined4 *)(local_24 + 0x34c) = uVar2;
        uVar2 = FUN_00437d30("misn0646.wav");
        *(undefined4 *)(local_24 + 0x350) = uVar2;
        uVar2 = FUN_00437d30("misn0651.wav");
        *(undefined4 *)(local_24 + 0x354) = uVar2;
        *(undefined1 *)(local_24 + 0x7e) = 0;
        *(undefined1 *)(local_24 + 0xaf) = 1;
        *(undefined1 *)(local_24 + 0xa8) = 1;
      }
    }
  }
  cVar1 = FUN_005cd610("sblpad");
  if ((cVar1 == '\x01') && (*(char *)(local_24 + 0x8f) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    local_10c = (float)fVar5;
    *(float *)(local_24 + 0xe8) = local_10c + 2.0;
    *(undefined1 *)(local_24 + 0x95) = 1;
    *(undefined1 *)(local_24 + 0x8f) = 1;
    FUN_004ff160();
    FUN_005c9610(*(undefined4 *)(local_24 + 0x1b8));
  }
  if ((*(char *)(local_24 + 0x95) == '\x01') && (*(char *)(local_24 + 0x7f) == '\x01')) {
    fVar5 = (float10)FUN_004b1670();
    local_114 = (float)fVar5;
    if ((*(float *)(local_24 + 0xe8) <= local_114 && local_114 != *(float *)(local_24 + 0xe8)) &&
       ((*(char *)(local_24 + 0x7b) == '\x01' && (*(char *)(local_24 + 0xac) == '\0')))) {
      FUN_00437d30("misn0629.wav");
      FUN_00437d30("misn0630.wav");
      FUN_00437d30("misn0647.wav");
      uVar2 = FUN_005c8250("svfigh",2,"ccaplatoonspawn",0,0);
      *(undefined4 *)(local_24 + 0x2e4) = uVar2;
      FUN_005cb820(*(undefined4 *)(local_24 + 0x2e4),*(undefined4 *)(local_24 + 0x1b0),1);
      FUN_005cb620(*(undefined4 *)(local_24 + 0x2e4),1);
      *(undefined1 *)(local_24 + 0x7e) = 0;
      *(undefined1 *)(local_24 + 0x96) = 1;
      *(undefined4 *)(local_24 + 0xd0) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xec) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xd8) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xe0) = 0x5368d4a5;
      *(undefined1 *)(local_24 + 0x6c) = 1;
      *(undefined1 *)(local_24 + 0xac) = 1;
    }
  }
  if ((*(char *)(local_24 + 0x95) == '\x01') && (*(char *)(local_24 + 0x7f) == '\x01')) {
    fVar5 = (float10)FUN_004b1670();
    local_11c = (float)fVar5;
    if ((*(float *)(local_24 + 0xe8) <= local_11c && local_11c != *(float *)(local_24 + 0xe8)) &&
       ((*(char *)(local_24 + 0x7b) == '\0' && (*(char *)(local_24 + 0xac) == '\0')))) {
      FUN_00437d30("misn0629.wav");
      FUN_00437d30("misn0630.wav");
      uVar2 = FUN_005c8250("svfigh",2,"ccaplatoonspawn",0,0);
      *(undefined4 *)(local_24 + 0x2e4) = uVar2;
      FUN_005cb820(*(undefined4 *)(local_24 + 0x2e4),*(undefined4 *)(local_24 + 0x1b0),1);
      FUN_005cb620(*(undefined4 *)(local_24 + 0x2e4),1);
      *(undefined1 *)(local_24 + 0x7e) = 0;
      *(undefined1 *)(local_24 + 0x96) = 1;
      *(undefined4 *)(local_24 + 0xd0) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xec) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xd8) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xe0) = 0x5368d4a5;
      *(undefined1 *)(local_24 + 0x6c) = 1;
      *(undefined1 *)(local_24 + 0xac) = 1;
    }
  }
  if (((*(char *)(local_24 + 0x91) == '\0') && (*(char *)(local_24 + 0x95) == '\x01')) &&
     (*(char *)(local_24 + 0x7f) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    local_124 = (float)fVar5;
    if (*(float *)(local_24 + 0xe8) <= local_124 && local_124 != *(float *)(local_24 + 0xe8)) {
      FUN_00437d30("misn0629.wav");
      FUN_00437d30("misn0630.wav");
      FUN_005cb620(*(undefined4 *)(local_24 + 0x2e4),1);
      *(undefined1 *)(local_24 + 0x7e) = 0;
      *(undefined1 *)(local_24 + 0x91) = 1;
      *(undefined1 *)(local_24 + 0x96) = 1;
      *(undefined4 *)(local_24 + 0xd0) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xec) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xd8) = 0x5368d4a5;
      *(undefined4 *)(local_24 + 0xe0) = 0x5368d4a5;
      *(undefined1 *)(local_24 + 0x6c) = 1;
      fVar5 = (float10)FUN_004b1670();
      local_12c = (float)fVar5;
      *(float *)(local_24 + 0x118) = local_12c + 30.0;
    }
  }
  fVar5 = (float10)FUN_004b1670();
  local_134 = (float)fVar5;
  if ((*(float *)(local_24 + 0x118) <= local_134 && local_134 != *(float *)(local_24 + 0x118)) &&
     (*(char *)(local_24 + 0xa9) == '\0')) {
    *(undefined1 *)(local_24 + 0xa9) = 1;
    *(undefined4 *)(local_24 + 0x118) = 0x56b5e621;
    FUN_00437d30("misn0635.wav");
    uVar2 = FUN_005c8250("svfigh",2,"ccaplatoonspawn",0,0);
    *(undefined4 *)(local_24 + 0x2e4) = uVar2;
    FUN_005cb820(*(undefined4 *)(local_24 + 0x2e4),*(undefined4 *)(local_24 + 0x1b0),1);
  }
  if (*(char *)(local_24 + 0x96) == '\x01') {
    local_30 = *(undefined4 *)(local_24 + 0x334);
    switch(local_30) {
    case 0:
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"bugout1",0,0);
      *(undefined4 *)(local_24 + 0x1c0) = uVar2;
      break;
    case 1:
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"bugout2",0,0);
      *(undefined4 *)(local_24 + 0x1c0) = uVar2;
      break;
    case 2:
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"bugout3",0,0);
      *(undefined4 *)(local_24 + 0x1c0) = uVar2;
      break;
    case 3:
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"bugout4",0,0);
      *(undefined4 *)(local_24 + 0x1c0) = uVar2;
    }
    FUN_005c9640(*(undefined4 *)(local_24 + 0x1c0),"Dust Off");
    *(undefined1 *)(local_24 + 0x96) = 0;
    *(undefined1 *)(local_24 + 0x97) = 1;
    FUN_005c9610(*(undefined4 *)(local_24 + 0x1b8));
  }
  if ((*(char *)(local_24 + 0xac) == '\x01') &&
     (cVar1 = FUN_005c84d0(local_24 + 0x1c0), cVar1 == '\0')) {
    *(undefined1 *)(local_24 + 0x96) = 1;
  }
  fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x1b0),*(undefined4 *)(local_24 + 0x1c0))
  ;
  local_13c = (float)fVar5;
  if (local_13c < 100.0) {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x1a0),
                                  *(undefined4 *)(local_24 + 0x1c0));
    local_144 = (float)fVar5;
    if ((local_144 < 100.0) && (*(char *)(local_24 + 0x97) == '\x01')) {
      FUN_00437d30("misn0649.wav");
      fVar5 = (float10)FUN_004b1670("misn06w1.des");
      local_14c = (float)fVar5;
      FUN_0045c110(local_14c + 5.0);
      *(undefined1 *)(local_24 + 0x97) = 0;
      *(undefined1 *)(local_24 + 0x9a) = 1;
      *(undefined1 *)(local_24 + 0x6c) = 1;
    }
  }
  fVar5 = (float10)FUN_004b1670();
  local_154 = (float)fVar5;
  if (((*(float *)(local_24 + 0xd0) <= local_154 && local_154 != *(float *)(local_24 + 0xd0)) &&
      (*(char *)(local_24 + 0x7e) == '\x01')) && (*(char *)(local_24 + 0x99) == '\x01')) {
    fVar5 = (float10)FUN_004b1670();
    local_15c = (float)fVar5;
    if (*(float *)(local_24 + 0xe8) <= local_15c && local_15c != *(float *)(local_24 + 0xe8)) {
      FUN_00437d30("misn0635.wav");
      FUN_00437d30("misn0648.wav");
      uVar2 = FUN_005c8250("svfigh",2,"ccaplatoonspawn",0,0);
      *(undefined4 *)(local_24 + 0x2e4) = uVar2;
      FUN_005cb820(*(undefined4 *)(local_24 + 0x2e4),*(undefined4 *)(local_24 + 0x1b0),1);
      FUN_005cb620(*(undefined4 *)(local_24 + 0x2e4),1);
      *(undefined1 *)(local_24 + 0x7e) = 0;
      *(undefined4 *)(local_24 + 0xec) = 0x5368d4a5;
      *(undefined1 *)(local_24 + 0x7f) = 0;
    }
  }
  cVar1 = FUN_005c84d0(local_24 + 0x2e4);
  if (cVar1 != '\0') {
    uVar2 = FUN_005ca150(*(undefined4 *)(local_24 + 0x2e4));
    *(undefined4 *)(local_24 + 0x198) = uVar2;
  }
  fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_24 + 0x2e4),*(undefined4 *)(local_24 + 0x198))
  ;
  local_164 = (float)fVar5;
  if ((local_164 < 410.0) && (*(char *)(local_24 + 0x79) == '\0')) {
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x2e4),0);
    *(undefined4 *)(local_24 + 0x2e8) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x2e4),0);
    *(undefined4 *)(local_24 + 0x2ec) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x2e4),0);
    *(undefined4 *)(local_24 + 0x2f0) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_24 + 0x2e4),0);
    *(undefined4 *)(local_24 + 0x2f4) = uVar2;
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_24 + 0x2e4),0);
    *(undefined4 *)(local_24 + 0x2f8) = uVar2;
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_24 + 0x2e4),0);
    *(undefined4 *)(local_24 + 0x2fc) = uVar2;
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_24 + 0x2e4),0);
    *(undefined4 *)(local_24 + 0x300) = uVar2;
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_24 + 0x2e4),0);
    *(undefined4 *)(local_24 + 0x304) = uVar2;
    FUN_005cb820(*(undefined4 *)(local_24 + 0x2e8),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x2ec),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x2f0),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x2f4),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x2f8),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x2fc),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x300),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb820(*(undefined4 *)(local_24 + 0x304),*(undefined4 *)(local_24 + 0x1b0),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x2e8),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x2ec),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x2f0),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x2f4),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x2f8),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x2fc),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x300),1);
    FUN_005cb620(*(undefined4 *)(local_24 + 0x304),1);
    *(undefined1 *)(local_24 + 0x79) = 1;
  }
  if (((((*(char *)(local_24 + 0x7e) == '\x01') && (*(char *)(local_24 + 0xa3) == '\0')) &&
       ((cVar1 = FUN_005c84d0(local_24 + 0x2e4), cVar1 == '\0' &&
        ((((cVar1 = FUN_005c84d0(local_24 + 0x2e8), cVar1 == '\0' &&
           (cVar1 = FUN_005c84d0(local_24 + 0x2ec), cVar1 == '\0')) &&
          (cVar1 = FUN_005c84d0(local_24 + 0x2f0), cVar1 == '\0')) &&
         ((cVar1 = FUN_005c84d0(local_24 + 0x2f4), cVar1 == '\0' &&
          (cVar1 = FUN_005c84d0(local_24 + 0x2f8), cVar1 == '\0')))))))) &&
      (cVar1 = FUN_005c84d0(local_24 + 0x2fc), cVar1 == '\0')) &&
     ((cVar1 = FUN_005c84d0(local_24 + 0x300), cVar1 == '\0' &&
      (cVar1 = FUN_005c84d0(local_24 + 0x304), cVar1 == '\0')))) {
    uVar2 = FUN_005c8250("svfigh",2,"ccaplatoonspawn",0,0);
    *(undefined4 *)(local_24 + 0x2e4) = uVar2;
    *(undefined1 *)(local_24 + 0xa3) = 1;
    *(undefined1 *)(local_24 + 0x79) = 0;
  }
  fVar5 = (float10)FUN_004b1670();
  local_16c = (float)fVar5;
  if ((*(float *)(local_24 + 0xec) <= local_16c && local_16c != *(float *)(local_24 + 0xec)) &&
     (*(char *)(local_24 + 0x7f) == '\x01')) {
    *(undefined1 *)(local_24 + 0x7f) = 0;
  }
  fVar5 = (float10)FUN_004b1670();
  local_174 = (float)fVar5;
  if (((*(float *)(local_24 + 0xd0) <= local_174 && local_174 != *(float *)(local_24 + 0xd0)) &&
      (*(char *)(local_24 + 0x7e) == '\x01')) && (*(char *)(local_24 + 0x99) == '\0')) {
    uVar2 = FUN_00437d30("misn0635.wav");
    *(undefined4 *)(local_24 + 0x34c) = uVar2;
    uVar2 = FUN_00437d30("misn0646.wav");
    *(undefined4 *)(local_24 + 0x350) = uVar2;
    uVar2 = FUN_00437d30("misn0651.wav");
    *(undefined4 *)(local_24 + 0x354) = uVar2;
    *(undefined1 *)(local_24 + 0x7e) = 0;
    *(undefined1 *)(local_24 + 0xaf) = 1;
  }
  if (((*(char *)(local_24 + 0xaf) == '\x01') &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x34c)), cVar1 != '\0')) &&
     ((cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x350)), cVar1 != '\0' &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(local_24 + 0x354)), cVar1 != '\0')))) {
    fVar5 = (float10)FUN_004b1670("misn06l4.des");
    local_17c = (float)fVar5;
    FUN_0045c0f0(local_17c + 0.0);
  }
  cVar1 = FUN_005c84d0(local_24 + 0x1a0);
  if ((cVar1 == '\0') &&
     (cVar1 = FUN_005c8410(*(undefined4 *)(local_24 + 0x1a0),"asuser"), cVar1 != '\0')) {
    fVar5 = (float10)FUN_00822d80(0);
    local_184 = (float)fVar5;
    FUN_0045c0f0(local_184 + 5.0);
  }
  FUN_0083e885();
  return;
}

