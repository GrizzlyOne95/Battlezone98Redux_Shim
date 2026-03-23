
void FUN_005493f0(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_10 = FUN_005c7fb0();
  if (*(char *)(local_8 + 0x55) == '\0') {
    uVar2 = FUN_00437d30("misn1601.wav");
    *(undefined4 *)(local_8 + 0xa0) = uVar2;
    uVar2 = FUN_00437d30("misn1602.wav");
    *(undefined4 *)(local_8 + 0xa4) = uVar2;
    uVar2 = FUN_005c7e90("avrecy0_recycler");
    *(undefined4 *)(local_8 + 0x98) = uVar2;
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    *(uint *)(local_8 + 0xdc) = uVar3 + 1;
    *(undefined1 *)(local_8 + 0x55) = 1;
    uVar2 = FUN_005c7e90("alien_hq");
    *(undefined4 *)(local_8 + 0x84) = uVar2;
    uVar2 = FUN_005c7e90("alien_hangar");
    *(undefined4 *)(local_8 + 0x88) = uVar2;
    FUN_005cadd0(1,0x32);
    FUN_005cb2d0("misn16.aip",2);
    FUN_004f6aa0();
    FUN_004f6ab0("misn1601.otf",DAT_0091755c,0x41000000,0);
    uVar2 = FUN_005c7e90("apcamr12_camerapod");
    *(undefined4 *)(local_8 + 0xa8) = uVar2;
    uVar2 = FUN_005c7e90("apcamr15_camerapod");
    *(undefined4 *)(local_8 + 0xac) = uVar2;
    uVar2 = FUN_005c7e90("apcamr13_camerapod");
    *(undefined4 *)(local_8 + 0xb0) = uVar2;
    uVar2 = FUN_005c7e90("apcamr11_camerapod");
    *(undefined4 *)(local_8 + 0xb4) = uVar2;
    if (*(int *)(local_8 + 0xa8) != 0) {
      FUN_005c9640(*(undefined4 *)(local_8 + 0xa8),"NW Geyser");
    }
    if (*(int *)(local_8 + 0xac) != 0) {
      FUN_005c9640(*(undefined4 *)(local_8 + 0xac),"Foothill Geysers");
    }
    if (*(int *)(local_8 + 0xb0) != 0) {
      FUN_005c9640(*(undefined4 *)(local_8 + 0xb0),"Geyser Site");
    }
    if (*(int *)(local_8 + 0xb4) != 0) {
      FUN_005c9640(*(undefined4 *)(local_8 + 0xb4),"Alien HQ");
    }
    uVar2 = FUN_005c7e90("sbtowe0_turret");
    *(undefined4 *)(local_8 + 200) = uVar2;
    uVar2 = FUN_005c7e90("sbtowe1_turret");
    *(undefined4 *)(local_8 + 0xcc) = uVar2;
    uVar2 = FUN_005c7e90("sbtowe2_turret");
    *(undefined4 *)(local_8 + 0xd0) = uVar2;
    uVar2 = FUN_005c7e90("sbtowe3_turret");
    *(undefined4 *)(local_8 + 0xd4) = uVar2;
    uVar2 = FUN_005c7e90("hvsat0_wingman");
    *(undefined4 *)(local_8 + 0xbc) = uVar2;
    uVar2 = FUN_005c7e90("hvsat1_wingman");
    *(undefined4 *)(local_8 + 0xc0) = uVar2;
    uVar2 = FUN_005c7e90("hvsat2_wingman");
    *(undefined4 *)(local_8 + 0xc4) = uVar2;
    if (*(int *)(local_8 + 0xbc) != 0) {
      FUN_005cbc80(*(undefined4 *)(local_8 + 0xbc),1);
    }
    if (*(int *)(local_8 + 0xc0) != 0) {
      FUN_005cbc80(*(undefined4 *)(local_8 + 0xc0),1);
    }
    if (*(int *)(local_8 + 0xc4) != 0) {
      FUN_005cbc80(*(undefined4 *)(local_8 + 0xc4),1);
    }
    iVar4 = FUN_005c7e90("hvsav47_sav");
    if (iVar4 != 0) {
      FUN_005cbc80(iVar4,1);
    }
    uVar2 = FUN_005c7e90("avmuf26_factory");
    *(undefined4 *)(local_8 + 0x9c) = uVar2;
    *(undefined1 *)(local_8 + 0x59) = 1;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_8 + 0x74) = (float)fVar6 + 20.0;
    FUN_005cd2a0();
  }
  if (*(char *)(local_8 + 0x59) != '\0') {
    FUN_005cd300("camera_path1",4000,500,*(undefined4 *)(local_8 + 0x88));
  }
  if ((*(char *)(local_8 + 0x59) != '\0') &&
     (((cVar1 = FUN_005cd560(), cVar1 != '\0' ||
       (fVar6 = (float10)FUN_004b1670(),
       *(float *)(local_8 + 0x74) <= (float)fVar6 && (float)fVar6 != *(float *)(local_8 + 0x74))) ||
      (cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 0xa4)), cVar1 != '\0')))) {
    *(undefined1 *)(local_8 + 0x59) = 0;
    FUN_005cd4e0();
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_8 + 0x68) = (float)fVar6 + 60.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_8 + 0x78) = (float)fVar6 + 90.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_8 + 0x5c) = (float)fVar6 + 120.0;
    iVar4 = FUN_005c7e90("hvsav47_sav");
    if (iVar4 != 0) {
      FUN_005cbd40(iVar4,0);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if ((*(float *)(local_8 + 0x5c) <= (float)fVar6 && (float)fVar6 != *(float *)(local_8 + 0x5c)) &&
     (*(int *)(local_8 + 0xe0) = *(int *)(local_8 + 0xe0) + 1, *(int *)(local_8 + 0xe0) < 10)) {
    local_c = *(int *)(local_8 + 0xdc) + -1;
    switch(local_c) {
    case 0:
      FUN_00437d30("misn1603.wav");
      FUN_005c8250("svfigh",1,"starta",0,0);
      FUN_005c8250("svhaul",1,"starta2",0,0);
      FUN_005c8250("svhaul",1,"starta3",0,0);
      break;
    case 1:
      FUN_00437d30("misn1604.wav");
      FUN_005c8250("svscav",1,"startb",0,0);
      FUN_005c8250("svscav",1,"startb2",0,0);
      FUN_005c8250("svfigh",1,"startb3",0,0);
      break;
    case 2:
      FUN_00437d30("misn1605.wav");
      FUN_005c8250("svscav",1,"starta",0,0);
      FUN_005c8250("svturr",1,"starta2",0,0);
      FUN_005c8250("svfigh",1,"starta3",0,0);
      break;
    case 3:
      FUN_00437d30("misn1606.wav");
      FUN_005c8250("svfigh",1,"startb",0,0);
      FUN_005c8250("svfigh",1,"startb2",0,0);
      break;
    case 4:
      FUN_00437d30("misn1607.wav");
      FUN_005c8250("svfigh",1,"starta",0,0);
      FUN_005c8250("svfigh",1,"starta2",0,0);
      FUN_005c8250("svtank",1,"starta3",0,0);
      break;
    case 5:
      FUN_00437d30("misn1607.wav");
      FUN_005c8250("svtank",1,"startb",0,0);
      FUN_005c8250("svtank",1,"startb2",0,0);
      FUN_005c8250("svtank",1,"startb3",0,0);
      break;
    case 6:
      FUN_00437d30("misn1608.wav");
      FUN_005c8250("svwalk",1,"starta",0,0);
      FUN_005c8250("svwalk",1,"starta2",0,0);
      FUN_005c8250("svwalk",1,"starta3",0,0);
    }
    iVar4 = rand();
    *(int *)(local_8 + 0xdc) = iVar4 % 7 + 1;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_8 + 0x5c) = (float)fVar6 + 180.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_8 + 100) = (float)fVar6 + 2.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(local_8 + 100) <= (float)fVar6 && (float)fVar6 != *(float *)(local_8 + 100)) {
    cVar1 = FUN_005c84d0(&local_10);
    if (cVar1 != '\0') {
      uVar2 = FUN_005ca150(local_10);
      fVar6 = (float10)FUN_005c9780(local_10,uVar2);
      if (150.0 < (float)fVar6) {
        *(undefined1 *)(local_8 + 0x56) = 1;
        fVar6 = (float10)FUN_004b1670();
        *(float *)(local_8 + 0x60) = (float)fVar6 + 4.0;
        FUN_005cd2a0();
      }
    }
    *(undefined4 *)(local_8 + 100) = 0x47c34f80;
  }
  if (*(char *)(local_8 + 0x56) != '\0') {
    FUN_005cd440(*(undefined4 *)(local_8 + 0x94),0,2000,3000,*(undefined4 *)(local_8 + 0x94));
  }
  if ((*(char *)(local_8 + 0x56) != '\0') &&
     ((fVar6 = (float10)FUN_004b1670(),
      *(float *)(local_8 + 0x60) <= (float)fVar6 && (float)fVar6 != *(float *)(local_8 + 0x60) ||
      (cVar1 = FUN_005cd560(), cVar1 != '\0')))) {
    *(undefined1 *)(local_8 + 0x56) = 0;
    FUN_005cd4e0();
    *(undefined4 *)(local_8 + 0x60) = 0x47c34f80;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(local_8 + 0x68) <= (float)fVar6 && (float)fVar6 != *(float *)(local_8 + 0x68)) {
    FUN_005c8080("hvsav",2,*(undefined4 *)(local_8 + 0x88),0);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_8 + 0x68) = (float)fVar6 + *(float *)(local_8 + 0x70);
    if (60.0 < *(float *)(local_8 + 0x70)) {
      *(float *)(local_8 + 0x70) = *(float *)(local_8 + 0x70) - 5.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(local_8 + 0x78) <= (float)fVar6 && (float)fVar6 != *(float *)(local_8 + 0x78)) {
    uVar2 = FUN_005c8250("hvsat",2,&DAT_008814b8,0,0);
    FUN_005cb960(uVar2,"strike1",1);
    uVar2 = FUN_005c8250("hvsat",2,&DAT_00881544,0,0);
    FUN_005cb960(uVar2,"strike2",1);
    *(float *)(local_8 + 0x78) = *(float *)(local_8 + 0x68) + 90.0;
  }
  if ((((*(char *)(local_8 + 0x57) == '\0') && (*(char *)(local_8 + 0x58) == '\0')) &&
      (*(char *)(local_8 + 0x54) == '\0')) &&
     ((((cVar1 = FUN_005c84d0(local_8 + 200), cVar1 == '\0' &&
        (cVar1 = FUN_005c84d0(local_8 + 0xcc), cVar1 == '\0')) ||
       ((cVar1 = FUN_005c84d0(local_8 + 0xd0), cVar1 == '\0' &&
        (cVar1 = FUN_005c84d0(local_8 + 0xd4), cVar1 == '\0')))) ||
      ((cVar1 = FUN_005c84d0(local_8 + 0x84), cVar1 == '\0' ||
       (cVar1 = FUN_005c84d0(local_8 + 0x88), cVar1 == '\0')))))) {
    uVar2 = FUN_005c8080("hvsav",2,*(undefined4 *)(local_8 + 0x88),0);
    uVar5 = FUN_005c8080("hvsav",2,*(undefined4 *)(local_8 + 0x88),0);
    FUN_005cb820(uVar2,*(undefined4 *)(local_8 + 0x9c),1);
    FUN_005cb820(uVar5,*(undefined4 *)(local_8 + 0x9c),1);
    *(undefined1 *)(local_8 + 0x54) = 1;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(local_8 + 0x6c) = (float)fVar6 + 120.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(local_8 + 0x6c) <= (float)fVar6 && (float)fVar6 != *(float *)(local_8 + 0x6c)) {
    uVar2 = FUN_005c8080("hvsav",2,*(undefined4 *)(local_8 + 0x88),0);
    uVar5 = FUN_005c8080("hvsav",2,*(undefined4 *)(local_8 + 0x88),0);
    FUN_005cb820(uVar2,*(undefined4 *)(local_8 + 0x98),1);
    FUN_005cb820(uVar5,*(undefined4 *)(local_8 + 0x98),1);
    *(undefined4 *)(local_8 + 0x6c) = 0x47c34f80;
  }
  if (((*(char *)(local_8 + 0x57) == '\0') && (cVar1 = FUN_005c84d0(local_8 + 0x84), cVar1 == '\0'))
     && (cVar1 = FUN_005c84d0(local_8 + 0x88), cVar1 == '\0')) {
    FUN_00437d30("misn1613.wav");
    *(undefined1 *)(local_8 + 0x57) = 1;
    fVar6 = (float10)FUN_004b1670("misn16w1.des");
    FUN_0045c110((float)fVar6 + 15.0);
  }
  if ((*(char *)(local_8 + 0x58) == '\0') && (cVar1 = FUN_005c84d0(local_8 + 0x98), cVar1 == '\0'))
  {
    FUN_00437d30("misn1612.wav");
    *(undefined1 *)(local_8 + 0x58) = 1;
    fVar6 = (float10)FUN_004b1670("misn16l1.des");
    FUN_0045c0f0((float)fVar6 + 15.0);
  }
  return;
}

