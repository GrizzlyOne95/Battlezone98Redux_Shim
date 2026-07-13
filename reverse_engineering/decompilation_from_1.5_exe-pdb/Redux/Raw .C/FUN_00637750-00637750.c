
void __fastcall FUN_00637750(int param_1)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  undefined4 uVar4;
  float10 fVar5;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined1 local_6;
  
  uVar4 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x9c) = uVar4;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,8);
    FUN_005cacb0(1,10);
    FUN_004f6aa0();
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  if (*(char *)(param_1 + 0x5a) == '\0') {
    if (*(char *)(param_1 + 0x59) == '\0') {
      FUN_005cd2a0();
      uVar4 = FUN_00437d30("bd05001.wav");
      *(undefined4 *)(param_1 + 0x18c) = uVar4;
      FUN_00638e70();
      *(undefined1 *)(param_1 + 0x59) = 1;
    }
    cVar2 = FUN_005cd300("camera_start_arc",3000,2000,*(undefined4 *)(param_1 + 0xa0));
    cVar3 = FUN_005cd560();
    if (cVar3 != '\0') {
      cVar2 = '\x01';
      FUN_00437d80(*(undefined4 *)(param_1 + 0x18c));
    }
    if (cVar2 != '\0') {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x5a) = 1;
      *(undefined1 *)(param_1 + 0x59) = 0;
      FUN_00638e70();
    }
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x68) = (float)fVar5 + 240.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x6c) = (float)fVar5 + 300.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar5 + 540.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar5 + 840.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar5 + 1140.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar5 + 420.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar5 + 450.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar5 + 660.0;
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
  if ((*(char *)(param_1 + 0x5d) == '\0') &&
     (fVar5 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x68) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x68))) {
    FUN_00437d30("bd05002.wav");
    *(undefined1 *)(param_1 + 0x5d) = 1;
  }
  if ((*(char *)(param_1 + 0x5e) == '\0') &&
     (fVar5 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x6c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x6c))) {
    uVar4 = FUN_005c8250("cvfigh",2,"first_wave",0,0);
    *(undefined4 *)(param_1 + 0xe4) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xe4));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xe4),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvfigh",2,"first_wave",0,0);
    *(undefined4 *)(param_1 + 0xe8) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xe8));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xe8),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvltnk",2,"first_wave",0,0);
    *(undefined4 *)(param_1 + 0xec) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xec));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xec),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvltnk",2,"first_wave",0,0);
    *(undefined4 *)(param_1 + 0xf0) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xf0));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xa0),1);
    *(undefined1 *)(param_1 + 0x5e) = 1;
  }
  if ((*(char *)(param_1 + 0x5f) == '\0') &&
     (fVar5 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x70) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x70))) {
    uVar4 = FUN_005c8250("cvltnk",2,"second_wave",0,0);
    *(undefined4 *)(param_1 + 0xf4) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xf4));
    FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvltnk",2,"second_wave",0,0);
    *(undefined4 *)(param_1 + 0xf8) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xf8));
    FUN_005cb820(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"second_wave",0,0);
    *(undefined4 *)(param_1 + 0xfc) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xfc));
    FUN_005cb820(*(undefined4 *)(param_1 + 0xfc),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"second_wave",0,0);
    *(undefined4 *)(param_1 + 0x100) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x100));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x100),*(undefined4 *)(param_1 + 0xa0),1);
    *(undefined1 *)(param_1 + 0x5f) = 1;
  }
  if ((*(char *)(param_1 + 0x60) == '\0') &&
     (fVar5 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x74) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x74))) {
    uVar4 = FUN_005c8250("cvtnk",2,"third_wave",0,0);
    *(undefined4 *)(param_1 + 0x104) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x104));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x104),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"third_wave",0,0);
    *(undefined4 *)(param_1 + 0x108) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x108));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvhraz",2,"third_wave",0,0);
    *(undefined4 *)(param_1 + 0x10c) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x10c));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvhraz",2,"third_wave",0,0);
    *(undefined4 *)(param_1 + 0x110) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x110));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvwalk",2,"third_wave",0,0);
    *(undefined4 *)(param_1 + 0x114) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x114));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0xa0),1);
    *(undefined1 *)(param_1 + 0x60) = 1;
  }
  if ((*(char *)(param_1 + 0x61) == '\0') &&
     (fVar5 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x78) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x78))) {
    uVar4 = FUN_005c8250("cvtnk",2,"fourth_wave",0,0);
    *(undefined4 *)(param_1 + 0x118) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x118));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"fourth_wave",0,0);
    *(undefined4 *)(param_1 + 0x11c) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x11c));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvhraz",2,"fourth_wave",0,0);
    *(undefined4 *)(param_1 + 0x120) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x120));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x120),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvhraz",2,"fourth_wave",0,0);
    *(undefined4 *)(param_1 + 0x124) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x124));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x124),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"fourth_wave",0,0);
    *(undefined4 *)(param_1 + 0x128) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x128));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x128),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"fourth_wave",0,0);
    *(undefined4 *)(param_1 + 300) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 300));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 300),*(undefined4 *)(param_1 + 0xa0),1);
    *(undefined1 *)(param_1 + 0x61) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x7c)) {
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x130) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x130));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x130),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x134) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x134));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x134),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x138) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x138));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x13c) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x13c));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x140) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x140));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x140),*(undefined4 *)(param_1 + 0xa0),1);
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x80)) {
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x144) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x144));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x148) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x148));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x148),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x14c) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x14c));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x14c),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x150) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x150));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x150),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvtnk",2,"rear_attack",0,0);
    *(undefined4 *)(param_1 + 0x154) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x154));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x154),*(undefined4 *)(param_1 + 0xa0),1);
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x84) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x84)) {
    *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
    uVar4 = FUN_005c8250("cvartl",2,"howit",0,0);
    *(undefined4 *)(param_1 + 0x158) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x158));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x158),*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = FUN_005c8250("cvartl",2,"howit",0,0);
    *(undefined4 *)(param_1 + 0x15c) = uVar4;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x15c));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x15c),*(undefined4 *)(param_1 + 0xa0),1);
  }
  if (*(char *)(param_1 + 0x57) == '\0') {
    bVar1 = true;
    for (local_14 = 0; local_14 < 0x2e; local_14 = local_14 + 1) {
      cVar2 = FUN_005c84d0(param_1 + 0xa8 + local_14 * 4);
      if ((cVar2 != '\0') &&
         (cVar2 = FUN_005c8660(*(undefined4 *)(param_1 + 0xa8 + local_14 * 4)), cVar2 != '\0')) {
        bVar1 = false;
        break;
      }
    }
    if (bVar1) {
      *(undefined1 *)(param_1 + 0x57) = 1;
      FUN_00638e70();
      if ((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x58) != '\0')) {
        FUN_00437d30("bd05004.wav");
        FUN_00638e70();
      }
    }
  }
  if ((*(char *)(param_1 + 0x58) == '\0') && (*(char *)(param_1 + 0x61) != '\0')) {
    local_6 = 1;
    for (local_18 = 0; local_18 < 0x2e; local_18 = local_18 + 1) {
      cVar2 = FUN_005c84d0(param_1 + 0xa8 + local_18 * 4);
      if ((cVar2 != '\0') &&
         (cVar2 = FUN_005c8660(*(undefined4 *)(param_1 + 0xa8 + local_18 * 4)), cVar2 == '\0')) {
        local_6 = 0;
        break;
      }
    }
    *(undefined1 *)(param_1 + 0x58) = local_6;
    if ((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x58) != '\0')) {
      FUN_00437d30("bd05004.wav");
      FUN_00638e70();
    }
  }
  if (((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x58) != '\0')) &&
     (*(char *)(param_1 + 0x62) == '\0')) {
    uVar4 = FUN_005c8250("cvtnk",2,"quitters",0,0);
    *(undefined4 *)(param_1 + 0x160) = uVar4;
    uVar4 = FUN_005c8250("cvtnk",2,"quitters",0,0);
    *(undefined4 *)(param_1 + 0x164) = uVar4;
    uVar4 = FUN_005c8250("cvwalk",2,"quitters",0,0);
    *(undefined4 *)(param_1 + 0x168) = uVar4;
    uVar4 = FUN_005c8250("cvwalk",2,"quitters",0,0);
    *(undefined4 *)(param_1 + 0x16c) = uVar4;
    uVar4 = FUN_005c8250("cspilo",2,"quitters",0,0);
    *(undefined4 *)(param_1 + 0x170) = uVar4;
    uVar4 = FUN_005c8250("cvltnk",2,"quitters",0,0);
    *(undefined4 *)(param_1 + 0x174) = uVar4;
    for (local_1c = 0; local_1c < 6; local_1c = local_1c + 1) {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x160 + local_1c * 4),"portal_in",1);
    }
    *(undefined1 *)(param_1 + 0x62) = 1;
    FUN_005cdea0(*(undefined4 *)(param_1 + 0xa4),1);
  }
  if (*(char *)(param_1 + 0x62) != '\0') {
    for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
      if (*(int *)(param_1 + 0x160 + local_10 * 4) != 0) {
        cVar2 = FUN_005c84d0(param_1 + 0x160 + local_10 * 4);
        if (cVar2 == '\0') {
          *(undefined4 *)(param_1 + 0x160 + local_10 * 4) = 0;
        }
        else {
          cVar2 = FUN_005cdfb0(*(undefined4 *)(param_1 + 0x160 + local_10 * 4),
                               *(undefined4 *)(param_1 + 0xa4),0x3fa66666);
          if (cVar2 != '\0') {
            FUN_005c83e0(*(undefined4 *)(param_1 + 0x160 + local_10 * 4));
            *(undefined4 *)(param_1 + 0x160 + local_10 * 4) = 0;
          }
        }
      }
    }
  }
  if (((*(char *)(param_1 + 0x62) != '\0') && (*(char *)(param_1 + 0x5a) != '\0')) &&
     (*(char *)(param_1 + 0x5b) == '\0')) {
    if (*(char *)(param_1 + 0x59) == '\0') {
      FUN_005cd2a0();
      uVar4 = FUN_00437d30("bd05005.wav");
      *(undefined4 *)(param_1 + 0x188) = uVar4;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x94) = (float)fVar5 + 15.0;
      *(undefined1 *)(param_1 + 0x59) = 1;
    }
    bVar1 = false;
    FUN_005cd300("camera_retreat",3000,0,*(undefined4 *)(param_1 + 0xa4));
    if ((*(int *)(param_1 + 0x188) != 0) &&
       (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x188)), cVar2 != '\0')) {
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x88) = (float)fVar5 + 3.0;
      *(undefined4 *)(param_1 + 0x188) = 0;
    }
    fVar5 = (float10)FUN_004b1670();
    if ((*(float *)(param_1 + 0x88) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x88))
       && (fVar5 = (float10)FUN_004b1670(),
          *(float *)(param_1 + 0x94) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x94)))
    {
      bVar1 = true;
    }
    if ((bVar1) || (cVar2 = FUN_005cd560(), cVar2 != '\0')) {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x5b) = 1;
      *(undefined1 *)(param_1 + 0x59) = 0;
      *(undefined1 *)(param_1 + 99) = 1;
    }
  }
  if ((((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x58) != '\0')) &&
      (*(char *)(param_1 + 99) != '\0')) &&
     ((*(char *)(param_1 + 0x56) == '\0' && (*(char *)(param_1 + 0x55) == '\0')))) {
    uVar4 = FUN_00437d30("bd05006.wav");
    *(undefined4 *)(param_1 + 400) = uVar4;
    *(undefined1 *)(param_1 + 0x56) = 1;
  }
  if ((*(int *)(param_1 + 400) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 400)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 400) = 0;
    FUN_0045c110(0x3dcccccd,"bd05win.des");
  }
  return;
}

