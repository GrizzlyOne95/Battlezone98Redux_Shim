
void __fastcall FUN_0055d0f0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  float10 fVar4;
  
  if (*(char *)(param_1 + 0x55) == '\0') {
    uVar2 = FUN_005c7e90("svrecy0_recycler");
    *(undefined4 *)(param_1 + 0xa4) = uVar2;
    FUN_005cada0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar4 + 17.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar4 + 70.0;
    *(undefined1 *)(param_1 + 0x55) = 1;
    uVar2 = FUN_005c7e90("sbhang0_repairdepot");
    *(undefined4 *)(param_1 + 0x90) = uVar2;
    uVar2 = FUN_005c8250("avartl",2,"spawn1",0,0);
    *(undefined4 *)(param_1 + 0x7c) = uVar2;
    uVar2 = FUN_005c8250("avartl",2,"spawn2",0,0);
    *(undefined4 *)(param_1 + 0x80) = uVar2;
    FUN_005cd2a0();
    uVar2 = FUN_00437d30("misns501.wav");
    *(undefined4 *)(param_1 + 0xc4) = uVar2;
  }
  if (*(char *)(param_1 + 0x54) != '\0') {
    FUN_005cd300("campath",5000,0x9c4,*(undefined4 *)(param_1 + 0x90));
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xc4));
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x5d) == '\0')) {
      uVar2 = FUN_00437d30("misns503.wav");
      *(undefined4 *)(param_1 + 0xc4) = uVar2;
      *(undefined1 *)(param_1 + 0x5d) = 1;
    }
    cVar1 = FUN_005cd560();
    if (cVar1 == '\0') {
      cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xc4));
      if (cVar1 == '\0') goto LAB_0055d40c;
    }
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x6c) = (float)fVar4 + 180.0;
    uVar2 = FUN_005c7e90("sblpow2_powerplant");
    *(undefined4 *)(param_1 + 0x84) = uVar2;
    uVar2 = FUN_005c7e90("sblpow3_powerplant");
    *(undefined4 *)(param_1 + 0x88) = uVar2;
    uVar2 = FUN_005c7e90("sblpow4_powerplant");
    *(undefined4 *)(param_1 + 0x8c) = uVar2;
    uVar2 = FUN_005c7e90("svrecy0_recycler");
    *(undefined4 *)(param_1 + 0xa4) = uVar2;
    uVar2 = FUN_005c7e90("svmuf0_factory");
    *(undefined4 *)(param_1 + 0xa8) = uVar2;
    uVar2 = FUN_005c7e90("eggeizr11_geyser");
    *(undefined4 *)(param_1 + 0x9c) = uVar2;
    uVar2 = FUN_005c7e90("eggeizr12_geyser");
    *(undefined4 *)(param_1 + 0xa0) = uVar2;
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xa4),*(undefined4 *)(param_1 + 0x9c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0xa0),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x7c),*(undefined4 *)(param_1 + 0x84),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x80),*(undefined4 *)(param_1 + 0x88),1);
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 100) = (float)fVar4 + 10.0;
    FUN_005cd4e0();
    FUN_004f6aa0();
    FUN_004f6ab0("misns501.otf",DAT_0091755c,0x41000000,0);
    FUN_00437d80(*(undefined4 *)(param_1 + 0xc4));
    *(undefined1 *)(param_1 + 0x54) = 0;
  }
LAB_0055d40c:
  if ((*(char *)(param_1 + 0x56) != '\0') && (*(char *)(param_1 + 0x59) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x84);
    if (cVar1 == '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x7c),*(undefined4 *)(param_1 + 0x8c),1);
      *(undefined1 *)(param_1 + 0x59) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x56) != '\0') && (*(char *)(param_1 + 0x5a) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x88);
    if (cVar1 == '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x80),*(undefined4 *)(param_1 + 0x90),1);
      *(undefined1 *)(param_1 + 0x5a) = 1;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
    FUN_005c8250("avwalk",2,"spawn3",0,0);
    *(undefined4 *)(param_1 + 100) = 0x47c34f80;
    FUN_005cacb0(2,0x1e);
    *(undefined1 *)(param_1 + 0x56) = 1;
  }
  if ((*(char *)(param_1 + 0x56) != '\0') && (*(char *)(param_1 + 0x5f) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x7c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x80);
      if (cVar1 == '\0') {
        FUN_00437d30("misns504.wav");
        *(undefined1 *)(param_1 + 0x5f) = 1;
      }
    }
  }
  if (((*(char *)(param_1 + 0x56) != '\0') && (*(int *)(param_1 + 0x94) != 0)) &&
     (*(char *)(param_1 + 0x60) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0xa8));
    if ((float)fVar4 < 100.0) {
      *(undefined1 *)(param_1 + 0x60) = 1;
      FUN_00437d30("misns505.wav");
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x6c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x6c)) {
    fVar4 = (float10)FUN_004b1670();
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000003;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
    }
    *(float *)(param_1 + 0x6c) = (float)fVar4 + 50.0 + (float)(int)uVar3 * 10.0;
    FUN_005c8250("avfigh",2,"spawn5",0,0);
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x74)) {
    uVar2 = FUN_005c8250("avapc",2,"spawn6",0,0);
    *(undefined4 *)(param_1 + 0x94) = uVar2;
    uVar2 = FUN_005c8250("avapc",2,"spawn6",0,0);
    *(undefined4 *)(param_1 + 0x98) = uVar2;
    uVar2 = FUN_005c8250("avrecy",2,"spawn7",0,0);
    *(undefined4 *)(param_1 + 0xb4) = uVar2;
    uVar2 = FUN_005c8250("bvtank",2,"spawn7",0,0);
    FUN_005cbc80(uVar2,*(undefined4 *)(param_1 + 0xb4));
    uVar2 = FUN_005c8250("bvtank",2,"spawn7",0,0);
    FUN_005cbc80(uVar2,*(undefined4 *)(param_1 + 0xb4));
    FUN_005cb820(*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0xa8),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x98),*(undefined4 *)(param_1 + 0xa8),1);
    *(undefined4 *)(param_1 + 0x74) = 0x47c34f80;
  }
  if (*(char *)(param_1 + 0x56) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xac);
    if ((cVar1 == '\0') && (*(char *)(param_1 + 0x57) == '\0')) {
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x68) = (float)fVar4 + 120.0;
      *(undefined1 *)(param_1 + 0x57) = 1;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x68) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x68)) {
    *(int *)(param_1 + 0xbc) = *(int *)(param_1 + 0xbc) + 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x68) = (float)fVar4 + 180.0;
    FUN_00437d30("misns505.wav");
    if (*(int *)(param_1 + 0xbc) == 1) {
      FUN_005c8250("bvhraz",2,"spawn6",0,0);
      FUN_005c8250("bvhraz",2,"spawn6",0,0);
      FUN_005c8250("bvhraz",2,"spawn6",0,0);
    }
    else {
      FUN_005c8250("bvltnk",2,"spawn5",0,0);
      FUN_005c8250("bvltnk",2,"spawn5",0,0);
      FUN_005c8250("bvltnk",2,"spawn5",0,0);
    }
    if (*(int *)(param_1 + 0xbc) == 3) {
      *(undefined1 *)(param_1 + 0x58) = 1;
      FUN_005c8250("avscav",2,"spawn7",0,0);
      FUN_005c8250("avscav",2,"spawn7",0,0);
      uVar2 = FUN_005c8250("spcamr",1,"camera1",0,0);
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xb4),uVar2);
      FUN_004f6ab0("misns502.otf",DAT_0091755c,0x41000000,0);
      FUN_00437d30("misns506.wav");
      FUN_005cb2d0("misns5.aip",2);
    }
  }
  if (*(char *)(param_1 + 0x58) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xb4);
    if (((cVar1 == '\0') && (*(char *)(param_1 + 0x5b) == '\0')) &&
       (*(char *)(param_1 + 0x5c) == '\0')) {
      *(undefined1 *)(param_1 + 0x5b) = 1;
      FUN_00437d30("misns508.wav");
      fVar4 = (float10)FUN_004b1670("misns5w1.des");
      FUN_0045c110((float)fVar4 + 10.0);
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xa4);
  if (((cVar1 == '\0') && (*(char *)(param_1 + 0x5c) == '\0')) &&
     (*(char *)(param_1 + 0x5b) == '\0')) {
    *(undefined1 *)(param_1 + 0x5c) = 1;
    FUN_00437d30("misns507.wav");
    fVar4 = (float10)FUN_004b1670("misns5l1.des");
    FUN_0045c0f0((float)fVar4 + 10.0);
  }
  return;
}

