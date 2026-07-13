
void __fastcall FUN_0055bfa0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float10 fVar4;
  int local_c;
  
  uVar2 = FUN_005c7fb0();
  if (*(char *)(param_1 + 0x5b) == '\0') {
    *(undefined1 *)(param_1 + 0x5b) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar4 + 420.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar4 + 30.0;
    FUN_005c8250("avartl",2,"spawn2",0,0);
    uVar3 = FUN_005c8250("spcamr",1,"camerapt",0,0);
    *(undefined4 *)(param_1 + 0xb8) = uVar3;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar4 + 30.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar4 + 100.0;
    FUN_005cada0(1,0x32);
    FUN_005cacb0(1,0x1e);
    FUN_005cacb0(2,0x1e);
    FUN_004f6aa0();
    FUN_004f6ab0("misns4.otf",DAT_0091755c,0x41000000,0);
    FUN_00437d30("misns401.wav");
    FUN_004f6ae0(0x1a4,300,0);
    FUN_005c9640(*(undefined4 *)(param_1 + 0xb8),"Bridge");
    FUN_005c8250("abtowe",2,"tower1",0,0);
    FUN_005c8250("abtowe",2,"tower2",0,0);
    FUN_005c8250("ablpow",2,"power1",0,0);
    FUN_005c8250("ablpow",2,"power2",0,0);
    FUN_005c8250("svcnst",1,"svcnst",0,0);
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x74)) {
    uVar3 = FUN_005c8250("avfigh",2,"spawn4",0,0);
    FUN_005cb960(uVar3,"wakeup",1);
    *(undefined4 *)(param_1 + 0x74) = 0x47c34f80;
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x78) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x78)) {
    if (*(char *)(param_1 + 0x55) == '\0') {
      FUN_00437d30("misns402.wav");
      FUN_004ff150();
      FUN_004ff160();
      *(undefined1 *)(param_1 + 0x55) = 1;
    }
    uVar3 = FUN_005c8250("svhaul",1,"spawn1",0,0);
    *(undefined4 *)(param_1 + 0x90 + *(int *)(param_1 + 0xec) * 4) = uVar3;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    FUN_005cb960(uVar3,"escort",1);
    FUN_005c95e0(uVar3);
    FUN_005caff0(uVar3,1);
    if (*(int *)(param_1 + 0xec) < *(int *)(param_1 + 0xe8)) {
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x78) = (float)fVar4 + 45.0;
    }
    else {
      *(undefined4 *)(param_1 + 0x78) = 0x47c34f80;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x80)) {
    FUN_005c8250("avfigh",2,"spawn4",0,0);
    FUN_005c8250("avfigh",2,"spawn4",0,0);
    *(undefined4 *)(param_1 + 0x80) = 0x47c34f80;
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x84) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x84)) {
    uVar3 = FUN_005c8250("avtank",2,"sbridge",0,0);
    *(undefined4 *)(param_1 + 0xbc) = uVar3;
    uVar3 = FUN_005c8250("avtank",2,"sbridge",0,0);
    *(undefined4 *)(param_1 + 0xc0) = uVar3;
    uVar3 = FUN_005c8250("avhraz",2,"sbridge",0,0);
    *(undefined4 *)(param_1 + 0xc4) = uVar3;
    *(undefined4 *)(param_1 + 0x84) = 0x47c34f80;
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    fVar4 = (float10)FUN_005c9800(uVar2,"sbridge",0);
    if ((float)fVar4 < 200.0) {
      *(undefined1 *)(param_1 + 0x5c) = 1;
      FUN_005c8250("avltnk",2,"spawn3",0,0);
      FUN_005c8250("avturr",2,"spawn3",0,0);
      FUN_005c8250("avscav",2,"spawn3",0,0);
      FUN_005c8250("avrecy",2,"spawn3",0,0);
    }
  }
  if ((*(char *)(param_1 + 0x58) == '\0') && (*(char *)(param_1 + 0x5c) != '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0xbc);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xc0);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0xc4);
        if (cVar1 == '\0') {
          FUN_00437d30("misns405.wav");
          *(undefined1 *)(param_1 + 0x58) = 1;
          FUN_005cb2d0("misns4.aip",2);
          fVar4 = (float10)FUN_004b1670();
          *(float *)(param_1 + 0x88) = (float)fVar4 + 150.0;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x57) == '\0') {
    fVar4 = (float10)FUN_005c9800(uVar2,"warn1",0);
    if ((float)fVar4 < 200.0) {
      FUN_00437d30("misns409.wav");
      *(undefined1 *)(param_1 + 0x57) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x98);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x54) == '\0')) {
    fVar4 = (float10)FUN_004b1670();
    if ((float)fVar4 < *(float *)(param_1 + 0x88) || (float)fVar4 == *(float *)(param_1 + 0x88)) {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x98),"warn1",0);
      if (200.0 <= (float)fVar4) goto LAB_0055c6bc;
    }
    uVar2 = FUN_005c8250("avrckt",2,"counter",0,0);
    *(undefined4 *)(param_1 + 0xd4) = uVar2;
    uVar2 = FUN_005c8250("avrckt",2,"counter",0,0);
    *(undefined4 *)(param_1 + 0xd8) = uVar2;
    uVar2 = FUN_005c8250("avrckt",2,"counter",0,0);
    *(undefined4 *)(param_1 + 0xdc) = uVar2;
    uVar2 = FUN_005c8250("avrckt",2,"counter",0,0);
    *(undefined4 *)(param_1 + 0xe0) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"sbridge",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xd8),"sbridge",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xdc),"sbridge",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xe0),"sbridge",1);
    *(undefined1 *)(param_1 + 0x54) = 1;
    *(undefined4 *)(param_1 + 0x88) = 0x47c34f80;
  }
LAB_0055c6bc:
  for (local_c = 0; local_c < *(int *)(param_1 + 0xe8); local_c = local_c + 1) {
    if (*(int *)(param_1 + 0x90 + local_c * 4) != 0) {
      cVar1 = FUN_005c84d0(param_1 + 0x90 + local_c * 4);
      if ((cVar1 == '\0') && (*(char *)(param_1 + local_c + 0x5d) != '\0')) {
        FUN_00437d30("misns403.wav");
        *(undefined1 *)(param_1 + local_c + 0x5d) = 0;
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
        if (*(int *)(param_1 + 0xe8) / 3 < *(int *)(param_1 + 0xf0)) {
          fVar4 = (float10)FUN_004b1670("misns4l1.des");
          FUN_0045c0f0((float)fVar4 + 15.0);
        }
      }
    }
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x90 + local_c * 4),&DAT_008829ac,0);
    if (((float)fVar4 < 100.0) && (*(char *)(param_1 + local_c + 0x67) == '\0')) {
      *(undefined1 *)(param_1 + local_c + 0x67) = 1;
      *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
    }
  }
  if ((*(int *)(param_1 + 0xf4) == *(int *)(param_1 + 0xe8) + -1) &&
     (*(char *)(param_1 + 0x59) == '\0')) {
    fVar4 = (float10)FUN_004b1670("misns4w1.des");
    FUN_0045c110((float)fVar4 + 10.0);
    *(undefined1 *)(param_1 + 0x59) = 1;
  }
  return;
}

