
void __fastcall FUN_0064d8f0(int param_1)

{
  bool bVar1;
  undefined1 uVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  float10 fVar6;
  int local_24;
  int local_c;
  
  uVar4 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x9c) = uVar4;
  FUN_005cd780(0);
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,0x41);
    FUN_005cacb0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x6c) = (float)fVar6 + 1.0;
  }
  if (*(char *)(param_1 + 0x59) == '\0') {
    if (*(char *)(param_1 + 0x57) == '\0') {
      *(undefined1 *)(param_1 + 0x57) = 1;
      FUN_005cd2a0();
    }
    bVar1 = false;
    if (*(char *)(param_1 + 0x5b) == '\0') {
      uVar2 = FUN_005cd300("camera_start",800,2000,*(undefined4 *)(param_1 + 0xa4));
      *(undefined1 *)(param_1 + 0x5b) = uVar2;
      if (*(char *)(param_1 + 0x5b) != '\0') {
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x70) = (float)fVar6 + 2.0;
      }
    }
    else {
      fVar6 = (float10)FUN_004b1670();
      if (*(float *)(param_1 + 0x70) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x70))
      {
        bVar1 = true;
      }
    }
    cVar3 = FUN_005cd560();
    if (cVar3 != '\0') {
      bVar1 = true;
      FUN_00437d80(*(undefined4 *)(param_1 + 0x104));
    }
    if (bVar1) {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x59) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0("ch02001.otf",DAT_0091755c,0x41000000,0);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar6 + 60.0;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x94) = (float)fVar6 + 200.0;
      *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x94) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x94)) {
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x94) = (float)fVar6 + 200.0;
    cVar3 = FUN_005c8490(param_1 + 0xf0);
    if (cVar3 == '\0') {
      uVar4 = FUN_005c8250("svltnk",2,"annoy_1",0,0);
      *(undefined4 *)(param_1 + 0xf0) = uVar4;
      FUN_005cdb20(*(undefined4 *)(param_1 + 0xf0),1);
    }
    cVar3 = FUN_005c8490(param_1 + 0xf4);
    if (cVar3 == '\0') {
      uVar4 = FUN_005c8250("svltnk",2,"annoy_1",0,0);
      *(undefined4 *)(param_1 + 0xf4) = uVar4;
      FUN_005cdb20(*(undefined4 *)(param_1 + 0xf4),1);
    }
    cVar3 = FUN_005c8490(param_1 + 0xf8);
    if (cVar3 == '\0') {
      uVar4 = FUN_005c8250("svfigh",2,"annoy_1",0,0);
      *(undefined4 *)(param_1 + 0xf8) = uVar4;
      FUN_005cdb20(*(undefined4 *)(param_1 + 0xf8),1);
    }
    cVar3 = FUN_005c8490(param_1 + 0xfc);
    if (cVar3 == '\0') {
      uVar4 = FUN_005c8250("svfigh",2,"annoy_1",0,0);
      *(undefined4 *)(param_1 + 0xfc) = uVar4;
      FUN_005cdb20(*(undefined4 *)(param_1 + 0xfc),1);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x6c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x6c)) {
    *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    uVar4 = FUN_00437d30("ch02001.wav");
    *(undefined4 *)(param_1 + 0x104) = uVar4;
  }
  if ((*(int *)(param_1 + 0x104) != 0) &&
     (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x104)), cVar3 != '\0')) {
    *(undefined4 *)(param_1 + 0x104) = 0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x74)) {
    *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    FUN_00437d30("ch02002.wav");
  }
  fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa4));
  if ((((double)fVar6 <= 0.0) && (*(char *)(param_1 + 0x6a) == '\0')) &&
     (*(char *)(param_1 + 0x69) == '\0')) {
    *(undefined1 *)(param_1 + 0x6a) = 1;
    uVar4 = FUN_00437d30("ch02006.wav");
    *(undefined4 *)(param_1 + 0x108) = uVar4;
  }
  if ((*(int *)(param_1 + 0x108) != 0) &&
     (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x108)), cVar3 != '\0')) {
    *(undefined4 *)(param_1 + 0x108) = 0;
    fVar6 = (float10)FUN_004b1670("ch02lsea.des");
    FUN_0045c0f0((float)fVar6 + 1.0);
  }
  if (((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 0x6a) == '\0')) &&
     (*(char *)(param_1 + 0x69) == '\0')) {
    local_24 = 0;
    for (local_c = 0; local_c < 3; local_c = local_c + 1) {
      fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xdc + local_c * 4));
      if (((double)fVar6 <= 0.0) && (*(char *)(param_1 + local_c + 0x60) == '\0')) {
        local_24 = local_24 + 1;
      }
    }
    if (1 < local_24) {
      *(undefined1 *)(param_1 + 0x6a) = 1;
      uVar4 = FUN_00437d30("ch02006.wav");
      *(undefined4 *)(param_1 + 0x10c) = uVar4;
    }
  }
  if ((*(int *)(param_1 + 0x10c) != 0) &&
     (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x10c)), cVar3 != '\0')) {
    *(undefined4 *)(param_1 + 0x10c) = 0;
    fVar6 = (float10)FUN_004b1670("ch02lseb.des");
    FUN_0045c0f0((float)fVar6 + 1.0);
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    *(undefined1 *)(param_1 + 0x5c) = 1;
    for (local_c = 0; local_c < 5; local_c = local_c + 1) {
      cVar3 = FUN_005c84d0(param_1 + 0xb4 + local_c * 4);
      if (cVar3 != '\0') {
        *(undefined1 *)(param_1 + 0x5c) = 0;
        break;
      }
    }
    if (*(char *)(param_1 + 0x5c) != '\0') {
      uVar4 = FUN_005c8250("svartl",2,"hanger_attack_2",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
    }
  }
  if (*(char *)(param_1 + 0x5d) == '\0') {
    *(undefined1 *)(param_1 + 0x5d) = 1;
    for (local_c = 0; local_c < 5; local_c = local_c + 1) {
      cVar3 = FUN_005c84d0(param_1 + 200 + local_c * 4);
      if (cVar3 != '\0') {
        *(undefined1 *)(param_1 + 0x5d) = 0;
        break;
      }
    }
    if (*(char *)(param_1 + 0x5d) != '\0') {
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x78) = (float)fVar6 + 60.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x78) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x78)) {
    *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
    uVar4 = FUN_005c8250("svfigh",2,"attack_6",0,0);
    FUN_005cb960(uVar4,"attack_6_path",1);
    uVar4 = FUN_005c8250("svtank",2,"attack_6",0,0);
    FUN_005cb960(uVar4,"attack_6_path",1);
    uVar4 = FUN_005c8250("svfigh",2,"attack_7",0,0);
    uVar5 = FUN_0064d7b0(1);
    FUN_005cb9d0(uVar4,uVar5);
    uVar4 = FUN_005c8250("svtank",2,"attack_7",0,0);
    uVar5 = FUN_0064d7b0(1);
    FUN_005cb9d0(uVar4,uVar5);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar6 + 240.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x88) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x88)) {
    *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
    uVar4 = FUN_005c8250("svwalk",0,"walker_spawn",0,0);
    *(undefined4 *)(param_1 + 0xe8) = uVar4;
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xe8));
    FUN_005c88b0(*(undefined4 *)(param_1 + 0xe8),1);
    FUN_005cc100(*(undefined4 *)(param_1 + 0xe8),"walker_path",1);
    FUN_00437d30("ch02007.wav");
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar6 + 10.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar6 + 300.0;
    FUN_004f6aa0();
    FUN_004f6ab0("ch02001.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("ch02003.otf",DAT_0091755c,0x41000000,0);
  }
  if (((*(int *)(param_1 + 0xe8) != 0) && (*(char *)(param_1 + 0x67) == '\0')) &&
     (fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xe8),"walker_attack_3",0),
     (float)fVar6 < 200.0)) {
    *(undefined1 *)(param_1 + 0x67) = 1;
    uVar4 = FUN_005c8250("svfigh",2,"walker_attack_3",0,0);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xe8),1);
  }
  if (((*(int *)(param_1 + 0xe8) != 0) && (*(char *)(param_1 + 0x68) == '\0')) &&
     (fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xe8),"walker_attack_2",0),
     (float)fVar6 < 200.0)) {
    *(undefined1 *)(param_1 + 0x68) = 1;
    uVar4 = FUN_005c8250("svltnk",2,"walker_attack_2",0,0);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xe8),1);
  }
  if (((*(int *)(param_1 + 0xe8) != 0) &&
      (fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xe8)), (float)fVar6 <= 0.0)) &&
     ((*(char *)(param_1 + 0x6a) == '\0' && (*(char *)(param_1 + 0x69) == '\0')))) {
    *(undefined1 *)(param_1 + 0x6a) = 1;
    fVar6 = (float10)FUN_004b1670("ch02lsec.des");
    FUN_0045c0f0((float)fVar6);
  }
  if ((*(int *)(param_1 + 0xe8) != 0) &&
     (cVar3 = FUN_005cda90(*(undefined4 *)(param_1 + 0xe8),"walker_path"), cVar3 != '\0')) {
    FUN_005c8840(*(undefined4 *)(param_1 + 0xe8),1);
    FUN_005ce5d0(*(undefined4 *)(param_1 + 0xe8),1);
    *(undefined4 *)(param_1 + 0xe8) = 0;
    FUN_004ff0d0("ch02003.otf",DAT_009175b0,0x41000000,0);
    FUN_00437d30("ch02008.wav");
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x8c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x8c)) {
    *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
    uVar4 = FUN_005c8250("svartl",2,"hanger_attack_5",0,0);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x7c)) {
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    uVar4 = FUN_005c8250("svtank",2,"attack_8",0,0);
    uVar5 = FUN_0064d7b0(1);
    FUN_005cb9d0(uVar4,uVar5);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar6 + 270.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x80)) {
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    FUN_00437d30("ch02003.wav");
    *(undefined1 *)(param_1 + 0x5e) = 1;
    uVar4 = FUN_005c8250("cvapcb",1,"convoy_units",0,0);
    *(undefined4 *)(param_1 + 0xdc) = uVar4;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xdc),"convoy_path",1);
    uVar4 = FUN_005c8250("cvapcb",1,"convoy_units",0,0);
    *(undefined4 *)(param_1 + 0xe0) = uVar4;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xe0),"convoy_path",1);
    uVar4 = FUN_005c8250("cvapcb",1,"convoy_units",0,0);
    *(undefined4 *)(param_1 + 0xe4) = uVar4;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xe4),"convoy_path",1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xdc),1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xdc),1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xe0),1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xe0),1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xe4),1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xe4),1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xe0),1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xe4),1);
    uVar4 = FUN_005c8250("cvfighc",1,"convoy_defend",0,0);
    FUN_005cbce0(uVar4,*(undefined4 *)(param_1 + 0xe4),1);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar6 + 60.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x90) = (float)fVar6 + 300.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x90) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x90)) {
    *(undefined4 *)(param_1 + 0x90) = 0x497423fe;
    uVar4 = FUN_005c8250("svartl",2,"hanger_attack_6",0,0);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x84) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x84)) {
    *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
    uVar4 = FUN_005c8250("svfigh",2,"convoy_attack_1",0,0);
    uVar5 = FUN_0064d700(1);
    FUN_005cb9d0(uVar4,uVar5);
    uVar4 = FUN_005c8250("svartl",2,"convoy_attack_9",0,0);
    uVar5 = FUN_0064d700(1);
    FUN_005cb9d0(uVar4,uVar5);
  }
  if ((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 0x5f) == '\0')) {
    for (local_c = 0; local_c < 3; local_c = local_c + 1) {
      fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xdc + local_c * 4));
      if ((double)fVar6 < 1.0) {
        *(undefined1 *)(param_1 + 0x5f) = 1;
        break;
      }
    }
    if (*(char *)(param_1 + 0x5f) != '\0') {
      FUN_00437d30("ch02004.wav");
      uVar4 = FUN_005c8250("cpcamr",1,"nav_convoy",0,0);
      *(undefined4 *)(param_1 + 0xec) = uVar4;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0xec),"Convoy Intercept");
      FUN_004f6aa0();
      FUN_004f6ab0("ch02001.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("ch02002.otf",DAT_0091755c,0x41000000,0);
    }
  }
  if (((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 99) == '\0')) &&
     ((fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xdc),"trigger_point_1",0),
      (double)fVar6 < 30.0 ||
      ((fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xe0),"trigger_point_1",0),
       (double)fVar6 < 30.0 ||
       (fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xe4),"trigger_point_1",0),
       (double)fVar6 < 30.0)))))) {
    *(undefined1 *)(param_1 + 99) = 1;
    uVar4 = FUN_005c8250("svfigh",2,"convoy_attack_10",0,0);
    uVar5 = FUN_0064d700(1);
    FUN_005cb9d0(uVar4,uVar5);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
    uVar4 = FUN_005c8250("svhraz",2,"hanger_attack_3",0,0);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
  }
  if (((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 100) == '\0')) &&
     ((fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xdc),"trigger_point_2",0),
      (double)fVar6 < 40.0 ||
      ((fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xe0),"trigger_point_2",0),
       (double)fVar6 < 40.0 ||
       (fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xe4),"trigger_point_2",0),
       (double)fVar6 < 40.0)))))) {
    *(undefined1 *)(param_1 + 100) = 1;
    uVar4 = FUN_005c8250("svtank",2,"attack_9",0,0);
    uVar5 = FUN_0064d7b0(1);
    FUN_005cb9d0(uVar4,uVar5);
    uVar4 = FUN_005c8250("svtank",2,"attack_10",0,0);
    uVar5 = FUN_0064d7b0(1);
    FUN_005cb9d0(uVar4,uVar5);
    uVar4 = FUN_005c8250("svhraz",2,"hanger_attack_4",0,0);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa4),1);
  }
  if (((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 0x65) == '\0')) &&
     ((fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0xa4)
                                    ), (double)fVar6 < 40.0 ||
      ((fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xe0),
                                      *(undefined4 *)(param_1 + 0xa4)), (double)fVar6 < 40.0 ||
       (fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xe4),
                                      *(undefined4 *)(param_1 + 0xa4)), (double)fVar6 < 40.0)))))) {
    *(undefined1 *)(param_1 + 0x65) = 1;
    *(undefined1 *)(param_1 + 0x69) = 1;
    uVar4 = FUN_00437d30("ch02005.wav");
    *(undefined4 *)(param_1 + 0x110) = uVar4;
  }
  if ((*(int *)(param_1 + 0x110) != 0) &&
     (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x110)), cVar3 != '\0')) {
    *(undefined4 *)(param_1 + 0x110) = 0;
    fVar6 = (float10)FUN_004b1670("ch02win.des");
    FUN_0045c110((float)fVar6 + 1.0);
  }
  return;
}

