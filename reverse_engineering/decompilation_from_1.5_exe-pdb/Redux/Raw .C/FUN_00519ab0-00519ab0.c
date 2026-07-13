
void __fastcall FUN_00519ab0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  float10 fVar4;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x144) = uVar2;
  if (*(char *)(param_1 + 0x54) == '\0') {
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar4 + 30.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb0) = (float)fVar4 + 240.0;
    FUN_00437d30("misn0401.wav");
    uVar2 = FUN_005c7e90("apcamr352_camerapod");
    *(undefined4 *)(param_1 + 0x158) = uVar2;
    uVar2 = FUN_005c7e90("apcamr350_camerapod");
    *(undefined4 *)(param_1 + 0x15c) = uVar2;
    uVar2 = FUN_005c7e90("apcamr351_camerapod");
    *(undefined4 *)(param_1 + 0x160) = uVar2;
    uVar2 = FUN_005c7e90("apcamr-1_camerapod");
    *(undefined4 *)(param_1 + 0x164) = uVar2;
    uVar2 = FUN_005c7e90("svrecy-1_recycler");
    *(undefined4 *)(param_1 + 0xe4) = uVar2;
    uVar2 = FUN_005c7e90("avrecy-1_recycler");
    *(undefined4 *)(param_1 + 0x16c) = uVar2;
    uVar2 = FUN_005c8250("obdata",0,"relicstart1",0,0);
    *(undefined4 *)(param_1 + 0x1d0) = uVar2;
    uVar2 = FUN_005c7e90("svfigh-1_wingman");
    *(undefined4 *)(param_1 + 0xe8) = uVar2;
    uVar2 = FUN_005c7e90("svfigh282_wingman");
    *(undefined4 *)(param_1 + 0xf0) = uVar2;
    uVar2 = FUN_005c7e90("svfigh279_wingman");
    *(undefined4 *)(param_1 + 0xfc) = uVar2;
    uVar2 = FUN_005c7e90("svfigh278_wingman");
    *(undefined4 *)(param_1 + 0x104) = uVar2;
    FUN_005c9640(*(undefined4 *)(param_1 + 0x158),"SW Geyser");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x15c),"NW Geyser");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x160),"NE Geyser");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x164),"CCA Base");
    FUN_005cc0c0(*(undefined4 *)(param_1 + 0xe8),"innerpatrol",1);
    FUN_005cc0c0(*(undefined4 *)(param_1 + 0xf0),"innerpatrol",1);
    FUN_005cc0c0(*(undefined4 *)(param_1 + 0xfc),"outerpatrol",1);
    FUN_005cc0c0(*(undefined4 *)(param_1 + 0x104),"scouting",1);
    FUN_004f6ab0("misn0401.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("misn0400.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x54) = 1;
    *(undefined1 *)(param_1 + 0x89) = 0;
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000003;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
    }
    *(uint *)(param_1 + 0x1f0) = uVar3;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xcc) = (float)fVar4 + 30.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xd0) = (float)fVar4 + 45.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xd4) = (float)fVar4 + 60.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xd8) = (float)fVar4 + 75.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xdc) = (float)fVar4 + 3.0;
  }
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x144) = uVar2;
  cVar1 = FUN_005c84d0(param_1 + 0x158);
  if (cVar1 != '\0') {
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0x158),0x42c80000);
  }
  cVar1 = FUN_005c84d0(param_1 + 0x15c);
  if (cVar1 != '\0') {
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0x15c),0x42c80000);
  }
  cVar1 = FUN_005c84d0(param_1 + 0x160);
  if (cVar1 != '\0') {
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0x160),0x42c80000);
  }
  if (*(char *)(param_1 + 0x88) == '\0') {
    switch(*(undefined4 *)(param_1 + 0x1f0)) {
    case 0:
      FUN_005c8cb0(*(undefined4 *)(param_1 + 0x1d0),"relicstart1",0);
      break;
    case 1:
      FUN_005c8cb0(*(undefined4 *)(param_1 + 0x1d0),"relicstart2",0);
      break;
    case 2:
      FUN_005c8cb0(*(undefined4 *)(param_1 + 0x1d0),"relicstart3",0);
      break;
    case 3:
      FUN_005c8cb0(*(undefined4 *)(param_1 + 0x1d0),"relicstart4",0);
    }
    *(undefined1 *)(param_1 + 0x88) = 1;
  }
  if (((*(char *)(param_1 + 0x78) == '\0') && (*(char *)(param_1 + 0x89) == '\0')) &&
     (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x144),
                                    *(undefined4 *)(param_1 + 0x1d0)), (float)fVar4 < 600.0)) {
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x1d0),0);
    *(undefined4 *)(param_1 + 0x10c) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x1d0),0);
    *(undefined4 *)(param_1 + 0x110) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x1d0),0);
    *(undefined4 *)(param_1 + 0x114) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x1d0),0);
    *(undefined4 *)(param_1 + 0x118) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x1d0),0);
    *(undefined4 *)(param_1 + 0x11c) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x1d0),0);
    *(undefined4 *)(param_1 + 0x120) = uVar2;
    if (*(int *)(param_1 + 0x1f0) == 0) {
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x10c),"relicpatrolpath1a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x110),"relicpatrolpath1a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x114),"relicpatrolpath1a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x118),"relicpatrolpath1b",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x11c),"relicpatrolpath1b",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x120),"relicpatrolpath1b",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x110),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x114),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x118),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x11c),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x120),1);
    }
    if (*(int *)(param_1 + 0x1f0) == 1) {
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x10c),"relicpatrolpath2a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x110),"relicpatrolpath2a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x114),"relicpatrolpath2a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x118),"relicpatrolpath2b",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x11c),"relicpatrolpath2b",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x120),"relicpatrolpath2b",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x110),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x114),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x118),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x11c),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x120),1);
    }
    if (*(int *)(param_1 + 0x1f0) == 2) {
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x10c),"relicpatrolpath3a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x110),"relicpatrolpath3a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x114),"relicpatrolpath3a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x118),"relicpatrolpath3b",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x11c),"relicpatrolpath3b",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x120),"relicpatrolpath3b",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x110),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x114),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x118),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x11c),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x120),1);
    }
    if (*(int *)(param_1 + 0x1f0) == 3) {
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x10c),"relicpatrolpath4a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x110),"relicpatrolpath4a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x114),"relicpatrolpath4a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x118),"relicpatrolpath4b",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x11c),"relicpatrolpath4b",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x120),"relicpatrolpath4b",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x110),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x114),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x118),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x11c),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x120),1);
    }
    *(undefined1 *)(param_1 + 0x77) = 1;
    *(undefined1 *)(param_1 + 0x89) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb4) = (float)fVar4;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0xb0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb0)) &&
     (*(char *)(param_1 + 0x77) == '\0')) {
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x1d0),0);
    *(undefined4 *)(param_1 + 0x148) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0x1d0),0);
    *(undefined4 *)(param_1 + 0x14c) = uVar2;
    if (*(int *)(param_1 + 0x1f0) == 0) {
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x148),"relicpatrolpath1a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x14c),"relicpatrolpath1b",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x148),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x14c),1);
    }
    if (*(int *)(param_1 + 0x1f0) == 1) {
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x148),"relicpatrolpath2a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x14c),"relicpatrolpath2b",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x148),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x14c),1);
    }
    if (*(int *)(param_1 + 0x1f0) == 2) {
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x148),"relicpatrolpath3a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x14c),"relicpatrolpath3b",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x148),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x14c),1);
    }
    if (*(int *)(param_1 + 0x1f0) == 3) {
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x148),"relicpatrolpath4a",1);
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0x14c),"relicpatrolpath4b",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x148),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x14c),1);
    }
    *(undefined1 *)(param_1 + 0x77) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb4) = (float)fVar4 + 60.0;
  }
  if (((*(char *)(param_1 + 0x94) == '\0') &&
      (fVar4 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0xcc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xcc))) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svturr",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x1d8) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x1d8),"turret1",1);
    *(undefined1 *)(param_1 + 0x94) = 1;
  }
  if (((*(char *)(param_1 + 0x95) == '\0') &&
      (fVar4 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0xd0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd0))) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svturr",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x1dc) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x1dc),"turret2",1);
    *(undefined1 *)(param_1 + 0x95) = 1;
  }
  if (((*(char *)(param_1 + 0x96) == '\0') &&
      (fVar4 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0xd4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd4))) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svturr",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x1e0) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x1e0),"turret3",1);
    *(undefined1 *)(param_1 + 0x96) = 1;
  }
  if (((*(char *)(param_1 + 0x97) == '\0') &&
      (fVar4 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0xd8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd8))) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svturr",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x1e4) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x1e4),"turret4",1);
    *(undefined1 *)(param_1 + 0x97) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xb4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb4)) &&
      (*(char *)(param_1 + 0x78) == '\0')) && (*(char *)(param_1 + 0x77) == '\x01')) {
    uVar2 = FUN_00437d30("misn0406.wav");
    *(undefined4 *)(param_1 + 0x20c) = uVar2;
    switch(*(undefined4 *)(param_1 + 0x1f0)) {
    case 0:
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"reliccam1",0,0);
      *(undefined4 *)(param_1 + 0x168) = uVar2;
      break;
    case 1:
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"reliccam2",0,0);
      *(undefined4 *)(param_1 + 0x168) = uVar2;
      break;
    case 2:
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"reliccam3",0,0);
      *(undefined4 *)(param_1 + 0x168) = uVar2;
      break;
    case 3:
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"reliccam4",0,0);
      *(undefined4 *)(param_1 + 0x168) = uVar2;
    }
    *(undefined1 *)(param_1 + 0x78) = 1;
    *(undefined1 *)(param_1 + 0x85) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xc0) = (float)fVar4 + 90.0;
  }
  if ((*(char *)(param_1 + 0x85) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x20c)), cVar1 != '\0')) {
    FUN_005c9640(*(undefined4 *)(param_1 + 0x168),"Investigate CCA");
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined1 *)(param_1 + 0x85) = 0;
  }
  if (((*(char *)(param_1 + 0x62) == '\x01') && (*(char *)(param_1 + 0x7d) == '\0')) &&
     (cVar1 = FUN_005cd1d0(*(undefined4 *)(param_1 + 0x134)), cVar1 != '\0')) {
    FUN_00437d30("misn0419.wav");
    *(undefined1 *)(param_1 + 0x7d) = 1;
    FUN_005c9610(*(undefined4 *)(param_1 + 0x1d0));
    cVar1 = FUN_005c84d0(param_1 + 0x13c);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x134),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x140);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x140),*(undefined4 *)(param_1 + 0x134),1);
    }
  }
  if (((*(char *)(param_1 + 0x78) == '\x01') &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1d0),
                                     *(undefined4 *)(param_1 + 0x16c)), (float)fVar4 < 100.0)) &&
     (*(char *)(param_1 + 0x56) == '\0')) {
    uVar2 = FUN_00437d30("misn0420.wav");
    *(undefined4 *)(param_1 + 0x230) = uVar2;
    *(undefined1 *)(param_1 + 0x56) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0xc4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xc4)) &&
      (*(char *)(param_1 + 0x7e) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0'))
  {
    uVar2 = FUN_005c8080("svhaul",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x138) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x13c) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x140) = uVar2;
    FUN_005cc280(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x1d0),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x138),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x140),*(undefined4 *)(param_1 + 0x138),1);
    *(undefined1 *)(param_1 + 0x7e) = 1;
  }
  if (((*(char *)(param_1 + 0x7e) == '\x01') && (*(char *)(param_1 + 99) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x138), cVar1 != '\0' &&
      ((cVar1 = FUN_005cd1d0(*(undefined4 *)(param_1 + 0x138)), cVar1 != '\0' &&
       (cVar1 = FUN_005cd1d0(*(undefined4 *)(param_1 + 0x134)), cVar1 == '\0')))))) {
    *(undefined1 *)(param_1 + 99) = 1;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x138),"dropoff",1);
    FUN_00437d30("misn0427.wav");
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x138));
    FUN_005c9640(*(undefined4 *)(param_1 + 0x138),"CCA Tug");
  }
  if (((*(char *)(param_1 + 99) == '\x01') &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x138),
                                     *(undefined4 *)(param_1 + 0xe4)), (float)fVar4 < 60.0)) &&
     (*(char *)(param_1 + 0x5f) == '\0')) {
    uVar2 = FUN_00437d30("misn0431.wav");
    *(undefined4 *)(param_1 + 0x210) = uVar2;
    uVar2 = FUN_00437d30("misn0432.wav");
    *(undefined4 *)(param_1 + 0x214) = uVar2;
    uVar2 = FUN_00437d30("misn0433.wav");
    *(undefined4 *)(param_1 + 0x218) = uVar2;
    uVar2 = FUN_00437d30("misn0434.wav");
    *(undefined4 *)(param_1 + 0x21c) = uVar2;
    *(undefined1 *)(param_1 + 0x5f) = 1;
    FUN_005cd2a0();
  }
  if ((*(char *)(param_1 + 0x5f) == '\x01') && (*(char *)(param_1 + 0x60) == '\0')) {
    FUN_005cd300("ccareliccam",3000,1000,*(undefined4 *)(param_1 + 0x138));
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x210));
    if ((((cVar1 != '\0') &&
         ((cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x214)), cVar1 != '\0' &&
          (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x218)), cVar1 != '\0')))) &&
        (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x21c)), cVar1 != '\0')) ||
       (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
      FUN_005cd4e0();
      FUN_00437d80(*(undefined4 *)(param_1 + 0x210));
      FUN_00437d80(*(undefined4 *)(param_1 + 0x214));
      FUN_00437d80(*(undefined4 *)(param_1 + 0x218));
      FUN_00437d80(*(undefined4 *)(param_1 + 0x21c));
      fVar4 = (float10)FUN_004b1670("misn04l1.des");
      FUN_0045c0f0((float)fVar4);
      *(undefined1 *)(param_1 + 0x60) = 1;
    }
  }
  if ((((*(char *)(param_1 + 0x86) == '\0') && (*(char *)(param_1 + 0x78) == '\x01')) &&
      (fVar4 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0xc0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xc0))) &&
     ((*(char *)(param_1 + 99) == '\0' && (*(int *)(param_1 + 0x1fc) < 4)))) {
    FUN_00437d30("misn0429.wav");
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xc0) = (float)fVar4 + 85.0;
    *(int *)(param_1 + 0x1fc) = *(int *)(param_1 + 0x1fc) + 1;
  }
  if (((*(int *)(param_1 + 0x1fc) == 4) &&
      (fVar4 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0xc0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xc0))) &&
     (*(char *)(param_1 + 0x8d) == '\0')) {
    uVar2 = FUN_00437d30("misn0694.wav");
    *(undefined4 *)(param_1 + 0x220) = uVar2;
    *(undefined1 *)(param_1 + 0x8d) = 1;
  }
  if (((*(char *)(param_1 + 0x8d) == '\x01') && (*(int *)(param_1 + 0x1fc) == 4)) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x220)), cVar1 != '\0')) {
    fVar4 = (float10)FUN_004b1670("misn04l4.des");
    FUN_0045c0f0((float)fVar4);
    *(undefined4 *)(param_1 + 0x1fc) = 0;
  }
  if (*(char *)(param_1 + 0x86) == '\0') {
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0xdc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xdc)) {
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x1d0),0x43c80000,1,0);
      *(undefined4 *)(param_1 + 0x1f8) = uVar2;
      cVar1 = FUN_005c84d0(param_1 + 0x168);
      if (cVar1 != '\0') {
        *(int *)(param_1 + 0x1f8) = *(int *)(param_1 + 0x1f8) + -1;
      }
    }
    if (0 < *(int *)(param_1 + 0x1f8)) {
      uVar2 = FUN_00437d30("misn0408.wav");
      *(undefined4 *)(param_1 + 0x204) = uVar2;
      uVar2 = FUN_00437d30("misn0409.wav");
      *(undefined4 *)(param_1 + 0x208) = uVar2;
      *(undefined1 *)(param_1 + 0x8a) = 1;
      *(undefined1 *)(param_1 + 0x87) = 1;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0xc4) = (float)fVar4 + 200.0;
      *(undefined1 *)(param_1 + 0x86) = 1;
      FUN_005cd2a0();
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 200) = (float)fVar4 + 23.0;
    }
  }
  if (((*(char *)(param_1 + 0x86) == '\x01') && (*(char *)(param_1 + 0x7f) == '\0')) &&
     (((*(char *)(param_1 + 0x86) == '\x01' &&
       ((cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x204)), cVar1 != '\0' &&
        (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x208)), cVar1 != '\0')))) ||
      (cVar1 = FUN_005cd560(), cVar1 != '\0')))) {
    FUN_005cd4e0();
    FUN_00437d80(*(undefined4 *)(param_1 + 0x204));
    FUN_00437d80(*(undefined4 *)(param_1 + 0x208));
    *(undefined1 *)(param_1 + 0x7f) = 1;
  }
  if (((*(char *)(param_1 + 0x86) == '\x01') &&
      (fVar4 = (float10)FUN_004b1670(), (float)fVar4 < *(float *)(param_1 + 200))) &&
     (*(char *)(param_1 + 0x7f) == '\0')) {
    if (*(int *)(param_1 + 0x1f0) == 0) {
      FUN_005cd300("reliccin1",500,400,*(undefined4 *)(param_1 + 0x1d0));
    }
    if (*(int *)(param_1 + 0x1f0) == 1) {
      FUN_005cd300("reliccin2",500,400,*(undefined4 *)(param_1 + 0x1d0));
    }
    if (*(int *)(param_1 + 0x1f0) == 2) {
      FUN_005cd300("reliccin3",500,400,*(undefined4 *)(param_1 + 0x1d0));
    }
    if (*(int *)(param_1 + 0x1f0) == 3) {
      FUN_005cd300("reliccin4",500,400,*(undefined4 *)(param_1 + 0x1d0));
    }
  }
  if (*(char *)(param_1 + 0x87) == '\x01') {
    FUN_004f6aa0();
    if (*(char *)(param_1 + 0x55) == '\0') {
      FUN_004f6ab0("misn0401.otf",DAT_0091755c,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x55) == '\x01') {
      FUN_004f6ab0("misn0401.otf",DAT_009175b0,0x41000000,0);
    }
    if ((*(char *)(param_1 + 0x56) == '\0') && (*(char *)(param_1 + 0x8a) == '\x01')) {
      FUN_004f6ab0("misn0403.otf",DAT_0091755c,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x56) == '\x01') {
      FUN_004f6ab0("misn0403.otf",DAT_009175b0,0x41000000,0);
    }
    if ((*(char *)(param_1 + 0x78) == '\x01') && (*(char *)(param_1 + 0x86) == '\0')) {
      FUN_004f6ab0("misn0405.otf",DAT_0091755c,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x86) == '\x01') {
      FUN_004f6ab0("misn0405.otf",DAT_009175b0,0x41000000,0);
    }
    *(undefined1 *)(param_1 + 0x87) = 0;
  }
  if (*(int *)(param_1 + 500) == 1) {
    FUN_005c84d0(param_1 + 0x170);
    FUN_005c84d0(param_1 + 0x174);
  }
  if ((*(int *)(param_1 + 500) == 1) &&
     (fVar4 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x9c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x9c))) {
    uVar2 = FUN_005c8250("svfigh",2,"wave1",0,0);
    *(undefined4 *)(param_1 + 0x170) = uVar2;
    uVar2 = FUN_005c8250("svfigh",2,"wave1",0,0);
    *(undefined4 *)(param_1 + 0x174) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0x170),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x170),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x174),1);
    *(undefined4 *)(param_1 + 500) = 2;
    *(undefined1 *)(param_1 + 0x80) = 0;
  }
  if (*(int *)(param_1 + 500) == 2) {
    FUN_005c84d0(param_1 + 0x170);
    FUN_005c84d0(param_1 + 0x174);
  }
  if ((((*(int *)(param_1 + 500) == 2) && (cVar1 = FUN_005c84d0(param_1 + 0x170), cVar1 == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x174), cVar1 == '\0')) && (*(char *)(param_1 + 100) == '\0'))
  {
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa0) = (float)fVar4 + 60.0;
    *(undefined1 *)(param_1 + 100) = 1;
    *(undefined1 *)(param_1 + 0x8e) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0xa0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa0)) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')) {
    uVar2 = FUN_005c8250("svtank",2,"spawn2new",0,0);
    *(undefined4 *)(param_1 + 0x17c) = uVar2;
    uVar2 = FUN_005c8250("svfigh",2,"spawn2new",0,0);
    *(undefined4 *)(param_1 + 0x180) = uVar2;
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x17c),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x180),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x17c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x180),1);
    *(undefined4 *)(param_1 + 500) = 3;
    *(undefined1 *)(param_1 + 0x81) = 0;
    *(undefined4 *)(param_1 + 0xa0) = 0x47c34f80;
  }
  if (*(int *)(param_1 + 500) == 3) {
    FUN_005c84d0(param_1 + 0x17c);
    FUN_005c84d0(param_1 + 0x180);
  }
  if (((*(int *)(param_1 + 500) == 3) && (cVar1 = FUN_005c84d0(param_1 + 0x17c), cVar1 == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x180), cVar1 == '\0' && (*(char *)(param_1 + 0x65) == '\0')))
     ) {
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa4) = (float)fVar4 + 74.0;
    *(undefined1 *)(param_1 + 0x65) = 1;
    *(undefined1 *)(param_1 + 0x8f) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0xa4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa4)) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x188) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x18c) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 400) = uVar2;
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x188),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x18c),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 400),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x188),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x18c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 400),1);
    *(undefined4 *)(param_1 + 500) = 4;
    *(undefined1 *)(param_1 + 0x82) = 0;
    *(undefined4 *)(param_1 + 0xa4) = 0x47c34f80;
  }
  if (*(int *)(param_1 + 500) == 4) {
    FUN_005c84d0(param_1 + 0x188);
    FUN_005c84d0(param_1 + 0x18c);
    FUN_005c84d0(param_1 + 400);
  }
  if ((((*(int *)(param_1 + 500) == 4) && (cVar1 = FUN_005c84d0(param_1 + 0x188), cVar1 == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x18c), cVar1 == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 400), cVar1 == '\0' && (*(char *)(param_1 + 0x66) == '\0'))))
  {
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa8) = (float)fVar4 + 60.0;
    *(undefined1 *)(param_1 + 0x66) = 1;
    *(undefined1 *)(param_1 + 0x90) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0xa8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa8)) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')) {
    uVar2 = FUN_005c8250("svtank",2,"spawnotherside",0,0);
    *(undefined4 *)(param_1 + 0x198) = uVar2;
    uVar2 = FUN_005c8250("svfigh",2,"spawnotherside",0,0);
    *(undefined4 *)(param_1 + 0x19c) = uVar2;
    uVar2 = FUN_005c8250("svfigh",2,"spawnotherside",0,0);
    *(undefined4 *)(param_1 + 0x1a0) = uVar2;
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x19c),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1a0),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x198),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x19c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1a0),1);
    *(undefined4 *)(param_1 + 500) = 5;
    *(undefined1 *)(param_1 + 0x83) = 0;
    *(undefined4 *)(param_1 + 0xa8) = 0x47c34f80;
  }
  if (*(int *)(param_1 + 500) == 5) {
    FUN_005c84d0(param_1 + 0x198);
    FUN_005c84d0(param_1 + 0x19c);
    FUN_005c84d0(param_1 + 0x1a0);
  }
  if ((((*(int *)(param_1 + 500) == 5) && (cVar1 = FUN_005c84d0(param_1 + 0x198), cVar1 == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x19c), cVar1 == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x1a0), cVar1 == '\0' && (*(char *)(param_1 + 0x67) == '\0')))
     ) {
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xac) = (float)fVar4 + 30.0;
    *(undefined1 *)(param_1 + 0x67) = 1;
    *(undefined1 *)(param_1 + 0x91) = 1;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0xac) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xac)) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')) {
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x1ac) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x1b0) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x1b4) = uVar2;
    uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(param_1 + 0xe4),0);
    *(undefined4 *)(param_1 + 0x1b8) = uVar2;
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1ac),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1b0),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1b4),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1ac),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1b0),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1b4),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1b8),1);
    *(undefined4 *)(param_1 + 500) = 6;
    *(undefined1 *)(param_1 + 0x84) = 0;
    *(undefined4 *)(param_1 + 0xac) = 0x47c34f80;
  }
  if (((*(char *)(param_1 + 0x80) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')
      ) && ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                           *(undefined4 *)(param_1 + 0x170)), (float)fVar4 < 300.0
            || (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                              *(undefined4 *)(param_1 + 0x174)),
               (float)fVar4 < 300.0)))) {
    FUN_00437d30("misn0402.wav");
    *(undefined1 *)(param_1 + 0x80) = 1;
    *(undefined1 *)(param_1 + 0x8e) = 1;
  }
  if (((*(char *)(param_1 + 0x81) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')
      ) && ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                           *(undefined4 *)(param_1 + 0x17c)), (float)fVar4 < 300.0
            || (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                              *(undefined4 *)(param_1 + 0x180)),
               (float)fVar4 < 300.0)))) {
    FUN_00437d30("misn0404.wav");
    *(undefined1 *)(param_1 + 0x81) = 1;
  }
  if (((*(char *)(param_1 + 0x82) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')
      ) && ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                           *(undefined4 *)(param_1 + 0x188)), (float)fVar4 < 300.0
            || ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                               *(undefined4 *)(param_1 + 0x18c)),
                (float)fVar4 < 300.0 ||
                (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                               *(undefined4 *)(param_1 + 400)), (float)fVar4 < 300.0
                )))))) {
    FUN_00437d30("misn0410.wav");
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  if (((*(char *)(param_1 + 0x83) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')
      ) && ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                           *(undefined4 *)(param_1 + 0x198)), (float)fVar4 < 300.0
            || ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                               *(undefined4 *)(param_1 + 0x19c)),
                (float)fVar4 < 300.0 ||
                (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                               *(undefined4 *)(param_1 + 0x1a0)),
                (float)fVar4 < 300.0)))))) {
    FUN_00437d30("misn0412.wav");
    *(undefined1 *)(param_1 + 0x83) = 1;
  }
  if (((*(char *)(param_1 + 0x84) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')
      ) && ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                           *(undefined4 *)(param_1 + 0x1ac)), (float)fVar4 < 300.0
            || (((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                                *(undefined4 *)(param_1 + 0x1b0)),
                 (float)fVar4 < 300.0 ||
                 (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                                *(undefined4 *)(param_1 + 0x1b4)),
                 (float)fVar4 < 300.0)) ||
                (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                               *(undefined4 *)(param_1 + 0x1b8)),
                (float)fVar4 < 300.0)))))) {
    FUN_00437d30("misn0414.wav");
    *(undefined1 *)(param_1 + 0x84) = 1;
  }
  if ((*(char *)(param_1 + 0x73) == '\0') &&
     (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0xe4)
                                   ), (float)fVar4 < 300.0)) {
    FUN_00437d30("misn0423.wav");
    *(undefined1 *)(param_1 + 0x73) = 1;
  }
  if (((*(char *)(param_1 + 0x8e) == '\x01') &&
      (cVar1 = FUN_005c84d0(param_1 + 0x170), cVar1 == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x174), cVar1 == '\0')) {
    FUN_00437d30("misn0403.wav");
    *(undefined1 *)(param_1 + 0x8e) = 0;
  }
  if (*(char *)(param_1 + 0x8f) == '\x01') {
    FUN_00437d30("misn0405.wav");
    *(undefined1 *)(param_1 + 0x8f) = 0;
  }
  if (*(char *)(param_1 + 0x90) == '\x01') {
    FUN_00437d30("misn0411.wav");
    *(undefined1 *)(param_1 + 0x90) = 0;
  }
  if (*(char *)(param_1 + 0x91) == '\x01') {
    FUN_00437d30("misn0413.wav");
    *(undefined1 *)(param_1 + 0x91) = 0;
  }
  if ((((*(char *)(param_1 + 0x7b) == '\0') && (*(char *)(param_1 + 0x72) == '\0')) &&
      (*(char *)(param_1 + 0x8c) == '\0')) && (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 == '\0'))
  {
    FUN_00437d30("misn0417.wav");
    *(undefined1 *)(param_1 + 0x72) = 1;
    *(undefined1 *)(param_1 + 0x70) = 1;
    cVar1 = FUN_005c84d0(param_1 + 0xe4);
    if ((cVar1 == '\0') &&
       ((((((cVar1 = FUN_005c84d0(param_1 + 0x170), cVar1 != '\0' ||
            (cVar1 = FUN_005c84d0(param_1 + 0x174), cVar1 != '\0')) ||
           (((cVar1 = FUN_005c84d0(param_1 + 0x17c), cVar1 != '\0' ||
             ((cVar1 = FUN_005c84d0(param_1 + 0x180), cVar1 != '\0' ||
              (cVar1 = FUN_005c84d0(param_1 + 0x188), cVar1 != '\0')))) ||
            (cVar1 = FUN_005c84d0(param_1 + 0x18c), cVar1 != '\0')))) ||
          (((cVar1 = FUN_005c84d0(param_1 + 400), cVar1 != '\0' ||
            (cVar1 = FUN_005c84d0(param_1 + 0x198), cVar1 != '\0')) ||
           (cVar1 = FUN_005c84d0(param_1 + 0x19c), cVar1 != '\0')))) ||
         ((cVar1 = FUN_005c84d0(param_1 + 0x1a0), cVar1 != '\0' ||
          (cVar1 = FUN_005c84d0(param_1 + 0x1ac), cVar1 != '\0')))) ||
        ((cVar1 = FUN_005c84d0(param_1 + 0x1b0), cVar1 != '\0' ||
         ((cVar1 = FUN_005c84d0(param_1 + 0x1b4), cVar1 != '\0' ||
          (cVar1 = FUN_005c84d0(param_1 + 0x1b8), cVar1 != '\0')))))))) {
      FUN_00437d30("misn0418.wav");
      *(undefined1 *)(param_1 + 0x7b) = 1;
    }
  }
  if ((((((*(char *)(param_1 + 0x55) == '\0') &&
         (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 == '\0')) &&
        (cVar1 = FUN_005c84d0(param_1 + 0x170), cVar1 == '\0')) &&
       (((cVar1 = FUN_005c84d0(param_1 + 0x174), cVar1 == '\0' &&
         (cVar1 = FUN_005c84d0(param_1 + 0x17c), cVar1 == '\0')) &&
        ((cVar1 = FUN_005c84d0(param_1 + 0x180), cVar1 == '\0' &&
         ((cVar1 = FUN_005c84d0(param_1 + 0x188), cVar1 == '\0' &&
          (cVar1 = FUN_005c84d0(param_1 + 0x18c), cVar1 == '\0')))))))) &&
      (cVar1 = FUN_005c84d0(param_1 + 400), cVar1 == '\0')) &&
     ((((((cVar1 = FUN_005c84d0(param_1 + 0x198), cVar1 == '\0' &&
          (cVar1 = FUN_005c84d0(param_1 + 0x19c), cVar1 == '\0')) &&
         (cVar1 = FUN_005c84d0(param_1 + 0x1a0), cVar1 == '\0')) &&
        ((cVar1 = FUN_005c84d0(param_1 + 0x1ac), cVar1 == '\0' &&
         (cVar1 = FUN_005c84d0(param_1 + 0x1b0), cVar1 == '\0')))) &&
       (cVar1 = FUN_005c84d0(param_1 + 0x1b4), cVar1 == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x1b8), cVar1 == '\0')))) {
    *(undefined1 *)(param_1 + 0x55) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
  }
  if ((*(char *)(param_1 + 0x56) == '\x01') && (*(char *)(param_1 + 0x55) == '\x01')) {
    *(undefined1 *)(param_1 + 0x8c) = 1;
  }
  if ((((*(char *)(param_1 + 0x8c) == '\x01') && (*(char *)(param_1 + 0x74) == '\0')) &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x224)), cVar1 != '\0')) &&
     (((cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x228)), cVar1 != '\0' &&
       (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x22c)), cVar1 != '\0')) &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x230)), cVar1 != '\0')))) {
    fVar4 = (float10)FUN_004b1670("misn04w1.des");
    FUN_0045c110((float)fVar4);
  }
  if (((*(char *)(param_1 + 0x8c) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 == '\0')
      ) && (*(char *)(param_1 + 0x8d) == '\0')) {
    FUN_00437d30("misn0421.wav");
    FUN_00437d30("misn0422.wav");
    *(undefined1 *)(param_1 + 0x8d) = 1;
    fVar4 = (float10)FUN_004b1670("misn04l3.des");
    FUN_0045c0f0((float)fVar4 + 20.0);
  }
  if (((((*(char *)(param_1 + 0x55) == '\0') && (*(char *)(param_1 + 0x6f) == '\0')) &&
       (*(int *)(param_1 + 500) == 6)) &&
      ((cVar1 = FUN_005c84d0(param_1 + 0x1ac), cVar1 == '\0' &&
       (cVar1 = FUN_005c84d0(param_1 + 0x1b0), cVar1 == '\0')))) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x1b4), cVar1 == '\0' &&
      ((cVar1 = FUN_005c84d0(param_1 + 0x1b8), cVar1 == '\0' &&
       (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 != '\0')))))) {
    if (*(char *)(param_1 + 0x8b) == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x13c);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x13c),"retreatpoint",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x140);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x140),"retreatpoint28",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0xe8);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0xe8),"retreatpoint27",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0xec);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0xec),"retreatpoint26",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0xf0);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0xf0),"retreatpoint25",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0xf4);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0xf4),"retreatpoint24",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0xf8);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0xf8),"retreatpoint23",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0xfc);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0xfc),"retreatpoint22",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x100);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x100),"retreatpoint21",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x104);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x104),"retreatpoint20",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x10c);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x10c),"retreatpoint19",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x110);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x110),"retreatpoint18",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x114);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x114),"retreatpoint17",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x118);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x118),"retreatpoint16",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x11c);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x11c),"retreatpoint15",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x120);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x120),"retreatpoint14",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x124);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x124),"retreatpoint13",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x128);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x128),"retreatpoint12",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 300);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 300),"retreatpoint11",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x130);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x130),"retreatpoint10",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x148);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x148),"retreatpoint9",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x14c);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x14c),"retreatpoint8",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x150);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x150),"retreatpoint7",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x154);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x154),"retreatpoint6",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1d8);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x1d8),"retreatpoint2",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1dc);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x1dc),"retreatpoint3",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1e0);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x1e0),"retreatpoint4",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1e4);
      if (cVar1 != '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x1e4),"retreatpoint5",1);
      }
      *(undefined1 *)(param_1 + 0x8b) = 1;
    }
    uVar2 = FUN_00437d30("misn0415.wav");
    *(undefined4 *)(param_1 + 0x228) = uVar2;
    uVar2 = FUN_00437d30("misn0416.wav");
    *(undefined4 *)(param_1 + 0x22c) = uVar2;
    *(undefined1 *)(param_1 + 0x55) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined1 *)(param_1 + 0x6f) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1d0);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x8d) == '\0')) {
    fVar4 = (float10)FUN_004b1670("misn04l2.des");
    FUN_0045c0f0((float)fVar4 + 20.0);
    FUN_00437d30("misn0431.wav");
    FUN_00437d30("misn0432.wav");
    FUN_00437d30("misn0433.wav");
    FUN_00437d30("misn0434.wav");
    *(undefined1 *)(param_1 + 0x8d) = 1;
  }
  if (*(int *)(param_1 + 500) == 6) {
    FUN_005c84d0(param_1 + 0x1ac);
    FUN_005c84d0(param_1 + 0x1b0);
    FUN_005c84d0(param_1 + 0x1b4);
    FUN_005c84d0(param_1 + 0x1b8);
  }
  if ((((((*(char *)(param_1 + 0x55) == '\0') && (*(char *)(param_1 + 0x6f) == '\0')) &&
        (*(int *)(param_1 + 500) == 6)) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x1ac), cVar1 == '\0' &&
        (cVar1 = FUN_005c84d0(param_1 + 0x1b0), cVar1 == '\0')))) &&
      ((cVar1 = FUN_005c84d0(param_1 + 0x1b4), cVar1 == '\0' &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x1b8), cVar1 == '\0' &&
        (cVar1 = FUN_005c84d0(param_1 + 0xe4), cVar1 == '\0')))))) &&
     (*(char *)(param_1 + 0x70) == '\x01')) {
    uVar2 = FUN_00437d30("misn0425.wav");
    *(undefined4 *)(param_1 + 0x224) = uVar2;
    *(undefined1 *)(param_1 + 0x55) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined1 *)(param_1 + 0x6f) = 1;
  }
  return;
}

