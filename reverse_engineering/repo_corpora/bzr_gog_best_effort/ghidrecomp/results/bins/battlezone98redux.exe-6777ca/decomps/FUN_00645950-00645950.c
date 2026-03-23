
void __fastcall FUN_00645950(int param_1)

{
  bool bVar1;
  undefined1 uVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  int local_80;
  char *local_78 [4];
  char *local_68;
  char *local_64;
  char *local_60;
  char *local_5c;
  char *local_58;
  char *local_54 [4];
  char *local_44;
  char *local_40;
  char *local_3c;
  char *local_38 [4];
  char *local_28;
  char *local_24;
  char *local_20 [4];
  char *local_10;
  char *local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x84);
  uVar4 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x84) = uVar4;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,0x1e);
    FUN_005cacb0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar6 + 180.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar6 + 600.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar6 + 900.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar6 + 1800.0;
    FUN_004f6ae0(0xa8c,0x1e,10);
    uVar4 = FUN_005c7e90("nav_chin_silo1");
    FUN_005cd7f0(uVar4,"Scrap Field");
    uVar4 = FUN_005c7e90("nav_chin_silo2");
    FUN_005cd7f0(uVar4,"Scrap Field");
    uVar4 = FUN_005c7e90("nav_chin_silo3");
    FUN_005cd7f0(uVar4,"Scrap Field");
    uVar4 = FUN_005c7e90("nav_chin_silo4");
    FUN_005cd7f0(uVar4,"Scrap Field");
    uVar4 = FUN_005c7e90("nav_chin_silo5");
    FUN_005cd7f0(uVar4,"Scrap Field");
    uVar4 = FUN_005c7e90("nav_chin_silo6");
    FUN_005cd7f0(uVar4,"Scrap Field");
  }
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_1 + 0xb0);
  uVar4 = FUN_005cae10(1);
  *(undefined4 *)(param_1 + 0xb0) = uVar4;
  if (*(char *)(param_1 + 0x5a) == '\0') {
    if (*(char *)(param_1 + 0x58) == '\0') {
      FUN_005cd2a0();
      *(undefined1 *)(param_1 + 0x58) = 1;
      uVar4 = FUN_00437d30("bd13001.wav");
      *(undefined4 *)(param_1 + 0xb8) = uVar4;
    }
    bVar1 = false;
    if (*(char *)(param_1 + 0x6b) == '\0') {
      uVar2 = FUN_005cd300("camera_intro",500,0x5dc,*(undefined4 *)(param_1 + 0xa8));
      *(undefined1 *)(param_1 + 0x6b) = uVar2;
    }
    if ((*(char *)(param_1 + 0x6b) != '\0') &&
       (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0xb8)), cVar3 != '\0')) {
      bVar1 = true;
    }
    cVar3 = FUN_005cd560();
    if (cVar3 != '\0') {
      bVar1 = true;
      FUN_00437d80(*(undefined4 *)(param_1 + 0xb8));
    }
    if (bVar1) {
      *(undefined1 *)(param_1 + 0x5a) = 1;
      FUN_005cd4e0();
      FUN_004f6aa0();
      FUN_004f6ab0("bd13001.otf",DAT_0091755c,0x41000000,0);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x70)) {
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    local_54[0] = "cvfigh";
    local_54[1] = "cvfigh";
    local_54[2] = "cvfigh";
    local_54[3] = "cvfigh";
    local_44 = "cvltnk";
    local_40 = "cvltnk";
    local_3c = "cvtnk";
    for (local_80 = 0; local_80 < 7; local_80 = local_80 + 1) {
      uVar4 = FUN_005c8250(local_54[local_80],2,"spawn_attack_waves",0,0);
      FUN_005cb9d0(uVar4,*(undefined4 *)(param_1 + 0x8c),1);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x74)) {
    *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    local_20[0] = "cvrckt";
    local_20[1] = "cvrckt";
    local_20[2] = "cvltnk";
    local_20[3] = "cvltnk";
    local_10 = "cvtnk";
    local_c = "cvtnk";
    for (local_80 = 0; local_80 < 6; local_80 = local_80 + 1) {
      uVar4 = FUN_005c8250(local_20[local_80],2,"spawn_attack_waves",0,0);
      FUN_005cb9d0(uVar4,*(undefined4 *)(param_1 + 0x8c),1);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x78) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x78)) {
    *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
    local_78[0] = "cvhraz";
    local_78[1] = "cvhraz";
    local_78[2] = "cvhraz";
    local_78[3] = "cvfigh";
    local_68 = "cvfigh";
    local_64 = "cvfigh";
    local_60 = "cvfigh";
    local_5c = "cvfigh";
    local_58 = "cvfigh";
    for (local_80 = 0; local_80 < 9; local_80 = local_80 + 1) {
      uVar4 = FUN_005c8250(local_78[local_80],2,"spawn_attack_waves",0,0);
      FUN_005cb9d0(uVar4,*(undefined4 *)(param_1 + 0x8c),1);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x7c)) {
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    local_38[0] = "cvfigh";
    local_38[1] = "cvfigh";
    local_38[2] = "cvfigh";
    local_38[3] = "cvfigh";
    local_28 = "cvhtnk";
    local_24 = "cvhtnk";
    for (local_80 = 0; local_80 < 6; local_80 = local_80 + 1) {
      uVar4 = FUN_005c8250(local_38[local_80],2,"spawn_attack_waves",0,0);
      FUN_005cb9d0(uVar4,*(undefined4 *)(param_1 + 0x8c),1);
    }
  }
  if ((*(char *)(param_1 + 0x5c) == '\0') &&
     (fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0x94))
     , (float)fVar6 != 0.0)) {
    *(undefined1 *)(param_1 + 0x5c) = 1;
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x94),1);
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x94),1);
    uVar4 = FUN_005c8250("cvltnk",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x94),1);
    uVar4 = FUN_005c8250("cvltnk",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x94),1);
  }
  if ((*(char *)(param_1 + 0x5d) == '\0') &&
     (fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0x98))
     , (float)fVar6 != 0.0)) {
    *(undefined1 *)(param_1 + 0x5d) = 1;
    uVar4 = FUN_005c8250("cvltnk",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x98),1);
    uVar4 = FUN_005c8250("cvltnk",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x98),1);
    uVar4 = FUN_005c8250("cvltnk",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x98),1);
    uVar4 = FUN_005c8250("cvltnk",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x98),1);
  }
  if ((*(char *)(param_1 + 0x5e) == '\0') &&
     (fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0x9c))
     , (float)fVar6 != 0.0)) {
    *(undefined1 *)(param_1 + 0x5e) = 1;
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x9c),1);
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x9c),1);
    uVar4 = FUN_005c8250("cvrckt",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x9c),1);
    uVar4 = FUN_005c8250("cvrckt",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0x9c),1);
  }
  if ((*(char *)(param_1 + 0x5f) == '\0') &&
     (fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0xa0))
     , (float)fVar6 != 0.0)) {
    *(undefined1 *)(param_1 + 0x5f) = 1;
    uVar4 = FUN_005c8250("cvtnk",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvltnk",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvltnk",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa0),1);
  }
  if ((*(char *)(param_1 + 0x60) == '\0') &&
     (fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0xa4))
     , (float)fVar6 != 0.0)) {
    *(undefined1 *)(param_1 + 0x60) = 1;
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
  }
  if ((*(char *)(param_1 + 0x61) == '\0') &&
     (fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0xa8))
     , (float)fVar6 != 0.0)) {
    *(undefined1 *)(param_1 + 0x61) = 1;
    uVar4 = FUN_005c8250("cvhtnk",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    uVar4 = FUN_005c8250("cvhtnk",2,"spawn_defend1",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    uVar4 = FUN_005c8250("cvfigh",2,"spawn_defend6",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
  }
  if ((((*(char *)(param_1 + 0x69) == '\0') && (iVar5 = FUN_004f6b10(), (double)iVar5 <= 0.0)) &&
      (*(char *)(param_1 + 0x6c) == '\0')) && (*(char *)(param_1 + 0x6d) == '\0')) {
    *(undefined1 *)(param_1 + 0x69) = 1;
    if (*(char *)(param_1 + 0x68) == '\0') {
      *(undefined1 *)(param_1 + 0x6c) = 1;
      uVar4 = FUN_00437d30("bd13005.wav");
      *(undefined4 *)(param_1 + 0xc4) = uVar4;
    }
    else {
      FUN_004ff160();
    }
  }
  if ((*(int *)(param_1 + 0xc4) != 0) &&
     (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0xc4)), cVar3 != '\0')) {
    *(undefined4 *)(param_1 + 0xc4) = 0;
    fVar6 = (float10)FUN_004b1670("bd13lsea.des");
    FUN_0045c0f0((float)fVar6 + 1.0);
  }
  if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x6c) == '\0')) &&
     (*(char *)(param_1 + 0x6d) == '\0')) {
    for (local_80 = 0; local_80 < 6; local_80 = local_80 + 1) {
      if ((*(char *)(param_1 + local_80 + 0x62) == '\0') &&
         (fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x94 + local_80 * 4)),
         (double)fVar6 <= 0.0)) {
        cVar3 = FUN_005ce3a0(*(undefined4 *)(param_1 + 0x94 + local_80 * 4),1);
        if (cVar3 == '\0') {
          *(undefined1 *)(param_1 + 0x6c) = 1;
          fVar6 = (float10)FUN_004b1670("bd13lsec.des");
          FUN_0045c0f0((float)fVar6 + 1.0);
        }
        else {
          *(undefined1 *)(param_1 + local_80 + 0x62) = 1;
        }
      }
    }
    *(undefined1 *)(param_1 + 0x68) = 1;
    for (local_80 = 0; local_80 < 6; local_80 = local_80 + 1) {
      if (*(char *)(param_1 + local_80 + 0x62) == '\0') {
        *(undefined1 *)(param_1 + 0x68) = 0;
      }
    }
  }
  if ((*(char *)(param_1 + 0x68) != '\0') && (*(char *)(param_1 + 0x6a) == '\0')) {
    FUN_004ff160();
    *(undefined1 *)(param_1 + 0x69) = 1;
    *(undefined1 *)(param_1 + 0x6a) = 1;
    FUN_00437d30("bd13002.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("bd13001.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("bd13002.otf",DAT_0091755c,0x41000000,0);
  }
  fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x8c));
  if ((((double)fVar6 <= 0.0) && (*(char *)(param_1 + 0x6c) == '\0')) &&
     (*(char *)(param_1 + 0x6d) == '\0')) {
    *(undefined1 *)(param_1 + 0x6c) = 1;
    uVar4 = FUN_00437d30("bd13004.wav");
    *(undefined4 *)(param_1 + 0xc0) = uVar4;
  }
  if ((*(int *)(param_1 + 0xc0) != 0) &&
     (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0xc0)), cVar3 != '\0')) {
    *(undefined4 *)(param_1 + 0xc0) = 0;
    fVar6 = (float10)FUN_004b1670("bd13lseb.des");
    FUN_0045c0f0((float)fVar6 + 1.0);
  }
  fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x90));
  if ((((double)fVar6 < 1.0) && (*(char *)(param_1 + 0x68) == '\0')) &&
     ((*(char *)(param_1 + 0x6c) == '\0' && (*(char *)(param_1 + 0x6d) == '\0')))) {
    *(undefined1 *)(param_1 + 0x6c) = 1;
    fVar6 = (float10)FUN_004b1670("bd13lsed.des");
    FUN_0045c0f0((float)fVar6 + 1.0);
  }
  fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x90));
  if (((((double)fVar6 <= 0.0) && (*(char *)(param_1 + 0x68) != '\0')) &&
      (*(char *)(param_1 + 0x6d) == '\0')) && (*(char *)(param_1 + 0x6c) == '\0')) {
    *(undefined1 *)(param_1 + 0x6d) = 1;
    uVar4 = FUN_00437d30("bd13003.wav");
    *(undefined4 *)(param_1 + 0xbc) = uVar4;
  }
  if ((*(int *)(param_1 + 0xbc) != 0) &&
     (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0xbc)), cVar3 != '\0')) {
    *(undefined4 *)(param_1 + 0xbc) = 0;
    fVar6 = (float10)FUN_004b1670("bd13win.des");
    FUN_0045c110((float)fVar6 + 1.0);
  }
  FUN_0083e885();
  return;
}

