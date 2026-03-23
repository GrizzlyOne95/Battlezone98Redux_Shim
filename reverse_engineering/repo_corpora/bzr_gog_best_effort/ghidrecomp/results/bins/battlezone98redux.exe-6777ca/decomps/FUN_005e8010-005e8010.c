
void __fastcall FUN_005e8010(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  
  if (*(char *)(param_1 + 0x55) == '\0') {
    iVar2 = FUN_004f2de0();
    if (iVar2 != 0) {
      FUN_004f49c0(0x1c);
    }
    FUN_00437d30("tran0301.wav");
    iVar2 = FUN_004f2de0();
    if (iVar2 == 0) {
      uVar3 = FUN_00437d30("tran0302.wav");
      *(undefined4 *)(param_1 + 0xa0) = uVar3;
    }
    else {
      FUN_004f49c0(0x1d);
    }
    uVar3 = FUN_005c7e90("eggeizr111_geyser");
    *(undefined4 *)(param_1 + 0x80) = uVar3;
    uVar3 = FUN_005c7e90("avrecy-1_recycler");
    *(undefined4 *)(param_1 + 0x84) = uVar3;
    uVar3 = FUN_005c7e90("avfigh-1_wingman");
    *(undefined4 *)(param_1 + 0x7c) = uVar3;
    FUN_005c8a50(*(undefined4 *)(param_1 + 0x7c),&DAT_008a1ad8);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x7c),0);
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x84));
    FUN_005c9640(*(undefined4 *)(param_1 + 0x84),"recycler");
    FUN_00462630(*(undefined4 *)(param_1 + 0x84));
    FUN_005cadd0(1,7);
    FUN_004f6aa0();
    FUN_004f6ab0("tran0301.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("tran0302.otf",DAT_0091755c,0x41000000,0);
    FUN_0041e220(200,400,0x41e80000);
    *(undefined1 *)(param_1 + 0x55) = 1;
  }
  if (((*(char *)(param_1 + 0x55) != '\0') && (*(char *)(param_1 + 0x61) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0')) {
    FUN_00462630(*(undefined4 *)(param_1 + 0x84));
    cVar1 = FUN_00492d20();
    if (cVar1 != '\0') {
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa0));
      FUN_0041e220(200,0x307,0x41800000);
      iVar2 = FUN_004f2de0();
      if (iVar2 == 0) {
        uVar3 = FUN_00437d30("tran0303.wav");
        *(undefined4 *)(param_1 + 0xa0) = uVar3;
      }
      else {
        FUN_004f49c0(0x1e);
      }
      FUN_005c9610(*(undefined4 *)(param_1 + 0x84));
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x80));
      FUN_005c9640(*(undefined4 *)(param_1 + 0x80),"Check Point 1");
      *(undefined1 *)(param_1 + 0x61) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x61) != '\0') && (*(char *)(param_1 + 0x62) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0' &&
      (cVar1 = FUN_005caec0(*(undefined4 *)(param_1 + 0x84)), cVar1 == '\0')))) {
    FUN_0041e220(200,400,0x41600000);
    FUN_00437d80(*(undefined4 *)(param_1 + 0xa0));
    iVar2 = FUN_004f2de0();
    if (iVar2 != 0) {
      FUN_004f49c0(0x1f);
    }
    uVar3 = FUN_00437d30("tran0304.wav");
    *(undefined4 *)(param_1 + 0xa0) = uVar3;
    *(undefined1 *)(param_1 + 0x62) = 1;
  }
  if (((*(char *)(param_1 + 0x62) == '\0') || (*(char *)(param_1 + 99) != '\0')) ||
     ((cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 == '\0' ||
      (cVar1 = FUN_005caf90(*(undefined4 *)(param_1 + 0x84)), cVar1 == '\0')))) {
    if (*(char *)(param_1 + 99) == '\0') {
      uVar3 = FUN_005c7fb0();
      cVar1 = FUN_005ce520(*(undefined4 *)(param_1 + 0x84),uVar3);
      if (cVar1 != '\0') {
        FUN_0041e260();
      }
    }
  }
  else {
    iVar2 = FUN_005e6960();
    if (iVar2 == 5) {
      FUN_0041e220(200,0x5a,0);
    }
    else {
      FUN_0041e260();
    }
  }
  if (((*(char *)(param_1 + 0x62) != '\0') && (*(char *)(param_1 + 99) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0')) {
    iVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x84));
    iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x80));
    puVar5 = (undefined4 *)(**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
    puVar5 = (undefined4 *)(**(code **)(*(int *)(iVar4 + 0x18) + 0xc))(*puVar5,puVar5[1],puVar5[2]);
    fVar6 = (float10)FUN_004620b0(*puVar5,puVar5[1],puVar5[2]);
    if ((float)fVar6 < 40000.0) {
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa0));
      iVar2 = FUN_004f2de0();
      if (iVar2 != 0) {
        FUN_004f49c0(0x20);
      }
      uVar3 = FUN_00437d30("tran0305.wav");
      *(undefined4 *)(param_1 + 0xa0) = uVar3;
      *(undefined1 *)(param_1 + 99) = 1;
      FUN_0041e220(200,400,0x40a00000);
    }
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 100) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0')) {
    FUN_00462630(*(undefined4 *)(param_1 + 0x84));
    cVar1 = FUN_00492d20();
    if (cVar1 != '\0') {
      FUN_0041e220(200,900,0x41600000);
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa0));
      iVar2 = FUN_004f2de0();
      if (iVar2 == 0) {
        uVar3 = FUN_00437d30("tran0306.wav");
        *(undefined4 *)(param_1 + 0xa0) = uVar3;
      }
      else {
        FUN_004f49c0(0x21);
      }
      *(undefined1 *)(param_1 + 100) = 1;
    }
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x65) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0' &&
      (cVar1 = FUN_005caec0(*(undefined4 *)(param_1 + 0x84)), cVar1 != '\0')))) {
    FUN_0041e220(200,400,0);
    FUN_005c9610(*(undefined4 *)(param_1 + 0x80));
    FUN_004f6aa0();
    FUN_004f6ab0("tran0301.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("tran0302.otf",DAT_0091755c,0x41000000,0);
    FUN_00437d80(*(undefined4 *)(param_1 + 0xa0));
    iVar2 = FUN_004f2de0();
    if (iVar2 != 0) {
      FUN_004f49c0(0x22);
    }
    uVar3 = FUN_00437d30("tran0307.wav");
    *(undefined4 *)(param_1 + 0xa0) = uVar3;
    *(undefined1 *)(param_1 + 0x65) = 1;
  }
  if ((*(char *)(param_1 + 0x65) != '\0') && (*(char *)(param_1 + 0x66) == '\0')) {
    FUN_00462630(*(undefined4 *)(param_1 + 0x84));
    cVar1 = FUN_00492d20();
    if (cVar1 != '\0') {
      FUN_0041e220(200,0x5a,0);
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa0));
      iVar2 = FUN_004f2de0();
      if (iVar2 == 0) {
        uVar3 = FUN_00437d30("tran0309.wav");
        *(undefined4 *)(param_1 + 0xa0) = uVar3;
      }
      else {
        FUN_004f49c0(0x24);
      }
      *(undefined1 *)(param_1 + 0x66) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x7c);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x67) == '\0')) {
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0x7c),0x42480000);
  }
  if (((*(char *)(param_1 + 0x65) != '\0') && (*(char *)(param_1 + 0x67) == '\0')) &&
     (*(char *)(param_1 + 0x54) != '\0')) {
    FUN_0041e260();
    FUN_00437d80(*(undefined4 *)(param_1 + 0xa0));
    iVar2 = FUN_004f2de0();
    if (iVar2 != 0) {
      FUN_004f49c0(0x25);
    }
    uVar3 = FUN_00437d30("tran0310.wav");
    *(undefined4 *)(param_1 + 0xa0) = uVar3;
    *(undefined1 *)(param_1 + 0x67) = 1;
    fVar6 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
  }
  if ((*(char *)(param_1 + 0x6a) == '\0') &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 == '\0' ||
      ((*(char *)(param_1 + 0x67) != '\0' && (cVar1 = FUN_005c84d0(param_1 + 0x78), cVar1 == '\0')))
      ))) {
    *(undefined1 *)(param_1 + 0x6a) = 1;
    FUN_00437d80(*(undefined4 *)(param_1 + 0xa0));
    iVar2 = FUN_004f2de0();
    if (iVar2 != 0) {
      FUN_004f49c0(0x26);
    }
    uVar3 = FUN_00437d30("tran0313.wav");
    *(undefined4 *)(param_1 + 0xa0) = uVar3;
    fVar6 = (float10)FUN_004b1670("tran03l1.des");
    FUN_0045c0f0((float)fVar6 + 10.0);
  }
  fVar6 = (float10)FUN_00822d80();
  if (*(float *)(param_1 + 0x70) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x70)) {
    cVar1 = FUN_005c84d0(param_1 + 0x7c);
    if (cVar1 != '\0') {
      iVar2 = FUN_004f2de0();
      if (iVar2 != 0) {
        FUN_004f49c0(0x23);
      }
      FUN_00437d30("tran0308.wav");
      FUN_005cb820(*(undefined4 *)(param_1 + 0x7c),*(undefined4 *)(param_1 + 0x78),1);
    }
    *(undefined4 *)(param_1 + 0x70) = 0x47c34f80;
  }
  if (((*(char *)(param_1 + 0x67) != '\0') && (*(char *)(param_1 + 0x68) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x7c), cVar1 == '\0')) {
    iVar2 = FUN_004f2de0();
    if (iVar2 != 0) {
      FUN_004f49c0(0x27);
    }
    FUN_00437d30("tran0314.wav");
    *(undefined1 *)(param_1 + 0x68) = 1;
    FUN_004f6aa0();
    FUN_004f6ab0("tran0301.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("tran0302.otf",DAT_009175b0,0x41000000,0);
  }
  if ((*(char *)(param_1 + 0x68) != '\0') && (*(char *)(param_1 + 0x69) == '\0')) {
    FUN_00462630(*(undefined4 *)(param_1 + 0x84));
    FUN_00462590();
    iVar2 = FUN_005e10b0();
    if (8 < iVar2) {
      iVar2 = FUN_004f2de0();
      if (iVar2 != 0) {
        FUN_004f49c0(0x28);
      }
      FUN_00437d30("tran0315.wav");
      *(undefined1 *)(param_1 + 0x69) = 1;
      fVar6 = (float10)FUN_004b1670("tran03w1.des");
      FUN_0045c110((float)fVar6 + 10.0);
    }
  }
  return;
}

