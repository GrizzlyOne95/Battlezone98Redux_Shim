
void __fastcall FUN_00552a20(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  
  if (*(char *)(param_1 + 0x5a) == '\0') {
    FUN_00437d30("misns101.wav");
    uVar2 = FUN_005c7e90("eggeizr10_geyser");
    *(undefined4 *)(param_1 + 0x138) = uVar2;
    uVar2 = FUN_005c7e90("avmuf1_factory");
    *(undefined4 *)(param_1 + 300) = uVar2;
    uVar2 = FUN_005c7e90("absilo1_i76building");
    *(undefined4 *)(param_1 + 0x128) = uVar2;
    uVar2 = FUN_005c7e90("avrecy1_recycler");
    *(undefined4 *)(param_1 + 0x108) = uVar2;
    uVar2 = FUN_005c7e90("svrecy2_recycler");
    *(undefined4 *)(param_1 + 0x130) = uVar2;
    FUN_005cadd0(2,0x32);
    FUN_005cadd0(1,0x14);
    uVar2 = FUN_005c7e90("avfigh3_wingman");
    *(undefined4 *)(param_1 + 0x10c) = uVar2;
    uVar2 = FUN_005c7e90("avfigh4_wingman");
    *(undefined4 *)(param_1 + 0x110) = uVar2;
    uVar2 = FUN_005c7e90("avfigh5_wingman");
    *(undefined4 *)(param_1 + 0x114) = uVar2;
    uVar2 = FUN_005c7e90("avtank5_wingman");
    *(undefined4 *)(param_1 + 0x118) = uVar2;
    uVar2 = FUN_005c7e90("avtank6_wingman");
    *(undefined4 *)(param_1 + 0x11c) = uVar2;
    uVar2 = FUN_005c7e90("avtank7_wingman");
    *(undefined4 *)(param_1 + 0x120) = uVar2;
    uVar2 = FUN_005c7e90("avtank8_wingman");
    *(undefined4 *)(param_1 + 0x124) = uVar2;
    uVar2 = FUN_005c7e90("ambase");
    *(undefined4 *)(param_1 + 0x1b8) = uVar2;
    uVar2 = FUN_005c8250("svwalk",1,"spawnwalker1",0,0);
    *(undefined4 *)(param_1 + 0x144) = uVar2;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"walkcam1",0,0);
    *(undefined4 *)(param_1 + 0x150) = uVar2;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"hidcamupper",0,0);
    *(undefined4 *)(param_1 + 0x15c) = uVar2;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"hidcammiddle",0,0);
    *(undefined4 *)(param_1 + 0x160) = uVar2;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"hidcamlower",0,0);
    *(undefined4 *)(param_1 + 0x164) = uVar2;
    uVar2 = FUN_005c7e90("apcamr0_camerapod");
    *(undefined4 *)(param_1 + 0x168) = uVar2;
    FUN_005c9640(*(undefined4 *)(param_1 + 0x150),"Walker Cut Off");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x1b8),"American Outpost");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x15c),"Upper Pass Exit");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x160),"Middle Pass Exit");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x164),"Lower Pass Exit");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x168),"Home Base");
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x120));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x124));
    FUN_005c8250("svtank",1,"tank1",0,0);
    FUN_005c8250("svtank",1,"tank2",0,0);
    FUN_005c8250("svfigh",1,"figh1",0,0);
    FUN_005c8250("svturr",1,"turr1",0,0);
    FUN_005c8250("svturr",1,"turr2",0,0);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x98) = (float)fVar5 + 180.0;
    *(undefined1 *)(param_1 + 0x5a) = 1;
    FUN_005cadd0(1,0x14);
    FUN_005cadd0(2,0x32);
    iVar3 = rand();
    *(int *)(param_1 + 0x1c0) = iVar3 % 3;
    uVar4 = rand();
    uVar4 = uVar4 & 0x80000003;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
    }
    *(uint *)(param_1 + 0x1c4) = uVar4;
    *(undefined1 *)(param_1 + 0x76) = 1;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa0) = (float)fVar5 + 11.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa4) = (float)fVar5 + 11.1;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa8) = (float)fVar5 + 20.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xac) = (float)fVar5 + 27.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb0) = (float)fVar5 + 29.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb4) = (float)fVar5 + 31.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb8) = (float)fVar5 + 33.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xbc) = (float)fVar5 + 44.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xc0) = (float)fVar5 + 46.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xc4) = (float)fVar5 + 48.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 200) = (float)fVar5 + 50.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xcc) = (float)fVar5 + 60.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xd0) = (float)fVar5 + 66.0;
  }
  FUN_005c84d0(param_1 + 0x108);
  if (*(char *)(param_1 + 0x76) == '\x01') {
    FUN_004f6aa0();
    cVar1 = FUN_005c84d0(param_1 + 0x108);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x5e) == '\0')) {
      FUN_004f6ab0("misns101.otf",DAT_0091755c,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x108);
    if ((cVar1 == '\0') && (*(char *)(param_1 + 0x5e) == '\0')) {
      FUN_004f6ab0("misns101.otf",DAT_009175b0,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x73) == '\x01') {
      FUN_004f6ab0("misns101.otf",DAT_0091757c,0x41000000,0);
    }
    if ((*(char *)(param_1 + 0x5e) == '\0') &&
       ((cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0' ||
        (cVar1 = FUN_005c84d0(param_1 + 0x128), cVar1 != '\0')))) {
      FUN_004f6ab0("misns102.otf",DAT_0091755c,0x41000000,0);
    }
    if ((*(char *)(param_1 + 0x5e) == '\x01') &&
       (((cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0' ||
         (cVar1 = FUN_005c84d0(param_1 + 0x128), cVar1 != '\0')) ||
        (cVar1 = FUN_005c84d0(param_1 + 0x108), cVar1 != '\0')))) {
      FUN_004f6ab0("misns102.otf",DAT_0091755c,0x41000000,0);
    }
    if (((*(char *)(param_1 + 0x5e) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 == '\0')
        ) && (cVar1 = FUN_005c84d0(param_1 + 0x128), cVar1 == '\0')) {
      FUN_004f6ab0("misns102.otf",DAT_009175b0,0x41000000,0);
    }
    if (((*(char *)(param_1 + 0x5e) == '\x01') &&
        (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 == '\0')) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x128), cVar1 == '\0' &&
        (cVar1 = FUN_005c84d0(param_1 + 0x108), cVar1 == '\0')))) {
      FUN_004f6ab0("misns102.otf",DAT_009175b0,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x130);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x5b) == '\0')) {
      FUN_004f6ab0("misns103.otf",DAT_0091755c,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x130);
    if (cVar1 == '\0') {
      FUN_004f6ab0("misns103.otf",DAT_0091757c,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x5b) == '\x01') {
      FUN_004f6ab0("misns103.otf",DAT_009175b0,0x41000000,0);
    }
    if ((*(char *)(param_1 + 0x5e) == '\x01') && (*(char *)(param_1 + 0x5b) == '\0')) {
      FUN_004f6ab0("misns101.otf",DAT_0091757c,0x41000000,0);
    }
    *(undefined1 *)(param_1 + 0x76) = 0;
  }
  if ((*(char *)(param_1 + 99) == '\0') &&
     (fVar5 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x98) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x98))) {
    iVar3 = *(int *)(param_1 + 0x1c0);
    if (iVar3 == 0) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x108),"upperpath",1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0x108),1);
    }
    else if (iVar3 == 1) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x108),"midpath",1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0x108),1);
    }
    else if (iVar3 == 2) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x108),"lowerpath",1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0x108),1);
    }
    FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x110),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x114),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x11c),1);
    *(undefined1 *)(param_1 + 99) = 1;
    FUN_00437d30("misns125.wav");
  }
  fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0x150));
  if (((((float)fVar5 < 50.0) && (*(char *)(param_1 + 0x5d) == '\0')) &&
      (*(char *)(param_1 + 0x87) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 0x108), cVar1 != '\0')
     ) {
    *(undefined1 *)(param_1 + 0x5d) = 1;
    FUN_00437d30("misns123.wav");
  }
  if ((*(char *)(param_1 + 0x55) == '\x01') && (*(char *)(param_1 + 0x87) == '\0')) {
    if ((*(int *)(param_1 + 0x1c0) == 0) &&
       (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x108),
                                      *(undefined4 *)(param_1 + 0x15c)), (float)fVar5 < 70.0)) {
      *(undefined1 *)(param_1 + 0x87) = 1;
      FUN_00437d30("misns124.wav");
    }
    if ((*(int *)(param_1 + 0x1c0) == 1) &&
       (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x108),
                                      *(undefined4 *)(param_1 + 0x160)), (float)fVar5 < 70.0)) {
      *(undefined1 *)(param_1 + 0x87) = 1;
      FUN_00437d30("misns124.wav");
    }
    if ((*(int *)(param_1 + 0x1c0) == 2) &&
       (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x108),
                                      *(undefined4 *)(param_1 + 0x164)), (float)fVar5 < 70.0)) {
      *(undefined1 *)(param_1 + 0x87) = 1;
      FUN_00437d30("misns124.wav");
    }
  }
  if ((*(char *)(param_1 + 0x59) == '\0') && (*(char *)(param_1 + 0x87) == '\0')) {
    uVar2 = FUN_005ca150(*(undefined4 *)(param_1 + 0x108));
    *(undefined4 *)(param_1 + 0x1b4) = uVar2;
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1b4),*(undefined4 *)(param_1 + 0x108))
    ;
    if ((float)fVar5 < 200.0) {
      *(undefined1 *)(param_1 + 0x59) = 1;
      FUN_00437d30("misns114.wav");
    }
  }
  if ((*(char *)(param_1 + 0x86) == '\0') && (*(char *)(param_1 + 0x59) == '\x01')) {
    FUN_005cb960(*(undefined4 *)(param_1 + 0x108),"retreat1",1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0x1b4),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 0x10c),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x120),*(undefined4 *)(param_1 + 0x10c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x110),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x120),1);
    *(undefined1 *)(param_1 + 0x86) = 1;
  }
  if (((*(char *)(param_1 + 0x59) == '\x01') &&
      (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x108),
                                     *(undefined4 *)(param_1 + 0x138)), (float)fVar5 < 50.0)) &&
     (*(char *)(param_1 + 0x5e) == '\0')) {
    *(undefined1 *)(param_1 + 0x5e) = 1;
    FUN_005cb2d0("misn09.aip",2);
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x108));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x128));
    FUN_005c95e0(*(undefined4 *)(param_1 + 300));
    FUN_00437d30("misns106.wav");
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xd8) = (float)fVar5 + 25.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xdc) = (float)fVar5 + 30.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xe0) = (float)fVar5 + 35.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xe4) = (float)fVar5 + 90.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xe8) = (float)fVar5 + 95.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xec) = (float)fVar5 + 100.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xf0) = (float)fVar5 + 190.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xf4) = (float)fVar5 + 195.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xf8) = (float)fVar5 + 200.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xfc) = (float)fVar5 + 60.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x100) = (float)fVar5 + 75.0;
    *(undefined1 *)(param_1 + 0x76) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x108);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x77) == '\0')) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 300),1000);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 300),1000);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 300),1000);
    *(undefined1 *)(param_1 + 0x77) = 1;
  }
  if (((*(char *)(param_1 + 0x93) == '\0') && (*(char *)(param_1 + 0x5e) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x108), cVar1 == '\0')) {
    FUN_005cb2d0(&DAT_0087b758,2);
    uVar2 = FUN_005c8080("avscav",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined4 *)(param_1 + 0x180) = uVar2;
    uVar2 = FUN_005c8080("avscav",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined4 *)(param_1 + 0x184) = uVar2;
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x128));
    FUN_005c95e0(*(undefined4 *)(param_1 + 300));
    *(undefined1 *)(param_1 + 0x93) = 1;
    FUN_00437d30("misns105.wav");
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xd8) = (float)fVar5 + 25.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xdc) = (float)fVar5 + 35.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xe0) = (float)fVar5 + 40.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xe4) = (float)fVar5 + 90.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xe8) = (float)fVar5 + 95.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xec) = (float)fVar5 + 100.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xf0) = (float)fVar5 + 190.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xf4) = (float)fVar5 + 195.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xf8) = (float)fVar5 + 200.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xfc) = (float)fVar5 + 60.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x100) = (float)fVar5 + 75.0;
    *(undefined1 *)(param_1 + 0x76) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xd8) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xd8)) &&
      (*(char *)(param_1 + 0x88) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0'))
  {
    FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x88) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xdc) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xdc)) &&
      (*(char *)(param_1 + 0x89) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0'))
  {
    FUN_005c8080("avfigh",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x89) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xe0) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xe0)) &&
      (*(char *)(param_1 + 0x8a) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0'))
  {
    FUN_005c8080("avfigh",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x8a) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xe4) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xe4)) &&
      (*(char *)(param_1 + 0x8b) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0'))
  {
    FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x8b) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xe8) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xe8)) &&
      (*(char *)(param_1 + 0x8c) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0'))
  {
    FUN_005c8080("avfigh",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x8c) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xec) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xec)) &&
      (*(char *)(param_1 + 0x8d) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0'))
  {
    FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x8d) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if ((((*(float *)(param_1 + 0xf0) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xf0))
       && (*(char *)(param_1 + 0x8e) == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x128), cVar1 != '\0')) {
    FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x8e) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xf4) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xf4)) &&
      (*(char *)(param_1 + 0x8f) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0' &&
      (cVar1 = FUN_005c84d0(param_1 + 0x128), cVar1 != '\0')))) {
    FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x8f) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xf8) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xf8)) &&
      (*(char *)(param_1 + 0x90) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 300), cVar1 != '\0' &&
      (cVar1 = FUN_005c84d0(param_1 + 0x128), cVar1 != '\0')))) {
    FUN_005c8080("avfigh",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x90) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0xfc) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xfc)) &&
     (*(char *)(param_1 + 0x91) == '\0')) {
    FUN_005c8080("avturr",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x91) = 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x100) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x100))
     && (*(char *)(param_1 + 0x92) == '\0')) {
    FUN_005c8080("avturr",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined1 *)(param_1 + 0x92) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x108);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x56) == '\0')) {
    *(undefined1 *)(param_1 + 0x56) = 1;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar5 + 180.0;
  }
  cVar1 = FUN_005c84d0(param_1 + 300);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x58) == '\0')) {
    FUN_00437d30("misns108.wav");
    *(undefined1 *)(param_1 + 0x58) = 1;
    *(undefined1 *)(param_1 + 0x74) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x128);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x57) == '\0')) {
    *(undefined1 *)(param_1 + 0x75) = 1;
    FUN_00437d30("misns107.wav");
    *(undefined1 *)(param_1 + 0x57) = 1;
  }
  if ((*(char *)(param_1 + 0x74) == '\x01') && (*(char *)(param_1 + 0x75) == '\x01')) {
    *(undefined1 *)(param_1 + 0x76) = 1;
  }
  if ((((*(char *)(param_1 + 0x58) == '\x01') && (*(char *)(param_1 + 0x57) == '\x01')) &&
      (*(char *)(param_1 + 0x56) == '\x01')) && (*(char *)(param_1 + 0x5b) == '\0')) {
    *(undefined1 *)(param_1 + 0x76) = 1;
    *(undefined1 *)(param_1 + 0x5b) = 1;
  }
  if ((*(char *)(param_1 + 0x5b) == '\x01') && (*(char *)(param_1 + 0x6c) == '\0')) {
    uVar2 = FUN_00437d30("misns110.wav");
    *(undefined4 *)(param_1 + 0x1d8) = uVar2;
    *(undefined1 *)(param_1 + 0x6c) = 1;
  }
  if ((*(char *)(param_1 + 0x6c) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1d8)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("misns1w1.des");
    FUN_0045c110((float)fVar5);
  }
  if ((*(char *)(param_1 + 0x5c) == '\0') &&
     (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x108),
                                    *(undefined4 *)(param_1 + 0x150)), (float)fVar5 < 70.0)) {
    if (*(int *)(param_1 + 0x1c0) == 0) {
      FUN_00437d30("misns117.wav");
      *(undefined1 *)(param_1 + 0x5c) = 1;
    }
    if (*(int *)(param_1 + 0x1c0) == 1) {
      FUN_00437d30("misns116.wav");
      *(undefined1 *)(param_1 + 0x5c) = 1;
    }
    if (*(int *)(param_1 + 0x1c0) == 2) {
      FUN_00437d30("misns115.wav");
      *(undefined1 *)(param_1 + 0x5c) = 1;
    }
  }
  fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x108),"halfwayupper",0);
  if (((float)fVar5 < 100.0) && (*(char *)(param_1 + 0x55) == '\0')) {
    *(undefined1 *)(param_1 + 0x55) = 1;
    FUN_00437d30("misns102.wav");
  }
  fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x108),"halfwaymid",0);
  if (((float)fVar5 < 100.0) && (*(char *)(param_1 + 0x55) == '\0')) {
    *(undefined1 *)(param_1 + 0x55) = 1;
    FUN_00437d30("misns103.wav");
  }
  fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x108),"halfwaylower",0);
  if (((float)fVar5 < 100.0) && (*(char *)(param_1 + 0x55) == '\0')) {
    *(undefined1 *)(param_1 + 0x55) = 1;
    FUN_00437d30("misns104.wav");
  }
  if (((*(char *)(param_1 + 0x87) == '\x01') &&
      (fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x108),"safepoint",0),
      (float)fVar5 < 60.0)) && (*(char *)(param_1 + 0x73) == '\0')) {
    uVar2 = FUN_00437d30("misns109.wav");
    *(undefined4 *)(param_1 + 0x1c8) = uVar2;
    uVar2 = FUN_00437d30("misns111.wav");
    *(undefined4 *)(param_1 + 0x1cc) = uVar2;
    *(undefined1 *)(param_1 + 0x73) = 1;
    *(undefined1 *)(param_1 + 0x76) = 1;
    FUN_005cd2a0();
    FUN_005cd440(*(undefined4 *)(param_1 + 0x13c),0x4b0,500,0x4b0,*(undefined4 *)(param_1 + 0x108));
  }
  if (((*(char *)(param_1 + 0x73) == '\x01') &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1c8)), cVar1 != '\0')) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1cc)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("misns1l1.des");
    FUN_0045c0f0((float)fVar5);
  }
  cVar1 = FUN_005c84d0(param_1 + 0x130);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x5f) == '\0')) {
    uVar2 = FUN_00437d30("misns112.wav");
    *(undefined4 *)(param_1 + 0x1d0) = uVar2;
    uVar2 = FUN_00437d30("misns113.wav");
    *(undefined4 *)(param_1 + 0x1d4) = uVar2;
    *(undefined1 *)(param_1 + 0x5f) = 1;
    *(undefined1 *)(param_1 + 0x76) = 1;
  }
  if (((*(char *)(param_1 + 0x5f) == '\x01') &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1d0)), cVar1 != '\0')) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1d4)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("misns1l2.des");
    FUN_0045c0f0((float)fVar5);
  }
  fVar5 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x9c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x9c)) &&
     (*(char *)(param_1 + 0x6d) == '\0')) {
    *(undefined4 *)(param_1 + 0x9c) = 0x51ba43b7;
    *(undefined1 *)(param_1 + 0x6d) = 1;
    uVar2 = FUN_005c8250("avfigh",2,"cavspawn",0,0);
    *(undefined4 *)(param_1 + 0x16c) = uVar2;
    uVar2 = FUN_005c8250("avtank",2,"cavspawn",0,0);
    *(undefined4 *)(param_1 + 0x170) = uVar2;
    uVar2 = FUN_005c8250("avfigh",2,"cavspawn",0,0);
    *(undefined4 *)(param_1 + 0x174) = uVar2;
    FUN_00437d30("misns122.wav");
  }
  if ((*(char *)(param_1 + 0x6d) == '\x01') && (*(char *)(param_1 + 0x6e) == '\0')) {
    switch(*(undefined4 *)(param_1 + 0x1c4)) {
    case 0:
      FUN_005cb960(*(undefined4 *)(param_1 + 0x16c),"cavpath1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x170),"cavpath1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x174),"cavpath1",1);
      *(undefined1 *)(param_1 + 0x6f) = 1;
      break;
    case 1:
      FUN_005cb960(*(undefined4 *)(param_1 + 0x16c),"cavpath2",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x170),"cavpath2",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x174),"cavpath2",1);
      *(undefined1 *)(param_1 + 0x70) = 1;
      break;
    case 2:
      FUN_005cb960(*(undefined4 *)(param_1 + 0x16c),"cavpath1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x170),"cavpath1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x174),"cavpath1",1);
      *(undefined1 *)(param_1 + 0x6f) = 1;
      break;
    case 3:
      FUN_005cb960(*(undefined4 *)(param_1 + 0x16c),"cavpath2",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x170),"cavpath2",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x174),"cavpath2",1);
      *(undefined1 *)(param_1 + 0x70) = 1;
    }
    *(undefined1 *)(param_1 + 0x6e) = 1;
  }
  if ((*(char *)(param_1 + 0x6f) == '\x01') &&
     ((((fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                       *(undefined4 *)(param_1 + 0x150)), (float)fVar5 < 200.0 ||
        (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x170),
                                       *(undefined4 *)(param_1 + 0x150)), (float)fVar5 < 200.0)) ||
       (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x174),
                                      *(undefined4 *)(param_1 + 0x150)), (float)fVar5 < 200.0)) &&
      (*(char *)(param_1 + 100) == '\0')))) {
    FUN_00437d30("misns118.wav");
    *(undefined1 *)(param_1 + 100) = 1;
  }
  if ((*(char *)(param_1 + 0x70) == '\x01') &&
     ((((fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                       *(undefined4 *)(param_1 + 0x154)), (float)fVar5 < 50.0 ||
        (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x170),
                                       *(undefined4 *)(param_1 + 0x154)), (float)fVar5 < 50.0)) ||
       (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x174),
                                      *(undefined4 *)(param_1 + 0x154)), (float)fVar5 < 50.0)) &&
      (*(char *)(param_1 + 0x66) == '\0')))) {
    FUN_00437d30("misns119.wav");
    *(undefined1 *)(param_1 + 0x66) = 1;
  }
  return;
}

