
void __fastcall FUN_0054fe40(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  if (-1 < *(int *)(param_1 + 0x44)) {
    if (*(char *)(param_1 + 0x41) != '\0') {
      return;
    }
    FUN_00437d30("misn1808.wav");
    fVar4 = (float10)FUN_004b1670(0);
    FUN_0045c110((float)fVar4 + 12.0);
    *(undefined1 *)(param_1 + 0x6f) = 1;
    *(undefined1 *)(param_1 + 99) = 1;
    *(undefined1 *)(param_1 + 0x68) = 1;
    *(undefined1 *)(param_1 + 0x41) = 1;
  }
  if (*(int *)(param_1 + 0x4c) < 0) goto LAB_0054ffc5;
  if (*(char *)(param_1 + 0x41) != '\0') {
    return;
  }
  if (*(int *)(param_1 + 0x4c) == 1) {
LAB_0054ff32:
    FUN_005cd2a0();
    fVar4 = (float10)FUN_004b1670("misn18l2.des");
    FUN_0045c0f0((float)fVar4 + 7.0);
    FUN_00437d30("misn1807.wav");
    *(undefined1 *)(param_1 + 0x6f) = 1;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  else {
    if (*(int *)(param_1 + 0x4c) == 2) {
      fVar4 = (float10)FUN_004b1670("misn18l1.des");
      FUN_0045c0f0((float)fVar4 + 5.0);
      FUN_00437d30("misn1806.wav");
      *(undefined1 *)(param_1 + 0x6e) = 1;
      goto LAB_0054ff32;
    }
    *(undefined1 *)(param_1 + 0x76) = 1;
    fVar4 = (float10)FUN_004b1670("misn18l3.des");
    FUN_0045c0f0((float)fVar4 + 7.0);
    FUN_00437d30("misn1704.wav");
  }
  *(undefined1 *)(param_1 + 0x41) = 1;
LAB_0054ffc5:
  if (*(char *)(param_1 + 0x5e) == '\0') {
    uVar2 = FUN_00437d30("misn1801.wav");
    *(undefined4 *)(param_1 + 0x138) = uVar2;
    uVar2 = FUN_005c7e90("avrecy2_recycler");
    *(undefined4 *)(param_1 + 0xbc) = uVar2;
    FUN_005cadd0(1,0x50);
    uVar2 = FUN_005c7e90("scrapcam");
    *(undefined4 *)(param_1 + 0x1b0) = uVar2;
    uVar2 = FUN_005c7e90("scrapcam2");
    *(undefined4 *)(param_1 + 0x1b4) = uVar2;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar4 + 150.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar4 + 230.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar4 + 310.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x90) = (float)fVar4 + 600.0;
    uVar2 = FUN_005c7e90("basenav");
    *(undefined4 *)(param_1 + 0x13c) = uVar2;
    FUN_005c9640(*(undefined4 *)(param_1 + 0x13c),"Home Base");
    *(undefined1 *)(param_1 + 0x5e) = 1;
    uVar2 = FUN_005c7e90("hbtrn20049_i76building");
    *(undefined4 *)(param_1 + 200) = uVar2;
    uVar2 = FUN_005c7e90("hbtrn20050_i76building");
    *(undefined4 *)(param_1 + 0xcc) = uVar2;
    uVar2 = FUN_005c7e90("hbtrn20051_i76building");
    *(undefined4 *)(param_1 + 0xd0) = uVar2;
    uVar2 = FUN_005c7e90("hbtrn20052_i76building");
    *(undefined4 *)(param_1 + 0xd4) = uVar2;
    uVar2 = FUN_005c7e90("hbtran0038_i76building");
    *(undefined4 *)(param_1 + 0xb8) = uVar2;
    FUN_004ff170(0x40000000);
    *(undefined4 *)(param_1 + 0x1c8) = 2;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa8) = (float)fVar4 + 2.0;
    *(undefined1 *)(param_1 + 0x68) = 1;
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xb8));
    FUN_005c9640(*(undefined4 *)(param_1 + 0xb8),"Fury Transport");
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xac) = (float)fVar4 + 5.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb0) = (float)fVar4 + 3.0;
  }
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xc0) = uVar2;
  if (((*(char *)(param_1 + 0x61) == '\0') &&
      (fVar4 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0xb0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb0))) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xb8), cVar1 != '\0')) {
    uVar2 = FUN_005ca150(*(undefined4 *)(param_1 + 0xb8));
    *(undefined4 *)(param_1 + 0xc4) = uVar2;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb0) = (float)fVar4 + 3.0;
  }
  if (*(char *)(param_1 + 0x68) == '\x01') {
    FUN_004f6aa0();
    if (*(char *)(param_1 + 99) == '\x01') {
      FUN_004f6ab0("misn1803.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn1802.otf",DAT_009175b0,0x41000000,0);
    }
    if ((*(char *)(param_1 + 0x60) == '\x01') && (*(char *)(param_1 + 99) == '\0')) {
      FUN_004f6ab0("misn1803.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misn1802.otf",DAT_009175b0,0x41000000,0);
    }
    if ((*(char *)(param_1 + 0x60) == '\0') && (*(char *)(param_1 + 0x61) == '\x01')) {
      FUN_004f6ab0("misn1802.otf",DAT_0091755c,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x61) == '\0') {
      FUN_004f6ab0("misn1801.otf",DAT_0091755c,0x41000000,0);
    }
    *(undefined1 *)(param_1 + 0x68) = 0;
  }
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cd2a0();
    *(undefined1 *)(param_1 + 0x55) = 1;
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  if ((*(char *)(param_1 + 0x56) == '\x01') &&
     (cVar1 = FUN_005cd300("opencam1",0x5dc,8000,*(undefined4 *)(param_1 + 0x1b0)), cVar1 != '\0'))
  {
    *(undefined1 *)(param_1 + 0x56) = 0;
    *(undefined1 *)(param_1 + 0x57) = 1;
  }
  if ((*(char *)(param_1 + 0x57) == '\x01') &&
     (cVar1 = FUN_005cd300("opencam2",0x5dc,9000,*(undefined4 *)(param_1 + 0x1b4)), cVar1 != '\0'))
  {
    *(undefined1 *)(param_1 + 0x57) = 0;
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1b0));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1b4));
  }
  if (*(char *)(param_1 + 0x55) == '\x01') {
    fVar4 = (float10)FUN_00822d60();
    *(int *)(param_1 + 0x1bc) = *(int *)(param_1 + 0x1bc) - (int)((float)fVar4 * 300.0);
    cVar1 = FUN_005cd300("opencam3",*(undefined4 *)(param_1 + 0x1bc),2000,
                         *(undefined4 *)(param_1 + 0xb8));
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x55) = 0;
      *(undefined1 *)(param_1 + 0x56) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x77) == '\0') &&
     ((cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x138)), cVar1 != '\0' ||
      (cVar1 = FUN_005cd560(), cVar1 != '\0')))) {
    FUN_00437d80(*(undefined4 *)(param_1 + 0x138));
    *(undefined1 *)(param_1 + 0x77) = 1;
    *(undefined1 *)(param_1 + 0x55) = 0;
    *(undefined1 *)(param_1 + 0x56) = 0;
    *(undefined1 *)(param_1 + 0x57) = 0;
    FUN_005cd4e0();
  }
  if (((*(char *)(param_1 + 0x60) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xb8), cVar1 != '\0'))
     && (fVar4 = (float10)FUN_004b1670(),
        *(float *)(param_1 + 0xac) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xac))) {
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0xb8),0x42c80000);
  }
  if ((*(char *)(param_1 + 0x60) == '\x01') && (*(char *)(param_1 + 0x78) == '\0')) {
    FUN_005cb1c0(*(undefined4 *)(param_1 + 0xb8),0x4e6e6b28);
    *(undefined1 *)(param_1 + 0x78) = 1;
  }
  if ((*(char *)(param_1 + 0x61) == '\0') &&
     (fVar4 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0xac) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xac))) {
    cVar1 = FUN_005c84d0(param_1 + 200);
    if (cVar1 != '\0') {
      FUN_005ccfd0(*(undefined4 *)(param_1 + 200),0x42480000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xcc);
    if (cVar1 != '\0') {
      FUN_005ccfd0(*(undefined4 *)(param_1 + 0xcc),0x42480000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xd0);
    if (cVar1 != '\0') {
      FUN_005ccfd0(*(undefined4 *)(param_1 + 0xd0),0x42480000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xd4);
    if (cVar1 != '\0') {
      FUN_005ccfd0(*(undefined4 *)(param_1 + 0xd4),0x42480000);
    }
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xac) = (float)fVar4 + 1.0;
  }
  if ((*(char *)(param_1 + 0x58) == '\0') &&
     ((((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"spawn1a",0),
        (float)fVar4 < 100.0 ||
        (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"spawnalt1a",0),
        (float)fVar4 < 100.0)) ||
       (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"cheat1a",0),
       (float)fVar4 < 200.0)) ||
      (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"cheatalt1a",0),
      (float)fVar4 < 200.0)))) {
    uVar2 = FUN_005c8250("hvsat",2,"spawn1b",0,0);
    *(undefined4 *)(param_1 + 0xd8) = uVar2;
    uVar2 = FUN_005c8250("hvsat",2,"spawnalt1b",0,0);
    *(undefined4 *)(param_1 + 0xe0) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xd8),"transport1",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xe0),"transport2",1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xd8),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xe0),1);
    *(undefined1 *)(param_1 + 0x58) = 1;
  }
  if ((*(char *)(param_1 + 0x59) == '\0') &&
     (((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"spawn2a",0),
       (float)fVar4 < 100.0 ||
       (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"spawnalt2a",0),
       (float)fVar4 < 100.0)) ||
      ((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"cheat2a",0),
       (float)fVar4 < 200.0 ||
       (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"cheatalt2a",0),
       (float)fVar4 < 200.0)))))) {
    uVar2 = FUN_005c8250("hvsat",2,"spawn2b",0,0);
    *(undefined4 *)(param_1 + 0xec) = uVar2;
    uVar2 = FUN_005c8250("hvsat",2,"spawnalt2b",0,0);
    *(undefined4 *)(param_1 + 0xf4) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xec),"transport3",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xf4),"transport4",1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xec),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xf4),1);
    *(undefined1 *)(param_1 + 0x59) = 1;
  }
  if ((*(char *)(param_1 + 0x5a) == '\0') &&
     (((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"spawn3a",0),
       (float)fVar4 < 100.0 ||
       (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"spawnalt3a",0),
       (float)fVar4 < 100.0)) ||
      ((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"cheat3a",0),
       (float)fVar4 < 200.0 ||
       (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"cheatalt3a",0),
       (float)fVar4 < 200.0)))))) {
    uVar2 = FUN_005c8250("hvsat",2,"spawn3b",0,0);
    *(undefined4 *)(param_1 + 0xf8) = uVar2;
    uVar2 = FUN_005c8250("hvsat",2,"spawnalt3b",0,0);
    *(undefined4 *)(param_1 + 0x100) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xf8),"transport5",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x100),"transport6",1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xf8),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x100),1);
    *(undefined1 *)(param_1 + 0x5a) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x84) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x84)) &&
     (*(char *)(param_1 + 0x65) == '\0')) {
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand",0,0);
    *(undefined4 *)(param_1 + 0x140) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x140),"transport7",1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x140),1);
    *(undefined1 *)(param_1 + 0x65) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x88) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x88)) &&
     (*(char *)(param_1 + 0x66) == '\0')) {
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand",0,0);
    *(undefined4 *)(param_1 + 0x14c) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x14c),"transport8",1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x14c),1);
    *(undefined1 *)(param_1 + 0x66) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x8c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x8c)) &&
     (*(char *)(param_1 + 0x67) == '\0')) {
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand",0,0);
    *(undefined4 *)(param_1 + 0x158) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x158),"transport9",1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x158),1);
    *(undefined1 *)(param_1 + 0x67) = 1;
  }
  if (((*(char *)(param_1 + 0x60) == '\x01') && (*(char *)(param_1 + 0x69) == '\0')) &&
     (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"dontgo",0), (float)fVar4 < 50.0
     )) {
    FUN_00437d30("misn1805.wav");
    *(undefined1 *)(param_1 + 0x69) = 1;
  }
  if (((*(char *)(param_1 + 0x69) == '\x01') &&
      (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"dontgo1",0),
      (float)fVar4 < 100.0)) && (*(char *)(param_1 + 0x6a) == '\0')) {
    uVar2 = FUN_005c8250("hvsat",2,&DAT_00881d64,0,0);
    *(undefined4 *)(param_1 + 0x164) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawn1",0,0);
    *(undefined4 *)(param_1 + 0x168) = uVar2;
    *(undefined1 *)(param_1 + 0x6a) = 1;
  }
  if (((*(char *)(param_1 + 0x69) == '\x01') &&
      (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"dontgo2",0),
      (float)fVar4 < 100.0)) && (*(char *)(param_1 + 0x6b) == '\0')) {
    uVar2 = FUN_005c8250("hvsat",2,&DAT_00881d74,0,0);
    *(undefined4 *)(param_1 + 0x174) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawn1",0,0);
    *(undefined4 *)(param_1 + 0x178) = uVar2;
    *(undefined1 *)(param_1 + 0x6b) = 1;
  }
  if (((*(char *)(param_1 + 0x69) == '\x01') &&
      (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"dontgo3",0),
      (float)fVar4 < 100.0)) && (*(char *)(param_1 + 0x6c) == '\0')) {
    uVar2 = FUN_005c8250("hvsat",2,&DAT_00881d84,0,0);
    *(undefined4 *)(param_1 + 0x184) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawn1",0,0);
    *(undefined4 *)(param_1 + 0x188) = uVar2;
    *(undefined1 *)(param_1 + 0x6c) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 200);
  if (((cVar1 == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xcc), cVar1 == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0xd0), cVar1 == '\0' &&
      ((cVar1 = FUN_005c84d0(param_1 + 0xd4), cVar1 == '\0' && (*(char *)(param_1 + 0x60) == '\0')))
      ))) {
    FUN_00437d30("misn1804.wav");
    *(undefined1 *)(param_1 + 0x60) = 1;
    *(undefined1 *)(param_1 + 0x68) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x94) = (float)fVar4 + 60.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x98) = (float)fVar4 + 85.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar4 + 115.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa0) = (float)fVar4 + 140.0;
    *(undefined4 *)(param_1 + 0x1c8) = 6;
    FUN_004f6ae0(0xb4,0x78,0x1e);
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x94) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x94)) &&
     (*(char *)(param_1 + 99) == '\0')) {
    FUN_00437d30("misn1809.wav");
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x94) = (float)fVar4 + 1e+08;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x98) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x98)) &&
     (*(char *)(param_1 + 99) == '\0')) {
    FUN_00437d30("misn1810.wav");
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x98) = (float)fVar4 + 1e+08;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x9c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x9c)) &&
     (*(char *)(param_1 + 99) == '\0')) {
    FUN_00437d30("misn1811.wav");
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar4 + 1e+08;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0xa0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa0)) &&
     (*(char *)(param_1 + 99) == '\0')) {
    FUN_00437d30("misn1812.wav");
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa0) = (float)fVar4 + 1e+08;
  }
  if ((*(char *)(param_1 + 0x61) == '\0') &&
     ((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"transfound",0),
      (float)fVar4 < 100.0 ||
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xc4),*(undefined4 *)(param_1 + 0xb8)
                                    ), (float)fVar4 < 200.0)))) {
    FUN_00437d30("misn1816.wav");
    *(undefined1 *)(param_1 + 0x61) = 1;
    cVar1 = FUN_005c84d0(param_1 + 0xb8);
    if (cVar1 != '\0') {
      FUN_005c9610(*(undefined4 *)(param_1 + 0xb8));
    }
    cVar1 = FUN_005c84d0(param_1 + 200);
    if (cVar1 != '\0') {
      FUN_005c95e0(*(undefined4 *)(param_1 + 200));
    }
    cVar1 = FUN_005c84d0(param_1 + 0xcc);
    if (cVar1 != '\0') {
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xcc));
    }
    cVar1 = FUN_005c84d0(param_1 + 0xd0);
    if (cVar1 != '\0') {
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xd0));
    }
    cVar1 = FUN_005c84d0(param_1 + 0xd4);
    if (cVar1 != '\0') {
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xd4));
    }
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa4) = (float)fVar4 + 180.0;
    *(undefined1 *)(param_1 + 0x68) = 1;
    if (*(char *)(param_1 + 0x58) == '\0') {
      uVar2 = FUN_005c8250("hvsat",2,"spawn1b",0,0);
      *(undefined4 *)(param_1 + 0xd8) = uVar2;
      uVar2 = FUN_005c8250("hvsat",2,"spawnalt1b",0,0);
      *(undefined4 *)(param_1 + 0xe0) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd8),"transport1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0xe0),"transport2",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xd8),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xe0),1);
      *(undefined1 *)(param_1 + 0x58) = 1;
    }
    if (*(char *)(param_1 + 0x59) == '\0') {
      uVar2 = FUN_005c8250("hvsat",2,"spawn2b",0,0);
      *(undefined4 *)(param_1 + 0xec) = uVar2;
      uVar2 = FUN_005c8250("hvsat",2,"spawnalt2b",0,0);
      *(undefined4 *)(param_1 + 0xf4) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xec),"transport3",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0xf4),"transport4",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xec),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xf4),1);
      *(undefined1 *)(param_1 + 0x59) = 1;
    }
    if (*(char *)(param_1 + 0x5a) == '\0') {
      uVar2 = FUN_005c8250("hvsat",2,"spawn3b",0,0);
      *(undefined4 *)(param_1 + 0xf8) = uVar2;
      uVar2 = FUN_005c8250("hvsat",2,"spawnalt3b",0,0);
      *(undefined4 *)(param_1 + 0x100) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xf8),"transport5",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x100),"transport6",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xf8),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x100),1);
      *(undefined1 *)(param_1 + 0x5a) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x60) == '\0') && (*(char *)(param_1 + 0x7d) == '\0')) &&
     (fVar4 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0xa4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa4))) {
    *(undefined1 *)(param_1 + 0x7d) = 1;
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand",0,0);
    *(undefined4 *)(param_1 + 0x194) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand",0,0);
    *(undefined4 *)(param_1 + 0x198) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand2",0,0);
    *(undefined4 *)(param_1 + 0x19c) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand2",0,0);
    *(undefined4 *)(param_1 + 0x1a0) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0x194),*(undefined4 *)(param_1 + 0xbc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0xbc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x19c),*(undefined4 *)(param_1 + 0xbc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x1a0),*(undefined4 *)(param_1 + 0xbc),1);
  }
  if (((*(char *)(param_1 + 0x7d) == '\x01') &&
      (cVar1 = FUN_005c84d0(param_1 + 0x194), cVar1 == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x198), cVar1 == '\0' &&
      ((cVar1 = FUN_005c84d0(param_1 + 0x19c), cVar1 == '\0' &&
       (cVar1 = FUN_005c84d0(param_1 + 0x1a0), cVar1 == '\0')))))) {
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand",0,0);
    *(undefined4 *)(param_1 + 0x194) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand",0,0);
    *(undefined4 *)(param_1 + 0x198) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand2",0,0);
    *(undefined4 *)(param_1 + 0x19c) = uVar2;
    uVar2 = FUN_005c8250("hvsav",2,"spawnrand2",0,0);
    *(undefined4 *)(param_1 + 0x1a0) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0x194),*(undefined4 *)(param_1 + 0xbc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0xbc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x19c),*(undefined4 *)(param_1 + 0xbc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x1a0),*(undefined4 *)(param_1 + 0xbc),1);
  }
  if (((*(char *)(param_1 + 0x61) == '\0') &&
      (fVar4 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0x90) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x90))) &&
     (*(char *)(param_1 + 0x6e) == '\0')) {
    fVar4 = (float10)FUN_004b1670("misn18l1.des");
    FUN_0045c0f0((float)fVar4 + 5.0);
    FUN_00437d30("misn1806.wav");
    *(undefined1 *)(param_1 + 0x6e) = 1;
  }
  if (((*(char *)(param_1 + 0x60) == '\x01') &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xc0),*(undefined4 *)(param_1 + 0xbc)
                                    ), 400.0 < (float)fVar4)) &&
     ((iVar3 = FUN_004f6b10(), iVar3 < 1 && (*(char *)(param_1 + 0x6f) == '\0')))) {
    FUN_005cd2a0();
    fVar4 = (float10)FUN_004b1670("misn18l2.des");
    FUN_0045c0f0((float)fVar4 + 7.0);
    FUN_00437d30("misn1807.wav");
    *(undefined1 *)(param_1 + 0x6f) = 1;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xbc);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x76) == '\0')) {
    *(undefined1 *)(param_1 + 0x76) = 1;
    fVar4 = (float10)FUN_004b1670("misn18l3.des");
    FUN_0045c0f0((float)fVar4 + 7.0);
    FUN_00437d30("misn1704.wav");
  }
  if (*(char *)(param_1 + 0x71) == '\x01') {
    *(int *)(param_1 + 0x1c0) = *(int *)(param_1 + 0x1c0) + 500;
    FUN_005cd440(*(undefined4 *)(param_1 + 0xc0),1,*(undefined4 *)(param_1 + 0x1c0),1000,
                 *(undefined4 *)(param_1 + 0xc0));
  }
  fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"return1",0);
  if (((((float)fVar4 < 100.0) ||
       (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc0),"return2",0),
       (float)fVar4 < 100.0)) && (*(char *)(param_1 + 0x62) == '\0')) &&
     (*(char *)(param_1 + 0x60) == '\x01')) {
    uVar2 = FUN_005c8250("hvsat",2,"spawnreturn",0,0);
    *(undefined4 *)(param_1 + 0x1a4) = uVar2;
    *(undefined1 *)(param_1 + 0x62) = 1;
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xc0),*(undefined4 *)(param_1 + 0xbc));
  if ((((float)fVar4 < 200.0) && (*(char *)(param_1 + 0x60) == '\x01')) &&
     (*(char *)(param_1 + 99) == '\0')) {
    FUN_00437d30("misn1808.wav");
    fVar4 = (float10)FUN_004b1670(0);
    FUN_0045c110((float)fVar4 + 12.0);
    *(undefined1 *)(param_1 + 0x6f) = 1;
    *(undefined1 *)(param_1 + 99) = 1;
    *(undefined1 *)(param_1 + 0x68) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 200);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x72) == '\0')) {
    *(int *)(param_1 + 0x1c4) = *(int *)(param_1 + 0x1c4) + 1;
    *(undefined1 *)(param_1 + 0x72) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xcc);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x73) == '\0')) {
    *(int *)(param_1 + 0x1c4) = *(int *)(param_1 + 0x1c4) + 1;
    *(undefined1 *)(param_1 + 0x73) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xd0);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x74) == '\0')) {
    *(int *)(param_1 + 0x1c4) = *(int *)(param_1 + 0x1c4) + 1;
    *(undefined1 *)(param_1 + 0x74) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xd4);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x75) == '\0')) {
    *(int *)(param_1 + 0x1c4) = *(int *)(param_1 + 0x1c4) + 1;
    *(undefined1 *)(param_1 + 0x75) = 1;
  }
  if ((*(int *)(param_1 + 0x1c4) == 1) && (*(char *)(param_1 + 0x79) == '\0')) {
    FUN_00437d30("misn1813.wav");
    *(undefined1 *)(param_1 + 0x79) = 1;
  }
  if ((*(int *)(param_1 + 0x1c4) == 2) && (*(char *)(param_1 + 0x7a) == '\0')) {
    FUN_00437d30("misn1814.wav");
    *(undefined1 *)(param_1 + 0x7a) = 1;
  }
  if ((*(int *)(param_1 + 0x1c4) == 3) && (*(char *)(param_1 + 0x7b) == '\0')) {
    FUN_00437d30("misn1815.wav");
    *(undefined1 *)(param_1 + 0x7b) = 1;
  }
  return;
}

