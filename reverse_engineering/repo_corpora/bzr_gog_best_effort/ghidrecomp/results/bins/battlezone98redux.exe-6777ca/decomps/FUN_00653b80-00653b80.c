
void FUN_00653b80(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  float10 fVar6;
  undefined1 local_1f4 [4];
  double local_1f0;
  double local_1e8;
  char *local_1e0;
  double local_1dc;
  undefined1 local_1d4 [4];
  double local_1d0;
  undefined1 local_1c8 [4];
  double local_1c4;
  undefined1 local_1bc [4];
  char *local_1b8 [2];
  float local_1b0;
  float local_1ac;
  undefined4 local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
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
  undefined4 local_fc;
  float local_f8;
  undefined4 local_f4;
  float local_f0;
  undefined4 local_ec;
  float local_e8;
  undefined4 local_e4;
  float local_e0;
  undefined4 local_dc;
  float local_d8;
  undefined4 local_d4;
  float local_d0;
  undefined4 local_cc;
  float local_c8;
  undefined4 local_c4;
  float local_c0;
  undefined4 local_bc;
  float local_b8;
  undefined4 local_b4;
  float local_b0;
  undefined4 local_ac;
  float local_a8;
  undefined4 local_a4;
  float local_a0;
  undefined4 local_9c;
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
  undefined4 local_6c;
  undefined4 local_68;
  undefined1 local_64 [4];
  int local_60;
  char *local_5c;
  undefined1 local_58 [4];
  int local_54;
  int local_50;
  char *local_4c;
  char *local_48;
  undefined4 local_44;
  int local_40;
  char local_39;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40 = 0;
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(local_1c + 0xd8) = uVar2;
  if (*(char *)(local_1c + 0x54) == '\0') {
    FUN_005cacb0(1,10);
    FUN_005cadd0(1,0);
    *(undefined1 *)(local_1c + 0x54) = 1;
    fVar6 = (float10)FUN_004b1670();
    local_18c = (float)fVar6;
    *(float *)(local_1c + 0x68) = local_18c + 3.0;
    *(undefined1 *)(local_1c + 0x5a) = 1;
    FUN_004f6aa0();
    FUN_004f6ab0("ch05001.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(local_1c + 99) = 1;
    FUN_005cbd40(*(undefined4 *)(local_1c + 0x100),1);
  }
  if (*(char *)(local_1c + 99) != '\0') {
    FUN_005c88b0(*(undefined4 *)(local_1c + 0xd8),2);
  }
  fVar6 = (float10)FUN_004b1670();
  local_188 = (float)fVar6;
  if (*(float *)(local_1c + 0x68) <= local_188 && local_188 != *(float *)(local_1c + 0x68)) {
    *(undefined4 *)(local_1c + 0x68) = 0x497423fe;
    uVar2 = FUN_00437d30("ch05001.wav");
    *(undefined4 *)(local_1c + 0x160) = uVar2;
  }
  if (*(int *)(local_1c + 0x160) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_1c + 0x160));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_1c + 0x160) = 0;
    }
  }
  if (*(char *)(local_1c + 0x5a) != '\0') {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_1c + 0xd8),*(undefined4 *)(local_1c + 0xdc))
    ;
    local_1f0 = (double)fVar6;
    if (((250.0 < local_1f0) && (*(char *)(local_1c + 0x65) == '\0')) &&
       (*(char *)(local_1c + 100) == '\0')) {
      fVar6 = (float10)FUN_004b1670("ch05lsea.des");
      local_78 = (float)fVar6;
      FUN_0045c0f0(local_78 + 1.0);
      *(undefined1 *)(local_1c + 0x65) = 1;
    }
  }
  if (*(char *)(local_1c + 0x59) == '\0') {
    iVar3 = FUN_005cae10(1);
    if (2 < iVar3) {
      *(undefined1 *)(local_1c + 0x59) = 1;
      uVar2 = FUN_005c8250("cvfighh",1,"scout_1",0,0);
      *(undefined4 *)(local_1c + 0xe0) = uVar2;
      FUN_005c88b0(*(undefined4 *)(local_1c + 0xe0),2);
      FUN_005cb960(*(undefined4 *)(local_1c + 0xe0),"scout_path",1);
      uVar2 = FUN_005c8250("cvfighh",1,"scout_2",0,0);
      *(undefined4 *)(local_1c + 0xe4) = uVar2;
      FUN_005c88b0(*(undefined4 *)(local_1c + 0xe4),2);
      FUN_005ce680(*(undefined4 *)(local_1c + 0xe4),*(undefined4 *)(local_1c + 0xe0),1);
      uVar2 = FUN_005c8250("cvfighh",1,"scout_2",0,0);
      *(undefined4 *)(local_1c + 0xe8) = uVar2;
      FUN_005c88b0(*(undefined4 *)(local_1c + 0xe8),2);
      FUN_005ce680(*(undefined4 *)(local_1c + 0xe8),*(undefined4 *)(local_1c + 0xe0),1);
      uVar2 = FUN_005c8250("cvfighh",1,"scout_2",0,0);
      *(undefined4 *)(local_1c + 0xec) = uVar2;
      FUN_005c88b0(*(undefined4 *)(local_1c + 0xec),2);
      FUN_005ce680(*(undefined4 *)(local_1c + 0xec),*(undefined4 *)(local_1c + 0xe0),1);
    }
  }
  if (*(char *)(local_1c + 0x59) != '\0') {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_1c + 0xe0),*(undefined4 *)(local_1c + 0xdc))
    ;
    local_1a4 = (float)fVar6;
    if ((local_1a4 < 300.0) && (*(char *)(local_1c + 0x5b) == '\0')) {
      *(undefined1 *)(local_1c + 0x5b) = 1;
      FUN_00437d30("ch05002.wav");
    }
  }
  if (*(char *)(local_1c + 0x59) != '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(local_1c + 0xe0),"trigger_1",0);
    local_1c4 = (double)fVar6;
    if ((local_1c4 < 30.0) && (*(char *)(local_1c + 0x5c) == '\0')) {
      *(undefined1 *)(local_1c + 0x5c) = 1;
      FUN_005c83e0(*(undefined4 *)(local_1c + 0xe4));
      FUN_005c83e0(*(undefined4 *)(local_1c + 0xe8));
      FUN_005c83e0(*(undefined4 *)(local_1c + 0xec));
      FUN_005c83e0(*(undefined4 *)(local_1c + 0xe0));
      fVar6 = (float10)FUN_004b1670();
      local_80 = (float)fVar6;
      *(float *)(local_1c + 0x6c) = local_80 + 1.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_130 = (float)fVar6;
  if (*(float *)(local_1c + 0x6c) <= local_130 && local_130 != *(float *)(local_1c + 0x6c)) {
    *(undefined4 *)(local_1c + 0x6c) = 0x497423fe;
    uVar2 = FUN_00437d30("ch05003.wav");
    *(undefined4 *)(local_1c + 0x164) = uVar2;
  }
  if (*(int *)(local_1c + 0x164) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_1c + 0x164));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_1c + 0x164) = 0;
      fVar6 = (float10)FUN_004b1670();
      local_88 = (float)fVar6;
      *(float *)(local_1c + 0x70) = local_88 + 5.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_1ac = (float)fVar6;
  if (*(float *)(local_1c + 0x70) <= local_1ac && local_1ac != *(float *)(local_1c + 0x70)) {
    *(undefined4 *)(local_1c + 0x70) = 0x497423fe;
    uVar2 = FUN_00437d30("ch05004.wav");
    *(undefined4 *)(local_1c + 0x168) = uVar2;
    *(undefined1 *)(local_1c + 0x5a) = 0;
  }
  if (*(int *)(local_1c + 0x168) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_1c + 0x168));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_1c + 0x168) = 0;
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"nav_1",0,0);
      *(undefined4 *)(local_1c + 0x154) = uVar2;
      FUN_005cd7f0(*(undefined4 *)(local_1c + 0x154),"Last GPS Fix");
      FUN_005c88e0(*(undefined4 *)(local_1c + 0x154));
      FUN_004f6aa0();
      FUN_004f6ab0("ch05001.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("ch05002.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(local_1c + 0x55) = 1;
    }
  }
  fVar6 = (float10)FUN_005c9800(*(undefined4 *)(local_1c + 0xd8),"trigger_1",0);
  local_1d0 = (double)fVar6;
  if ((local_1d0 < 400.0) && (*(char *)(local_1c + 0x5e) == '\0')) {
    *(undefined1 *)(local_1c + 0x5e) = 1;
    uVar2 = FUN_005c8250("cvfigh",0,"haul_scout",0,0);
    *(undefined4 *)(local_1c + 0xf0) = uVar2;
    FUN_005ce150(*(undefined4 *)(local_1c + 0xf0));
    uVar2 = FUN_005c8250("svhaul",2,"enemy_haul",0,0);
    *(undefined4 *)(local_1c + 0xf4) = uVar2;
    uVar2 = FUN_005c8250("svfigh",2,"haul_defend",0,0);
    *(undefined4 *)(local_1c + 0xf8) = uVar2;
    FUN_005cbce0(*(undefined4 *)(local_1c + 0xf8),*(undefined4 *)(local_1c + 0xf4),1);
    local_60 = FUN_00462630(*(undefined4 *)(local_1c + 0xf8));
    *(undefined4 *)(local_60 + 0xec) = 0;
    uVar2 = FUN_005c8250("svfigh",2,"haul_defend",0,0);
    *(undefined4 *)(local_1c + 0xfc) = uVar2;
    FUN_005cbce0(*(undefined4 *)(local_1c + 0xfc),*(undefined4 *)(local_1c + 0xf4),1);
    local_60 = FUN_00462630(*(undefined4 *)(local_1c + 0xfc));
    *(undefined4 *)(local_60 + 0xec) = 0;
    fVar6 = (float10)FUN_004b1670();
    local_90 = (float)fVar6;
    *(float *)(local_1c + 200) = local_90 + 0.5;
  }
  fVar6 = (float10)FUN_004b1670();
  local_138 = (float)fVar6;
  if (*(float *)(local_1c + 200) <= local_138 && local_138 != *(float *)(local_1c + 200)) {
    *(undefined4 *)(local_1c + 200) = 0x497423fe;
    FUN_005cc280(*(undefined4 *)(local_1c + 0xf4),*(undefined4 *)(local_1c + 0xf0),1);
    *(undefined1 *)(local_1c + 0x58) = 1;
    fVar6 = (float10)FUN_004b1670();
    local_98 = (float)fVar6;
    *(float *)(local_1c + 0xcc) = local_98 + 15.0;
    FUN_005cd2a0();
  }
  if (*(char *)(local_1c + 0x58) != '\0') {
    FUN_005cd300("haul_cam",800,0,*(undefined4 *)(local_1c + 0xf4));
    cVar1 = FUN_005cd560();
    if (cVar1 == '\0') {
      fVar6 = (float10)FUN_004b1670();
      local_1a0 = (float)fVar6;
      if (local_1a0 < *(float *)(local_1c + 0xcc) || local_1a0 == *(float *)(local_1c + 0xcc))
      goto LAB_006544d2;
    }
    *(undefined1 *)(local_1c + 0x58) = 0;
    FUN_005cd4e0();
    FUN_00437d30("ch05005.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("ch05003.otf",DAT_0091755c,0x41000000,0);
    FUN_005c95e0(*(undefined4 *)(local_1c + 0xf4));
    local_68 = DAT_00917a74;
    FID_conflict_begin(local_58);
    while( true ) {
      uVar2 = FID_conflict_end(local_1d4);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      local_54 = *piVar4;
      iVar3 = (*(code *)**(undefined4 **)(local_54 + 0x18))();
      if (*(int *)(iVar3 + 0x14) == 0x53435250) {
        (**(code **)(*(int *)(local_54 + 0x18) + 0x10))();
      }
      FUN_0046b260(local_1bc,0);
    }
  }
LAB_006544d2:
  if (*(char *)(local_1c + 0x5e) != '\0') {
    iVar3 = FUN_005cd240(*(undefined4 *)(local_1c + 0xf0));
    if ((iVar3 == *(int *)(local_1c + 0xf4)) && (*(char *)(local_1c + 0x5f) == '\0')) {
      *(undefined1 *)(local_1c + 0x5f) = 1;
      FUN_005cb960(*(undefined4 *)(local_1c + 0xf4),"haul_path",1);
      *(undefined1 *)(local_1c + 0x60) = 1;
    }
  }
  if ((*(char *)(local_1c + 0x5e) != '\0') && (*(char *)(local_1c + 99) != '\0')) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_1c + 0xd8),*(undefined4 *)(local_1c + 0xf4))
    ;
    local_a0 = (float)fVar6;
    if ((local_a0 < 175.0) &&
       ((*(char *)(local_1c + 0x65) == '\0' && (*(char *)(local_1c + 100) == '\0')))) {
      *(undefined1 *)(local_1c + 0x65) = 1;
      fVar6 = (float10)FUN_004b1670("ch05lseb.des");
      local_140 = (float)fVar6;
      FUN_0045c0f0(local_140 + 1.0);
    }
  }
  if (*(char *)(local_1c + 0x60) != '\0') {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_1c + 0xd8),*(undefined4 *)(local_1c + 0xf4))
    ;
    local_a8 = (float)fVar6;
    if (((700.0 < local_a8) && (*(char *)(local_1c + 0x65) == '\0')) &&
       (*(char *)(local_1c + 100) == '\0')) {
      *(undefined1 *)(local_1c + 0x65) = 1;
      fVar6 = (float10)FUN_004b1670("ch05lsed.des");
      local_190 = (float)fVar6;
      FUN_0045c0f0(local_190 + 1.0);
    }
  }
  if (*(char *)(local_1c + 0x5e) != '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(local_1c + 0xf4),"trigger_2",0);
    local_b0 = (float)fVar6;
    if ((local_b0 < 200.0) && (*(char *)(local_1c + 0x5d) == '\0')) {
      *(undefined1 *)(local_1c + 0x60) = 0;
      *(undefined1 *)(local_1c + 0x5d) = 1;
      fVar6 = (float10)FUN_004b1670();
      local_148 = (float)fVar6;
      *(float *)(local_1c + 0x78) = local_148 + 5.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_b8 = (float)fVar6;
  if (*(float *)(local_1c + 0x78) <= local_b8 && local_b8 != *(float *)(local_1c + 0x78)) {
    *(undefined4 *)(local_1c + 0x78) = 0x497423fe;
    uVar2 = FUN_00437d30("abetty6.wav");
    *(undefined4 *)(local_1c + 0x170) = uVar2;
  }
  if (*(int *)(local_1c + 0x170) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_1c + 0x170));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_1c + 0x170) = 0;
      fVar6 = (float10)FUN_004b1670();
      local_1b0 = (float)fVar6;
      *(float *)(local_1c + 0x7c) = local_1b0 + 5.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_c0 = (float)fVar6;
  if (*(float *)(local_1c + 0x7c) <= local_c0 && local_c0 != *(float *)(local_1c + 0x7c)) {
    *(undefined4 *)(local_1c + 0x7c) = 0x497423fe;
    uVar2 = FUN_00437d30("abetty14.wav");
    *(undefined4 *)(local_1c + 0x174) = uVar2;
  }
  if (*(int *)(local_1c + 0x174) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_1c + 0x174));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_1c + 0x174) = 0;
      fVar6 = (float10)FUN_004b1670();
      local_150 = (float)fVar6;
      *(float *)(local_1c + 0x74) = local_150 + 2.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_c8 = (float)fVar6;
  if (*(float *)(local_1c + 0x74) <= local_c8 && local_c8 != *(float *)(local_1c + 0x74)) {
    *(undefined4 *)(local_1c + 0x74) = 0x497423fe;
    uVar2 = FUN_00437d30("ch05006.wav");
    *(undefined4 *)(local_1c + 0x16c) = uVar2;
    FUN_004f6aa0();
    FUN_004f6ab0("ch05003.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("ch05004.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(local_1c + 99) = 0;
    fVar6 = (float10)FUN_004b1670();
    local_198 = (float)fVar6;
    *(float *)(local_1c + 0xd0) = local_198 + 10.0;
    fVar6 = (float10)FUN_004b1670();
    local_d0 = (float)fVar6;
    *(float *)(local_1c + 0xc4) = local_d0 + 240.0;
    FUN_005c9610(*(undefined4 *)(local_1c + 0xf4));
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"base_1",0,0);
    *(undefined4 *)(local_1c + 0x158) = uVar2;
    FUN_005cd7f0(*(undefined4 *)(local_1c + 0x158),&DAT_00890cfc);
    FUN_005c95e0(*(undefined4 *)(local_1c + 0x158));
    FUN_005cb960(*(undefined4 *)(local_1c + 0x100),"convoy_path",1);
    uVar2 = FUN_005c8250("cvfigh",1,"convoy",0,0);
    *(undefined4 *)(local_1c + 0x108) = uVar2;
    uVar2 = FUN_005c8250("cvfigh",1,"convoy",0,0);
    *(undefined4 *)(local_1c + 0x10c) = uVar2;
    uVar2 = FUN_005c8250("cvmuf",1,"convoy",0,0);
    *(undefined4 *)(local_1c + 0x104) = uVar2;
    FUN_005cb960(*(undefined4 *)(local_1c + 0x104),"convoy_path",1);
    FUN_005cbc20(*(undefined4 *)(local_1c + 0x108),*(undefined4 *)(local_1c + 0x104),1);
    FUN_005cbc20(*(undefined4 *)(local_1c + 0x10c),*(undefined4 *)(local_1c + 0x104),1);
    uVar2 = FUN_005c8250("cvcnst",1,"convoy",0,0);
    *(undefined4 *)(local_1c + 0x110) = uVar2;
    FUN_005cb960(*(undefined4 *)(local_1c + 0x110),"convoy_path",1);
    FUN_005cadd0(1,0x32);
    local_6c = DAT_00917a74;
    FID_conflict_begin(local_64);
    while( true ) {
      uVar2 = FID_conflict_end(local_1c8);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      local_50 = *piVar4;
      local_18[0] = '\0';
      local_18[1] = '\0';
      local_18[2] = '\0';
      local_18[3] = '\0';
      local_18[4] = '\0';
      local_18[5] = '\0';
      local_18[6] = '\0';
      local_18[7] = '\0';
      local_18[8] = '\0';
      local_18[9] = '\0';
      local_18[10] = '\0';
      local_18[0xb] = '\0';
      local_18[0xc] = '\0';
      local_18[0xd] = '\0';
      local_18[0xe] = '\0';
      local_18[0xf] = 0;
      iVar3 = (*(code *)**(undefined4 **)(local_50 + 0x18))();
      local_5c = (char *)(iVar3 + 0x14);
      local_1e0 = local_18;
      local_4c = local_1e0;
      do {
        local_39 = *local_5c;
        *local_4c = local_39;
        local_5c = local_5c + 1;
        local_4c = local_4c + 1;
      } while (local_39 != '\0');
      iVar3 = _strnicmp(local_18,"nsp",2);
      if (iVar3 == 0) {
        (**(code **)(*(int *)(local_50 + 0x18) + 0x10))();
      }
      FUN_0046b260(local_1f4,0);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_158 = (float)fVar6;
  if (*(float *)(local_1c + 0xc4) <= local_158 && local_158 != *(float *)(local_1c + 0xc4)) {
    fVar6 = (float10)FUN_004b1670();
    local_d8 = (float)fVar6;
    *(float *)(local_1c + 0xc4) = local_d8 + 240.0;
    for (local_40 = 0; local_40 < 8; local_40 = local_40 + 1) {
      local_1a8 = FUN_005c8250("sssold",2,"aerial_1",400,0);
      uVar2 = FUN_00653ac0(1);
      FUN_005cb820(local_1a8,uVar2);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_e0 = (float)fVar6;
  if (*(float *)(local_1c + 0xd0) <= local_e0 && local_e0 != *(float *)(local_1c + 0xd0)) {
    *(undefined4 *)(local_1c + 0xd0) = 0x497423fe;
    FUN_005c88b0(*(undefined4 *)(local_1c + 0xd8),1);
  }
  if (*(int *)(local_1c + 0x158) != 0) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_1c + 0x158),*(undefined4 *)(local_1c + 0xd8)
                                 );
    local_160 = (float)fVar6;
    if (local_160 < 100.0) {
      FUN_005c9610(*(undefined4 *)(local_1c + 0x158));
      *(undefined4 *)(local_1c + 0x158) = 0;
    }
  }
  if (*(int *)(local_1c + 0x16c) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_1c + 0x16c));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_1c + 0x16c) = 0;
      fVar6 = (float10)FUN_004b1670();
      local_e8 = (float)fVar6;
      *(float *)(local_1c + 0x80) = local_e8 + 240.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_184 = (float)fVar6;
  if (*(float *)(local_1c + 0x80) <= local_184 && local_184 != *(float *)(local_1c + 0x80)) {
    *(undefined4 *)(local_1c + 0x80) = 0x497423fe;
    FUN_005c83e0(*(undefined4 *)(local_1c + 0xf0));
    FUN_005c83e0(*(undefined4 *)(local_1c + 0xf4));
    FUN_005c83e0(*(undefined4 *)(local_1c + 0xf8));
    FUN_005c83e0(*(undefined4 *)(local_1c + 0xfc));
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_1c + 0x84) = (float)fVar6;
    fVar6 = (float10)FUN_004b1670();
    local_f0 = (float)fVar6;
    *(float *)(local_1c + 0x88) = local_f0 + 300.0;
    fVar6 = (float10)FUN_004b1670();
    local_168 = (float)fVar6;
    *(float *)(local_1c + 0x8c) = local_168 + 540.0;
    fVar6 = (float10)FUN_004b1670();
    local_f8 = (float)fVar6;
    *(float *)(local_1c + 0x90) = local_f8 + 900.0;
    fVar6 = (float10)FUN_004b1670();
    local_70 = (float)fVar6;
    *(float *)(local_1c + 0x94) = local_70 + 1020.0;
    fVar6 = (float10)FUN_004b1670();
    local_100 = (float)fVar6;
    *(float *)(local_1c + 0x98) = local_100 + 1200.0;
    fVar6 = (float10)FUN_004b1670();
    local_170 = (float)fVar6;
    *(float *)(local_1c + 0x9c) = local_170 + 1320.0;
    fVar6 = (float10)FUN_004b1670();
    local_108 = (float)fVar6;
    *(float *)(local_1c + 0xa0) = local_108 + 120.0;
    fVar6 = (float10)FUN_004b1670();
    local_194 = (float)fVar6;
    *(float *)(local_1c + 0xa4) = local_194 + 480.0;
    fVar6 = (float10)FUN_004b1670();
    local_110 = (float)fVar6;
    *(float *)(local_1c + 0xa8) = local_110 + 720.0;
    fVar6 = (float10)FUN_004b1670();
    local_178 = (float)fVar6;
    *(float *)(local_1c + 0xac) = local_178 + 960.0;
    fVar6 = (float10)FUN_004b1670();
    local_118 = (float)fVar6;
    *(float *)(local_1c + 0xb0) = local_118 + 1020.0;
    fVar6 = (float10)FUN_004b1670();
    local_19c = (float)fVar6;
    *(float *)(local_1c + 0xb4) = local_19c + 1200.0;
    fVar6 = (float10)FUN_004b1670();
    local_120 = (float)fVar6;
    *(float *)(local_1c + 0xc0) = local_120 + 240.0;
  }
  fVar6 = (float10)FUN_004b1670();
  local_180 = (float)fVar6;
  if (*(float *)(local_1c + 0x84) <= local_180 && local_180 != *(float *)(local_1c + 0x84)) {
    *(undefined4 *)(local_1c + 0x84) = 0x497423fe;
    local_30 = FUN_005c8250("svwalk",2,"wave_1",0,0);
    FUN_005cb960(local_30,"wave_1_path",1);
    local_30 = FUN_005c8250("svwalk",2,"wave_1",0,0);
    FUN_005cb960(local_30,"wave_1_path",1);
    local_30 = FUN_005c8250("svhraz",2,"wave_1",0,0);
    FUN_005cb960(local_30,"wave_1_path",1);
    local_30 = FUN_005c8250("svhraz",2,"wave_1",0,0);
    FUN_005cb960(local_30,"wave_1_path",1);
    local_30 = FUN_005c8250("svtank",2,"wave_1",0,0);
    FUN_005cb960(local_30,"wave_1_path",1);
    local_30 = FUN_005c8250("svtank",2,"wave_1",0,0);
    FUN_005cb960(local_30,"wave_1_path",1);
    local_30 = FUN_005c8250("svtank",2,"wave_1",0,0);
    FUN_005cb960(local_30,"wave_1_path",1);
  }
  fVar6 = (float10)FUN_004b1670();
  local_128 = (float)fVar6;
  if (*(float *)(local_1c + 0x88) <= local_128 && local_128 != *(float *)(local_1c + 0x88)) {
    *(undefined4 *)(local_1c + 0x88) = 0x497423fe;
    local_28 = FUN_005c8250("svhraz",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
    local_28 = FUN_005c8250("svhraz",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
    local_28 = FUN_005c8250("svhraz",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
    local_28 = FUN_005c8250("svhraz",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
    local_28 = FUN_005c8250("svfigh",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
    local_28 = FUN_005c8250("svfigh",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
    local_28 = FUN_005c8250("svfigh",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
    local_28 = FUN_005c8250("svrckt",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
    local_28 = FUN_005c8250("svrckt",2,"wave_2",0,0);
    FUN_005cb960(local_28,"wave_2_path",1);
  }
  fVar6 = (float10)FUN_004b1670();
  local_74 = (float)fVar6;
  if (*(float *)(local_1c + 0x8c) <= local_74 && local_74 != *(float *)(local_1c + 0x8c)) {
    *(undefined4 *)(local_1c + 0x8c) = 0x497423fe;
    local_34 = FUN_005c8250("sssold",2,"wave_3",0,0);
    uVar2 = FUN_00653ac0(1);
    FUN_005cb820(local_34,uVar2);
    local_34 = FUN_005c8250("sssold",2,"wave_3",0,0);
    uVar2 = FUN_00653ac0(1);
    FUN_005cb820(local_34,uVar2);
    local_34 = FUN_005c8250("sssold",2,"wave_3",0,0);
    uVar2 = FUN_00653ac0(1);
    FUN_005cb820(local_34,uVar2);
    local_34 = FUN_005c8250("sssold",2,"wave_3",0,0);
    uVar2 = FUN_00653ac0(1);
    FUN_005cb820(local_34,uVar2);
    local_34 = FUN_005c8250("sssold",2,"wave_3",0,0);
    uVar2 = FUN_00653ac0(1);
    FUN_005cb820(local_34,uVar2);
    local_34 = FUN_005c8250("ssuser",2,"wave_3",0,0);
    FUN_005cb820(local_34,*(undefined4 *)(local_1c + 0xd8),1);
    local_34 = FUN_005c8250("ssuser",2,"wave_3",0,0);
    FUN_005cb820(local_34,*(undefined4 *)(local_1c + 0xd8),1);
  }
  fVar6 = (float10)FUN_004b1670();
  local_7c = (float)fVar6;
  if (*(float *)(local_1c + 0x90) <= local_7c && local_7c != *(float *)(local_1c + 0x90)) {
    *(undefined4 *)(local_1c + 0x90) = 0x497423fe;
    local_24 = FUN_005c8250("svtank",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svtank",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svtank",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svtank",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svtank",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svtank",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svtank",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svltnk",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svltnk",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
    local_24 = FUN_005c8250("svltnk",2,"wave_4",0,0);
    FUN_005cb960(local_24,"wave_4_path",1);
  }
  fVar6 = (float10)FUN_004b1670();
  local_84 = (float)fVar6;
  if (*(float *)(local_1c + 0x94) <= local_84 && local_84 != *(float *)(local_1c + 0x94)) {
    *(undefined4 *)(local_1c + 0x94) = 0x497423fe;
    local_20 = FUN_005c8250("svwalk",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svwalk",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svwalk",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svwalk",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svfigh",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svfigh",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svfigh",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svfigh",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svrckt",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svrckt",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svtank",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svtank",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
    local_20 = FUN_005c8250("svtank",2,"wave_5",0,0);
    FUN_005cb960(local_20,"wave_5_path",1);
  }
  fVar6 = (float10)FUN_004b1670();
  local_8c = (float)fVar6;
  if (*(float *)(local_1c + 0x98) <= local_8c && local_8c != *(float *)(local_1c + 0x98)) {
    *(undefined4 *)(local_1c + 0x98) = 0x497423fe;
    local_2c = FUN_005c8250("svltnk",2,"wave_6",0,0);
    FUN_005cb960(local_2c,"wave_6_path",1);
    local_2c = FUN_005c8250("svltnk",2,"wave_6",0,0);
    FUN_005cb960(local_2c,"wave_6_path",1);
    local_2c = FUN_005c8250("svltnk",2,"wave_6",0,0);
    FUN_005cb960(local_2c,"wave_6_path",1);
    local_2c = FUN_005c8250("svltnk",2,"wave_6",0,0);
    FUN_005cb960(local_2c,"wave_6_path",1);
    local_2c = FUN_005c8250("svltnk",2,"wave_6",0,0);
    FUN_005cb960(local_2c,"wave_6_path",1);
    local_2c = FUN_005c8250("svltnk",2,"wave_6",0,0);
    FUN_005cb960(local_2c,"wave_6_path",1);
    local_2c = FUN_005c8250("svltnk",2,"wave_6",0,0);
    FUN_005cb960(local_2c,"wave_6_path",1);
    local_2c = FUN_005c8250("svltnk",2,"wave_6",0,0);
    FUN_005cb960(local_2c,"wave_6_path",1);
  }
  fVar6 = (float10)FUN_004b1670();
  local_94 = (float)fVar6;
  if (*(float *)(local_1c + 0x9c) <= local_94 && local_94 != *(float *)(local_1c + 0x9c)) {
    *(undefined4 *)(local_1c + 0x9c) = 0x497423fe;
    uVar2 = FUN_005c8250("svwalk",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_9c = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_9c,"wave_7_path",1);
    uVar2 = FUN_005c8250("svwalk",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_a4 = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_a4,"wave_7_path",1);
    uVar2 = FUN_005c8250("svwalk",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_ac = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_ac,"wave_7_path",1);
    uVar2 = FUN_005c8250("svwalk",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_b4 = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_b4,"wave_7_path",1);
    uVar2 = FUN_005c8250("svhraz",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_bc = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_bc,"wave_7_path",1);
    uVar2 = FUN_005c8250("svhraz",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_c4 = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_c4,"wave_7_path",1);
    uVar2 = FUN_005c8250("svhraz",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_cc = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_cc,"wave_7_path",1);
    uVar2 = FUN_005c8250("svhraz",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_d4 = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_d4,"wave_7_path",1);
    uVar2 = FUN_005c8250("svtank",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_dc = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_dc,"wave_7_path",1);
    uVar2 = FUN_005c8250("svtank",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_e4 = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_e4,"wave_7_path",1);
    uVar2 = FUN_005c8250("svtank",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_ec = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_ec,"wave_7_path",1);
    uVar2 = FUN_005c8250("svtank",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_f4 = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_f4,"wave_7_path",1);
    uVar2 = FUN_005c8250("svapc",2,"wave_7",0,0);
    *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4) = uVar2;
    local_fc = *(undefined4 *)(local_1c + 0x11c + *(int *)(local_1c + 0x184) * 4);
    *(int *)(local_1c + 0x184) = *(int *)(local_1c + 0x184) + 1;
    FUN_005cb960(local_fc,"wave_7_path",1);
    *(undefined1 *)(local_1c + 0x62) = 1;
  }
  fVar6 = (float10)FUN_004b1670();
  local_104 = (float)fVar6;
  if (*(float *)(local_1c + 0xa0) <= local_104 && local_104 != *(float *)(local_1c + 0xa0)) {
    *(undefined4 *)(local_1c + 0xa0) = 0x497423fe;
    FUN_005c8250("apwrck",0,"day_1",0,0);
  }
  fVar6 = (float10)FUN_004b1670();
  local_10c = (float)fVar6;
  if (*(float *)(local_1c + 0xa4) <= local_10c && local_10c != *(float *)(local_1c + 0xa4)) {
    *(undefined4 *)(local_1c + 0xa4) = 0x497423fe;
    FUN_005c8250("apwrck",0,"day_2",0,0);
  }
  fVar6 = (float10)FUN_004b1670();
  local_114 = (float)fVar6;
  if (*(float *)(local_1c + 0xa8) <= local_114 && local_114 != *(float *)(local_1c + 0xa8)) {
    *(undefined4 *)(local_1c + 0xa8) = 0x497423fe;
    FUN_005c8250("apwrck",0,"day_3",0,0);
  }
  fVar6 = (float10)FUN_004b1670();
  local_11c = (float)fVar6;
  if (*(float *)(local_1c + 0xac) <= local_11c && local_11c != *(float *)(local_1c + 0xac)) {
    *(undefined4 *)(local_1c + 0xac) = 0x497423fe;
    FUN_005c8250("apwrck",0,"day_4",0,0);
  }
  fVar6 = (float10)FUN_004b1670();
  local_124 = (float)fVar6;
  if (*(float *)(local_1c + 0xb0) <= local_124 && local_124 != *(float *)(local_1c + 0xb0)) {
    *(undefined4 *)(local_1c + 0xb0) = 0x497423fe;
    FUN_005c8250("apwrck",0,"day_5",0,0);
    FUN_00437d30("ch05007.wav");
    uVar2 = FUN_005c8250("svartl",2,"artl_1",0,0);
    *(undefined4 *)(local_1c + 0x114) = uVar2;
    uVar2 = FUN_005c8250("svartl",2,"artl_2",0,0);
    *(undefined4 *)(local_1c + 0x118) = uVar2;
    local_44 = FUN_005c8250("svfigh",2,"artl_defend",0,0);
    FUN_005cbce0(local_44,*(undefined4 *)(local_1c + 0x114),1);
    local_44 = FUN_005c8250("svfigh",2,"artl_defend",0,0);
    FUN_005cbce0(local_44,*(undefined4 *)(local_1c + 0x114),1);
    local_44 = FUN_005c8250("svfigh",2,"artl_defend",0,0);
    FUN_005cbce0(local_44,*(undefined4 *)(local_1c + 0x118),1);
    local_44 = FUN_005c8250("svfigh",2,"artl_defend",0,0);
    FUN_005cbce0(local_44,*(undefined4 *)(local_1c + 0x118),1);
    fVar6 = (float10)FUN_004b1670();
    local_12c = (float)fVar6;
    *(float *)(local_1c + 0xb8) = local_12c + 300.0;
    fVar6 = (float10)FUN_004b1670();
    local_134 = (float)fVar6;
    *(float *)(local_1c + 0xbc) = local_134 + 300.0 + 20.0;
  }
  fVar6 = (float10)FUN_004b1670();
  local_13c = (float)fVar6;
  if (*(float *)(local_1c + 0xb4) <= local_13c && local_13c != *(float *)(local_1c + 0xb4)) {
    *(undefined4 *)(local_1c + 0xb4) = 0x497423fe;
    FUN_005c8250("apwrck",0,"day_6",0,0);
  }
  fVar6 = (float10)FUN_004b1670();
  local_144 = (float)fVar6;
  if (*(float *)(local_1c + 0xb8) <= local_144 && local_144 != *(float *)(local_1c + 0xb8)) {
    *(undefined4 *)(local_1c + 0xb8) = 0x497423fe;
    FUN_005c8250("apwrck",0,"day_7",0,0);
  }
  fVar6 = (float10)FUN_004b1670();
  local_14c = (float)fVar6;
  if (*(float *)(local_1c + 0xbc) <= local_14c && local_14c != *(float *)(local_1c + 0xbc)) {
    *(undefined4 *)(local_1c + 0xbc) = 0x497423fe;
    FUN_005c8250("apwrck",0,"day_8",0,0);
  }
  if ((*(int *)(local_1c + 0x114) != 0) && (*(int *)(local_1c + 0x118) != 0)) {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(local_1c + 0x114));
    local_1dc = (double)fVar6;
    if (local_1dc <= 0.0) {
      fVar6 = (float10)FUN_005cced0(*(undefined4 *)(local_1c + 0x118));
      local_1e8 = (double)fVar6;
      if (local_1e8 <= 0.0) {
        *(undefined4 *)(local_1c + 0x114) = 0;
        *(undefined4 *)(local_1c + 0x118) = 0;
        *(undefined4 *)(local_1c + 0xa0) = 0x497423fe;
        *(undefined4 *)(local_1c + 0xa4) = 0x497423fe;
        *(undefined4 *)(local_1c + 0xa8) = 0x497423fe;
        *(undefined4 *)(local_1c + 0xac) = 0x497423fe;
        *(undefined4 *)(local_1c + 0xb0) = 0x497423fe;
        *(undefined4 *)(local_1c + 0xb4) = 0x497423fe;
        *(undefined4 *)(local_1c + 0xb8) = 0x497423fe;
        *(undefined4 *)(local_1c + 0xbc) = 0x497423fe;
      }
    }
  }
  fVar6 = (float10)FUN_004b1670();
  local_154 = (float)fVar6;
  if (*(float *)(local_1c + 0xc0) <= local_154 && local_154 != *(float *)(local_1c + 0xc0)) {
    fVar6 = (float10)FUN_004b1670();
    local_15c = (float)fVar6;
    *(float *)(local_1c + 0xc0) = local_15c + 240.0;
    local_1b8[0] = "annoy_path_1";
    local_1b8[1] = "annoy_path_2";
    uVar5 = rand();
    uVar5 = uVar5 & 0x80000001;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
    }
    local_48 = local_1b8[uVar5];
    local_38 = FUN_005c8250("svltnk",2,"annoy_1",0,0);
    FUN_005cb960(local_38,local_48,1);
    local_38 = FUN_005c8250("svltnk",2,"annoy_1",0,0);
    FUN_005cb960(local_38,local_48,1);
    local_38 = FUN_005c8250("svtank",2,"annoy_1",0,0);
    FUN_005cb960(local_38,local_48,1);
    local_38 = FUN_005c8250("svtank",2,"annoy_1",0,0);
    FUN_005cb960(local_38,local_48,1);
    local_38 = FUN_005c8250("svrckt",2,"annoy_1",0,0);
    FUN_005cb960(local_38,local_48,1);
    local_38 = FUN_005c8250("svfigh",2,"annoy_1",0,0);
    FUN_005cb960(local_38,local_48,1);
  }
  if ((*(int *)(local_1c + 0x100) != 0) && (*(int *)(local_1c + 0x104) != 0)) {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(local_1c + 0x100));
    local_164 = (float)fVar6;
    if (local_164 <= 0.0) {
      fVar6 = (float10)FUN_005cced0(*(undefined4 *)(local_1c + 0x104));
      local_16c = (float)fVar6;
      if (((local_16c <= 0.0) && (*(char *)(local_1c + 0x65) == '\0')) &&
         (*(char *)(local_1c + 100) == '\0')) {
        *(undefined1 *)(local_1c + 0x65) = 1;
        fVar6 = (float10)FUN_004b1670("ch05lsec.des");
        local_174 = (float)fVar6;
        FUN_0045c0f0(local_174 + 1.0);
      }
    }
  }
  if (((*(char *)(local_1c + 0x62) != '\0') && (*(char *)(local_1c + 100) == '\0')) &&
     (*(char *)(local_1c + 0x65) == '\0')) {
    *(undefined1 *)(local_1c + 100) = 1;
    for (local_40 = 0; local_40 < *(int *)(local_1c + 0x184); local_40 = local_40 + 1) {
      cVar1 = FUN_005c84d0(local_1c + 0x11c + local_40 * 4);
      if (cVar1 != '\0') {
        *(undefined1 *)(local_1c + 100) = 0;
        break;
      }
    }
    if (*(char *)(local_1c + 100) != '\0') {
      fVar6 = (float10)FUN_004b1670("ch05win.des");
      local_17c = (float)fVar6;
      FUN_0045c110(local_17c + 1.0);
    }
  }
  FUN_0083e885();
  return;
}

