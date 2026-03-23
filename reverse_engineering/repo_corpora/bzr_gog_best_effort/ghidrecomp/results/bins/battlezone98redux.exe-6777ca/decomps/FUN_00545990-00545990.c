
void FUN_00545990(void)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_e4 [4];
  undefined1 local_e0 [4];
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
  undefined4 local_84;
  float local_80;
  undefined4 local_7c;
  float local_78;
  float local_74;
  float local_70;
  int local_6c;
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
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  int local_18;
  undefined1 local_14 [4];
  undefined4 local_10;
  int local_c;
  int local_8;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(local_8 + 0xac) = uVar2;
  if (*(char *)(local_8 + 0x54) == '\0') {
    uVar2 = FUN_005c7e90("avrecy-1_recycler");
    *(undefined4 *)(local_8 + 0xb0) = uVar2;
    uVar2 = FUN_005c7e90("svrecy-1_recycler");
    *(undefined4 *)(local_8 + 0xc4) = uVar2;
    uVar2 = FUN_005c7e90("sbbarr0_i76building");
    *(undefined4 *)(local_8 + 200) = uVar2;
    FUN_005cb2d0(&DAT_0087b758,2);
    FUN_005cac80(2,0x1e);
    FUN_005cadd0(1,0x1e);
    FUN_005cadd0(2,0x2d);
    uVar2 = FUN_005c7e90("apcamr0_camerapod");
    *(undefined4 *)(local_8 + 0xb4) = uVar2;
    uVar2 = FUN_005c7e90("apcamr1_camerapod");
    *(undefined4 *)(local_8 + 0xb8) = uVar2;
    uVar2 = FUN_005c7e90("apcamr2_camerapod");
    *(undefined4 *)(local_8 + 0xbc) = uVar2;
    uVar2 = FUN_005c7e90("apcamr3_camerapod");
    *(undefined4 *)(local_8 + 0xc0) = uVar2;
    uVar2 = FUN_005c7e90("sbtowe0_turret");
    *(undefined4 *)(local_8 + 0xdc) = uVar2;
    uVar2 = FUN_005c7e90("sbtowe1_turret");
    *(undefined4 *)(local_8 + 0xe0) = uVar2;
    uVar2 = FUN_005c7e90("sbtowe55_turret");
    *(undefined4 *)(local_8 + 0xe4) = uVar2;
    uVar2 = FUN_005c7e90("sbtowe56_turret");
    *(undefined4 *)(local_8 + 0xe8) = uVar2;
    uVar2 = FUN_005c7e90("sblpow1_powerplant");
    *(undefined4 *)(local_8 + 0xec) = uVar2;
    uVar2 = FUN_005c7e90("sblpow55_powerplant");
    *(undefined4 *)(local_8 + 0xf0) = uVar2;
    FUN_005c9640(*(undefined4 *)(local_8 + 0xb4),"Foothill Geysers");
    FUN_005c9640(*(undefined4 *)(local_8 + 0xb8),"Canyon Geysers");
    FUN_005c9640(*(undefined4 *)(local_8 + 0xbc),"CCA Base");
    FUN_005c9640(*(undefined4 *)(local_8 + 0xc0),"Plateau Geysers");
    *(undefined1 *)(local_8 + 0x54) = 1;
    fVar5 = (float10)FUN_004b1670();
    local_78 = (float)fVar5;
    *(float *)(local_8 + 0x94) = local_78 + 1.0;
    *(undefined1 *)(local_8 + 0x55) = 1;
    FUN_005cd2a0();
    fVar5 = (float10)FUN_004b1670();
    local_28 = (float)fVar5;
    *(float *)(local_8 + 0x70) = local_28 + 12.0;
    uVar2 = FUN_00437d30("misn1401.wav");
    *(undefined4 *)(local_8 + 0xa8) = uVar2;
    cVar1 = FUN_005c84d0(local_8 + 200);
    if (cVar1 != '\0') {
      FUN_005ccfa0(*(undefined4 *)(local_8 + 200),0x47c35000);
      fVar5 = (float10)FUN_004b1670();
      local_88 = (float)fVar5;
      *(float *)(local_8 + 0x94) = local_88 + 1.0;
    }
  }
  if (*(char *)(local_8 + 0x55) != '\0') {
    FUN_005cd300("cam_path1",2000,1000,*(undefined4 *)(local_8 + 0xb0));
  }
  if (*(char *)(local_8 + 0x55) != '\0') {
    fVar5 = (float10)FUN_004b1670();
    local_30 = (float)fVar5;
    if ((*(float *)(local_8 + 0x70) <= local_30 && local_30 != *(float *)(local_8 + 0x70)) ||
       (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
      *(undefined1 *)(local_8 + 0x55) = 0;
      *(undefined1 *)(local_8 + 0x56) = 1;
      fVar5 = (float10)FUN_004b1670();
      local_b8 = (float)fVar5;
      *(float *)(local_8 + 0x70) = local_b8 + 15.0;
    }
  }
  if (*(char *)(local_8 + 0x56) != '\0') {
    FUN_005cd300("cam_path2",2000,500,*(undefined4 *)(local_8 + 0xb0));
  }
  if (*(char *)(local_8 + 0x56) != '\0') {
    fVar5 = (float10)FUN_004b1670();
    local_38 = (float)fVar5;
    if ((*(float *)(local_8 + 0x70) <= local_38 && local_38 != *(float *)(local_8 + 0x70)) ||
       (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
      FUN_00437d80(*(undefined4 *)(local_8 + 0xa8));
      *(undefined1 *)(local_8 + 0x56) = 0;
      FUN_005cd4e0();
      FUN_004f6aa0();
      FUN_004f6ab0("misn1401.otf",DAT_0091755c,0x41000000,0);
      fVar5 = (float10)FUN_00822d80();
      local_90 = (float)fVar5;
      *(float *)(local_8 + 0x74) = local_90 + 720.0;
      fVar5 = (float10)FUN_004b1670();
      local_40 = (float)fVar5;
      *(float *)(local_8 + 0x7c) = local_40 + 15.0;
    }
  }
  fVar5 = (float10)FUN_004b1670();
  local_d0 = (float)fVar5;
  if (*(float *)(local_8 + 0x7c) <= local_d0 && local_d0 != *(float *)(local_8 + 0x7c)) {
    FUN_00437d30("misn1416.wav");
    *(undefined4 *)(local_8 + 0x7c) = 0x47c34f80;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"rescue1",0,0);
    *(undefined4 *)(local_8 + 0x9c) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help1",0,0);
    *(undefined4 *)(local_8 + 0xd0) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help2",0,0);
    *(undefined4 *)(local_8 + 0xd4) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help3",0,0);
    *(undefined4 *)(local_8 + 0xd8) = uVar2;
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd0),0);
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd4),0);
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd8),0);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd0),1);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd4),1);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd8),1);
    FUN_005c9640(*(undefined4 *)(local_8 + 0x9c),"Rescue 1");
    FUN_005c95e0(*(undefined4 *)(local_8 + 0x9c));
  }
  if (*(int *)(local_8 + 0x9c) != 0) {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xac),*(undefined4 *)(local_8 + 0x9c));
    local_48 = (float)fVar5;
    if ((local_48 < 200.0) && (*(char *)(local_8 + 0x5e) == '\0')) {
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xcc),*(undefined4 *)(local_8 + 0x9c))
      ;
      local_98 = (float)fVar5;
      if (300.0 < local_98) {
        FUN_00437d30("misn1415.wav");
        *(undefined1 *)(local_8 + 0x5e) = 1;
      }
    }
  }
  if ((((*(char *)(local_8 + 0x62) == '\0') && (*(int *)(local_8 + 0x9c) != 0)) &&
      (*(char *)(local_8 + 0x69) == '\0')) &&
     (((cVar1 = FUN_005c84d0(local_8 + 0xd0), cVar1 == '\0' ||
       (cVar1 = FUN_005c84d0(local_8 + 0xd4), cVar1 == '\0')) ||
      (cVar1 = FUN_005c84d0(local_8 + 0xd8), cVar1 == '\0')))) {
    FUN_00437d30("misn1421.wav");
    fVar5 = (float10)FUN_004b1670("misn14l2.des");
    local_50 = (float)fVar5;
    FUN_0045c0f0(local_50 + 15.0);
    *(undefined1 *)(local_8 + 0x62) = 1;
  }
  if (((*(int *)(local_8 + 0x9c) != 0) && (*(int *)(local_8 + 0xcc) != 0)) &&
     (*(char *)(local_8 + 0x69) == '\0')) {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xcc),*(undefined4 *)(local_8 + 0x9c));
    local_c0 = (float)fVar5;
    if (local_c0 < 100.0) {
      *(undefined1 *)(local_8 + 0x69) = 1;
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd0),*(undefined4 *)(local_8 + 0x9c),1);
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd4),*(undefined4 *)(local_8 + 0x9c),1);
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd8),*(undefined4 *)(local_8 + 0x9c),1);
      fVar5 = (float10)FUN_004b1670();
      local_58 = (float)fVar5;
      *(float *)(local_8 + 0x88) = local_58 + 25.0;
      FUN_00437d30("misn1409.wav");
      fVar5 = (float10)FUN_004b1670();
      local_a0 = (float)fVar5;
      *(float *)(local_8 + 0x70) = local_a0 + 3.0;
      FUN_005cd2a0();
      *(undefined1 *)(local_8 + 0x66) = 1;
    }
  }
  if (*(char *)(local_8 + 0x66) != '\0') {
    FUN_005cd440(*(undefined4 *)(local_8 + 0xcc),1000,1000,1000,*(undefined4 *)(local_8 + 0xcc));
    cVar1 = FUN_005cd560();
    if (cVar1 == '\0') {
      fVar5 = (float10)FUN_004b1670();
      local_60 = (float)fVar5;
      if (local_60 < *(float *)(local_8 + 0x70) || local_60 == *(float *)(local_8 + 0x70))
      goto LAB_005461c3;
    }
    FUN_005cd4e0();
    *(undefined1 *)(local_8 + 0x66) = 0;
  }
LAB_005461c3:
  if ((*(int *)(local_8 + 0x9c) != 0) && (*(char *)(local_8 + 0x69) != '\0')) {
    fVar5 = (float10)FUN_004b1670();
    local_dc = (float)fVar5;
    if (*(float *)(local_8 + 0x88) <= local_dc && local_dc != *(float *)(local_8 + 0x88)) {
      cVar1 = FUN_005c84d0(local_8 + 0xd0);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd0));
      }
      cVar1 = FUN_005c84d0(local_8 + 0xd4);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd4));
      }
      cVar1 = FUN_005c84d0(local_8 + 0xd8);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd8));
      }
      cVar1 = FUN_005c84d0(local_8 + 0x9c);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0x9c));
      }
      fVar5 = (float10)FUN_004b1670();
      local_68 = (float)fVar5;
      *(float *)(local_8 + 0x80) = local_68 + 10.0;
      FUN_005cd2a0();
      FUN_00437d30("misn1417.wav");
      *(undefined1 *)(local_8 + 99) = 1;
      *(undefined4 *)(local_8 + 0x88) = 0x47c34f80;
      fVar5 = (float10)FUN_004b1670();
      local_a8 = (float)fVar5;
      *(float *)(local_8 + 0x70) = local_a8 + 3.0;
    }
  }
  if (*(char *)(local_8 + 99) != '\0') {
    FUN_005cd440(*(undefined4 *)(local_8 + 0xcc),1000,1000,1000,*(undefined4 *)(local_8 + 0xcc));
    cVar1 = FUN_005cd560();
    if (cVar1 == '\0') {
      fVar5 = (float10)FUN_004b1670();
      local_70 = (float)fVar5;
      if (local_70 < *(float *)(local_8 + 0x70) || local_70 == *(float *)(local_8 + 0x70))
      goto LAB_00546383;
    }
    FUN_005cd4e0();
    *(undefined1 *)(local_8 + 99) = 0;
  }
LAB_00546383:
  fVar5 = (float10)FUN_004b1670();
  local_c8 = (float)fVar5;
  if (*(float *)(local_8 + 0x80) <= local_c8 && local_c8 != *(float *)(local_8 + 0x80)) {
    *(undefined4 *)(local_8 + 0x80) = 0x47c34f80;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"rescue2",0,0);
    *(undefined4 *)(local_8 + 0xa0) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help4",0,0);
    *(undefined4 *)(local_8 + 0xd0) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help5",0,0);
    *(undefined4 *)(local_8 + 0xd4) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help6",0,0);
    *(undefined4 *)(local_8 + 0xd8) = uVar2;
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd0),0);
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd4),0);
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd8),0);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd0),1);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd4),1);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd8),1);
    FUN_005c9640(*(undefined4 *)(local_8 + 0xa0),"Rescue 2");
    FUN_005c95e0(*(undefined4 *)(local_8 + 0xa0));
  }
  if ((((*(char *)(local_8 + 0x62) == '\0') && (*(int *)(local_8 + 0xa0) != 0)) &&
      (*(char *)(local_8 + 0x6a) == '\0')) &&
     (((cVar1 = FUN_005c84d0(local_8 + 0xd0), cVar1 == '\0' ||
       (cVar1 = FUN_005c84d0(local_8 + 0xd4), cVar1 == '\0')) ||
      (cVar1 = FUN_005c84d0(local_8 + 0xd8), cVar1 == '\0')))) {
    *(undefined1 *)(local_8 + 0x62) = 1;
    FUN_00437d30("misn1421.wav");
    fVar5 = (float10)FUN_004b1670("misn14l2.des");
    local_20 = (float)fVar5;
    FUN_0045c0f0(local_20 + 15.0);
  }
  if (((*(int *)(local_8 + 0xa0) != 0) && (*(int *)(local_8 + 0xcc) != 0)) &&
     (*(char *)(local_8 + 0x6a) == '\0')) {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xcc),*(undefined4 *)(local_8 + 0xa0));
    local_b0 = (float)fVar5;
    if (local_b0 < 100.0) {
      *(undefined1 *)(local_8 + 0x6a) = 1;
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd0),*(undefined4 *)(local_8 + 0xa0),1);
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd4),*(undefined4 *)(local_8 + 0xa0),1);
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd8),*(undefined4 *)(local_8 + 0xa0),1);
      fVar5 = (float10)FUN_004b1670();
      local_80 = (float)fVar5;
      *(float *)(local_8 + 0x8c) = local_80 + 25.0;
      FUN_00437d30("misn1409.wav");
    }
  }
  if ((*(int *)(local_8 + 0xa0) != 0) && (*(char *)(local_8 + 0x6a) != '\0')) {
    fVar5 = (float10)FUN_004b1670();
    local_d8 = (float)fVar5;
    if (*(float *)(local_8 + 0x8c) <= local_d8 && local_d8 != *(float *)(local_8 + 0x8c)) {
      cVar1 = FUN_005c84d0(local_8 + 0xd0);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd0));
      }
      cVar1 = FUN_005c84d0(local_8 + 0xd4);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd4));
      }
      cVar1 = FUN_005c84d0(local_8 + 0xd8);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd8));
      }
      cVar1 = FUN_005c84d0(local_8 + 0xa0);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xa0));
      }
      FUN_00437d30("misn1418.wav");
      *(undefined4 *)(local_8 + 0x8c) = 0x47c34f80;
      fVar5 = (float10)FUN_004b1670();
      local_24 = (float)fVar5;
      *(float *)(local_8 + 0x84) = local_24 + 10.0;
    }
  }
  fVar5 = (float10)FUN_004b1670();
  local_2c = (float)fVar5;
  if (*(float *)(local_8 + 0x84) <= local_2c && local_2c != *(float *)(local_8 + 0x84)) {
    *(undefined4 *)(local_8 + 0x84) = 0x47c34f80;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"rescue3",0,0);
    *(undefined4 *)(local_8 + 0xa4) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help7",0,0);
    *(undefined4 *)(local_8 + 0xd0) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help8",0,0);
    *(undefined4 *)(local_8 + 0xd4) = uVar2;
    uVar2 = FUN_005c8250("aspilo",1,"help9",0,0);
    *(undefined4 *)(local_8 + 0xd8) = uVar2;
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd0),0);
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd4),0);
    FUN_005cb620(*(undefined4 *)(local_8 + 0xd8),0);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd0),1);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd4),1);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xd8),1);
    FUN_005c9640(*(undefined4 *)(local_8 + 0xa4),"Rescue 3");
    FUN_005c95e0(*(undefined4 *)(local_8 + 0xa4));
  }
  if ((((*(char *)(local_8 + 0x62) == '\0') && (*(int *)(local_8 + 0xa4) != 0)) &&
      (*(char *)(local_8 + 0x6b) == '\0')) &&
     (((cVar1 = FUN_005c84d0(local_8 + 0xd0), cVar1 == '\0' ||
       (cVar1 = FUN_005c84d0(local_8 + 0xd4), cVar1 == '\0')) ||
      (cVar1 = FUN_005c84d0(local_8 + 0xd8), cVar1 == '\0')))) {
    *(undefined1 *)(local_8 + 0x62) = 1;
    FUN_00437d30("misn1421.wav");
    fVar5 = (float10)FUN_004b1670("misn14l2.des");
    local_34 = (float)fVar5;
    FUN_0045c0f0(local_34 + 15.0);
  }
  if (((*(int *)(local_8 + 0xa4) != 0) && (*(int *)(local_8 + 0xcc) != 0)) &&
     (*(char *)(local_8 + 0x6b) == '\0')) {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xcc),*(undefined4 *)(local_8 + 0xa4));
    local_3c = (float)fVar5;
    if (local_3c < 100.0) {
      *(undefined1 *)(local_8 + 0x6b) = 1;
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd0),*(undefined4 *)(local_8 + 0xa4),1);
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd4),*(undefined4 *)(local_8 + 0xa4),1);
      FUN_005cb9d0(*(undefined4 *)(local_8 + 0xd8),*(undefined4 *)(local_8 + 0xa4),1);
      fVar5 = (float10)FUN_004b1670();
      local_44 = (float)fVar5;
      *(float *)(local_8 + 0x90) = local_44 + 25.0;
      FUN_00437d30("misn1409.wav");
    }
  }
  if ((*(int *)(local_8 + 0xa4) != 0) && (*(char *)(local_8 + 0x6b) != '\0')) {
    fVar5 = (float10)FUN_004b1670();
    local_4c = (float)fVar5;
    if (*(float *)(local_8 + 0x90) <= local_4c && local_4c != *(float *)(local_8 + 0x90)) {
      cVar1 = FUN_005c84d0(local_8 + 0xd0);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd0));
      }
      cVar1 = FUN_005c84d0(local_8 + 0xd4);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd4));
      }
      cVar1 = FUN_005c84d0(local_8 + 0xd8);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xd8));
      }
      cVar1 = FUN_005c84d0(local_8 + 0xa4);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(local_8 + 0xa4));
      }
      FUN_00437d30("misn1419.wav");
      *(undefined4 *)(local_8 + 0x90) = 0x47c34f80;
      FUN_004f6aa0();
      FUN_004f6ab0("misn1401.otf",DAT_009175b0,0x41000000,0);
    }
  }
  cVar1 = FUN_005c84d0(local_8 + 200);
  if (cVar1 != '\0') {
    fVar5 = (float10)FUN_004b1670();
    local_54 = (float)fVar5;
    if (*(float *)(local_8 + 0x94) <= local_54 && local_54 != *(float *)(local_8 + 0x94)) {
      FUN_005ccfd0(*(undefined4 *)(local_8 + 200),0x459c4000);
      fVar5 = (float10)FUN_004b1670();
      local_5c = (float)fVar5;
      *(float *)(local_8 + 0x94) = local_5c + 1.0;
    }
  }
  fVar5 = (float10)FUN_00822d80();
  local_64 = (float)fVar5;
  if (*(float *)(local_8 + 0x74) <= local_64 && local_64 != *(float *)(local_8 + 0x74)) {
    *(undefined1 *)(local_8 + 0x59) = 1;
    *(int *)(local_8 + 0xf8) = *(int *)(local_8 + 0xf8) + 1;
    local_6c = rand();
    local_6c = local_6c % 3;
    local_18 = local_6c;
    if (local_6c == 0) {
      FUN_005c8250("hvsav",3,"alien1",0,0);
      FUN_005c8250("hvsav",3,"alien2",0,0);
      FUN_005c8250("hvsav",3,"alien5",0,0);
    }
    else if (local_6c == 1) {
      FUN_005c8250("hvsav",3,"alien3",0,0);
      FUN_005c8250("hvsav",3,"alien4",0,0);
      FUN_005c8250("hvsav",3,"alien1",0,0);
    }
    else if (local_6c == 2) {
      FUN_005c8250("hvsav",3,"alien5",0,0);
      FUN_005c8250("hvsav",3,"alien6",0,0);
      FUN_005c8250("hvsav",3,"alien3",0,0);
    }
    fVar5 = (float10)FUN_00822d80();
    local_74 = (float)fVar5;
    *(float *)(local_8 + 0x74) = local_74 + 180.0;
  }
  if ((*(char *)(local_8 + 0x59) != '\0') && (*(char *)(local_8 + 0x58) == '\0')) {
    FUN_00437d30("misn1403.wav");
    *(undefined1 *)(local_8 + 0x58) = 1;
  }
  if ((2 < *(int *)(local_8 + 0xf8)) && (*(char *)(local_8 + 0x5a) == '\0')) {
    FUN_00437d30("misn1404.wav");
    FUN_00437d30("misn1405.wav");
    *(undefined1 *)(local_8 + 0x5a) = 1;
    local_1c = DAT_00917a74;
    FID_conflict_begin(local_14);
    while( true ) {
      uVar2 = FID_conflict_end(local_e4);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_00421ec0();
      local_c = *piVar3;
      local_10 = FUN_00477590(local_c);
      local_7c = (**(code **)(*(int *)(local_c + 0x18) + 0x30))();
      iVar4 = FUN_00417e20(local_7c);
      if ((iVar4 != 0) && (iVar4 = (**(code **)(*(int *)(local_c + 0x18) + 4))(), iVar4 == 2)) {
        (**(code **)(*(int *)(local_c + 0x18) + 8))(0);
        cVar1 = FUN_005c8410(local_10,"svtank");
        if ((cVar1 != '\0') ||
           ((cVar1 = FUN_005c8410(local_10,"svturr"), cVar1 != '\0' ||
            (cVar1 = FUN_005c8410(local_10,"svfigh"), cVar1 != '\0')))) {
          FUN_005cc100(local_10,"escape",1);
        }
      }
      FUN_0046b260(local_e0,0);
    }
    cVar1 = FUN_005c84d0(local_8 + 200);
    if (cVar1 != '\0') {
      FUN_005c8840(*(undefined4 *)(local_8 + 200),1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xec);
    if (cVar1 != '\0') {
      FUN_005c8840(*(undefined4 *)(local_8 + 0xec),1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xf0);
    if (cVar1 != '\0') {
      FUN_005c8840(*(undefined4 *)(local_8 + 0xf0),1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xdc);
    if (cVar1 != '\0') {
      FUN_005c8840(*(undefined4 *)(local_8 + 0xdc),1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xe0);
    if (cVar1 != '\0') {
      FUN_005c8840(*(undefined4 *)(local_8 + 0xe0),1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xe4);
    if (cVar1 != '\0') {
      FUN_005c8840(*(undefined4 *)(local_8 + 0xe4),1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xe8);
    if (cVar1 != '\0') {
      FUN_005c8840(*(undefined4 *)(local_8 + 0xe8),1);
    }
  }
  if (((3 < *(int *)(local_8 + 0xf8)) && (*(char *)(local_8 + 0x5b) == '\0')) &&
     (*(char *)(local_8 + 0x6b) != '\0')) {
    FUN_005cadd0(2,0);
    uVar2 = FUN_00437d30("misn1406.wav");
    *(undefined4 *)(local_8 + 0xa8) = uVar2;
    *(undefined1 *)(local_8 + 0x5b) = 1;
    local_84 = FUN_005ca150(*(undefined4 *)(local_8 + 0xac));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xac),local_84);
    local_8c = (float)fVar5;
    if (local_8c <= 150.0) {
      *(undefined1 *)(local_8 + 0x57) = 0;
    }
    else {
      *(undefined1 *)(local_8 + 0x57) = 1;
      fVar5 = (float10)FUN_00822d80();
      local_94 = (float)fVar5;
      *(float *)(local_8 + 0x70) = local_94 + 20.0;
      FUN_005cd2a0();
    }
  }
  if (*(char *)(local_8 + 0x57) != '\0') {
    FUN_005cd300("camera_path",0x9c4,300,*(undefined4 *)(local_8 + 200));
  }
  if (*(char *)(local_8 + 0x57) != '\0') {
    fVar5 = (float10)FUN_00822d80();
    local_9c = (float)fVar5;
    if ((*(float *)(local_8 + 0x70) <= local_9c && local_9c != *(float *)(local_8 + 0x70)) ||
       (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
      FUN_00437d80(*(undefined4 *)(local_8 + 0xa8));
      *(undefined1 *)(local_8 + 0x57) = 0;
      FUN_005cd4e0();
    }
  }
  if (((4 < *(int *)(local_8 + 0xf8)) && (*(char *)(local_8 + 0x5c) == '\0')) &&
     (*(char *)(local_8 + 0x6b) != '\0')) {
    FUN_005cadd0(2,0);
    FUN_00437d30("misn1407.wav");
    *(undefined1 *)(local_8 + 0x5c) = 1;
    cVar1 = FUN_005c84d0(local_8 + 200);
    if (cVar1 == '\0') {
      FUN_0045c0f0(0x40a00000,"misn14l.des");
    }
    else {
      FUN_005c95e0(*(undefined4 *)(local_8 + 200));
      FUN_005c9640(*(undefined4 *)(local_8 + 200),"Rescue CCA");
    }
  }
  if ((((4 < *(int *)(local_8 + 0xf8)) && (*(char *)(local_8 + 0x5f) != '\0')) &&
      (*(char *)(local_8 + 0x5d) == '\0')) && (*(char *)(local_8 + 0x6b) != '\0')) {
    FUN_00437d30("misn1408.wav");
    *(undefined1 *)(local_8 + 0x5d) = 1;
  }
  if ((*(char *)(local_8 + 0x60) == '\0') && (*(char *)(local_8 + 0x5d) != '\0')) {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xcc),*(undefined4 *)(local_8 + 200));
    local_a4 = (float)fVar5;
    if (local_a4 < 200.0) {
      *(undefined1 *)(local_8 + 0x60) = 1;
      fVar5 = (float10)FUN_00822d80();
      local_ac = (float)fVar5;
      *(float *)(local_8 + 0x78) = local_ac + 15.0;
      FUN_00437d30("misn1409.wav");
    }
  }
  if (*(char *)(local_8 + 0x60) != '\0') {
    fVar5 = (float10)FUN_00822d80();
    local_b4 = (float)fVar5;
    if (*(float *)(local_8 + 0x78) <= local_b4 && local_b4 != *(float *)(local_8 + 0x78)) {
      *(undefined4 *)(local_8 + 0x78) = 0x47c34f80;
      FUN_00437d30("misn1410.wav");
    }
  }
  if (((*(char *)(local_8 + 0x62) == '\0') && (*(char *)(local_8 + 0x60) != '\0')) &&
     (cVar1 = FUN_005c84d0(local_8 + 0xcc), cVar1 == '\0')) {
    FUN_00437d30("misn1412.wav");
    FUN_00437d30("misn1413.wav");
    fVar5 = (float10)FUN_004b1670("misn14l3.des");
    local_bc = (float)fVar5;
    FUN_0045c0f0(local_bc + 10.0);
    *(undefined1 *)(local_8 + 0x62) = 1;
  }
  if ((*(char *)(local_8 + 0x61) == '\0') && (*(char *)(local_8 + 0x60) != '\0')) {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb0),*(undefined4 *)(local_8 + 0xcc));
    local_c4 = (float)fVar5;
    if (local_c4 < 300.0) {
      *(undefined1 *)(local_8 + 0x61) = 1;
      fVar5 = (float10)FUN_004b1670("misn14w1.des");
      local_cc = (float)fVar5;
      FUN_0045c110(local_cc + 10.0);
      FUN_00437d30("misn1411.wav");
    }
  }
  if ((*(char *)(local_8 + 0x62) == '\0') && (cVar1 = FUN_005c84d0(local_8 + 0xb0), cVar1 == '\0'))
  {
    FUN_00437d30("misn1414.wav");
    fVar5 = (float10)FUN_004b1670("misn14l1.des");
    local_d4 = (float)fVar5;
    FUN_0045c0f0(local_d4 + 10.0);
    *(undefined1 *)(local_8 + 0x62) = 1;
  }
  return;
}

