
void __fastcall FUN_005eaf60(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xbc) = uVar2;
  if (*(char *)(param_1 + 0x59) == '\0') {
    FUN_0041e260();
    FUN_005cacb0(1,2);
    FUN_005cadd0(1,5);
    FUN_005cb2d0("misn02.aip",2);
    uVar2 = FUN_005c7e90("fake_player");
    *(undefined4 *)(param_1 + 0xcc) = uVar2;
    uVar2 = FUN_005c7e90("avland0_wingman");
    *(undefined4 *)(param_1 + 200) = uVar2;
    uVar2 = FUN_005c7e90("sscr_171_scrap");
    *(undefined4 *)(param_1 + 0xac) = uVar2;
    uVar2 = FUN_005c7e90("abcomm1_i76building");
    *(undefined4 *)(param_1 + 0xb0) = uVar2;
    uVar2 = FUN_005c7e90("avrecy-1_recycler");
    *(undefined4 *)(param_1 + 0x9c) = uVar2;
    uVar2 = FUN_005c7e90("apscrap-1_camerapod");
    *(undefined4 *)(param_1 + 0xc0) = uVar2;
    uVar2 = FUN_005c7e90("sscr_176_scrap");
    *(undefined4 *)(param_1 + 0xd0) = uVar2;
    FUN_005c88e0(*(undefined4 *)(param_1 + 0xc0));
    *(undefined1 *)(param_1 + 0x59) = 1;
    *(undefined1 *)(param_1 + 0x54) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar4 + 30.0;
    FUN_005cd2a0();
    uVar2 = FUN_00437d30("misn0230.wav");
    *(undefined4 *)(param_1 + 0xf4) = uVar2;
    FUN_0041e260();
  }
  if (*(char *)(param_1 + 0x54) != '\0') {
    cVar1 = FUN_005cd300("fixcam",0x4b0,0xfa,*(undefined4 *)(param_1 + 200));
    if (cVar1 == '\0') {
      cVar1 = FUN_005cd560();
      if (cVar1 == '\0') goto LAB_005eb12d;
    }
    *(undefined1 *)(param_1 + 0x54) = 0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar4 + 10.0;
    *(undefined1 *)(param_1 + 0x55) = 1;
  }
LAB_005eb12d:
  if (*(char *)(param_1 + 0x55) != '\0') {
    *(undefined1 *)(param_1 + 0x55) = 0;
    *(undefined1 *)(param_1 + 0x56) = 1;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xcc),"player_path",1);
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar4 + 25.0;
  }
  if (*(char *)(param_1 + 0x56) != '\0') {
    cVar1 = FUN_005cd300("zoomcam",0x4b0,800,*(undefined4 *)(param_1 + 0xcc));
    if (cVar1 == '\0') {
      fVar4 = (float10)FUN_004b1670();
      if ((float)fVar4 < *(float *)(param_1 + 0x84) || (float)fVar4 == *(float *)(param_1 + 0x84)) {
        cVar1 = FUN_005cd560();
        if (cVar1 == '\0') goto LAB_005eb27c;
      }
    }
    *(undefined1 *)(param_1 + 0x56) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0x47c34f80;
    FUN_005cd4e0();
    FUN_005c83e0(*(undefined4 *)(param_1 + 0xcc));
    FUN_00437d80(*(undefined4 *)(param_1 + 0xf4));
    *(undefined4 *)(param_1 + 0xf4) = 0;
    FUN_00437d30("misn0224.wav");
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x74) = (float)fVar4 + 30.0;
    FUN_004f6ab0("misn02b1.otf",DAT_0091755c,0x41000000,0);
  }
LAB_005eb27c:
  if ((*(char *)(param_1 + 0x5a) == '\0') && (*(char *)(param_1 + 0x57) != '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xac),*(undefined4 *)(param_1 + 0xb4));
    if ((float)fVar4 < 75.0) {
      iVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0xac));
      (**(code **)(*(int *)(iVar3 + 0x18) + 0xc))();
      FUN_005c8250("svfigh",2,"spawn1",0,0);
      FUN_00437d30("misn0233.wav");
      *(undefined1 *)(param_1 + 0x5b) = 1;
      *(undefined1 *)(param_1 + 0x5a) = 1;
      if ((*(char *)(param_1 + 0x5e) == '\0') && (*(char *)(param_1 + 0x58) != '\0')) {
        *(undefined1 *)(param_1 + 0x5e) = 1;
      }
    }
  }
  if ((*(char *)(param_1 + 0x5e) == '\0') && (*(char *)(param_1 + 0x58) != '\0')) {
    *(undefined1 *)(param_1 + 0x5e) = 1;
  }
  if ((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 0x5f) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xb4),*(undefined4 *)(param_1 + 0xd0));
    if ((float)fVar4 < 200.0) {
      FUN_005c8250("svfigh",2,"spawn2",0,0);
      *(undefined1 *)(param_1 + 0x5f) = 1;
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x74) = (float)fVar4 + 30.0;
    }
  }
  if (*(char *)(param_1 + 0x5f) != '\0') {
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x74) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x74)) {
      FUN_005c8250("svfigh",2,"spawn2",0,0);
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar4 + 45.0;
    }
  }
  if (((*(char *)(param_1 + 0x5b) != '\0') && (*(char *)(param_1 + 0x5f) != '\0')) &&
     (*(char *)(param_1 + 0x5c) == '\0')) {
    iVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0xb4));
    if (iVar3 != 0) {
      FUN_00462630(*(undefined4 *)(param_1 + 0xb4));
      fVar4 = (float10)FUN_0046d040();
      if ((float)fVar4 <= 0.0) goto LAB_005eb541;
    }
    iVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0xb4));
    if (iVar3 != 0) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0xb4),*(undefined4 *)(param_1 + 0xb0),0);
    }
    FUN_004f6aa0();
    FUN_004f6ab0("misn02b2.otf",DAT_0091755c,0x41000000,0);
    FUN_00437d30("misn0225.wav");
    uVar2 = FUN_005c7e90("apbase-1_camerapod");
    FUN_005c88e0(uVar2);
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
LAB_005eb541:
  if (*(int *)(param_1 + 0xb4) == 0) goto LAB_005eb5a3;
  cVar1 = FUN_005c84d0(param_1 + 0xbc);
  if (cVar1 != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xb4);
    if (cVar1 != '\0') {
      if (*(char *)(param_1 + 0x5d) != '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0xb8);
        if (cVar1 == '\0') goto LAB_005eb5d4;
      }
LAB_005eb5a3:
      cVar1 = FUN_005c84d0(param_1 + 0xb0);
      if (cVar1 != '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x9c);
        if (cVar1 != '\0') goto LAB_005eb625;
      }
    }
  }
LAB_005eb5d4:
  if (*(char *)(param_1 + 0x6b) == '\0') {
    FUN_004f6aa0();
    FUN_004f6ab0("misn02b4.otf",DAT_0091757c,0x41000000,0);
    uVar2 = FUN_00437d30("misn0227.wav");
    *(undefined4 *)(param_1 + 0xf4) = uVar2;
    *(undefined1 *)(param_1 + 0x6b) = 1;
  }
LAB_005eb625:
  if (*(char *)(param_1 + 0x6b) != '\0') {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xf4));
    if (cVar1 != '\0') {
      fVar4 = (float10)FUN_004b1670("misn02l1.des");
      FUN_0045c0f0((float)fVar4);
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xbc);
  if (((cVar1 != '\0') && (*(char *)(param_1 + 0x5b) != '\0')) &&
     (*(char *)(param_1 + 0x5e) != '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0xb4));
    if (((float)fVar4 < 300.0) && (*(char *)(param_1 + 0x5d) == '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0xb4),*(undefined4 *)(param_1 + 0xb0),1);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x74) = (float)fVar4 + 45.0;
      uVar2 = FUN_005c8250("avscav",1,"spawn3",0,0);
      *(undefined4 *)(param_1 + 0xb8) = uVar2;
      FUN_005caff0(*(undefined4 *)(param_1 + 0xb8),1);
      FUN_005cc100(*(undefined4 *)(param_1 + 0xb8),"retreat",1);
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xb8));
      FUN_00437d30("misn0228.wav");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x70) = (float)fVar4 + 10.0;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x88) = (float)fVar4 + 1.0;
      *(undefined1 *)(param_1 + 0x5d) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xb4);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x5d) != '\0')) {
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x88) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x88)) {
      FUN_005ccfd0(*(undefined4 *)(param_1 + 0xb4),0x43480000);
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x88) = (float)fVar4 + 1.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x70)) {
    uVar2 = FUN_005c8250("svfigh",2,"spawn4",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xb8),1);
    *(undefined4 *)(param_1 + 0x70) = 0x47c34f80;
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0xb8));
  if ((((float)fVar4 < 200.0) && (*(char *)(param_1 + 0x5d) != '\0')) &&
     (*(char *)(param_1 + 0x6a) == '\0')) {
    FUN_004f6aa0();
    FUN_004f6ab0("misn02b3.otf",DAT_009175b0,0x41000000,0);
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0xb4),0x447a0000);
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0xb8),0x447a0000);
    uVar2 = FUN_00437d30("misn0234.wav");
    *(undefined4 *)(param_1 + 0xf4) = uVar2;
    *(undefined1 *)(param_1 + 0x6a) = 1;
  }
  if (*(char *)(param_1 + 0x6a) != '\0') {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xf4));
    if (cVar1 != '\0') {
      fVar4 = (float10)FUN_004b1670("misn02w1.des");
      FUN_0045c110((float)fVar4);
    }
  }
  FUN_0083e885();
  return;
}

