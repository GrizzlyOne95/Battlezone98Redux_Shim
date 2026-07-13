
void FUN_00513600(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  int local_1c [3];
  undefined8 local_10;
  int local_8;
  
  iVar2 = FUN_00417c70();
  local_1c[0] = FUN_005c7fb0();
  cVar1 = FUN_005c84d0(local_1c);
  if (cVar1 != '\0') {
    puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
    local_10 = FUN_0045c460(*puVar3,puVar3[1],puVar3[2]);
  }
  if (*(char *)(local_8 + 0x54) == '\0') {
    uVar4 = FUN_005c7e90("avfigh0_wingman");
    *(undefined4 *)(local_8 + 0x78) = uVar4;
    iVar5 = FUN_004f2de0();
    if (iVar5 == 1) {
      FUN_004f49c0(1);
    }
    else {
      uVar4 = FUN_00437d30("misn0101.wav");
      *(undefined4 *)(local_8 + 0x9c) = uVar4;
    }
    uVar4 = FUN_00460fc0("path_1");
    *(undefined4 *)(local_8 + 0x88) = uVar4;
    uVar4 = FUN_00460fc0("path_2");
    *(undefined4 *)(local_8 + 0x8c) = uVar4;
    uVar4 = FUN_00460fc0("path_3");
    *(undefined4 *)(local_8 + 0x90) = uVar4;
    uVar4 = FUN_00460fc0("path_5");
    *(undefined4 *)(local_8 + 0x94) = uVar4;
    uVar4 = FUN_005c7e90("svturr0_turrettank");
    *(undefined4 *)(local_8 + 0x7c) = uVar4;
    FUN_005c8a50(*(undefined4 *)(local_8 + 0x7c),&DAT_008a1ad8);
    uVar4 = FUN_005c7e90("svturr1_turrettank");
    *(undefined4 *)(local_8 + 0x80) = uVar4;
    FUN_005c8a50(*(undefined4 *)(local_8 + 0x80),&DAT_008a1ad8);
    *(undefined1 *)(local_8 + 0x54) = 1;
    fVar7 = (float10)FUN_00822d80();
    *(float *)(local_8 + 0x68) = (float)fVar7 + 30.0;
    FUN_004f6aa0();
    FUN_004f6ab0("misn0101.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("misn0103.otf",DAT_0091755c,0x41000000,0);
    FUN_0041e260();
    local_1c[1] = 0x76c;
    local_1c[2] = 0x339;
    FUN_0041e220(0x76c,0x339,0x41980000);
    *(undefined4 *)(local_8 + 0xa0) = 0;
  }
  iVar5 = FUN_00462630(*(undefined4 *)(local_8 + 0x7c));
  if (*(char *)(local_8 + 0x5b) == '\0') {
    fVar7 = (float10)FUN_00822d80();
    if (*(float *)(local_8 + 0x68) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x68)) {
      fVar7 = (float10)FUN_00822d80();
      *(float *)(local_8 + 0x68) = (float)fVar7 + 20.0;
      FUN_004f6aa0();
      FUN_004f6ab0("misn0101.otf",DAT_009175b0,0x41000000,0);
      *(int *)(local_8 + 0xa0) = *(int *)(local_8 + 0xa0) + 1;
    }
  }
  if (*(char *)(local_8 + 0x5b) == '\0') {
    puVar3 = *(undefined4 **)(*(int *)(local_8 + 0x88) + 8);
    uVar9 = FUN_00444e40(*puVar3,puVar3[1],local_10);
    fVar7 = (float10)FUN_00460300(uVar9);
    if ((float)fVar7 < *(float *)(local_8 + 0x6c)) {
      if ((local_1c[0] == *(int *)(local_8 + 0x78)) || (*(char *)(local_8 + 0x55) != '\0')) {
        FUN_004f6aa0();
        FUN_004f6ab0("misn0101.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misn0103.otf",DAT_0091755c,0x41000000,0);
      }
      else {
        *(undefined1 *)(local_8 + 0x55) = 1;
        FUN_00437d80(*(undefined4 *)(local_8 + 0x9c));
        iVar6 = FUN_004f2de0();
        if (iVar6 == 1) {
          FUN_004f49c0(0xd);
        }
        FUN_00437d30("misn0122.wav");
      }
      FUN_004ff120(0,300,0xf0);
      *(undefined4 *)(local_8 + 0x68) = 0;
      *(undefined4 *)(local_8 + 0xa0) = 0;
      *(undefined1 *)(local_8 + 0x5b) = 1;
      *(undefined4 *)(local_8 + 0xa4) = 0;
    }
  }
  if (((*(char *)(local_8 + 0x5b) != '\0') && (*(char *)(local_8 + 0x5c) == '\0')) &&
     (local_1c[0] == *(int *)(local_8 + 0x78))) {
    FUN_0041e260();
    iVar6 = *(int *)(*(int *)(local_8 + 0x88) + 8);
    uVar9 = FUN_00444e40(*(undefined4 *)(iVar6 + *(int *)(local_8 + 0xa4) * 8),
                         *(undefined4 *)(iVar6 + 4 + *(int *)(local_8 + 0xa4) * 8),local_10);
    fVar7 = (float10)FUN_00460300(uVar9);
    if (*(float *)(local_8 + 0x6c) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x6c)) {
      fVar7 = (float10)FUN_00822d80();
      if (*(float *)(local_8 + 0x68) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x68))
      {
        iVar6 = FUN_004f2de0();
        if (iVar6 == 1) {
          FUN_004f49c0(2);
        }
        FUN_00437d30("misn0103.wav");
        cVar1 = FUN_005c84d0(local_8 + 0x7c);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_8 + 0x80);
          if ((cVar1 == '\0') && (*(char *)(local_8 + 99) == '\0')) {
            *(undefined1 *)(local_8 + 99) = 1;
            fVar7 = (float10)FUN_004b1670("misn01l1.des");
            FUN_0045c0f0((float)fVar7 + 5.0);
          }
        }
        fVar7 = (float10)FUN_00822d80();
        *(float *)(local_8 + 0x68) = (float)fVar7 + 15.0;
        *(int *)(local_8 + 0xa0) = *(int *)(local_8 + 0xa0) + 1;
      }
    }
    iVar6 = *(int *)(*(int *)(local_8 + 0x88) + 8);
    uVar10 = FUN_00444e40(*(undefined4 *)(iVar6 + 8 + *(int *)(local_8 + 0xa4) * 8),
                          *(undefined4 *)(iVar6 + 0xc + *(int *)(local_8 + 0xa4) * 8),local_10);
    fVar7 = (float10)FUN_00460300(uVar10);
    fVar8 = (float10)FUN_00460300(uVar9);
    if (((float)fVar7 < (float)fVar8) &&
       (*(int *)(local_8 + 0xa4) = *(int *)(local_8 + 0xa4) + 1,
       *(int *)(local_8 + 0xa4) == *(int *)(*(int *)(local_8 + 0x88) + 4) + -1)) {
      *(undefined1 *)(local_8 + 0x5c) = 1;
      *(undefined4 *)(local_8 + 0xa4) = 0;
    }
  }
  if ((*(char *)(local_8 + 0x5c) != '\0') && (*(char *)(local_8 + 0x5d) == '\0')) {
    iVar6 = *(int *)(*(int *)(local_8 + 0x8c) + 8);
    uVar9 = FUN_00444e40(*(undefined4 *)(iVar6 + *(int *)(local_8 + 0xa4) * 8),
                         *(undefined4 *)(iVar6 + 4 + *(int *)(local_8 + 0xa4) * 8),local_10);
    fVar7 = (float10)FUN_00460300(uVar9);
    if (*(float *)(local_8 + 0x6c) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x6c)) {
      fVar7 = (float10)FUN_00822d80();
      if (*(float *)(local_8 + 0x68) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x68))
      {
        iVar6 = FUN_004f2de0();
        if (iVar6 == 1) {
          FUN_004f49c0(2);
        }
        FUN_00437d30("misn0103.wav");
        cVar1 = FUN_005c84d0(local_8 + 0x7c);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_8 + 0x80);
          if ((cVar1 == '\0') && (*(char *)(local_8 + 99) == '\0')) {
            *(undefined1 *)(local_8 + 99) = 1;
            fVar7 = (float10)FUN_004b1670("misn01l1.des");
            FUN_0045c0f0((float)fVar7 + 5.0);
          }
        }
        fVar7 = (float10)FUN_00822d80();
        *(float *)(local_8 + 0x68) = (float)fVar7 + 15.0;
        *(int *)(local_8 + 0xa0) = *(int *)(local_8 + 0xa0) + 1;
      }
    }
    iVar6 = *(int *)(*(int *)(local_8 + 0x8c) + 8);
    uVar10 = FUN_00444e40(*(undefined4 *)(iVar6 + 8 + *(int *)(local_8 + 0xa4) * 8),
                          *(undefined4 *)(iVar6 + 0xc + *(int *)(local_8 + 0xa4) * 8),local_10);
    fVar7 = (float10)FUN_00460300(uVar10);
    fVar8 = (float10)FUN_00460300(uVar9);
    if (((float)fVar7 < (float)fVar8) &&
       (*(int *)(local_8 + 0xa4) = *(int *)(local_8 + 0xa4) + 1,
       *(int *)(local_8 + 0xa4) == *(int *)(*(int *)(local_8 + 0x8c) + 4) + -1)) {
      *(undefined1 *)(local_8 + 0x5d) = 1;
      iVar6 = FUN_004f2de0();
      if (iVar6 == 0) {
        uVar4 = FUN_00437d30("misn0104.wav");
        *(undefined4 *)(local_8 + 0x9c) = uVar4;
      }
      else {
        FUN_004f49c0(3);
      }
      local_1c[1] = 0x1e;
      local_1c[2] = 0x44c;
      FUN_0041e220(0x1e,0x44c,0x40c00000);
      *(undefined4 *)(local_8 + 0xa4) = 0;
    }
  }
  if ((*(char *)(local_8 + 0x5d) != '\0') && (*(char *)(local_8 + 0x62) == '\0')) {
    iVar6 = *(int *)(*(int *)(local_8 + 0x90) + 8);
    uVar9 = FUN_00444e40(*(undefined4 *)(iVar6 + *(int *)(local_8 + 0xa4) * 8),
                         *(undefined4 *)(iVar6 + 4 + *(int *)(local_8 + 0xa4) * 8),local_10);
    fVar7 = (float10)FUN_00460300(uVar9);
    if (*(float *)(local_8 + 0x6c) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x6c)) {
      fVar7 = (float10)FUN_00822d80();
      if (*(float *)(local_8 + 0x68) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x68))
      {
        iVar6 = FUN_004f2de0();
        if (iVar6 == 1) {
          FUN_004f49c0(2);
        }
        FUN_00437d30("misn0103.wav");
        cVar1 = FUN_005c84d0(local_8 + 0x7c);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_8 + 0x80);
          if ((cVar1 == '\0') && (*(char *)(local_8 + 99) == '\0')) {
            *(undefined1 *)(local_8 + 99) = 1;
            fVar7 = (float10)FUN_004b1670("misn01l1.des");
            FUN_0045c0f0((float)fVar7 + 5.0);
          }
        }
        fVar7 = (float10)FUN_00822d80();
        *(float *)(local_8 + 0x68) = (float)fVar7 + 15.0;
        *(int *)(local_8 + 0xa0) = *(int *)(local_8 + 0xa0) + 1;
      }
    }
    iVar6 = *(int *)(*(int *)(local_8 + 0x90) + 8);
    uVar10 = FUN_00444e40(*(undefined4 *)(iVar6 + 8 + *(int *)(local_8 + 0xa4) * 8),
                          *(undefined4 *)(iVar6 + 0xc + *(int *)(local_8 + 0xa4) * 8),local_10);
    fVar7 = (float10)FUN_00460300(uVar10);
    fVar8 = (float10)FUN_00460300(uVar9);
    if (((float)fVar7 < (float)fVar8) &&
       (*(int *)(local_8 + 0xa4) = *(int *)(local_8 + 0xa4) + 1,
       *(int *)(local_8 + 0xa4) == *(int *)(*(int *)(local_8 + 0x90) + 4) + -1)) {
      *(undefined1 *)(local_8 + 0x62) = 1;
      fVar7 = (float10)FUN_00822d80();
      *(float *)(local_8 + 0x70) = (float)fVar7 + 8.0;
      FUN_0041e260();
    }
  }
  if ((*(char *)(local_8 + 0x62) != '\0') && (*(char *)(local_8 + 0x5f) == '\0')) {
    fVar7 = (float10)FUN_00822d80();
    if (*(float *)(local_8 + 0x70) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x70)) {
      fVar7 = (float10)FUN_00822d80();
      *(float *)(local_8 + 0x68) = (float)fVar7 + 45.0;
      iVar6 = FUN_004f2de0();
      if (iVar6 == 1) {
        FUN_004f49c0(4);
      }
      FUN_00437d30("misn0105.wav");
      *(float *)(local_8 + 0x6c) = *(float *)(local_8 + 0x6c) * 1.5;
      FUN_00437d30("misn0107.wav");
      *(undefined1 *)(local_8 + 0x5f) = 1;
    }
  }
  if (*(char *)(local_8 + 0x5e) == '\0') {
    puVar3 = *(undefined4 **)(*(int *)(local_8 + 0x94) + 8);
    uVar9 = FUN_00444e40(*puVar3,puVar3[1],local_10);
    fVar7 = (float10)FUN_00460300(uVar9);
    if ((float)fVar7 < *(float *)(local_8 + 0x6c)) {
      *(undefined4 *)(local_8 + 0x68) = 0;
      *(undefined4 *)(local_8 + 0xa0) = 0;
      *(undefined1 *)(local_8 + 0x5e) = 1;
      *(undefined4 *)(local_8 + 0xa4) = 0;
      if (local_1c[0] != *(int *)(local_8 + 0x78)) {
        iVar6 = FUN_004f2de0();
        if (iVar6 == 1) {
          FUN_004f49c0(0xd);
        }
        FUN_00437d30("misn0122.wav");
      }
    }
  }
  if ((*(char *)(local_8 + 0x5e) != '\0') && (*(char *)(local_8 + 0x59) == '\0')) {
    iVar6 = *(int *)(*(int *)(local_8 + 0x94) + 8);
    uVar9 = FUN_00444e40(*(undefined4 *)(iVar6 + *(int *)(local_8 + 0xa4) * 8),
                         *(undefined4 *)(iVar6 + 4 + *(int *)(local_8 + 0xa4) * 8),local_10);
    fVar7 = (float10)FUN_00460300(uVar9);
    if (*(float *)(local_8 + 0x6c) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x6c)) {
      fVar7 = (float10)FUN_00822d80();
      if (*(float *)(local_8 + 0x68) <= (float)fVar7 && (float)fVar7 != *(float *)(local_8 + 0x68))
      {
        iVar6 = FUN_004f2de0();
        if (iVar6 == 1) {
          FUN_004f49c0(6);
        }
        FUN_00437d30("misn0108.wav");
        fVar7 = (float10)FUN_00822d80();
        *(float *)(local_8 + 0x68) = (float)fVar7 + 15.0;
        *(int *)(local_8 + 0xa0) = *(int *)(local_8 + 0xa0) + 1;
      }
    }
    iVar6 = *(int *)(*(int *)(local_8 + 0x94) + 8);
    uVar10 = FUN_00444e40(*(undefined4 *)(iVar6 + 8 + *(int *)(local_8 + 0xa4) * 8),
                          *(undefined4 *)(iVar6 + 0xc + *(int *)(local_8 + 0xa4) * 8),local_10);
    fVar7 = (float10)FUN_00460300(uVar10);
    fVar8 = (float10)FUN_00460300(uVar9);
    if (((float)fVar7 < (float)fVar8) &&
       (*(int *)(local_8 + 0xa4) = *(int *)(local_8 + 0xa4) + 1,
       *(int *)(local_8 + 0xa4) == *(int *)(*(int *)(local_8 + 0x94) + 4) + -1)) {
      FUN_004ff150();
      *(undefined1 *)(local_8 + 0x59) = 1;
      FUN_005c95e0(*(undefined4 *)(local_8 + 0x7c));
      FUN_005c9640(*(undefined4 *)(local_8 + 0x7c),"Combat Training");
      iVar6 = FUN_004f2de0();
      if (iVar6 == 1) {
        FUN_004f49c0(7);
      }
      FUN_00437d30("misn0109.wav");
      FUN_0041e260();
      FUN_004f6aa0();
      FUN_004f6ab0("misn0101.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0103.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0105.otf",DAT_0091755c,0x41000000,0);
    }
  }
  if ((*(char *)(local_8 + 0x59) != '\0') && (*(char *)(local_8 + 0x60) == '\0')) {
    cVar1 = FUN_005c84d0(local_8 + 0x7c);
    if (cVar1 != '\0') {
      puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
      puVar3 = (undefined4 *)
               (**(code **)(*(int *)(iVar5 + 0x18) + 0xc))(*puVar3,puVar3[1],puVar3[2]);
      fVar7 = (float10)FUN_004620b0(*puVar3,puVar3[1],puVar3[2]);
      if ((float)fVar7 < 10000.0) {
        FUN_004ff160();
        iVar2 = FUN_004f2de0();
        if (iVar2 == 1) {
          FUN_004f49c0(8);
        }
        uVar4 = FUN_00437d30("misn0111.wav");
        *(undefined4 *)(local_8 + 0x9c) = uVar4;
        local_1c[1] = 0x71c;
        local_1c[2] = 0x546;
        FUN_0041e220(0x71c,0x546,0);
        *(undefined1 *)(local_8 + 0x60) = 1;
      }
    }
  }
  if (*(char *)(local_8 + 0x5a) == '\0') {
    cVar1 = FUN_005c84d0(local_8 + 0x7c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_8 + 0x80);
      if (cVar1 != '\0') {
        FUN_005c95e0(*(undefined4 *)(local_8 + 0x80));
        FUN_005c9640(*(undefined4 *)(local_8 + 0x80),"Combat Training 2");
        iVar2 = FUN_004f2de0();
        if (iVar2 == 1) {
          FUN_004f49c0(0xb);
        }
        FUN_00437d30("misn0113.wav");
        FUN_0041e260();
        *(undefined1 *)(local_8 + 0x5a) = 1;
      }
    }
  }
  if (*(char *)(local_8 + 0x61) == '\0') {
    cVar1 = FUN_005c84d0(local_8 + 0x7c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_8 + 0x80);
      if (cVar1 == '\0') {
        FUN_004ff0d0("misn0101.otf",DAT_009175b0,0x41000000,0);
        FUN_004ff0d0("misn0103.otf",DAT_009175b0,0x41000000,0);
        FUN_004ff0d0("misn0105.otf",DAT_009175b0,0x41000000,0);
        iVar2 = FUN_004f2de0();
        if (iVar2 == 1) {
          FUN_004f49c0(0xc);
        }
        FUN_00437d30("misn0121.wav");
        *(undefined1 *)(local_8 + 0x61) = 1;
        fVar7 = (float10)FUN_004b1670("misn01w1.des");
        FUN_0045c110((float)fVar7 + 10.0);
      }
    }
  }
  if ((4 < *(int *)(local_8 + 0xa0)) && (*(char *)(local_8 + 99) == '\0')) {
    *(undefined4 *)(local_8 + 0x68) = 0x47c34f80;
    FUN_004f6aa0();
    FUN_004f6ab0("misn0102.otf",DAT_0091757c,0x41000000,0);
    iVar2 = FUN_004f2de0();
    if (iVar2 == 1) {
      FUN_004f49c0(0xe);
    }
    FUN_00437d30("misn0123.wav");
    fVar7 = (float10)FUN_004b1670("misn01l1.des");
    FUN_0045c0f0((float)fVar7 + 10.0);
    *(undefined4 *)(local_8 + 0xa0) = 0;
  }
  return;
}

