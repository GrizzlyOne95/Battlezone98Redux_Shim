
void __fastcall FUN_005e6d50(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  
  cVar1 = FUN_005c84d0(param_1 + 0x78);
  if ((cVar1 == '\0') ||
     ((*(char *)(param_1 + 0x67) == '\0' && (cVar1 = FUN_005c84d0(param_1 + 0x80), cVar1 == '\0'))))
  {
    if (*(char *)(param_1 + 0x54) == '\0') {
      *(undefined1 *)(param_1 + 0x54) = 1;
      fVar6 = (float10)FUN_004b1670("tran02l1.des");
      FUN_0045c0f0((float)fVar6 + 5.0);
    }
  }
  else {
    fVar6 = (float10)FUN_005e6af0(*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0xa4));
    *(float *)(param_1 + 0x70) = (float)fVar6;
    if (*(char *)(param_1 + 0x56) == '\0') {
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x78));
      FUN_005c9640(*(undefined4 *)(param_1 + 0x78),"Turret");
      iVar2 = FUN_004f2de0();
      if (iVar2 != 0) {
        FUN_004f49c0(0xf);
      }
      uVar3 = FUN_00437d30("tran0201.wav");
      *(undefined4 *)(param_1 + 0xa8) = uVar3;
      fVar6 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x6c) = (float)fVar6 + 10.0;
      FUN_004f6aa0();
      FUN_004f6ab0("tran0201.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(param_1 + 0x56) = 1;
      FUN_0041e260();
    }
    if ((*(char *)(param_1 + 99) == '\0') &&
       (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xa8)), cVar1 != '\0')) {
      iVar2 = FUN_004344a0();
      if (iVar2 == 2) {
        FUN_004f49c0(0x10);
      }
      else {
        uVar3 = FUN_00437d30("tran0202.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar3;
      }
      *(undefined4 *)(param_1 + 0x6c) = 0x47c34f80;
      fVar6 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
      *(undefined4 *)(param_1 + 0xa4) = 3;
      *(undefined1 *)(param_1 + 99) = 1;
      FUN_0041e220(200,0xa5,0x41400000);
    }
    if (((*(char *)(param_1 + 0x65) == '\0') && (*(char *)(param_1 + 99) != '\0')) &&
       (iVar2 = FUN_005e6960(), iVar2 == 2)) {
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa8));
      FUN_0041e220(200,0x5a,0x41600000);
      iVar2 = FUN_004f2de0();
      if (iVar2 == 0) {
        uVar3 = FUN_00437d30("tran0205.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar3;
      }
      else {
        FUN_004f49c0(0x12);
      }
      *(undefined1 *)(param_1 + 0x65) = 1;
      fVar6 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
      *(undefined4 *)(param_1 + 0xa4) = 4;
    }
    if ((*(char *)(param_1 + 100) == '\0') && (*(char *)(param_1 + 99) != '\0')) {
      FUN_00462630(*(undefined4 *)(param_1 + 0x78));
      cVar1 = FUN_00492d20();
      if (cVar1 != '\0') {
        FUN_0041e220(200,0x5a,0x40c00000);
        FUN_00437d80(*(undefined4 *)(param_1 + 0xa8));
        iVar2 = FUN_004f2de0();
        if (iVar2 == 0) {
          uVar3 = FUN_00437d30("tran0206.wav");
          *(undefined4 *)(param_1 + 0xa8) = uVar3;
        }
        else {
          FUN_004f49c0(0x13);
        }
        FUN_005c9610(*(undefined4 *)(param_1 + 0x78));
        FUN_005c95e0(*(undefined4 *)(param_1 + 0x7c));
        FUN_005c9640(*(undefined4 *)(param_1 + 0x7c),"Target Range");
        *(undefined1 *)(param_1 + 100) = 1;
        fVar6 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
        *(undefined4 *)(param_1 + 0xa4) = 5;
      }
    }
    if ((*(char *)(param_1 + 100) != '\0') && (*(char *)(param_1 + 0x55) == '\0')) {
      FUN_00462630(*(undefined4 *)(param_1 + 0x78));
      cVar1 = FUN_00492d20();
      if (cVar1 == '\0') {
        FUN_00437d80(*(undefined4 *)(param_1 + 0xa8));
        iVar2 = FUN_004f2de0();
        if (iVar2 == 1) {
          FUN_004f49c0(7);
        }
        uVar3 = FUN_00437d30("misn0109.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar3;
        *(undefined1 *)(param_1 + 0x55) = 1;
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
        *(undefined4 *)(param_1 + 0xa4) = 6;
        FUN_0041e260();
      }
    }
    if ((*(char *)(param_1 + 100) != '\0') && (*(char *)(param_1 + 0x60) == '\0')) {
      iVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x78));
      iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x7c));
      puVar5 = (undefined4 *)(**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
      puVar5 = (undefined4 *)
               (**(code **)(*(int *)(iVar4 + 0x18) + 0xc))(*puVar5,puVar5[1],puVar5[2]);
      fVar6 = (float10)FUN_004620b0(*puVar5,puVar5[1],puVar5[2]);
      if ((float)fVar6 < 10000.0) {
        iVar2 = FUN_004f2de0();
        if (iVar2 == 0) {
          iVar2 = FUN_004f2de0();
          if (iVar2 != 0) {
            FUN_004f49c0(0x1b);
          }
          uVar3 = FUN_00437d30("tran0207.wav");
          *(undefined4 *)(param_1 + 0xa8) = uVar3;
          uVar3 = FUN_00437d30("tran0212.wav");
          *(undefined4 *)(param_1 + 0xa8) = uVar3;
        }
        else {
          FUN_004f49c0(0x14);
        }
        *(undefined1 *)(param_1 + 0x60) = 1;
        fVar6 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
        *(undefined4 *)(param_1 + 0xa4) = 7;
        FUN_0041e220(200,0xa5,0x40c00000);
      }
    }
    if (((*(char *)(param_1 + 0x60) != '\0') && (*(char *)(param_1 + 0x61) == '\0')) &&
       (iVar2 = FUN_005e6960(), iVar2 == 2)) {
      *(undefined1 *)(param_1 + 0x61) = 1;
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa8));
      iVar2 = FUN_004f2de0();
      if (iVar2 == 0) {
        uVar3 = FUN_00437d30("tran0211.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar3;
      }
      else {
        FUN_004f49c0(0x1a);
      }
      FUN_0041e220(200,0x5a,0x40400000);
      fVar6 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x70) = (float)fVar6 + 20.0;
      *(undefined4 *)(param_1 + 0xa4) = 4;
    }
    if ((*(char *)(param_1 + 0x60) != '\0') && (*(char *)(param_1 + 0x66) == '\0')) {
      FUN_00462630(*(undefined4 *)(param_1 + 0x78));
      cVar1 = FUN_00492d20();
      if (cVar1 != '\0') {
        FUN_00437d80(*(undefined4 *)(param_1 + 0xa8));
        iVar2 = FUN_004f2de0();
        if (iVar2 == 0) {
          uVar3 = FUN_00437d30("tran0208.wav");
          *(undefined4 *)(param_1 + 0xa8) = uVar3;
        }
        else {
          FUN_004f49c0(0x15);
        }
        FUN_0041e220(200,900,0x40e00000);
        *(undefined1 *)(param_1 + 0x66) = 1;
        fVar6 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
        *(undefined4 *)(param_1 + 0xa4) = 8;
      }
    }
    if (((*(char *)(param_1 + 0x66) != '\0') && (*(char *)(param_1 + 0x67) == '\0')) &&
       (iVar2 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x78)), iVar2 == 3)) {
      *(undefined4 *)(param_1 + 0x70) = 0x47c34f80;
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa8));
      iVar2 = FUN_004f2de0();
      if (iVar2 != 0) {
        FUN_004f49c0(0x18);
      }
      uVar3 = FUN_00437d30("tran0209.wav");
      *(undefined4 *)(param_1 + 0xa8) = uVar3;
      FUN_0041e260();
      FUN_005c9610(*(undefined4 *)(param_1 + 0x7c));
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x80),*(undefined4 *)(param_1 + 0x78),1);
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x80));
      FUN_005c9640(*(undefined4 *)(param_1 + 0x80),"Target Drone");
      *(undefined1 *)(param_1 + 0x67) = 1;
    }
    if (((*(char *)(param_1 + 0x67) != '\0') && (*(char *)(param_1 + 0x68) == '\0')) &&
       (iVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x80)), iVar2 == 0)) {
      FUN_004ff0d0("tran0201.otf",DAT_009175b0,0x41000000,0);
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa8));
      iVar2 = FUN_004f2de0();
      if (iVar2 != 0) {
        FUN_004f49c0(0x19);
      }
      uVar3 = FUN_00437d30("tran0210.wav");
      *(undefined4 *)(param_1 + 0xa8) = uVar3;
      *(undefined1 *)(param_1 + 0x68) = 1;
      fVar6 = (float10)FUN_004b1670("tran02w1.des");
      FUN_0045c110((float)fVar6 + 10.0);
    }
  }
  return;
}

