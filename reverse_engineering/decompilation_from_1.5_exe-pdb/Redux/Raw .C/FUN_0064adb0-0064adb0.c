
void __fastcall FUN_0064adb0(int param_1)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  undefined4 uVar7;
  int local_20;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar3 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x9c) = uVar3;
  FUN_005ccf70(*(undefined4 *)(param_1 + 0xd8),0x461c4000);
  FUN_005ccfa0(*(undefined4 *)(param_1 + 0xd8),0x461c4000);
  FUN_005cd780(0);
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,0);
    FUN_005cacb0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x6c) = (float)fVar5 + 5.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x6c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x6c)) {
    *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    uVar3 = FUN_00437d30("ch01001.wav");
    *(undefined4 *)(param_1 + 0xf8) = uVar3;
  }
  if ((*(int *)(param_1 + 0xf8) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0xf8)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0xf8) = 0;
    uVar3 = FUN_005c8250(&DAT_00878c18,1,"nav_start",0,0);
    *(undefined4 *)(param_1 + 0xe8) = uVar3;
    FUN_005cd7f0(*(undefined4 *)(param_1 + 0xe8),"CCA Base");
    FUN_004f6aa0();
    FUN_004f6ab0("ch01001.otf",DAT_0091755c,0x41000000,0);
  }
  if ((*(char *)(param_1 + 0x5e) == '\0') &&
     (cVar2 = FUN_005ce630(*(undefined4 *)(param_1 + 0xd8)), cVar2 != '\0')) {
    *(undefined1 *)(param_1 + 0x5e) = 1;
    uVar3 = FUN_00437d30("ch01002.wav");
    *(undefined4 *)(param_1 + 0xfc) = uVar3;
    FUN_004f6aa0();
    FUN_004f6ab0("ch01001.otf",DAT_009175b0,0x41000000,0);
    *(undefined1 *)(param_1 + 0x55) = 1;
  }
  if ((*(int *)(param_1 + 0xfc) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0xfc)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0xfc) = 0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar5 + 15.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x70)) {
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    uVar3 = FUN_00437d30("ch01003.wav");
    *(undefined4 *)(param_1 + 0x100) = uVar3;
  }
  if ((*(int *)(param_1 + 0x100) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x100)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x100) = 0;
    FUN_005c8250("cvslfb",1,"armoury",0,0);
    FUN_00437d30("ch01004.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("ch01001.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("ch01002.otf",DAT_0091755c,0x41000000,0);
    FUN_005cada0(1,99);
  }
  if ((*(char *)(param_1 + 0x56) == '\0') &&
     (fVar5 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xdc)), (float)fVar5 <= 0.0)) {
    *(undefined1 *)(param_1 + 0x56) = 1;
    *(undefined1 *)(param_1 + 0x5e) = 1;
    FUN_00437d30("ch01005.wav");
    uVar3 = FUN_005c8250("cvrecyd",1,"recycler",0,0);
    *(undefined4 *)(param_1 + 0xa0) = uVar3;
    FUN_005cada0(1,0x32);
    FUN_004f6aa0();
    FUN_004f6ab0("ch01001.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("ch01002.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("ch01006.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("ch01007.otf",DAT_0091755c,0x41000000,0);
  }
  if (((*(int *)(param_1 + 0xa0) != 0) && (*(char *)(param_1 + 0x5f) == '\0')) &&
     (cVar2 = FUN_005cd7c0(*(undefined4 *)(param_1 + 0xa0)), cVar2 != '\0')) {
    *(undefined1 *)(param_1 + 0x5f) = 1;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar5 + 60.0;
    FUN_004f6aa0();
    FUN_004f6ab0("ch01006.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("ch01007.otf",DAT_0091755c,0x41000000,0);
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x74)) {
    *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    uVar3 = FUN_005c8250("svfigh",2,"wave_1",0,0);
    FUN_005cb960(uVar3,"follow_1",1);
    uVar3 = FUN_005c8250("svfigh",2,"wave_1",0,0);
    FUN_005cb960(uVar3,"follow_1",1);
    uVar3 = FUN_005c8250("svfigh",2,"wave_1",0,0);
    FUN_005cb960(uVar3,"follow_1",1);
    uVar3 = FUN_005c8250("svfigh",2,"wave_1",0,0);
    FUN_005cb960(uVar3,"follow_1",1);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar5 + 300.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x78) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x78)) {
    *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
    uVar3 = FUN_005c8250("svltnk",2,"wave_2",0,0);
    FUN_005cb960(uVar3,"follow_2",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_2",0,0);
    FUN_005cb960(uVar3,"follow_2",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_2",0,0);
    FUN_005cb960(uVar3,"follow_2",1);
    uVar3 = FUN_005c8250("svfigh",2,"wave_2",0,0);
    FUN_005cb960(uVar3,"follow_2",1);
    uVar3 = FUN_005c8250("svfigh",2,"wave_2",0,0);
    FUN_005cb960(uVar3,"follow_2",1);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar5 + 300.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x7c)) {
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    uVar3 = FUN_005c8250("svtank",2,"wave_3",0,0);
    FUN_005cb960(uVar3,"follow_3",1);
    uVar3 = FUN_005c8250("svtank",2,"wave_3",0,0);
    FUN_005cb960(uVar3,"follow_3",1);
    uVar3 = FUN_005c8250("svtank",2,"wave_3",0,0);
    FUN_005cb960(uVar3,"follow_3",1);
    uVar3 = FUN_005c8250("svtank",2,"wave_3",0,0);
    FUN_005cb960(uVar3,"follow_3",1);
    uVar3 = FUN_005c8250("svtank",2,"wave_3",0,0);
    FUN_005cb960(uVar3,"follow_3",1);
    uVar3 = FUN_005c8250("svhraz",2,"wave_3",0,0);
    FUN_005cb960(uVar3,"follow_3",1);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar5 + 180.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x88) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x88)) {
    *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
    uVar3 = FUN_005c8250("sspilo",2,"aerial_1",200,0);
    FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xa0),1);
    uVar3 = FUN_005c8250("sspilo",2,"aerial_1",200,0);
    FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xa0),1);
    uVar3 = FUN_005c8250("sspilo",2,"aerial_1",200,0);
    FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xa0),1);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar5 + 30.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x8c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x8c)) {
    *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
    uVar3 = FUN_005c8250("sssold",2,"aerial_2",200,0);
    FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xa0),1);
    uVar3 = FUN_005c8250("sssold",2,"aerial_2",200,0);
    FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xa0),1);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar5 + 60.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x80)) {
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    uVar3 = FUN_005c8250("svltnk",2,"wave_4",0,0);
    FUN_005cb960(uVar3,"follow_4",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_4",0,0);
    FUN_005cb960(uVar3,"follow_4",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_4",0,0);
    FUN_005cb960(uVar3,"follow_4",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_4",0,0);
    FUN_005cb960(uVar3,"follow_4",1);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x90) = (float)fVar5 + 120.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x90) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x90)) {
    *(undefined4 *)(param_1 + 0x90) = 0x497423fe;
    uVar3 = FUN_005c8250("svhaula",2,"relic_tug",0,0);
    *(undefined4 *)(param_1 + 0xa4) = uVar3;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xa4),"tug_path",1);
    uVar3 = FUN_005c8250("svfigh",2,"tug_defend",0,0);
    FUN_005cbce0(uVar3,*(undefined4 *)(param_1 + 0xa4),1);
    uVar3 = FUN_005c8250("svfigh",2,"tug_defend",0,0);
    FUN_005cbce0(uVar3,*(undefined4 *)(param_1 + 0xa4),1);
  }
  if (((*(int *)(param_1 + 0xa4) != 0) && (*(char *)(param_1 + 0x60) == '\0')) &&
     (fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa4),"nav_tug",0),
     (float)fVar5 < 1000.0)) {
    *(undefined1 *)(param_1 + 0x60) = 1;
    FUN_00437d30("ch01006.wav");
    uVar3 = FUN_005c8250(&DAT_00878c18,1,"nav_tug",0,0);
    *(undefined4 *)(param_1 + 0xec) = uVar3;
    FUN_004f6aa0();
    FUN_004f6ab0("ch01007.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("ch01003.otf",DAT_0091755c,0x41000000,0);
  }
  if (((*(int *)(param_1 + 0xa4) != 0) &&
      (fVar5 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa4)), (float)fVar5 <= 0.0)) &&
     ((*(char *)(param_1 + 0x68) == '\0' && (*(char *)(param_1 + 0x67) == '\0')))) {
    *(undefined1 *)(param_1 + 0x68) = 1;
    uVar3 = FUN_00437d30("ch01011.wav");
    *(undefined4 *)(param_1 + 0x10c) = uVar3;
  }
  if ((*(int *)(param_1 + 0x10c) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x10c)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x10c) = 0;
    fVar5 = (float10)FUN_004b1670("ch01lseb.des");
    FUN_0045c0f0((float)fVar5 + 1.0);
  }
  if ((((*(int *)(param_1 + 0xa4) != 0) &&
       (fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa4),"tug_fail",0),
       (float)fVar5 < 350.0)) && (iVar4 = FUN_005c8800(*(undefined4 *)(param_1 + 0xa4)), iVar4 == 2)
      ) && ((*(char *)(param_1 + 0x68) == '\0' && (*(char *)(param_1 + 0x67) == '\0')))) {
    fVar5 = (float10)FUN_004b1670("ch01lsea.des");
    FUN_0045c0f0((float)fVar5 + 1.0);
    *(undefined1 *)(param_1 + 0x68) = 1;
  }
  if (((*(int *)(param_1 + 0xa4) != 0) &&
      (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa4),*(undefined4 *)(param_1 + 0xa0)
                                    ), (float)fVar5 < 75.0)) && (*(char *)(param_1 + 0x57) == '\0'))
  {
    FUN_00437d30("ch01007.wav");
    uVar3 = FUN_005c8250("svfigh",1,"fighters",0,0);
    *(undefined4 *)(param_1 + 0xa8) = uVar3;
    FUN_005c88b0(*(undefined4 *)(param_1 + 0xa8),2);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xa8),0);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0xa8),2);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xa8),"fighters_to",1);
    uVar3 = FUN_005c8250("svfigh",1,"fighters",0,0);
    *(undefined4 *)(param_1 + 0xac) = uVar3;
    FUN_005c88b0(*(undefined4 *)(param_1 + 0xac),2);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xac),0);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0xac),2);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xac),"fighters_to",1);
    *(undefined1 *)(param_1 + 0x57) = 1;
    FUN_004f6aa0();
    FUN_004f6ab0("ch01003.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("ch01004.otf",DAT_0091755c,0x41000000,0);
    uVar3 = FUN_005c8250("obdata",0,"relic_loc",0,0);
    *(undefined4 *)(param_1 + 0xe4) = uVar3;
    uVar3 = FUN_005c8250("svtank",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svtank",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svtank",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svtank",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svhraz",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svhraz",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svhraz",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svhraz",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svltnk",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svturrb",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svturrb",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svturrb",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
    uVar3 = FUN_005c8250("svturrb",2,"wave_5",0,0);
    FUN_005cb960(uVar3,"follow_5",1);
  }
  if ((((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x58) == '\0')) &&
      (*(char *)(param_1 + 0x68) == '\0')) && (*(char *)(param_1 + 0x67) == '\0')) {
    bVar1 = false;
    for (local_20 = 0; local_20 < 10; local_20 = local_20 + 1) {
      cVar2 = FUN_005c84d0(param_1 + 0xb0 + local_20 * 4);
      if ((cVar2 != '\0') &&
         (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x9c),
                                        *(undefined4 *)(param_1 + 0xb0 + local_20 * 4)),
         (float)fVar5 < 350.0)) {
        bVar1 = true;
        break;
      }
    }
    if ((*(char *)(param_1 + 0x61) == '\0') && (bVar1)) {
      FUN_005c8250("sspilo",2,"aerial_3",100,0);
      FUN_005c8250("sspilo",2,"aerial_3",100,0);
      FUN_005c8250("sspilo",2,"aerial_3",100,0);
      FUN_005c8250("sspilo",2,"aerial_3",100,0);
      FUN_005c8250("sssold",2,"aerial_4",100,0);
      FUN_005c8250("sssold",2,"aerial_4",100,0);
      FUN_005c8250("sssold",2,"aerial_4",100,0);
      FUN_005c8250("sssold",2,"aerial_4",100,0);
      FUN_005c8250("sssold",2,"aerial_4",100,0);
      FUN_005c8250("sssold",2,"aerial_4",100,0);
      *(undefined1 *)(param_1 + 0x61) = 1;
    }
    FUN_005cd0a0(*(undefined4 *)(param_1 + 0xa8),0);
    FUN_005cd0a0(*(undefined4 *)(param_1 + 0xac),0);
    FUN_005cd0d0(*(undefined4 *)(param_1 + 0xa8),0);
    FUN_005cd0d0(*(undefined4 *)(param_1 + 0xac),0);
    cVar2 = FUN_005ce520(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x9c));
    if ((cVar2 == '\0') ||
       (cVar2 = FUN_005ce520(*(undefined4 *)(param_1 + 0xac),*(undefined4 *)(param_1 + 0x9c)),
       cVar2 == '\0')) {
      if (bVar1) {
        *(undefined1 *)(param_1 + 0x68) = 1;
        uVar3 = FUN_00437d30("ch01008.wav");
        *(undefined4 *)(param_1 + 0x108) = uVar3;
      }
    }
    else {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x9c),2);
    }
  }
  if ((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x58) == '\0')) {
    cVar2 = FUN_005ce520(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x9c));
    if ((cVar2 == '\0') ||
       (cVar2 = FUN_005ce520(*(undefined4 *)(param_1 + 0xac),*(undefined4 *)(param_1 + 0x9c)),
       cVar2 == '\0')) {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x9c),1);
    }
    else {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x9c),2);
    }
  }
  if ((*(int *)(param_1 + 0x108) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x108)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x108) = 0;
    fVar5 = (float10)FUN_004b1670("ch01lsec.des");
    FUN_0045c0f0((float)fVar5);
  }
  if ((((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x58) == '\0')) &&
      (*(int *)(param_1 + 0xe4) != 0)) &&
     ((*(int *)(param_1 + 0xa4) != 0 &&
      (iVar4 = FUN_005ce580(*(undefined4 *)(param_1 + 0xa4)), iVar4 == *(int *)(param_1 + 0xe4)))))
  {
    *(undefined1 *)(param_1 + 0x58) = 1;
    FUN_004f6aa0();
    FUN_004f6ab0("ch01004.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("ch01005.otf",DAT_0091755c,0x41000000,0);
    uVar3 = FUN_005c8250(&DAT_00878c18,1,"nav_end",0,0);
    *(undefined4 *)(param_1 + 0xf0) = uVar3;
    uVar3 = FUN_0081cb40("names","Safe Distance");
    FUN_005cd7f0(*(undefined4 *)(param_1 + 0xf0),uVar3);
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xf0));
    FUN_004f6ae0(0xb4,0xf,5);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x94) = (float)fVar5 + 30.0;
  }
  if ((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 0x66) == '\0')) {
    bVar1 = false;
    for (local_20 = 0; local_20 < 10; local_20 = local_20 + 1) {
      cVar2 = FUN_005c84d0(param_1 + 0xb0 + local_20 * 4);
      if ((cVar2 != '\0') &&
         (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x9c),
                                        *(undefined4 *)(param_1 + 0xb0 + local_20 * 4)),
         (float)fVar5 < 300.0)) {
        bVar1 = true;
        break;
      }
    }
    if (bVar1) {
      *(undefined1 *)(param_1 + 0x66) = 1;
      FUN_00437d30("ch01009.wav");
      FUN_005cd0a0(*(undefined4 *)(param_1 + 0xa8),100);
      FUN_005cd0a0(*(undefined4 *)(param_1 + 0xac),100);
      FUN_005cd0d0(*(undefined4 *)(param_1 + 0xa8),100);
      FUN_005cd0d0(*(undefined4 *)(param_1 + 0xac),100);
      for (local_20 = 0; local_20 < 7; local_20 = local_20 + 1) {
        uVar3 = FUN_005c8250("cvhtnk",1,"decoy_units",0,0);
        uVar7 = 1;
        iVar4 = rand();
        FUN_005cb9d0(uVar3,*(undefined4 *)(param_1 + 0xb0 + (iVar4 % 10) * 4),uVar7);
      }
    }
  }
  if ((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 99) == '\0')) {
    iVar4 = FUN_004f6b10();
    if (iVar4 < 1) {
      *(undefined4 *)(param_1 + 0x94) = 0x497423fe;
      FUN_004ff160();
      *(undefined1 *)(param_1 + 100) = 1;
      *(undefined1 *)(param_1 + 99) = 1;
      FUN_0049b760(0x3f800000,0x3f000000,0xff,0xff,0xff);
    }
    else {
      iVar4 = FUN_004f6b10();
      if ((2.0 < (double)iVar4) || (*(char *)(param_1 + 0x62) != '\0')) {
        iVar4 = FUN_004f6b10();
        if (((double)iVar4 <= 5.0) && (*(char *)(param_1 + 0x59) == '\0')) {
          fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf0),
                                        *(undefined4 *)(param_1 + 0xd8));
          fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x9c),
                                        *(undefined4 *)(param_1 + 0xd8));
          if (((float)fVar5 - 50.0 < (float)fVar6) && (*(char *)(param_1 + 0x62) == '\0')) {
            *(undefined1 *)(param_1 + 0x59) = 1;
            FUN_00437d30("ch01010.wav");
          }
        }
      }
      else {
        fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf0),
                                      *(undefined4 *)(param_1 + 0xd8));
        fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x9c),
                                      *(undefined4 *)(param_1 + 0xd8));
        if (((float)fVar5 - 50.0 < (float)fVar6) && (*(char *)(param_1 + 0x62) == '\0')) {
          FUN_005cd2a0();
          FUN_005cd300("cut_end",3000,0,*(undefined4 *)(param_1 + 0xe0));
          *(undefined1 *)(param_1 + 0x62) = 1;
        }
      }
    }
  }
  if (*(char *)(param_1 + 100) != '\0') {
    *(undefined1 *)(param_1 + 100) = 0;
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xd8));
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xe4),*(undefined4 *)(param_1 + 0xd8));
    if ((float)fVar6 <= (float)fVar5 - 50.0) {
      fVar5 = (float10)FUN_004b1670("ch01lsee.des");
      FUN_0045c0f0((float)fVar5 + 3.0);
      *(undefined1 *)(param_1 + 0x68) = 1;
    }
    else {
      fVar5 = (float10)FUN_004b1670("ch01win.des");
      FUN_0045c110((float)fVar5 + 3.0);
      *(undefined1 *)(param_1 + 0x67) = 1;
    }
    local_14 = 0x44820000;
    local_10 = 0x42200000;
    local_c = 0x47c72900;
    FUN_005ce280(&local_14,"xpltrsn");
  }
  if ((((*(int *)(param_1 + 0xa0) != 0) &&
       (fVar5 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa0)), (double)fVar5 <= 0.0)) &&
      (*(char *)(param_1 + 0x57) == '\0')) &&
     ((*(char *)(param_1 + 0x68) == '\0' && (*(char *)(param_1 + 0x67) == '\0')))) {
    *(undefined1 *)(param_1 + 0x68) = 1;
    fVar5 = (float10)FUN_004b1670("ch01lsed.des");
    FUN_0045c0f0((float)fVar5 + 1.0);
  }
  FUN_0083e885();
  return;
}

