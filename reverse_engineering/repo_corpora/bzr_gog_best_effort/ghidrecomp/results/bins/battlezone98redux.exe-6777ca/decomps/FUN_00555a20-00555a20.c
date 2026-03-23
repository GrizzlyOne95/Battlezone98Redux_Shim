
void __fastcall FUN_00555a20(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  if (*(char *)(param_1 + 0x55) == '\0') {
    uVar2 = FUN_00437d30("misns200.wav");
    *(undefined4 *)(param_1 + 0x24c) = uVar2;
    uVar2 = FUN_005c7e90("sblpad59_i76building");
    *(undefined4 *)(param_1 + 0x1a4) = uVar2;
    uVar2 = FUN_005c7e90("svtank0_wingman");
    *(undefined4 *)(param_1 + 0xa4) = uVar2;
    uVar2 = FUN_005c7e90("svfigh2_wingman");
    *(undefined4 *)(param_1 + 0xa8) = uVar2;
    uVar2 = FUN_005c7e90("apcamr5_camerapod");
    *(undefined4 *)(param_1 + 500) = uVar2;
    uVar2 = FUN_005c7e90("svfigh3_wingman");
    *(undefined4 *)(param_1 + 0xac) = uVar2;
    uVar2 = FUN_005c7e90("svfigh5_wingman");
    *(undefined4 *)(param_1 + 0xb8) = uVar2;
    uVar2 = FUN_005c7e90("svfigh6_wingman");
    *(undefined4 *)(param_1 + 0xbc) = uVar2;
    uVar2 = FUN_005c7e90("svtank5_wingman");
    *(undefined4 *)(param_1 + 0xb4) = uVar2;
    uVar2 = FUN_005c7e90("svtank4_wingman");
    *(undefined4 *)(param_1 + 0xb0) = uVar2;
    uVar2 = FUN_005c7e90("svtank12_wingman");
    *(undefined4 *)(param_1 + 0xc0) = uVar2;
    uVar2 = FUN_005c7e90("svapc0_apc");
    *(undefined4 *)(param_1 + 0xc4) = uVar2;
    uVar2 = FUN_005c7e90("svapc1_apc");
    *(undefined4 *)(param_1 + 200) = uVar2;
    uVar2 = FUN_005c7e90("svapc2_apc");
    *(undefined4 *)(param_1 + 0xcc) = uVar2;
    FUN_005caff0(*(undefined4 *)(param_1 + 0xc4),1);
    FUN_005caff0(*(undefined4 *)(param_1 + 200),1);
    FUN_005caff0(*(undefined4 *)(param_1 + 0xcc),1);
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar4 + 10.0;
    *(undefined1 *)(param_1 + 0x55) = 1;
    FUN_004f6ab0("misns201.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("misns202.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("misns203.otf",DAT_0091755c,0x41000000,0);
    FUN_005cd2a0();
    uVar2 = FUN_005c7e90(&DAT_0087ea98);
    *(undefined4 *)(param_1 + 0x1b8) = uVar2;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x90) = (float)fVar4 + 9.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x94) = (float)fVar4 + 9.01;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x98) = (float)fVar4 + 24.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar4 + 34.0;
    FUN_005c9640(*(undefined4 *)(param_1 + 0x1b8),"Launch Pad");
  }
  if (*(char *)(param_1 + 0x77) == '\0') {
    FUN_005cd300("cinpath1",500,200,*(undefined4 *)(param_1 + 0xc4));
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x24c));
    if (cVar1 == '\0') {
      cVar1 = FUN_005cd560();
      if (cVar1 == '\0') goto LAB_00555d6e;
    }
    *(undefined1 *)(param_1 + 0x77) = 1;
    FUN_005cd4e0();
    FUN_00437d80(*(undefined4 *)(param_1 + 0x24c));
    FUN_00437d30("misns202.wav");
  }
LAB_00555d6e:
  if (*(char *)(param_1 + 0x71) == '\x01') {
    FUN_004f6aa0();
    cVar1 = FUN_005c84d0(param_1 + 0xc4);
    if (cVar1 == '\0') {
      FUN_004f6ab0("misns201.otf",DAT_0091757c,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 200);
    if (cVar1 == '\0') {
      FUN_004f6ab0("misns202.otf",DAT_0091757c,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xcc);
    if (cVar1 == '\0') {
      FUN_004f6ab0("misns203.otf",DAT_0091757c,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xc4);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x6e) == '\0')) {
      FUN_004f6ab0("misns201.otf",DAT_0091755c,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xc4);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x6e) == '\x01')) {
      FUN_004f6ab0("misns201.otf",DAT_009175b0,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 200);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x6f) == '\x01')) {
      FUN_004f6ab0("misns202.otf",DAT_009175b0,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 200);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x6f) == '\0')) {
      FUN_004f6ab0("misns202.otf",DAT_0091755c,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xcc);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x70) == '\x01')) {
      FUN_004f6ab0("misns203.otf",DAT_009175b0,0x41000000,0);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xcc);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x70) == '\0')) {
      FUN_004f6ab0("misns203.otf",DAT_0091755c,0x41000000,0);
    }
    *(undefined1 *)(param_1 + 0x71) = 0;
  }
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x7c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x7c)) &&
     (*(char *)(param_1 + 0x59) == '\0')) {
    uVar2 = FUN_005c8250("bvtank",2,"bdsp1",0,0);
    *(undefined4 *)(param_1 + 0xd0) = uVar2;
    uVar2 = FUN_005c8250("bvraz",2,"bdsp1",0,0);
    *(undefined4 *)(param_1 + 0xd4) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0xd0),*(undefined4 *)(param_1 + 0xc4),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xcc),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xd0),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xd4),1);
    *(undefined1 *)(param_1 + 0x59) = 1;
    *(undefined4 *)(param_1 + 0x7c) = 0x5368d4a5;
  }
  if (*(char *)(param_1 + 0x59) == '\x01') {
    cVar1 = FUN_005c84d0(param_1 + 0xd0);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xd4);
      if ((cVar1 == '\0') && (*(char *)(param_1 + 0x54) == '\0')) {
        FUN_00437d30("misns203.wav");
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x8c) = (float)fVar4 + 3.0;
        *(undefined1 *)(param_1 + 0x54) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xd0);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xd4);
    if (((cVar1 == '\0') && (*(char *)(param_1 + 0x72) == '\0')) &&
       (*(char *)(param_1 + 0x59) == '\x01')) {
      fVar4 = (float10)FUN_004b1670();
      if (*(float *)(param_1 + 0x8c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x8c))
      {
        uVar2 = FUN_00437d30("misns204.wav");
        *(undefined4 *)(param_1 + 0x250) = uVar2;
        uVar2 = FUN_00437d30("misns205.wav");
        *(undefined4 *)(param_1 + 0x254) = uVar2;
        *(undefined1 *)(param_1 + 0x72) = 1;
        FUN_005cd2a0();
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x80) = (float)fVar4 + 20.0;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_008823dc,0,0);
        *(undefined4 *)(param_1 + 0x13c) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_008823f4,0,0);
        *(undefined4 *)(param_1 + 0x140) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_008823f0,0,0);
        *(undefined4 *)(param_1 + 0x144) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_00882388,0,0);
        *(undefined4 *)(param_1 + 0x148) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_00882384,0,0);
        *(undefined4 *)(param_1 + 0x14c) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_00882390,0,0);
        *(undefined4 *)(param_1 + 0x150) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_0088238c,0,0);
        *(undefined4 *)(param_1 + 0x154) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_00882398,0,0);
        *(undefined4 *)(param_1 + 0x158) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_00882394,0,0);
        *(undefined4 *)(param_1 + 0x15c) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_008823a0,0,0);
        *(undefined4 *)(param_1 + 0x160) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,&DAT_0088239c,0,0);
        *(undefined4 *)(param_1 + 0x164) = uVar2;
      }
    }
  }
  if ((*(char *)(param_1 + 0x78) == '\0') && (*(char *)(param_1 + 0x72) == '\x01')) {
    FUN_005cd300("platooncam",1000,600,*(undefined4 *)(param_1 + 0x13c));
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x250));
    if (cVar1 == '\0') {
LAB_005563ff:
      cVar1 = FUN_005cd560();
      if (cVar1 == '\0') goto LAB_0055653a;
    }
    else {
      cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x254));
      if (cVar1 == '\0') goto LAB_005563ff;
    }
    FUN_005cd4e0();
    FUN_00437d80(*(undefined4 *)(param_1 + 0x250));
    FUN_00437d80(*(undefined4 *)(param_1 + 0x254));
    uVar2 = FUN_00437d30("misns206.wav");
    *(undefined4 *)(param_1 + 600) = uVar2;
    *(undefined1 *)(param_1 + 0x6d) = 1;
    FUN_005cb820(*(undefined4 *)(param_1 + 0x148),*(undefined4 *)(param_1 + 0xcc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x14c),*(undefined4 *)(param_1 + 200),1);
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x13c));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x140));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x144));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x150));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x154));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x158));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x15c));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x160));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x164));
    *(undefined1 *)(param_1 + 0x78) = 1;
  }
LAB_0055653a:
  if (*(char *)(param_1 + 0x5a) == '\0') {
    uVar2 = FUN_005c9d10("bdsp2",1);
    *(undefined4 *)(param_1 + 0x1b0) = uVar2;
  }
  if (*(char *)(param_1 + 0x5a) == '\0') {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x1b0),"bdsp2",0);
    if ((float)fVar4 < 420.0) {
      uVar2 = FUN_005c8250("bvraz",2,"bdsp2",0,0);
      *(undefined4 *)(param_1 + 0xe0) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdsp2",0,0);
      *(undefined4 *)(param_1 + 0xe4) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdsp2",0,0);
      *(undefined4 *)(param_1 + 0xe8) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdsp2",0,0);
      *(undefined4 *)(param_1 + 0xec) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 0xe0),*(undefined4 *)(param_1 + 0xcc),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0xe4),*(undefined4 *)(param_1 + 0xc4),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0xe8),*(undefined4 *)(param_1 + 0xcc),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0xec),*(undefined4 *)(param_1 + 200),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xe0),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xe4),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xe8),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xec),1);
      *(undefined1 *)(param_1 + 0x5a) = 1;
    }
  }
  fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc4),&DAT_00882460,0);
  if ((float)fVar4 < 200.0) {
LAB_0055677b:
    if (*(char *)(param_1 + 0x5a) == '\0') {
      uVar2 = FUN_005c8250("bvraz",2,"bdsp2",0,0);
      *(undefined4 *)(param_1 + 0xe0) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdsp2",0,0);
      *(undefined4 *)(param_1 + 0xe4) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdsp2",0,0);
      *(undefined4 *)(param_1 + 0xe8) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdsp2",0,0);
      *(undefined4 *)(param_1 + 0xec) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 0xe0),*(undefined4 *)(param_1 + 0xc4),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0xe4),*(undefined4 *)(param_1 + 200),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0xe8),*(undefined4 *)(param_1 + 200),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0xec),*(undefined4 *)(param_1 + 0xcc),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xe0),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xe4),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xe8),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0xec),1);
      *(undefined1 *)(param_1 + 0x5a) = 1;
    }
  }
  else {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),&DAT_00882460,0);
    if ((float)fVar4 < 200.0) goto LAB_0055677b;
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),&DAT_00882460,0);
    if ((float)fVar4 < 200.0) goto LAB_0055677b;
  }
  if (*(char *)(param_1 + 0x5b) == '\0') {
    uVar2 = FUN_005c9d10("bdsp3",1);
    *(undefined4 *)(param_1 + 0x1a8) = uVar2;
  }
  if (*(char *)(param_1 + 0x5b) == '\0') {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x1a8),"bdsp3",0);
    if ((float)fVar4 < 450.0) {
      iVar3 = FUN_005c8800(*(undefined4 *)(param_1 + 0x1a8));
      if (iVar3 == 1) {
        uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf0) = uVar2;
        uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf4) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf8) = uVar2;
        FUN_005cb620(*(undefined4 *)(param_1 + 0xf8),1);
        *(undefined1 *)(param_1 + 0x5b) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x5b) == '\0') {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc4),&DAT_00882470,0);
    if (400.0 <= (float)fVar4) {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),&DAT_00882470,0);
      if (400.0 <= (float)fVar4) {
        fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),&DAT_00882470,0);
        if (400.0 <= (float)fVar4) goto LAB_00556d2f;
      }
    }
    uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
    *(undefined4 *)(param_1 + 0xf0) = uVar2;
    uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
    *(undefined4 *)(param_1 + 0xf4) = uVar2;
    uVar2 = FUN_005c8250("bvtank",2,"bdsp3",0,0);
    *(undefined4 *)(param_1 + 0xf8) = uVar2;
    FUN_005c8250("proxmine",2,"mine1",0,0);
    FUN_005c8250("proxmine",2,"mine2",0,0);
    FUN_005c8250("proxmine",2,"mine3",0,0);
    FUN_005c8250("proxmine",2,"mine4",0,0);
    FUN_005c8250("proxmine",2,"mine5",0,0);
    FUN_005c8250("proxmine",2,"mine6",0,0);
    FUN_005c8250("proxmine",2,"mine7",0,0);
    FUN_005c8250("proxmine",2,"mine8",0,0);
    FUN_005c8250("proxmine",2,"mine9",0,0);
    FUN_005c8250("proxmine",2,"mine10",0,0);
    FUN_005c8250("proxmine",2,"mine11",0,0);
    FUN_005c8250("proxmine",2,"mine12",0,0);
    FUN_005c8250("proxmine",2,"mine13",0,0);
    FUN_005c8250("proxmine",2,"mine14",0,0);
    FUN_005c8250("proxmine",2,"mine15",0,0);
    FUN_005c8250("proxmine",2,"mine16",0,0);
    FUN_005c8250("proxmine",2,"mine17",0,0);
    FUN_005c8250("proxmine",2,"mine18",0,0);
    FUN_005c8250("proxmine",2,"mine19",0,0);
    FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xcc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 200),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xf0),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0xf8),1);
    *(undefined1 *)(param_1 + 0x5b) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar4 + 15.0;
  }
LAB_00556d2f:
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x88) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x88)) &&
     (*(char *)(param_1 + 0x6a) == '\0')) {
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xf0));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xf4));
    FUN_00437d30("misns210.wav");
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xfc));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x100));
    *(undefined1 *)(param_1 + 0x6a) = 1;
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    uVar2 = FUN_005c9d10("bdsp4",1);
    *(undefined4 *)(param_1 + 0x1ac) = uVar2;
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x1ac),"bdsp4",0);
    if ((float)fVar4 < 450.0) {
      iVar3 = FUN_005c8800(*(undefined4 *)(param_1 + 0x1ac));
      if (iVar3 == 1) {
        uVar2 = FUN_005c8250("bvartl",2,"bdsp4",0,0);
        *(undefined4 *)(param_1 + 0xfc) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,"bdsp4",0,0);
        *(undefined4 *)(param_1 + 0x100) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,"bdsp4",0,0);
        *(undefined4 *)(param_1 + 0x104) = uVar2;
        FUN_005cb620(*(undefined4 *)(param_1 + 0x104),1);
        *(undefined1 *)(param_1 + 0x5c) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xc4),&DAT_00882470,0);
    if (200.0 <= (float)fVar4) {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),&DAT_00882470,0);
      if (200.0 <= (float)fVar4) {
        fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),&DAT_00882470,0);
        if (200.0 <= (float)fVar4) goto LAB_0055701f;
      }
    }
    uVar2 = FUN_005c8250("bvartl",2,"bdsp4",0,0);
    *(undefined4 *)(param_1 + 0xfc) = uVar2;
    uVar2 = FUN_005c8250("bvartl",2,"bdsp4",0,0);
    *(undefined4 *)(param_1 + 0x100) = uVar2;
    uVar2 = FUN_005c8250("bvtank",2,"bdsp4",0,0);
    *(undefined4 *)(param_1 + 0x104) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0xfc),*(undefined4 *)(param_1 + 0xc4),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x100),*(undefined4 *)(param_1 + 200),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x104),*(undefined4 *)(param_1 + 0xfc),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x104),1);
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
LAB_0055701f:
  if (((*(char *)(param_1 + 0x5c) == '\x01') && (*(char *)(param_1 + 0x5b) == '\x01')) &&
     (*(char *)(param_1 + 0x5e) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0xf0);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xf4);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0xfc);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x100);
          if (cVar1 == '\0') {
            uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
            *(undefined4 *)(param_1 + 0x108) = uVar2;
            uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
            *(undefined4 *)(param_1 + 0x10c) = uVar2;
            uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
            *(undefined4 *)(param_1 + 0x110) = uVar2;
            uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
            *(undefined4 *)(param_1 + 0x114) = uVar2;
            *(undefined1 *)(param_1 + 0x5e) = 1;
            FUN_005cb820(*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0xc4),1);
            FUN_005cb820(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0xc4),1);
            FUN_005cb820(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 200),1);
            FUN_005cb820(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 200),1);
          }
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x5d) == '\0') {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa4),*(undefined4 *)(param_1 + 0x1a4));
    if (550.0 <= (float)fVar4) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xc4),*(undefined4 *)(param_1 + 0x1a4)
                                   );
      if (550.0 <= (float)fVar4) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 200),
                                      *(undefined4 *)(param_1 + 0x1a4));
        if (550.0 <= (float)fVar4) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xcc),
                                        *(undefined4 *)(param_1 + 0x1a4));
          if (550.0 <= (float)fVar4) goto LAB_00557358;
        }
      }
    }
    uVar2 = FUN_005c8250("bvraz",2,"bdsp5",0,0);
    *(undefined4 *)(param_1 + 0x124) = uVar2;
    uVar2 = FUN_005c8250("bvraz",2,"bdsp5",0,0);
    *(undefined4 *)(param_1 + 0x128) = uVar2;
    uVar2 = FUN_005c8250("bvraz",2,"bdsp5",0,0);
    *(undefined4 *)(param_1 + 300) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0x124),*(undefined4 *)(param_1 + 0xc4),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x128),*(undefined4 *)(param_1 + 200),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 300),*(undefined4 *)(param_1 + 0xcc),1);
    *(undefined1 *)(param_1 + 0x5d) = 1;
  }
LAB_00557358:
  if (*(char *)(param_1 + 0x5e) == '\0') {
    uVar2 = FUN_005c9d10("bdspmain",1);
    *(undefined4 *)(param_1 + 0x168) = uVar2;
  }
  fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x168),"bdspmain",0);
  if (((float)fVar4 < 420.0) && (*(char *)(param_1 + 0x5e) == '\0')) {
    iVar3 = FUN_005c8800(*(undefined4 *)(param_1 + 0x168));
    if (iVar3 == 1) {
      uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x108) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x10c) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x110) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x114) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x118) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x11c) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x120) = uVar2;
      *(undefined1 *)(param_1 + 0x5e) = 1;
    }
  }
  fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa4),"bdnet4",0);
  if (((float)fVar4 < 550.0) && (*(char *)(param_1 + 0x65) == '\0')) {
    uVar2 = FUN_005c8250("bvtank",2,"bdnet4",0,0);
    *(undefined4 *)(param_1 + 0x1fc) = uVar2;
    uVar2 = FUN_005c8250("bvtank",2,"bdnet4",0,0);
    *(undefined4 *)(param_1 + 0x200) = uVar2;
    uVar2 = FUN_005c8250("bvraz",2,"bdnet4",0,0);
    *(undefined4 *)(param_1 + 0x204) = uVar2;
    uVar2 = FUN_005c8250("bvraz",2,"bdnet4",0,0);
    *(undefined4 *)(param_1 + 0x208) = uVar2;
    uVar2 = FUN_005c8250("bvraz",2,"bdnet4",0,0);
    *(undefined4 *)(param_1 + 0x20c) = uVar2;
    uVar2 = FUN_005c8250("bvraz",2,"bdnet4",0,0);
    *(undefined4 *)(param_1 + 0x210) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0x1fc),*(undefined4 *)(param_1 + 0xc4),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1fc),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x200),*(undefined4 *)(param_1 + 0xc4),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x200),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x204),*(undefined4 *)(param_1 + 200),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x204),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x208),*(undefined4 *)(param_1 + 200),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x208),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x20c),*(undefined4 *)(param_1 + 0xcc),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x20c),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x210),*(undefined4 *)(param_1 + 0xcc),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x210),1);
    *(undefined1 *)(param_1 + 0x65) = 1;
    uVar2 = FUN_005c8250("bvartl",2,"bdsp4",0,0);
    *(undefined4 *)(param_1 + 0xfc) = uVar2;
    uVar2 = FUN_005c8250("bvartl",2,"bdsp4",0,0);
    *(undefined4 *)(param_1 + 0x100) = uVar2;
    uVar2 = FUN_005c8250("bvtank",2,"bdsp4",0,0);
    *(undefined4 *)(param_1 + 0x104) = uVar2;
    *(undefined1 *)(param_1 + 0x5b) = 1;
    FUN_005cb820(*(undefined4 *)(param_1 + 0xfc),*(undefined4 *)(param_1 + 0xcc),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x100),*(undefined4 *)(param_1 + 0xfc),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x104),*(undefined4 *)(param_1 + 0xfc),1);
  }
  if ((*(char *)(param_1 + 0x65) == '\x01') && (*(char *)(param_1 + 0x57) == '\0')) {
    uVar2 = FUN_005ca150(*(undefined4 *)(param_1 + 0x1fc));
    *(undefined4 *)(param_1 + 0x1b4) = uVar2;
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1b4),*(undefined4 *)(param_1 + 0x1fc));
  if (((float)fVar4 < 400.0) && (*(char *)(param_1 + 0x57) == '\0')) {
    FUN_00437d30("misns209.wav");
    *(undefined1 *)(param_1 + 0x57) = 1;
  }
  fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa4),"bdnet9",0);
  if ((float)fVar4 < 410.0) {
LAB_00557891:
    if (*(char *)(param_1 + 0x66) == '\0') {
      uVar2 = FUN_005c8250(&DAT_00878c18,2,"bdnet7",0,0);
      *(undefined4 *)(param_1 + 0x1d4) = uVar2;
      uVar2 = FUN_005c8250(&DAT_00878c18,2,"bdnet8",0,0);
      *(undefined4 *)(param_1 + 0x1d8) = uVar2;
      uVar2 = FUN_005c8250(&DAT_00878c18,2,"bdnet9",0,0);
      *(undefined4 *)(param_1 + 0x1dc) = uVar2;
      uVar2 = FUN_005c8250(&DAT_00878c18,2,"bdnet10",0,0);
      *(undefined4 *)(param_1 + 0x1e0) = uVar2;
      uVar2 = FUN_005c8250(&DAT_00878c18,2,"bdnet11",0,0);
      *(undefined4 *)(param_1 + 0x1e4) = uVar2;
      uVar2 = FUN_005c8250(&DAT_00878c18,2,"bdnet12",0,0);
      *(undefined4 *)(param_1 + 0x1e8) = uVar2;
      uVar2 = FUN_005c8250(&DAT_00878c18,2,"bdnet13",0,0);
      *(undefined4 *)(param_1 + 0x1ec) = uVar2;
      uVar2 = FUN_005c8250(&DAT_00878c18,2,"bdnet14",0,0);
      *(undefined4 *)(param_1 + 0x1f0) = uVar2;
      *(undefined1 *)(param_1 + 0x66) = 1;
      FUN_00437d30("misns207.wav");
    }
  }
  else {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa4),"bdnet12",0);
    if ((float)fVar4 < 410.0) goto LAB_00557891;
  }
  if (*(char *)(param_1 + 0x66) == '\x01') {
    uVar2 = FUN_005c9d10("bdnet7",1);
    *(undefined4 *)(param_1 + 0x21c) = uVar2;
    uVar2 = FUN_005c9d10("bdnet8",1);
    *(undefined4 *)(param_1 + 0x220) = uVar2;
    uVar2 = FUN_005c9d10("bdnet9",1);
    *(undefined4 *)(param_1 + 0x224) = uVar2;
    uVar2 = FUN_005c9d10("bdnet10",1);
    *(undefined4 *)(param_1 + 0x228) = uVar2;
    uVar2 = FUN_005c9d10("bdnet11",1);
    *(undefined4 *)(param_1 + 0x22c) = uVar2;
    uVar2 = FUN_005c9d10("bdnet12",1);
    *(undefined4 *)(param_1 + 0x230) = uVar2;
    uVar2 = FUN_005c9d10("bdnet13",1);
    *(undefined4 *)(param_1 + 0x234) = uVar2;
    uVar2 = FUN_005c9d10("bdnet14",1);
    *(undefined4 *)(param_1 + 0x238) = uVar2;
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x21c),"bdnet7",0);
    if (20.0 <= (float)fVar4) {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x220),"bdnet8",0);
      if (20.0 <= (float)fVar4) {
        fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x224),"bdnet9",0);
        if (20.0 <= (float)fVar4) {
          fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x228),"bdnet10",0);
          if (20.0 <= (float)fVar4) {
            fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x22c),"bdnet11",0);
            if (20.0 <= (float)fVar4) {
              fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x230),"bdnet12",0);
              if (20.0 <= (float)fVar4) {
                fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x234),"bdnet13",0);
                if (20.0 <= (float)fVar4) {
                  fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x238),"bdnet14",0);
                  if (20.0 <= (float)fVar4) goto LAB_00557cc7;
                }
              }
            }
          }
        }
      }
    }
    if (*(char *)(param_1 + 0x5b) == '\0') {
      uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
      *(undefined4 *)(param_1 + 0xf0) = uVar2;
      uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
      *(undefined4 *)(param_1 + 0xf4) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdsp3",0,0);
      *(undefined4 *)(param_1 + 0xf8) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xcc),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 200),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xf0),1);
      *(undefined1 *)(param_1 + 0x5b) = 1;
    }
  }
LAB_00557cc7:
  if (*(char *)(param_1 + 0x66) == '\x01') {
    cVar1 = FUN_005c84d0(param_1 + 0x1d4);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x1d8);
      if (cVar1 != '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x1dc);
        if (cVar1 != '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x1e0);
          if (cVar1 != '\0') {
            cVar1 = FUN_005c84d0(param_1 + 0x1e4);
            if (cVar1 != '\0') {
              cVar1 = FUN_005c84d0(param_1 + 0x1e8);
              if (cVar1 != '\0') {
                cVar1 = FUN_005c84d0(param_1 + 0x1ec);
                if (cVar1 != '\0') {
                  cVar1 = FUN_005c84d0(param_1 + 0x1f0);
                  if (cVar1 != '\0') goto LAB_00557de4;
                }
              }
            }
          }
        }
      }
    }
    if (*(char *)(param_1 + 100) == '\0') {
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x84) = (float)fVar4 + 45.0;
      *(undefined1 *)(param_1 + 100) = 1;
      FUN_00437d30("misns208.wav");
    }
  }
LAB_00557de4:
  fVar4 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x84) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x84)) &&
     (*(char *)(param_1 + 0x6b) == '\0')) {
    uVar2 = FUN_005c8250("bvraz",2,"bdspmain",0,0);
    *(undefined4 *)(param_1 + 0x214) = uVar2;
    uVar2 = FUN_005c8250("bvraz",2,"bdspmain",0,0);
    *(undefined4 *)(param_1 + 0x218) = uVar2;
    *(undefined1 *)(param_1 + 0x6b) = 1;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x214),"bdnet9",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x218),"bdnet12",1);
  }
  if ((*(char *)(param_1 + 0x6b) == '\x01') && (*(char *)(param_1 + 0x6c) == '\0')) {
    uVar2 = FUN_005ca150(*(undefined4 *)(param_1 + 0x214));
    *(undefined4 *)(param_1 + 0x240) = uVar2;
    uVar2 = FUN_005ca150(*(undefined4 *)(param_1 + 0x218));
    *(undefined4 *)(param_1 + 0x23c) = uVar2;
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x23c),*(undefined4 *)(param_1 + 0x214))
    ;
    if (((float)fVar4 < 50.0) && (*(char *)(param_1 + 0x5b) == '\0')) {
      if (*(char *)(param_1 + 0x5b) == '\0') {
        uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf0) = uVar2;
        uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf4) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf8) = uVar2;
        FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xcc),1);
        FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 200),1);
        FUN_005cbc20(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xf0),1);
        *(undefined1 *)(param_1 + 0x5b) = 1;
      }
      if (*(char *)(param_1 + 0x5b) == '\x01') {
        cVar1 = FUN_005c84d0(param_1 + 0xf0);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0x23c),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0xf4);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0x23c),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0xf8);
        if (cVar1 != '\0') {
          FUN_005cbc20(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xf0),1);
        }
        *(undefined1 *)(param_1 + 0x5b) = 1;
      }
    }
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x23c),*(undefined4 *)(param_1 + 0x214))
    ;
    if (((float)fVar4 < 50.0) && (*(char *)(param_1 + 0x5b) == '\0')) {
      if (*(char *)(param_1 + 0x5b) == '\0') {
        uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf0) = uVar2;
        uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf4) = uVar2;
        uVar2 = FUN_005c8250("bvtank",2,"bdsp3",0,0);
        *(undefined4 *)(param_1 + 0xf8) = uVar2;
        FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0x240),1);
        FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0x240),1);
        FUN_005cbc20(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xf0),1);
        *(undefined1 *)(param_1 + 0x5b) = 1;
      }
      if (*(char *)(param_1 + 0x5b) == '\x01') {
        cVar1 = FUN_005c84d0(param_1 + 0xf0);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0x240),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0xf4);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0x240),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0xf8);
        if (cVar1 != '\0') {
          FUN_005cbc20(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0x240),1);
        }
      }
      *(undefined1 *)(param_1 + 0x5b) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x6b) == '\x01') && (*(char *)(param_1 + 0x6c) == '\0')) {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x214),"bdnet9",0);
    if (20.0 <= (float)fVar4) {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x218),"bdnet12",0);
      if (20.0 <= (float)fVar4) goto LAB_00558567;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x108) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x10c) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x110) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x114) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x118) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x11c) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"bdspmain",0,0);
      *(undefined4 *)(param_1 + 0x120) = uVar2;
      *(undefined1 *)(param_1 + 0x5e) = 1;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0xc4),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x108),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0xc4),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 200),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x110),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 200),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x114),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0xcc),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x118),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0xcc),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x11c),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x120),*(undefined4 *)(param_1 + 0xc4),1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x120),1);
    }
  }
LAB_00558567:
  if ((*(char *)(param_1 + 0x6b) == '\x01') && (*(char *)(param_1 + 0x6c) == '\0')) {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x214),"bdnet9",0);
    if (20.0 <= (float)fVar4) {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x218),"bdnet12",0);
      if (20.0 <= (float)fVar4) goto LAB_00558779;
    }
    if (*(char *)(param_1 + 0x5b) == '\0') {
      uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
      *(undefined4 *)(param_1 + 0xf0) = uVar2;
      uVar2 = FUN_005c8250("bvartl",2,"bdsp3",0,0);
      *(undefined4 *)(param_1 + 0xf4) = uVar2;
      uVar2 = FUN_005c8250("bvtank",2,"bdsp3",0,0);
      *(undefined4 *)(param_1 + 0xf8) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xcc),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 200),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xf0),1);
      *(undefined1 *)(param_1 + 0x5b) = 1;
    }
    if (*(char *)(param_1 + 0x5b) == '\x01') {
      cVar1 = FUN_005c84d0(param_1 + 0xf0);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xcc),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0xf4);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 200),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0xf8);
      if (cVar1 != '\0') {
        FUN_005cbc20(*(undefined4 *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0xf0),1);
      }
    }
    *(undefined1 *)(param_1 + 0x5b) = 1;
  }
LAB_00558779:
  cVar1 = FUN_005c84d0(param_1 + 0xc4);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x58) == '\0')) {
    uVar2 = FUN_00437d30("misns212.wav");
    *(undefined4 *)(param_1 + 0x25c) = uVar2;
    *(undefined1 *)(param_1 + 0x58) = 1;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 200);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x58) == '\0')) {
    uVar2 = FUN_00437d30("misns212.wav");
    *(undefined4 *)(param_1 + 0x25c) = uVar2;
    *(undefined1 *)(param_1 + 0x58) = 1;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xcc);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x58) == '\0')) {
    uVar2 = FUN_00437d30("misns212.wav");
    *(undefined4 *)(param_1 + 0x25c) = uVar2;
    *(undefined1 *)(param_1 + 0x58) = 1;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  if (*(char *)(param_1 + 0x58) == '\x01') {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x25c));
    if (cVar1 != '\0') {
      fVar4 = (float10)FUN_004b1670("misns2l1.des");
      FUN_0045c0f0((float)fVar4);
    }
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xc4),*(undefined4 *)(param_1 + 0x1a4));
  if (((float)fVar4 < 100.0) && (*(char *)(param_1 + 0x6e) == '\0')) {
    FUN_00437d30("misns216.wav");
    *(undefined1 *)(param_1 + 0x6e) = 1;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x1a4));
  if (((float)fVar4 < 100.0) && (*(char *)(param_1 + 0x6f) == '\0')) {
    FUN_00437d30("misns217.wav");
    *(undefined1 *)(param_1 + 0x6f) = 1;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xcc),*(undefined4 *)(param_1 + 0x1a4));
  if (((float)fVar4 < 100.0) && (*(char *)(param_1 + 0x70) == '\0')) {
    FUN_00437d30("misns218.wav");
    *(undefined1 *)(param_1 + 0x70) = 1;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  if ((((*(char *)(param_1 + 0x56) == '\0') && (*(char *)(param_1 + 0x6e) == '\x01')) &&
      (*(char *)(param_1 + 0x6f) == '\x01')) && (*(char *)(param_1 + 0x70) == '\x01')) {
    *(undefined1 *)(param_1 + 0x56) = 1;
    uVar2 = FUN_00437d30("misns213.wav");
    *(undefined4 *)(param_1 + 0x268) = uVar2;
    uVar2 = FUN_00437d30("misns214.wav");
    *(undefined4 *)(param_1 + 0x260) = uVar2;
    uVar2 = FUN_00437d30("misns215.wav");
    *(undefined4 *)(param_1 + 0x264) = uVar2;
    cVar1 = FUN_005c84d0(param_1 + 0xd8);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xd8),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xdc);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xdc),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xe0);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xe0),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xe4);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xe4),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xe8);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xe8),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xec);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xec),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xf0);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xf0),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xf4);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xf4),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xf8);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xf8),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xfc);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0xfc),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x100);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x100),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x104);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x104),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x108);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x108),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x10c);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x10c),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x110);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x110),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x114);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x114),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x118);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x118),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x11c);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x11c),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x120);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x120),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x124);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x124),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x128);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x128),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 300);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 300),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x130);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x130),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x134);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x134),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x138);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x138),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x13c);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x13c),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x140);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x140),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x144);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x144),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x148);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x148),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x14c);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x14c),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x150);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x150),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x154);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x154),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x158);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x158),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x15c);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x15c),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x160);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x160),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x164);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x164),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1fc);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x1fc),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x200);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x200),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x204);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x204),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x208);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x208),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x20c);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x20c),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x210);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x210),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x214);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x214),"bdspmain",1000);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x218);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x218),"bdspmain",1000);
    }
  }
  if (*(char *)(param_1 + 0x56) == '\x01') {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x268));
    if (cVar1 != '\0') {
      cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x260));
      if (cVar1 != '\0') {
        cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x264));
        if (cVar1 != '\0') {
          fVar4 = (float10)FUN_004b1670("misns2w1.des");
          FUN_0045c110((float)fVar4 + 0.0);
        }
      }
    }
  }
  return;
}

