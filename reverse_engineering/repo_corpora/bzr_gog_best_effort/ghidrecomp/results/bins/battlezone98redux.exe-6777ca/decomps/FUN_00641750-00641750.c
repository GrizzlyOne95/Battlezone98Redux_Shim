
void __fastcall FUN_00641750(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  float fVar10;
  char local_11;
  int local_10;
  int local_c;
  
  uVar5 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 200) = uVar5;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,100);
    FUN_005cacb0(1,10);
    FUN_004f6aa0();
    FUN_004f6ab0("bd11001.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x54) = 1;
    uVar5 = FUN_005c8250(&DAT_00878c18,1,"recy_nav",0,0);
    *(undefined4 *)(param_1 + 0x228) = uVar5;
    FUN_005cd7f0(*(undefined4 *)(param_1 + 0x228),"Recycler");
  }
  if (((*(char *)(param_1 + 0x67) == '\0') &&
      (fVar9 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xcc)), (float)fVar9 <= 0.0)) &&
     (*(char *)(param_1 + 0x68) == '\0')) {
    *(undefined1 *)(param_1 + 0x67) = 1;
    if (*(char *)(param_1 + 0x60) == '\0') {
      fVar9 = (float10)FUN_004b1670("bd11lsed.des");
      FUN_0045c0f0((float)fVar9 + 1.0);
    }
    else {
      fVar9 = (float10)FUN_004b1670("bd11lseb.des");
      FUN_0045c0f0((float)fVar9 + 1.0);
    }
  }
  if (((*(char *)(param_1 + 0x55) == '\0') &&
      (fVar9 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xd0)), (float)fVar9 <= 0.0)) &&
     ((*(char *)(param_1 + 0x68) == '\0' && (*(char *)(param_1 + 0x67) == '\0')))) {
    *(undefined1 *)(param_1 + 0x67) = 1;
    fVar9 = (float10)FUN_004b1670("bd11lsea.des");
    FUN_0045c0f0((float)fVar9 + 1.0);
  }
  if (*(char *)(param_1 + 0x5a) == '\0') {
    if (*(char *)(param_1 + 0x58) == '\0') {
      *(undefined1 *)(param_1 + 0x58) = 1;
      FUN_005cd2a0();
      uVar5 = FUN_00437d30("bd11001.wav");
      *(undefined4 *)(param_1 + 0x23c) = uVar5;
    }
    local_11 = FUN_005cd300("camera_start",1000,0x640,*(undefined4 *)(param_1 + 0xcc));
    cVar4 = FUN_005cd560();
    if (cVar4 != '\0') {
      local_11 = '\x01';
      FUN_00437d80(*(undefined4 *)(param_1 + 0x23c));
    }
    if (local_11 != '\0') {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x5a) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x55) == '\0') && (*(char *)(param_1 + 0x5d) == '\0')) {
    fVar9 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd0),*(undefined4 *)(param_1 + 0xcc));
    uVar5 = FUN_005ca150(*(undefined4 *)(param_1 + 0xd0));
    if (((float)fVar9 < 50.0) &&
       (fVar9 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd0),uVar5), 200.0 < (float)fVar9))
    {
      FUN_005cbd40(*(undefined4 *)(param_1 + 0xd0),1);
      *(undefined1 *)(param_1 + 0x5d) = 1;
      uVar5 = FUN_005c8080("aspilo",1,*(undefined4 *)(param_1 + 0xd0),0);
      *(undefined4 *)(param_1 + 0xd4) = uVar5;
      FUN_005cc140(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xcc),1);
    }
  }
  if (*(char *)(param_1 + 0x5d) != '\0') {
    FUN_005ce190(*(undefined4 *)(param_1 + 0xd4));
    if (((*(char *)(param_1 + 0x67) == '\0') &&
        (fVar9 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xd4)), (float)fVar9 <= 0.0)) &&
       (*(char *)(param_1 + 0x68) == '\0')) {
      *(undefined1 *)(param_1 + 0x67) = 1;
      fVar9 = (float10)FUN_004b1670("bd11lsec.des");
      FUN_0045c0f0((float)fVar9 + 1.0);
    }
    fVar9 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xcc));
    if ((float)fVar9 < 50.0) {
      *(undefined1 *)(param_1 + 0x5d) = 0;
      *(undefined1 *)(param_1 + 0x55) = 1;
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xd4));
      *(undefined4 *)(param_1 + 0xd4) = 0;
      iVar6 = FUN_00462630(*(undefined4 *)(param_1 + 0xcc));
      uVar5 = FUN_004ff060("bspilo");
      *(undefined4 *)(iVar6 + 0xec) = uVar5;
      FUN_00461440(param_1,iVar6);
      fVar9 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x6c) = (float)fVar9 + 2.0;
      FUN_00437d30("bd11002.wav");
    }
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x6c) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0x6c)) {
    *(undefined1 *)(param_1 + 0x5e) = 1;
    FUN_005c8840(*(undefined4 *)(param_1 + 0xcc),1);
    *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xcc),"recycler_path",1);
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar9 + 20.0;
  }
  if ((*(char *)(param_1 + 0x5e) != '\0') &&
     (cVar4 = FUN_005cda90(*(undefined4 *)(param_1 + 0xcc),"recycler_path"), cVar4 != '\0')) {
    *(undefined1 *)(param_1 + 0x5e) = 0;
    FUN_004f6aa0();
    FUN_004f6ab0("bd11001.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("bd11002.otf",DAT_0091755c,0x41000000,0);
  }
  if ((*(char *)(param_1 + 0x5f) == '\0') &&
     (fVar9 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),"wave_trigger",0),
     (float)fVar9 < 50.0)) {
    *(undefined1 *)(param_1 + 0x5f) = 1;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar9 + 120.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar9 + 300.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar9 + 540.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar9 + 840.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar9 + 1080.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar9 + 1260.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar9 + 1560.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xac) = (float)fVar9 + 480.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xac) = (float)fVar9 + 780.0;
    uVar5 = FUN_005c8250("cvltnk",2,"drive_2",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    uVar5 = FUN_005c8250("cvltnk",2,"drive_2",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    uVar5 = FUN_005c8250("cvltnk",2,"drive_2",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    uVar5 = FUN_005c8250("cvhraz",2,"drive_2",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    uVar5 = FUN_005c8250("cvhraz",2,"drive_2",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
  }
  if (*(char *)(param_1 + 0x55) != '\0') {
    fVar9 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xcc));
    fVar10 = (float)fVar9;
    if (fVar10 <= 0.5) {
      if ((*(char *)(param_1 + 0x62) != '\0') || (fVar10 <= 0.25)) {
        if ((*(char *)(param_1 + 99) != '\0') || (fVar10 <= 0.15)) {
          if ((*(char *)(param_1 + 100) == '\0') && (0.0 < fVar10)) {
            FUN_00437d80(*(undefined4 *)(param_1 + 0x240));
            FUN_00437d80(*(undefined4 *)(param_1 + 0x244));
            *(undefined1 *)(param_1 + 100) = 1;
            uVar5 = FUN_00437d30("bd11006.wav");
            *(undefined4 *)(param_1 + 0x248) = uVar5;
          }
        }
        else {
          FUN_00437d80(*(undefined4 *)(param_1 + 0x240));
          *(undefined1 *)(param_1 + 99) = 1;
          uVar5 = FUN_00437d30("bd11005.wav");
          *(undefined4 *)(param_1 + 0x244) = uVar5;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x62) = 1;
        uVar5 = FUN_00437d30("bd11004.wav");
        *(undefined4 *)(param_1 + 0x240) = uVar5;
      }
    }
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0x70)) {
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    uVar5 = FUN_005c8250("cvwalk",2,"drive_1",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    uVar5 = FUN_005c8250("cvwalk",2,"drive_1",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    uVar5 = FUN_005c8250("cvltnk",2,"drive_1",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    uVar5 = FUN_005c8250("cvltnk",2,"drive_1",0,0);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xac) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0xac)) {
    *(undefined4 *)(param_1 + 0xac) = 0x497423fe;
    for (local_c = 0; local_c < 8; local_c = local_c + 1) {
      uVar5 = FUN_005c8250("cssold",2,"aerial_1",400,0);
      FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    }
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xb0) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0xb0)) {
    *(undefined4 *)(param_1 + 0xb0) = 0x497423fe;
    for (local_c = 0; local_c < 8; local_c = local_c + 1) {
      uVar5 = FUN_005c8250("cssold",2,"aerial_1",400,0);
      FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    }
  }
  local_c = 0;
  while ((local_c < 6 && (*(char *)(param_1 + 0x5f) != '\0'))) {
    fVar9 = (float10)FUN_004b1670();
    pfVar1 = (float *)(param_1 + 0x74 + local_c * 4);
    if (*pfVar1 <= (float)fVar9 && (float)fVar9 != *pfVar1) {
      *(undefined4 *)(param_1 + 0x74 + local_c * 4) = 0x497423fe;
      iVar6 = *(int *)(&DAT_0087306c + local_c * 4);
      iVar2 = *(int *)(&DAT_00873068 + local_c * 4);
      for (local_10 = 0; local_10 < iVar6 - iVar2; local_10 = local_10 + 1) {
        iVar8 = *(int *)(&DAT_00873068 + local_c * 4) + 6 + *(int *)(&DAT_00873084 + local_c * 4) +
                local_10;
        uVar5 = FUN_005c8250((&PTR_s_cvhraz_008ecc38)
                             [*(int *)(&DAT_00873068 + local_c * 4) + local_10],2,
                             (&PTR_s_attack_1_008ecd5c)[local_c],0,0);
        *(undefined4 *)(param_1 + 0xd8 + iVar8 * 4) = uVar5;
        FUN_005cd6f0(*(undefined4 *)(param_1 + 0xd8 + iVar8 * 4));
        FUN_005cb820(*(undefined4 *)(param_1 + 0xd8 + iVar8 * 4),*(undefined4 *)(param_1 + 0xcc),1);
      }
      iVar8 = *(int *)(&DAT_00873088 + local_c * 4);
      iVar3 = *(int *)(&DAT_00873084 + local_c * 4);
      for (local_10 = 0; local_10 < iVar8 - iVar3; local_10 = local_10 + 1) {
        iVar7 = *(int *)(&DAT_0087306c + local_c * 4) + 6 + *(int *)(&DAT_00873084 + local_c * 4) +
                local_10;
        uVar5 = FUN_005c8250((&PTR_s_cvtnk_008eccb0)
                             [*(int *)(&DAT_00873084 + local_c * 4) + local_10],2,
                             (&PTR_s_defend_1_008ecc98)[local_c],0,0);
        *(undefined4 *)(param_1 + 0xd8 + iVar7 * 4) = uVar5;
        FUN_005cd6f0(*(undefined4 *)(param_1 + 0xd8 + iVar7 * 4));
        FUN_005cbce0(uVar5,*(undefined4 *)
                            (param_1 + 0xd8 +
                            (*(int *)(&DAT_00873068 + local_c * 4) + 6 +
                             *(int *)(&DAT_00873084 + local_c * 4) + local_10 % (iVar6 - iVar2)) * 4
                            ),1);
      }
    }
    local_c = local_c + 1;
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x8c) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0x8c)) {
    *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
    FUN_004f6aa0();
    FUN_004f6ab0("bd11002.otf",DAT_009175b0,0x41000000,0);
    *(undefined1 *)(param_1 + 0x56) = 1;
    FUN_00437d30("bd11007.wav");
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb8) = (float)fVar9 + 3.0;
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xb8) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0xb8)) {
    *(undefined4 *)(param_1 + 0xb8) = 0x497423fe;
    uVar5 = FUN_00437d30("bd11008.wav");
    *(undefined4 *)(param_1 + 0x24c) = uVar5;
  }
  if ((*(int *)(param_1 + 0x24c) != 0) &&
     (cVar4 = FUN_00437d60(*(undefined4 *)(param_1 + 0x24c)), cVar4 != '\0')) {
    *(undefined4 *)(param_1 + 0x24c) = 0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xbc) = (float)fVar9 + 5.0;
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xbc) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0xbc)) {
    *(undefined4 *)(param_1 + 0xbc) = 0x497423fe;
    FUN_00437d30("bd11009.wav");
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xc0) = (float)fVar9 + 5.0;
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xc0) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0xc0)) {
    *(undefined4 *)(param_1 + 0xc0) = 0x497423fe;
    uVar5 = FUN_00437d30("bd11012.wav");
    *(undefined4 *)(param_1 + 0x254) = uVar5;
  }
  if ((*(int *)(param_1 + 0x254) != 0) &&
     (cVar4 = FUN_00437d60(*(undefined4 *)(param_1 + 0x254)), cVar4 != '\0')) {
    *(undefined4 *)(param_1 + 0x254) = 0;
    FUN_004f6aa0();
    FUN_004f6ab0("bd11003.otf",DAT_0091755c,0x41000000,0);
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x224));
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar9 + 90.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa0) = (float)fVar9 + 90.0 + 2.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa4) = (float)fVar9 + 90.0 + 4.0;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa8) = (float)fVar9 + 90.0 + 6.0;
    FUN_004f6ae0(0x5a,0x1e,10);
    *(undefined1 *)(param_1 + 0x65) = 1;
  }
  if ((*(char *)(param_1 + 0x65) != '\0') && (iVar6 = FUN_004f6b10(), (double)iVar6 <= 0.0)) {
    *(undefined1 *)(param_1 + 0x65) = 0;
    FUN_004ff160();
    *(undefined1 *)(param_1 + 0x60) = 1;
    if (*(float *)(param_1 + 0x94) == 999999.9) {
      uVar5 = FUN_00437d30("bd11010.wav");
      *(undefined4 *)(param_1 + 0x250) = uVar5;
      fVar9 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x94) = (float)fVar9 + 30.0;
      *(float *)(param_1 + 0x90) = *(float *)(param_1 + 0x94) - 1.0;
      FUN_004f6aa0();
      FUN_004f6ab0("bd11004.otf",DAT_0091757c,0x41000000,0);
      FUN_004f6ae0(0x1e,0x1e,0x1e);
      FUN_005c8950(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x224));
      FUN_005cdbb0(*(undefined4 *)(param_1 + 0x224),0);
      FUN_004ff170(0);
    }
  }
  if ((((*(char *)(param_1 + 0x66) == '\0') &&
       (*(float *)(param_1 + 0x9c) <= 999999.9 && *(float *)(param_1 + 0x9c) != 999999.9)) &&
      (*(float *)(param_1 + 0x94) == 999999.9)) &&
     (cVar4 = FUN_005c96a0(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x224),
                           0x43480000), cVar4 != '\0')) {
    *(undefined1 *)(param_1 + 0x65) = 0;
    *(undefined1 *)(param_1 + 0x60) = 1;
    uVar5 = FUN_00437d30("bd11010.wav");
    *(undefined4 *)(param_1 + 0x250) = uVar5;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x94) = (float)fVar9 + 30.0;
    *(float *)(param_1 + 0x90) = *(float *)(param_1 + 0x94) - 1.0;
    FUN_004f6aa0();
    FUN_004f6ab0("bd11004.otf",DAT_0091757c,0x41000000,0);
    FUN_004f6ae0(0x1e,0x1e,0x1e);
    FUN_005c8950(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x224));
    FUN_005cdbb0(*(undefined4 *)(param_1 + 0x224),0);
    FUN_004ff170(0x3f800000);
  }
  if ((*(char *)(param_1 + 0x66) == '\0') &&
     (*(float *)(param_1 + 0x94) <= 999999.9 && *(float *)(param_1 + 0x94) != 999999.9)) {
    fVar9 = (float10)FUN_004b1670();
    fVar10 = 1.0 - (*(float *)(param_1 + 0x94) - (float)fVar9) / 30.0;
    fVar9 = (float10)FUN_004b1670(0,0x3f800000);
    fVar9 = (float10)FUN_00822970((float)fVar9 * 10.0);
    fVar9 = (float10)FUN_00447ed0((1.0 - fVar10) * (1.0 - fVar10) + fVar10 * 0.2 * (float)fVar9);
    iVar6 = rand();
    if (iVar6 < (int)(fVar10 * 16383.0 * fVar10)) {
      FUN_005cdc40(*(undefined4 *)(param_1 + 0x224),(float)fVar9);
    }
    else {
      FUN_005cdbb0(*(undefined4 *)(param_1 + 0x224),(float)fVar9);
    }
    FUN_004ff190(fVar10 * 4.0 * fVar10);
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x9c) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0x9c)) {
    *(undefined4 *)(param_1 + 0x9c) = 0x497423fe;
    FUN_005ce330(&DAT_0088f654,"xpltrsk");
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xa0) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0xa0)) {
    *(undefined4 *)(param_1 + 0xa0) = 0x497423fe;
    FUN_005ce330(&DAT_0088f64c,"xpltrsk");
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xa4) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0xa4)) {
    *(undefined4 *)(param_1 + 0xa4) = 0x497423fe;
    FUN_005ce330(&DAT_0088f644,"xpltrsk");
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xa8) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0xa8)) {
    *(undefined4 *)(param_1 + 0xa8) = 0x497423fe;
    FUN_005ce330(&DAT_0088f63c,"xpltrsk");
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x90) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0x90)) {
    *(undefined4 *)(param_1 + 0x90) = 0x497423fe;
    FUN_005cd2a0();
    FUN_005cd300("camera_destruct",1000,0,*(undefined4 *)(param_1 + 0x224));
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x94) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0x94)) {
    *(undefined4 *)(param_1 + 0x94) = 0x497423fe;
    fVar9 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x98) = (float)fVar9 + 3.0;
    FUN_0049b760(0x40000000,0x3f000000,0xff,0xff,0xff);
    *(undefined1 *)(param_1 + 0x66) = 1;
    FUN_005ce2f0(*(undefined4 *)(param_1 + 0x224),"xpltrso");
  }
  fVar9 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x98) <= (float)fVar9 && (float)fVar9 != *(float *)(param_1 + 0x98)) {
    FUN_005cd4e0();
    *(undefined4 *)(param_1 + 0x98) = 0x497423fe;
    uVar5 = FUN_00437d30("bd11011.wav");
    *(undefined4 *)(param_1 + 0x238) = uVar5;
    FUN_004f6aa0();
  }
  if (((*(int *)(param_1 + 0x238) != 0) && (*(char *)(param_1 + 0x68) == '\0')) &&
     ((*(char *)(param_1 + 0x67) == '\0' &&
      (cVar4 = FUN_00437d60(*(undefined4 *)(param_1 + 0x238)), cVar4 != '\0')))) {
    *(undefined1 *)(param_1 + 0x68) = 1;
    fVar9 = (float10)FUN_004b1670("bd11win.des");
    FUN_0045c110((float)fVar9 + 3.0);
  }
  fVar9 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x224));
  if (((((float)fVar9 <= 0.0) && (*(char *)(param_1 + 0x66) == '\0')) &&
      (*(char *)(param_1 + 0x68) == '\0')) && (*(char *)(param_1 + 0x67) == '\0')) {
    *(undefined1 *)(param_1 + 0x67) = 1;
    fVar9 = (float10)FUN_004b1670("bd11lsee.des");
    FUN_0045c0f0((float)fVar9 + 1.0);
  }
  return;
}

