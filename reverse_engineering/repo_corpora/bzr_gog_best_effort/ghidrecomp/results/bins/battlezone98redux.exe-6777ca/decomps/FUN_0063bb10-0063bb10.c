
void __fastcall FUN_0063bb10(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  int local_14;
  int local_10;
  int local_c;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x78) = uVar2;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cb2d0("bdmisn07.aip",2);
    FUN_005cadd0(1,8);
    FUN_005cacb0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x5c) = (float)fVar4 + 5.0;
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x5c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x5c)) {
    *(undefined4 *)(param_1 + 0x5c) = 0x497423fe;
    uVar2 = FUN_00437d30("bd07001.wav");
    *(undefined4 *)(param_1 + 0xe4) = uVar2;
  }
  if (*(int *)(param_1 + 0xe4) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xe4));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xe4) = 0;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x60) = (float)fVar4 + 1.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x60) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x60)) {
    *(undefined4 *)(param_1 + 0x60) = 0x497423fe;
    uVar2 = FUN_00437d30("bd07002.wav");
    *(undefined4 *)(param_1 + 0xe8) = uVar2;
  }
  if (*(int *)(param_1 + 0xe8) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xe8));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 2.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
    *(undefined4 *)(param_1 + 100) = 0x497423fe;
    uVar2 = FUN_00437d30("bd07003.wav");
    *(undefined4 *)(param_1 + 0xec) = uVar2;
  }
  if (*(int *)(param_1 + 0xec) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xec));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_004f6aa0();
      FUN_004f6ab0("bd07001.otf",DAT_0091755c,0x41000000,0);
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x68) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x68)) {
    *(undefined4 *)(param_1 + 0x68) = 0x497423fe;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x6c) = (float)fVar4 + 30.0;
    for (local_c = 0; local_c < 3; local_c = local_c + 1) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xb4 + local_c * 4),"attack_path1",1);
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x6c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x6c)) {
    *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    for (local_c = 0; local_c < 8; local_c = local_c + 1) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc0 + local_c * 4),"attack_path2",1);
    }
    *(undefined1 *)(param_1 + 0x58) = 1;
  }
  if ((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 0x55) == '\0')) {
    *(undefined1 *)(param_1 + 0x55) = 1;
    for (local_c = 0; local_c < 3; local_c = local_c + 1) {
      cVar1 = FUN_005c84d0(param_1 + 0xb4 + local_c * 4);
      if (cVar1 != '\0') {
        *(undefined1 *)(param_1 + 0x55) = 0;
        break;
      }
    }
    for (local_c = 0; local_c < 8; local_c = local_c + 1) {
      cVar1 = FUN_005c84d0(param_1 + 0xc0 + local_c * 4);
      if (cVar1 != '\0') {
        *(undefined1 *)(param_1 + 0x55) = 0;
        break;
      }
    }
    if (*(char *)(param_1 + 0x55) != '\0') {
      FUN_004f6aa0();
      FUN_004f6ab0("bd07002.otf",DAT_0091755c,0x41000000,0);
      FUN_00437d30("bd07004.wav");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x70) = (float)fVar4 + 1.0;
      iVar3 = FUN_005cae10(2);
      if (iVar3 < 0x28) {
        FUN_005cadd0(2,0x28);
      }
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x70)) {
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar4 + 300.0;
    for (local_c = 0; local_c < 3; local_c = local_c + 1) {
      uVar2 = FUN_005c8250("cvfigh",2,"annoy_1",0,0);
      FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0x78),1);
    }
    for (local_c = 0; local_c < 2; local_c = local_c + 1) {
      uVar2 = FUN_005c8250("cvltnk",2,"annoy_1",0,0);
      FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0x78),1);
    }
  }
  if ((*(char *)(param_1 + 0x5a) == '\0') && (*(char *)(param_1 + 0x59) == '\0')) {
    *(undefined1 *)(param_1 + 0x5a) = 1;
    for (local_10 = 0; local_10 < 0xb; local_10 = local_10 + 1) {
      cVar1 = FUN_005c84d0(param_1 + 0x7c + local_10 * 4);
      if (cVar1 != '\0') {
        *(undefined1 *)(param_1 + 0x5a) = 0;
        break;
      }
    }
    if (*(char *)(param_1 + 0x5a) != '\0') {
      FUN_004f6aa0();
      FUN_004f6ab0("bd07002.otf",DAT_009175b0,0x41000000,0);
      fVar4 = (float10)FUN_004b1670("bd07win.des");
      FUN_0045c110((float)fVar4 + 1.0);
    }
  }
  if ((*(char *)(param_1 + 0x59) == '\0') && (*(char *)(param_1 + 0x5a) == '\0')) {
    *(undefined1 *)(param_1 + 0x59) = 1;
    for (local_14 = 0; local_14 < 3; local_14 = local_14 + 1) {
      fVar4 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa8 + local_14 * 4));
      if (0.0 < (float)fVar4) {
        *(undefined1 *)(param_1 + 0x59) = 0;
        break;
      }
    }
    if (*(char *)(param_1 + 0x59) != '\0') {
      fVar4 = (float10)FUN_004b1670("bd07lose.des");
      FUN_0045c0f0((float)fVar4 + 1.0);
    }
  }
  return;
}

