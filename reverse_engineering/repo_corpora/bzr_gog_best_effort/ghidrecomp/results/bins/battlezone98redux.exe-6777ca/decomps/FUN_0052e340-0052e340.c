
void __fastcall FUN_0052e340(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x10c) = uVar2;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_00437d30("misn0800.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("misn0800.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("misn0801.otf",DAT_0091755c,0x41000000,0);
    FUN_005cadd0(1,0x1e);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x130),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x134),1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xc4) = (float)fVar3 + 329.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xa4) = (float)fVar3 + 280.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb8) = (float)fVar3 + 285.0;
    *(undefined4 *)(param_1 + 0xe8) = 0x42c80000;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xa8) = (float)fVar3 + 61.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xcc) = (float)fVar3 + 20.0;
    FUN_005cb020(*(undefined4 *)(param_1 + 0x130),1);
    FUN_005cb020(*(undefined4 *)(param_1 + 0x134),1);
    FUN_005c9640(*(undefined4 *)(param_1 + 0x11c),"Drop Zone");
    FUN_005c9640(*(undefined4 *)(param_1 + 300),"Colorado Base");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x128),"CCA Main Base");
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf8) = (float)fVar3 + 5.0;
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  if (*(char *)(param_1 + 0x54) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xc4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xc4))
       && (*(char *)(param_1 + 0x6c) == '\0')) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x130),"gech_path1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x134),"gech_path2",1);
      *(undefined1 *)(param_1 + 0x6c) = 1;
    }
  }
  fVar3 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xcc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xcc)) &&
     (*(char *)(param_1 + 0x6e) == '\0')) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x184),*(undefined4 *)(param_1 + 0x158),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x188),*(undefined4 *)(param_1 + 0x158),1);
    *(undefined1 *)(param_1 + 0x6e) = 1;
  }
  fVar3 = (float10)FUN_00822d80();
  if (((*(float *)(param_1 + 0xe8) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xe8)) &&
      (*(char *)(param_1 + 0x5f) == '\0')) && (*(char *)(param_1 + 0x77) == '\0')) {
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x144),0);
    *(undefined4 *)(param_1 + 0x18c) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x144),0);
    *(undefined4 *)(param_1 + 400) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x144),0);
    *(undefined4 *)(param_1 + 0x194) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x18c),"gech_path2",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 400),"gech_path2",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x194),"gech_path2",1);
    *(undefined1 *)(param_1 + 0x77) = 1;
  }
  fVar3 = (float10)FUN_00822d80();
  if (((*(float *)(param_1 + 0xec) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xec)) &&
      (*(char *)(param_1 + 0x5f) == '\0')) && (*(char *)(param_1 + 0x78) == '\0')) {
    FUN_00437d30("misn0817.wav");
    *(undefined1 *)(param_1 + 0x78) = 1;
  }
  fVar3 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xa4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xa4)) &&
     (*(char *)(param_1 + 0x5f) == '\0')) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xa4) = (float)fVar3 + 10.0;
    fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 300));
    if (400.0 < (float)fVar3) {
      uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x144),0);
      *(undefined4 *)(param_1 + 0x184) = uVar2;
      uVar2 = FUN_005c8080("svltnk",2,*(undefined4 *)(param_1 + 0x144),0);
      *(undefined4 *)(param_1 + 0x184) = uVar2;
      uVar2 = FUN_005c8250("svwalk",2,"gech_spawn",0,0);
      *(undefined4 *)(param_1 + 0x138) = uVar2;
      FUN_005cb020(*(undefined4 *)(param_1 + 0x138),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x13c),1);
      FUN_00437d30("misn0801.wav");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x8c) = (float)fVar3 + 10.0;
      cVar1 = FUN_005c84d0(param_1 + 0x180);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x180),*(undefined4 *)(param_1 + 0x11c),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x184);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x184),*(undefined4 *)(param_1 + 0x11c),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x188);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x188),*(undefined4 *)(param_1 + 0x11c),1);
      }
      *(undefined1 *)(param_1 + 0x5f) = 1;
    }
  }
  fVar3 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0xf0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xf0)) &&
     (*(char *)(param_1 + 0x5f) == '\0')) {
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xf0) = (float)fVar3 + 32.0;
    fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 300));
    if ((float)fVar3 < 700.0) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xa4) = (float)fVar3 + 10.0;
      cVar1 = FUN_005c84d0(param_1 + 0x174);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x10c),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x178);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x178),*(undefined4 *)(param_1 + 0x10c),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x17c);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x17c),*(undefined4 *)(param_1 + 0x10c),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x180);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x180),*(undefined4 *)(param_1 + 0x158),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x184);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x184),*(undefined4 *)(param_1 + 0x158),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x188);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x188),*(undefined4 *)(param_1 + 0x158),1);
      }
    }
  }
  if (*(char *)(param_1 + 0x5f) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x138);
    if (cVar1 != '\0') {
      uVar2 = FUN_005cd070(*(undefined4 *)(param_1 + 0x138));
      FUN_005cd0a0(*(undefined4 *)(param_1 + 0x138),uVar2);
    }
  }
  if (*(char *)(param_1 + 0x5f) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x8c) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x8c))
       && (*(char *)(param_1 + 0x62) == '\0')) {
      FUN_00437d30("misn0803.wav");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x90) = (float)fVar3 + 7.0;
      *(undefined1 *)(param_1 + 0x62) = 1;
    }
  }
  if (*(char *)(param_1 + 0x62) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x90) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x90))
       && (*(char *)(param_1 + 99) == '\0')) {
      FUN_00437d30("misn0802.wav");
      FUN_00437d30("misn0804.wav");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x94) = (float)fVar3 + 10.0;
      *(undefined1 *)(param_1 + 99) = 1;
    }
  }
  fVar3 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0x94) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x94)) &&
     (*(char *)(param_1 + 0x7e) == '\0')) {
    cVar1 = FUN_00437da0();
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x7e) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x13c);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x7e) == '\0')) {
    fVar3 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x100) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x100))
    {
      fVar3 = (float10)FUN_005ccf40(*(undefined4 *)(param_1 + 0x13c));
      FUN_005ccf70(*(undefined4 *)(param_1 + 0x13c),(float)fVar3);
      fVar3 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x100) = (float)fVar3 + 1.0;
    }
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x7e) != '\0')) &&
     (*(char *)(param_1 + 100) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x13c);
    if (cVar1 != '\0') {
      FUN_005cb1c0(*(undefined4 *)(param_1 + 0x13c),0x469c4000);
    }
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xa0) = (float)fVar3 + 3.0;
    *(undefined1 *)(param_1 + 100) = 1;
  }
  if (*(char *)(param_1 + 100) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xa0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xa0))
       && (*(char *)(param_1 + 0x60) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x138);
      if (cVar1 == '\0') {
        FUN_005c83e0(*(undefined4 *)(param_1 + 300));
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 300),1);
      }
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x98) = (float)fVar3 + 5.0;
      *(undefined1 *)(param_1 + 0x60) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x60) != '\0') && (*(char *)(param_1 + 0x68) == '\0')) {
    fVar3 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x98) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x98)) {
      FUN_00437d30("misn0805.wav");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x98) = (float)fVar3 + 30.0;
      *(undefined1 *)(param_1 + 0x68) = 1;
    }
  }
  if (*(char *)(param_1 + 0x68) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x98) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x98))
       && (*(char *)(param_1 + 0x7f) == '\0')) {
      FUN_00437d30("misn0810.wav");
      *(undefined1 *)(param_1 + 0x7f) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x68) != '\0') && (*(char *)(param_1 + 0x6b) == '\0')) {
    FUN_005cb2d0("misn08.aip",2);
    FUN_005cadd0(2,0x28);
    FUN_005cacb0(2,0x28);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xe4) = (float)fVar3 + 420.0;
    cVar1 = FUN_005c84d0(param_1 + 0x138);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x138),"gech_path2",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x174);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x174),"cam3_spawn",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x178);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x178),"cam3_spawn",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x17c);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x17c),"cam3_spawn",1);
    }
    *(undefined1 *)(param_1 + 0x6b) = 1;
  }
  fVar3 = (float10)FUN_00822d80();
  if (((*(float *)(param_1 + 0xa8) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xa8)) &&
      (*(char *)(param_1 + 0x55) == '\0')) && (*(char *)(param_1 + 0x5b) == '\0')) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xa8) = (float)fVar3 + 6.0;
    fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0x130))
    ;
    if ((((float)fVar3 < 400.0) && (*(char *)(param_1 + 0x56) == '\0')) &&
       ((*(char *)(param_1 + 0x55) == '\0' && (*(char *)(param_1 + 0x5b) == '\0')))) {
      FUN_00437d30("misn0806.wav");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x88) = (float)fVar3 + 20.0;
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar3 + 10.0;
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xbc) = (float)fVar3 + 13.0;
      *(undefined4 *)(param_1 + 0xd8) = 0x42c80000;
      *(undefined4 *)(param_1 + 0xdc) = 0x42d20000;
      *(undefined1 *)(param_1 + 0x56) = 1;
      *(undefined1 *)(param_1 + 0x55) = 1;
    }
    fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0x134))
    ;
    if ((((float)fVar3 < 400.0) && (*(char *)(param_1 + 0x55) == '\0')) &&
       ((*(char *)(param_1 + 0x57) == '\0' && (*(char *)(param_1 + 0x5b) == '\0')))) {
      FUN_00437d30("misn0806.wav");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x88) = (float)fVar3 + 5.0;
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar3 + 60.0;
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xbc) = (float)fVar3 + 13.0;
      *(undefined4 *)(param_1 + 0xd8) = 0x42c80000;
      *(undefined4 *)(param_1 + 0xdc) = 0x42d20000;
      *(undefined1 *)(param_1 + 0x57) = 1;
      *(undefined1 *)(param_1 + 0x55) = 1;
    }
  }
  if (*(char *)(param_1 + 0x55) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x88) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x88))
       && (*(char *)(param_1 + 0x61) == '\0')) {
      FUN_00437d30("misn0807.wav");
      *(undefined1 *)(param_1 + 0x61) = 1;
    }
  }
  fVar3 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xf8) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xf8)) &&
     (*(char *)(param_1 + 0x7a) == '\0')) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf8) = (float)fVar3 + 2.0;
    cVar1 = FUN_005c84d0(param_1 + 0x15c);
    if (cVar1 != '\0') {
      cVar1 = FUN_005caec0(*(undefined4 *)(param_1 + 0x15c));
      if (cVar1 != '\0') {
        FUN_004f6aa0();
        FUN_004f6ab0("misn0800.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misn0801.otf",DAT_0091755c,0x41000000,0);
        *(undefined1 *)(param_1 + 0x7a) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x55) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if (((*(float *)(param_1 + 0xb4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xb4))
        && (*(char *)(param_1 + 0x65) == '\0')) && (*(char *)(param_1 + 0x66) == '\0')) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar3 + 21.0;
      if (*(char *)(param_1 + 0x56) != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),
                                      *(undefined4 *)(param_1 + 0x134));
        if (((float)fVar3 < 100.0) && (*(char *)(param_1 + 0x66) == '\0')) {
          FUN_00437d30("misn0813.wav");
          *(undefined1 *)(param_1 + 0x66) = 1;
        }
      }
      if (*(char *)(param_1 + 0x57) != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),
                                      *(undefined4 *)(param_1 + 0x130));
        if (((float)fVar3 < 100.0) && (*(char *)(param_1 + 0x66) == '\0')) {
          FUN_00437d30("misn0813.wav");
          *(undefined1 *)(param_1 + 0x66) = 1;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x55) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if (((*(float *)(param_1 + 0xbc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xbc))
        && (*(char *)(param_1 + 0x66) == '\0')) && (*(char *)(param_1 + 0x65) == '\0')) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xbc) = (float)fVar3 + 9.0;
      if (*(char *)(param_1 + 0x56) != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x150),
                                      *(undefined4 *)(param_1 + 0x134));
        if (((float)fVar3 < 100.0) && (*(char *)(param_1 + 0x65) == '\0')) {
          FUN_00437d30("misn0815.wav");
          uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam2_spawn",0,0);
          *(undefined4 *)(param_1 + 0x120) = uVar2;
          FUN_005c9640(*(undefined4 *)(param_1 + 0x120),"Nav Alpha 1");
          *(undefined1 *)(param_1 + 0x65) = 1;
        }
      }
      if (*(char *)(param_1 + 0x57) != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x154),
                                      *(undefined4 *)(param_1 + 0x130));
        if (((float)fVar3 < 100.0) && (*(char *)(param_1 + 0x65) == '\0')) {
          FUN_00437d30("misn0814.wav");
          uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam3_spawn",0,0);
          *(undefined4 *)(param_1 + 0x124) = uVar2;
          FUN_005c9640(*(undefined4 *)(param_1 + 0x124),"Nav Alpha 2");
          *(undefined1 *)(param_1 + 0x65) = 1;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x5f) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if (((*(float *)(param_1 + 0xb8) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xb8))
        && (*(char *)(param_1 + 0x5b) == '\0')) && (*(char *)(param_1 + 0x55) == '\0')) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb8) = (float)fVar3 + 19.0;
      if (*(char *)(param_1 + 0x55) == '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x150),
                                      *(undefined4 *)(param_1 + 0x134));
        if (((float)fVar3 < 100.0) && (*(char *)(param_1 + 0x5b) == '\0')) {
          FUN_00437d30("misn0809.wav");
          fVar3 = (float10)FUN_00822d80();
          *(float *)(param_1 + 0x9c) = (float)fVar3 + 20.0;
          *(undefined4 *)(param_1 + 0xd8) = 0x42c80000;
          *(undefined4 *)(param_1 + 0xdc) = 0x42d20000;
          *(undefined1 *)(param_1 + 0x5b) = 1;
          *(undefined1 *)(param_1 + 0x5c) = 1;
        }
      }
      if (*(char *)(param_1 + 0x55) == '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x154),
                                      *(undefined4 *)(param_1 + 0x130));
        if (((float)fVar3 < 100.0) && (*(char *)(param_1 + 0x5b) == '\0')) {
          FUN_00437d30("misn0808.wav");
          fVar3 = (float10)FUN_00822d80();
          *(float *)(param_1 + 0x9c) = (float)fVar3 + 20.0;
          *(undefined4 *)(param_1 + 0xd8) = 0x42c80000;
          *(undefined4 *)(param_1 + 0xdc) = 0x42d20000;
          *(undefined1 *)(param_1 + 0x5b) = 1;
          *(undefined1 *)(param_1 + 0x5d) = 1;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x5c) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x9c) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x9c))
       && (*(char *)(param_1 + 0x5e) == '\0')) {
      FUN_00437d30("misn0814.wav");
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam2_spawn",0,0);
      *(undefined4 *)(param_1 + 0x120) = uVar2;
      FUN_005c9640(*(undefined4 *)(param_1 + 0x120),"Nav Alpha 1");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xc0) = (float)fVar3 + 14.0;
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar3 + 100.0;
      *(undefined1 *)(param_1 + 0x5e) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5d) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x9c) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x9c))
       && (*(char *)(param_1 + 0x5e) == '\0')) {
      FUN_00437d30("misn0815.wav");
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam3_spawn",0,0);
      *(undefined4 *)(param_1 + 0x124) = uVar2;
      FUN_005c9640(*(undefined4 *)(param_1 + 0x124),"Nav Alpha 2");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xc0) = (float)fVar3 + 14.0;
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar3 + 100.0;
      *(undefined1 *)(param_1 + 0x5e) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5e) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if (((*(float *)(param_1 + 0xc0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xc0))
        && (*(char *)(param_1 + 0x65) == '\0')) && (*(char *)(param_1 + 0x6a) == '\0')) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xc0) = (float)fVar3 + 14.0;
      if (*(char *)(param_1 + 0x5c) != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x154),
                                      *(undefined4 *)(param_1 + 0x130));
        if (((float)fVar3 < 75.0) && (*(char *)(param_1 + 0x65) == '\0')) {
          FUN_00437d30("misn0812.wav");
          uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam3_spawn",0,0);
          *(undefined4 *)(param_1 + 0x124) = uVar2;
          FUN_005c9640(*(undefined4 *)(param_1 + 0x124),"Nav Alpha 2");
          *(undefined1 *)(param_1 + 0x65) = 1;
        }
      }
      if (*(char *)(param_1 + 0x5d) != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x150),
                                      *(undefined4 *)(param_1 + 0x134));
        if (((float)fVar3 < 75.0) && (*(char *)(param_1 + 0x65) == '\0')) {
          FUN_00437d30("misn0811.wav");
          uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam2_spawn",0,0);
          *(undefined4 *)(param_1 + 0x120) = uVar2;
          FUN_005c9640(*(undefined4 *)(param_1 + 0x120),"Nav Alpha 1");
          *(undefined1 *)(param_1 + 0x65) = 1;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x5e) != '\0') {
    fVar3 = (float10)FUN_00822d80();
    if (((*(float *)(param_1 + 0xb0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xb0))
        && (*(char *)(param_1 + 0x65) == '\0')) && (*(char *)(param_1 + 0x6a) == '\0')) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar3 + 23.0;
      if (*(char *)(param_1 + 0x5c) != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),
                                      *(undefined4 *)(param_1 + 0x130));
        if (((float)fVar3 < 100.0) && (*(char *)(param_1 + 0x6a) == '\0')) {
          FUN_00437d30("misn0813.wav");
          *(undefined1 *)(param_1 + 0x6a) = 1;
        }
      }
      if (*(char *)(param_1 + 0x5d) != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),
                                      *(undefined4 *)(param_1 + 0x134));
        if (((float)fVar3 < 100.0) && (*(char *)(param_1 + 0x6a) == '\0')) {
          FUN_00437d30("misn0813.wav");
          *(undefined1 *)(param_1 + 0x6a) = 1;
        }
      }
    }
  }
  if ((*(char *)(param_1 + 0x55) != '\0') || (*(char *)(param_1 + 0x5b) != '\0')) {
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xd8) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xd8))
       && (*(char *)(param_1 + 0x71) == '\0')) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xd8) = (float)fVar3 + 30.0;
      cVar1 = FUN_005c84d0(param_1 + 0x130);
      if (cVar1 != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x130),
                                      *(undefined4 *)(param_1 + 0x170));
        if ((float)fVar3 < 100.0) {
          cVar1 = FUN_005c84d0(param_1 + 0x158);
          if (cVar1 == '\0') {
            cVar1 = FUN_005c84d0(param_1 + 0x15c);
            if (cVar1 != '\0') {
              FUN_005cb820(*(undefined4 *)(param_1 + 0x130),*(undefined4 *)(param_1 + 0x15c),1);
              if (*(char *)(param_1 + 0x74) != '\0') {
                FUN_005cb020(*(undefined4 *)(param_1 + 0x130),5);
              }
              *(undefined1 *)(param_1 + 0x71) = 1;
            }
          }
          else {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x130),*(undefined4 *)(param_1 + 0x158),1);
            if (*(char *)(param_1 + 0x74) != '\0') {
              FUN_005cb020(*(undefined4 *)(param_1 + 0x130),5);
            }
            *(undefined1 *)(param_1 + 0x71) = 1;
          }
        }
      }
    }
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xdc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xdc))
       && (*(char *)(param_1 + 0x72) == '\0')) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xdc) = (float)fVar3 + 30.0;
      cVar1 = FUN_005c84d0(param_1 + 0x134);
      if (cVar1 != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x134),
                                      *(undefined4 *)(param_1 + 0x170));
        if ((float)fVar3 < 100.0) {
          cVar1 = FUN_005c84d0(param_1 + 0x158);
          if (cVar1 == '\0') {
            cVar1 = FUN_005c84d0(param_1 + 0x15c);
            if (cVar1 != '\0') {
              FUN_005cb820(*(undefined4 *)(param_1 + 0x134),*(undefined4 *)(param_1 + 0x15c),1);
              if (*(char *)(param_1 + 0x75) != '\0') {
                FUN_005cb020(*(undefined4 *)(param_1 + 0x134),5);
              }
              *(undefined1 *)(param_1 + 0x72) = 1;
            }
          }
          else {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x134),*(undefined4 *)(param_1 + 0x158),1);
            if (*(char *)(param_1 + 0x75) != '\0') {
              FUN_005cb020(*(undefined4 *)(param_1 + 0x134),5);
            }
            *(undefined1 *)(param_1 + 0x72) = 1;
          }
        }
      }
    }
    fVar3 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xe0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xe0))
       && (*(char *)(param_1 + 0x73) == '\0')) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xe0) = (float)fVar3 + 30.0;
      cVar1 = FUN_005c84d0(param_1 + 0x138);
      if (cVar1 != '\0') {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x138),
                                      *(undefined4 *)(param_1 + 0x170));
        if ((float)fVar3 < 100.0) {
          cVar1 = FUN_005c84d0(param_1 + 0x158);
          if (cVar1 == '\0') {
            cVar1 = FUN_005c84d0(param_1 + 0x15c);
            if (cVar1 != '\0') {
              FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x15c),1);
              if (*(char *)(param_1 + 0x76) != '\0') {
                FUN_005cb020(*(undefined4 *)(param_1 + 0x138),5);
              }
              *(undefined1 *)(param_1 + 0x73) = 1;
            }
          }
          else {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x158),1);
            if (*(char *)(param_1 + 0x76) != '\0') {
              FUN_005cb020(*(undefined4 *)(param_1 + 0x138),5);
            }
            *(undefined1 *)(param_1 + 0x73) = 1;
          }
        }
      }
    }
  }
  fVar3 = (float10)FUN_00822d80();
  if (*(float *)(param_1 + 0xe4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xe4)) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xe4) = (float)fVar3 + 420.0;
    uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x16c),0x459c4000,1,"avfigh");
    *(undefined4 *)(param_1 + 0x1b4) = uVar2;
    uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x16c),0x459c4000,1,"avtank");
    *(undefined4 *)(param_1 + 0x1b8) = uVar2;
    if (*(int *)(param_1 + 0x1b8) < *(int *)(param_1 + 0x1b4)) {
      FUN_005cb2d0("misn08b.aip",2);
    }
    else {
      FUN_005cb2d0("misn08a.aip",2);
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x198);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x79) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x19c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x1a0);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x15c);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x158);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0x158),1);
          }
        }
        else {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0x15c),1);
        }
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0x1a0),1);
      }
    }
    else {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0x19c),1);
    }
    *(undefined1 *)(param_1 + 0x79) = 1;
  }
  if (*(char *)(param_1 + 0x79) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x198);
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x79) = 0;
    }
  }
  fVar3 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xf4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xf4)) &&
     (*(char *)(param_1 + 0x67) == '\0')) {
    FUN_00437d30("misn0816.wav");
    *(undefined1 *)(param_1 + 0x67) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x130);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x74) == '\0')) {
    fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x130));
    if ((float)fVar3 < 0.25) {
      FUN_005cb020(*(undefined4 *)(param_1 + 0x130),4);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xf4) = (float)fVar3 + 6.0;
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x134);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x75) == '\0')) {
    fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x134));
    if ((float)fVar3 < 0.25) {
      FUN_005cb020(*(undefined4 *)(param_1 + 0x134),4);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xf4) = (float)fVar3 + 6.0;
      *(undefined1 *)(param_1 + 0x75) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x138);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x76) == '\0')) {
    fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x138));
    if ((float)fVar3 < 0.25) {
      FUN_005cb020(*(undefined4 *)(param_1 + 0x138),4);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xf4) = (float)fVar3 + 6.0;
      *(undefined1 *)(param_1 + 0x76) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x59) == '\0') && (*(char *)(param_1 + 0x7c) != '\0')) &&
     (*(char *)(param_1 + 0x58) != '\0')) {
    cVar1 = FUN_00437da0();
    if (cVar1 == '\0') {
      fVar3 = (float10)FUN_00822d80("misn08w1.des");
      FUN_0045c110((float)fVar3 + 3.0);
      *(undefined1 *)(param_1 + 0x59) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x5a) == '\0') && (*(char *)(param_1 + 0x7b) != '\0')) {
    cVar1 = FUN_00437da0();
    if (cVar1 == '\0') {
      fVar3 = (float10)FUN_00822d80("misn08f1.des");
      FUN_0045c0f0((float)fVar3 + 3.0);
      *(undefined1 *)(param_1 + 0x5a) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x7c) == '\0') && (*(char *)(param_1 + 0x7d) == '\0')) {
    cVar1 = FUN_005cd610("hbblde");
    if (cVar1 != '\x01') {
      cVar1 = FUN_005cd610("hbbldf");
      if (cVar1 != '\x01') goto LAB_00530672;
    }
    if (*(char *)(param_1 + 0x58) == '\0') {
      FUN_00437d30("misn0822.wav");
      *(undefined1 *)(param_1 + 0x7d) = 1;
    }
    else {
      FUN_00437d30("misn0821.wav");
      *(undefined1 *)(param_1 + 0x7d) = 1;
    }
  }
LAB_00530672:
  if (*(char *)(param_1 + 0x7c) == '\0') {
    fVar3 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xfc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xfc)) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xfc) = (float)fVar3 + 3.0;
      fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),
                                    *(undefined4 *)(param_1 + 0x1ac));
      if ((float)fVar3 < 70.0) {
        if (*(char *)(param_1 + 0x58) == '\0') {
          FUN_00437d30("misn0819.wav");
          *(undefined1 *)(param_1 + 0x7c) = 1;
        }
        else {
          FUN_00437d30("misn0818.wav");
          FUN_00437d30("misn0826.wav");
          *(undefined1 *)(param_1 + 0x7c) = 1;
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1ac);
  if (cVar1 != '\0') {
    fVar3 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x104) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x104))
    {
      FUN_005ccfd0(*(undefined4 *)(param_1 + 0x1ac),0x43fa0000);
      fVar3 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x104) = (float)fVar3 + 1.0;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x144);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x148);
    if ((cVar1 == '\0') && (*(char *)(param_1 + 0x58) == '\0')) {
      if (*(char *)(param_1 + 0x7c) == '\0') {
        FUN_004f6aa0();
        FUN_004f6ab0("misn0801.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misn0802.otf",DAT_0091755c,0x41000000,0);
        FUN_00437d30("misn0820.wav");
        FUN_005c95e0(*(undefined4 *)(param_1 + 0x1ac));
        FUN_005c9640(*(undefined4 *)(param_1 + 0x1ac),"Relic Site");
        *(undefined1 *)(param_1 + 0x58) = 1;
      }
      else {
        FUN_00437d30("misn0818.wav");
        FUN_00437d30("misn0826.wav");
        *(undefined1 *)(param_1 + 0x58) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x158);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x7b) == '\0')) {
    FUN_00437d30("misn0421.wav");
    *(undefined1 *)(param_1 + 0x7b) = 1;
  }
  return;
}

