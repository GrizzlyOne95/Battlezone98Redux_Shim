
void __fastcall FUN_005e9580(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  if (*(char *)(param_1 + 0x56) == '\0') {
    FUN_0041e220(200,400,0);
    uVar2 = FUN_005c7e90("avturr12_turrettank");
    *(undefined4 *)(param_1 + 0x7c) = uVar2;
    FUN_005c8a50(*(undefined4 *)(param_1 + 0x7c),&DAT_008a1ad8);
    uVar2 = FUN_005c7e90("avturr-1_turrettank");
    *(undefined4 *)(param_1 + 0x80) = uVar2;
    FUN_005c8a50(*(undefined4 *)(param_1 + 0x80),&DAT_008a1ad8);
    uVar2 = FUN_005c7e90("avrecy-1_recycler");
    *(undefined4 *)(param_1 + 0x84) = uVar2;
    uVar2 = FUN_005c7e90("apcamr-1_camerapod");
    *(undefined4 *)(param_1 + 0x8c) = uVar2;
    uVar2 = FUN_005c7e90("player-1_hover");
    *(undefined4 *)(param_1 + 0x78) = uVar2;
    FUN_00462630(*(undefined4 *)(param_1 + 0x84));
    FUN_005cadd0(1,0x1e);
    iVar3 = FUN_004f2de0();
    if (iVar3 == 1) {
      FUN_004f49c0(0x29);
    }
    FUN_00437d30("tran0401.wav");
    FUN_00437d30("tran0402.wav");
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0424.wav");
    }
    else {
      FUN_004f49c0(0x37);
    }
    FUN_004f6aa0();
    FUN_004f6ab0("tran0401.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("tran0402.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x56) = 1;
  }
  if (((*(char *)(param_1 + 0x57) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0'))
     && (cVar1 = FUN_005caf90(*(undefined4 *)(param_1 + 0x84)), cVar1 != '\0')) {
    FUN_0041e220(200,0xe1,0);
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0425.wav");
    }
    else {
      FUN_004f49c0(0x38);
    }
    *(undefined1 *)(param_1 + 0x57) = 1;
  }
  if (((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x58) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0' &&
      (cVar1 = FUN_005caec0(*(undefined4 *)(param_1 + 0x84)), cVar1 != '\0')))) {
    FUN_0041e220(200,400,0);
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0424.wav");
    }
    else {
      FUN_004f49c0(0x37);
    }
    *(undefined1 *)(param_1 + 0x58) = 1;
  }
  if (((*(char *)(param_1 + 0x58) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0'))
     && ((cVar1 = FUN_005caf90(*(undefined4 *)(param_1 + 0x84)), cVar1 != '\0' &&
         (*(char *)(param_1 + 0x67) == '\0')))) {
    FUN_0041e220(200,0x5a,0);
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0406.wav");
    }
    else {
      FUN_004f49c0(0x2a);
    }
    *(undefined1 *)(param_1 + 0x67) = 1;
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
  if ((((*(char *)(param_1 + 0x5c) != '\0') && (*(char *)(param_1 + 0x5d) == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 != '\0')) &&
     ((cVar1 = FUN_005caf90(*(undefined4 *)(param_1 + 0x84)), cVar1 == '\0' &&
      (cVar1 = FUN_005cb550(*(undefined4 *)(param_1 + 0x84)), cVar1 != '\0')))) {
    iVar3 = FUN_004f2de0();
    if (iVar3 == 1) {
      FUN_004f49c0(0x2b);
    }
    FUN_00437d30("tran0407.wav");
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x70) = (float)fVar4 + 5.0;
    *(undefined1 *)(param_1 + 0x5d) = 1;
  }
  if (((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x5e) == '\0')) &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0x70) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x70))) {
    FUN_0041e220(200,0x145,0);
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0408.wav");
    }
    else {
      FUN_004f49c0(0x2c);
    }
    *(undefined4 *)(param_1 + 0x70) = 0x47c34f80;
  }
  if (((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x5e) == '\0')) &&
     (iVar3 = FUN_005c8910(), iVar3 == *(int *)(param_1 + 0x8c))) {
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0409.wav");
    }
    else {
      FUN_004f49c0(0x2d);
    }
    *(undefined1 *)(param_1 + 0x5e) = 1;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x70) = (float)fVar4 + 3.0;
  }
  if (((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 0x5f) == '\0')) &&
     ((fVar4 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x70) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x70) &&
      (*(char *)(param_1 + 0x55) != '\0')))) {
    FUN_0041e220(200,0x5a,0);
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0410.wav");
    }
    else {
      FUN_004f49c0(0x2e);
    }
    *(undefined1 *)(param_1 + 0x5f) = 1;
    *(undefined4 *)(param_1 + 0x70) = 0x47c34f80;
  }
  if (((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x5e) != '\0')) &&
     ((*(char *)(param_1 + 0x55) != '\0' &&
      ((cVar1 = FUN_005c84d0(param_1 + 0x90), cVar1 == '\0' && (*(char *)(param_1 + 0x66) == '\0')))
      ))) {
    fVar4 = (float10)FUN_004b1670("tran04l1.des");
    FUN_0045c0f0((float)fVar4 + 5.0);
    *(undefined1 *)(param_1 + 0x66) = 1;
  }
  if ((((*(char *)(param_1 + 0x5f) != '\0') && (*(char *)(param_1 + 0x60) == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x90), cVar1 != '\0')) &&
     (cVar1 = FUN_005caf90(*(undefined4 *)(param_1 + 0x90)), cVar1 != '\0')) {
    FUN_0041e220(200,900,0);
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0411.wav");
    }
    else {
      FUN_004f49c0(0x2f);
    }
    *(undefined1 *)(param_1 + 0x60) = 1;
  }
  if (((*(char *)(param_1 + 0x60) != '\0') && (*(char *)(param_1 + 0x61) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x90), cVar1 != '\0' &&
      ((cVar1 = FUN_005caf90(*(undefined4 *)(param_1 + 0x90)), cVar1 == '\0' &&
       (*(float *)(param_1 + 0x70) == 99999.0)))))) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x70) = (float)fVar4 + 10.0;
    FUN_004f6aa0();
    FUN_004f6ab0("tran0401.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("tran0402.otf",DAT_009175b0,0x41000000,0);
  }
  if (((*(char *)(param_1 + 0x60) != '\0') && (*(char *)(param_1 + 0x61) == '\0')) &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0x70) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x70))) {
    iVar3 = FUN_004f2de0();
    if (iVar3 == 1) {
      FUN_004f49c0(0x30);
    }
    FUN_00437d30("tran0412.wav");
    *(undefined1 *)(param_1 + 0x61) = 1;
    *(undefined4 *)(param_1 + 0x70) = 0x47c34f80;
  }
  if (((*(char *)(param_1 + 0x60) != '\0') && (*(char *)(param_1 + 0x68) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x90), cVar1 != '\0')) {
    FUN_00462630(*(undefined4 *)(param_1 + 0x90));
    fVar4 = (float10)FUN_0046d040();
    if (0.0 < (float)fVar4) {
      iVar3 = FUN_004f2de0();
      if (iVar3 == 1) {
        FUN_004f49c0(0x31);
      }
      FUN_00437d30("tran0413.wav");
      *(undefined1 *)(param_1 + 0x68) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x7c);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x62) == '\0')) {
    iVar3 = FUN_004f2de0();
    if (iVar3 == 1) {
      FUN_004f49c0(0x32);
    }
    FUN_00437d30("tran0415.wav");
    cVar1 = FUN_005c84d0(param_1 + 0x80);
    if (cVar1 != '\0') {
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x80));
      FUN_005c9640(*(undefined4 *)(param_1 + 0x80),"Drone 2");
    }
    *(undefined1 *)(param_1 + 0x62) = 1;
  }
  iVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x78));
  if ((((iVar3 != 0) && (iVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x80)), iVar3 != 0)) &&
      (*(char *)(param_1 + 0x62) != '\0')) &&
     ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x80)
                                    ), (float)fVar4 < 300.0 && (*(char *)(param_1 + 99) == '\0'))))
  {
    iVar3 = FUN_004f2de0();
    if (iVar3 == 1) {
      FUN_004f49c0(0x33);
    }
    FUN_00437d30("tran0416.wav");
    *(undefined1 *)(param_1 + 99) = 1;
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0418.wav");
    }
    else {
      FUN_004f49c0(0x34);
    }
    *(undefined1 *)(param_1 + 99) = 1;
  }
  if (((*(char *)(param_1 + 99) != '\0') &&
      (iVar3 = FUN_005c8910(), iVar3 == *(int *)(param_1 + 0x80))) &&
     (*(char *)(param_1 + 100) == '\0')) {
    FUN_00437d30("tran0410.wav");
    *(undefined1 *)(param_1 + 100) = 1;
  }
  if (((*(char *)(param_1 + 100) != '\0') && (*(char *)(param_1 + 0x65) == '\0')) &&
     (cVar1 = FUN_005caf90(*(undefined4 *)(param_1 + 0x90)), cVar1 != '\0')) {
    iVar3 = FUN_004f2de0();
    if (iVar3 == 0) {
      FUN_00437d30("tran0420.wav");
    }
    else {
      FUN_004f49c0(0x35);
    }
    *(undefined1 *)(param_1 + 0x65) = 1;
  }
  if (((*(char *)(param_1 + 0x5c) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x7c), cVar1 == '\0'))
     && ((cVar1 = FUN_005c84d0(param_1 + 0x80), cVar1 == '\0' && (*(char *)(param_1 + 0x66) == '\0')
         ))) {
    iVar3 = FUN_004f2de0();
    if (iVar3 == 1) {
      FUN_004f49c0(0x36);
    }
    FUN_00437d30("tran0421.wav");
    fVar4 = (float10)FUN_004b1670("tran04w1.des");
    FUN_0045c110((float)fVar4 + 10.0);
    *(undefined1 *)(param_1 + 0x66) = 1;
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x7c);
    if ((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x80), cVar1 != '\0')) {
      return;
    }
    if (*(char *)(param_1 + 0x66) == '\0') {
      *(undefined1 *)(param_1 + 0x66) = 1;
      fVar4 = (float10)FUN_004b1670("tran04l1.des");
      FUN_0045c0f0((float)fVar4 + 5.0);
    }
  }
  return;
}

