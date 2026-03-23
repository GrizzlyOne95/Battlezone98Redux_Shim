
void __fastcall FUN_00547f20(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  undefined4 local_10;
  int local_c;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x98) = uVar2;
  if (*(char *)(param_1 + 0x57) == '\0') {
    FUN_005cada0(1,10);
    FUN_00547db0();
    iVar3 = FUN_005c7e90("misn15b");
    if (iVar3 == 0) {
      *(undefined1 *)(param_1 + 0x60) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x60) = 1;
    }
    uVar2 = FUN_005c7e90("ubtart0_i76building");
    *(undefined4 *)(param_1 + 0x94) = uVar2;
    uVar2 = FUN_005c7e90("avrecy0_recycler");
    *(undefined4 *)(param_1 + 0xe0) = uVar2;
    uVar2 = FUN_005c7e90("apcamr0_camerapod");
    *(undefined4 *)(param_1 + 0xe4) = uVar2;
    uVar2 = FUN_005c7e90("apcamr1_camerapod");
    *(undefined4 *)(param_1 + 0xe8) = uVar2;
    uVar2 = FUN_005c7e90("apcamr2_camerapod");
    *(undefined4 *)(param_1 + 0xec) = uVar2;
    uVar2 = FUN_005c7e90("apcamr3_camerapod");
    *(undefined4 *)(param_1 + 0xf0) = uVar2;
    uVar2 = FUN_005c7e90("apcamr4_camerapod");
    *(undefined4 *)(param_1 + 0xf4) = uVar2;
    uVar2 = FUN_005c7e90("apcamr5_camerapod");
    *(undefined4 *)(param_1 + 0xf8) = uVar2;
    uVar2 = FUN_005c7e90("svtank0_wingman");
    *(undefined4 *)(param_1 + 0xfc) = uVar2;
    uVar2 = FUN_005c7e90("svtank1_wingman");
    *(undefined4 *)(param_1 + 0x100) = uVar2;
    uVar2 = FUN_005c7e90("svapc0_apc");
    *(undefined4 *)(param_1 + 0xb8) = uVar2;
    uVar2 = FUN_005c7e90("eggeizr15_geyser");
    *(undefined4 *)(param_1 + 0xd8) = uVar2;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar5 + 180.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar5 + 240.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar5 + 300.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar5 + 400.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar5 + 5.0;
    FUN_005c9640(*(undefined4 *)(param_1 + 0xe4),"Geyser Site");
    FUN_005c9640(*(undefined4 *)(param_1 + 0xe8),"NW Geyser");
    FUN_005c9640(*(undefined4 *)(param_1 + 0xec),"NE Geyser");
    FUN_005c9640(*(undefined4 *)(param_1 + 0xf0),"Geyser Site");
    FUN_005c9640(*(undefined4 *)(param_1 + 0xf4),"Supply");
    FUN_005c9640(*(undefined4 *)(param_1 + 0xf8),"Nav Bravo");
    FUN_005cb960(*(undefined4 *)(param_1 + 0xfc),"tank_path",0);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x100),"tank_path",0);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xb8),"tank_path",0);
    uVar2 = FUN_00437d30("misn1501.wav");
    *(undefined4 *)(param_1 + 0xbc) = uVar2;
    fVar5 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x68) = (float)fVar5 + 2.0;
    fVar5 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x6c) = (float)fVar5 + 120.0;
    *(undefined4 *)(param_1 + 0x88) = 0x42200000;
    *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(param_1 + 0xe0);
    *(undefined1 *)(param_1 + 0x57) = 1;
    if (*(int *)(param_1 + 0xf8) != 0) {
      FUN_005c88e0(*(undefined4 *)(param_1 + 0xf8));
    }
  }
  cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xbc));
  if (cVar1 != '\0') {
    fVar5 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x68) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x68)) {
      FUN_00437d30("misn1502.wav");
      FUN_005cd2a0();
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar5 + 8.0;
      *(undefined4 *)(param_1 + 0x68) = 0x47c34f80;
      *(undefined1 *)(param_1 + 0x5c) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5c) != '\0') {
    FUN_005cd440(*(undefined4 *)(param_1 + 0xfc),800,600,0x4b0,*(undefined4 *)(param_1 + 0xfc));
  }
  if (*(char *)(param_1 + 0x5c) != '\0') {
    fVar5 = (float10)FUN_00822d80();
    if ((float)fVar5 < *(float *)(param_1 + 100) || (float)fVar5 == *(float *)(param_1 + 100)) {
      cVar1 = FUN_005cd560();
      if (cVar1 == '\0') goto LAB_00548370;
    }
    *(undefined1 *)(param_1 + 0x5c) = 0;
    FUN_005cd4e0();
  }
LAB_00548370:
  if (*(char *)(param_1 + 0x58) == '\0') {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xfc));
    if (100.0 <= (float)fVar5) {
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xfc))
      ;
      if (100.0 <= (float)fVar5) goto LAB_005483f1;
    }
    *(undefined1 *)(param_1 + 0x58) = 1;
    FUN_00437d30("misn1503.wav");
    FUN_00547db0();
  }
LAB_005483f1:
  if (*(char *)(param_1 + 0x54) == '\0') {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x70) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x70)) {
      FUN_005c88e0(*(undefined4 *)(param_1 + 0xe8));
      FUN_00437d30("misn1511.wav");
      *(undefined4 *)(param_1 + 0x70) = 0x47c34f80;
    }
  }
  if (*(char *)(param_1 + 0x54) == '\0') {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xe8),*(undefined4 *)(param_1 + 0x98));
    if ((float)fVar5 < 150.0) {
      FUN_00437d30("misn1518.wav");
      uVar2 = FUN_005c8250("avscav",1,"scav3here",0,0);
      *(undefined4 *)(param_1 + 0xb4) = uVar2;
      FUN_005c8250("avapc",1,"mufhere",0,0);
      FUN_005c8250("avturr",1,"turhere",0,0);
      *(undefined1 *)(param_1 + 0x54) = 1;
      FUN_00547db0();
      *(undefined1 *)(param_1 + 0x5d) = 1;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x78) = (float)fVar5 + 3.0;
      FUN_005cd2a0();
    }
  }
  if (*(char *)(param_1 + 0x5d) != '\0') {
    FUN_005cd300("rescue_cam1",1000,0,*(undefined4 *)(param_1 + 0xb4));
  }
  if (*(char *)(param_1 + 0x54) != '\0') {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x78) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x78)) {
      *(undefined1 *)(param_1 + 0x5d) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0x47c34f80;
      FUN_005cd4e0();
    }
  }
  if (*(char *)(param_1 + 0x62) == '\0') {
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x98),*(undefined4 *)(param_1 + 0x94));
    if ((float)fVar5 < 150.0) {
      *(undefined1 *)(param_1 + 0x62) = 1;
      FUN_00437d30("misn1513.wav");
      FUN_00437d30("misn1514.wav");
    }
  }
  fVar5 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x6c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x6c)) &&
     (*(int *)(param_1 + 0x29c) < 0x32)) {
    uVar4 = rand();
    uVar4 = uVar4 & 0x80000001;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
    }
    if (uVar4 == 1) {
      local_10 = FUN_005c8250("hvsav",2,"alien1",0,0);
      FUN_005cb820(local_10,*(undefined4 *)(param_1 + 0x104),1);
    }
    else {
      local_10 = FUN_005c8250("hvsav",2,"alien2",0,0);
      FUN_005cb820(local_10,*(undefined4 *)(param_1 + 0x104),1);
    }
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x6c) = (float)fVar5 + 240.0;
    *(undefined4 *)(param_1 + 0x108 + *(int *)(param_1 + 0x29c) * 4) = local_10;
    *(int *)(param_1 + 0x29c) = *(int *)(param_1 + 0x29c) + 1;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x8c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x8c)) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x29c); local_c = local_c + 1) {
      cVar1 = FUN_005c84d0(param_1 + 0x108 + local_c * 4);
      if (cVar1 != '\0') {
        iVar3 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x108 + local_c * 4));
        if (iVar3 == 0) {
          FUN_005cb960(*(undefined4 *)(param_1 + 0x108 + local_c * 4),"alien_path",1);
        }
      }
    }
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar5 + 5.0;
  }
  if (*(char *)(param_1 + 0x60) != '\0') {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x80) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x80)) {
      uVar2 = FUN_005c8250("hvsat",2,"alien1",0,0);
      *(undefined4 *)(param_1 + 0xc0) = uVar2;
      uVar2 = FUN_005c8250("hvsat",2,"alien1",0,0);
      *(undefined4 *)(param_1 + 0xc4) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc0),"deny1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc4),"deny1",1);
      *(undefined4 *)(param_1 + 0x80) = 0x47c34f80;
    }
  }
  if (*(char *)(param_1 + 0x60) != '\0') {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x84) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x84)) {
      uVar2 = FUN_005c8250("hvsat",2,"alien2",0,0);
      *(undefined4 *)(param_1 + 0xc0) = uVar2;
      uVar2 = FUN_005c8250("hvsat",2,"alien2",0,0);
      *(undefined4 *)(param_1 + 0xc4) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc0),"deny2",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc4),"deny2",1);
      *(undefined4 *)(param_1 + 0x84) = 0x47c34f80;
    }
  }
  if (*(char *)(param_1 + 0x5b) == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xe0);
    if (cVar1 == '\0') {
      FUN_00437d30("misn1414.wav");
      *(undefined1 *)(param_1 + 0x5b) = 1;
      fVar5 = (float10)FUN_004b1670("misn15l1.des");
      FUN_0045c0f0((float)fVar5 + 10.0);
    }
  }
  if ((1 < *(int *)(param_1 + 0x2a0)) && (*(char *)(param_1 + 0x61) == '\0')) {
    *(undefined1 *)(param_1 + 0x61) = 1;
    FUN_00547db0();
  }
  if (*(char *)(param_1 + 0x56) == '\0') {
    iVar3 = FUN_005cae10(1);
    if (0x4a < iVar3) {
      FUN_004f6aa0();
      FUN_004f6ab0("misn1501.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn1502.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn1503.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn1504.otf",DAT_009175b0,0x41000000,0);
      *(undefined1 *)(param_1 + 0x56) = 1;
      FUN_00437d30("misn1510.wav");
      fVar5 = (float10)FUN_004b1670("misn15w1.des");
      FUN_0045c110((float)fVar5 + 10.0);
    }
  }
  return;
}

