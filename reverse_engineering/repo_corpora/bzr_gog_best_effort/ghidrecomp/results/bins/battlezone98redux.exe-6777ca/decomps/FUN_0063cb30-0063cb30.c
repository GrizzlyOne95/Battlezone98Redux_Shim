
void __fastcall FUN_0063cb30(int param_1)

{
  bool bVar1;
  undefined1 uVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  undefined4 uVar7;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar4 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x8c) = uVar4;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,100);
    FUN_005cacb0(1,10);
    local_14 = 0x449a8000;
    local_10 = 0x42880000;
    local_c = 0x47c54a80;
    FUN_005c65a0(&local_14,2);
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  if (*(char *)(param_1 + 0x5a) == '\0') {
    if (*(char *)(param_1 + 0x58) == '\0') {
      *(undefined1 *)(param_1 + 0x58) = 1;
      FUN_005cd2a0();
      uVar4 = FUN_00437d30("bd08001.wav");
      *(undefined4 *)(param_1 + 0xc4) = uVar4;
    }
    bVar1 = false;
    if (*(char *)(param_1 + 0x5c) == '\0') {
      uVar2 = FUN_005cd300("path_camera_intro",2000,0x5dc,*(undefined4 *)(param_1 + 0x8c));
      *(undefined1 *)(param_1 + 0x5c) = uVar2;
    }
    if (*(char *)(param_1 + 0x5c) != '\0') {
      cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0xc4));
      if (cVar3 != '\0') {
        bVar1 = true;
      }
    }
    cVar3 = FUN_005cd560();
    if (cVar3 != '\0') {
      bVar1 = true;
      FUN_00437d80(*(undefined4 *)(param_1 + 0xc4));
    }
    if (bVar1) {
      *(undefined1 *)(param_1 + 0x5c) = 0;
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x5a) = 1;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x68) = (float)fVar6 + 25.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x68) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x68)) &&
     (*(char *)(param_1 + 0x5b) == '\0')) {
    if (*(char *)(param_1 + 0x59) == '\0') {
      *(undefined1 *)(param_1 + 0x59) = 1;
      FUN_005cd2a0();
      uVar4 = FUN_00437d30("bd08002.wav");
      *(undefined4 *)(param_1 + 200) = uVar4;
      FUN_004f6aa0();
      FUN_004f6ab0("bd08001.otf",DAT_0091755c,0x41000000,0);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x6c) = (float)fVar6 + 0.5;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar6 + 90.0;
    }
    uVar2 = FUN_005cd300("path_portalcam",4000,1000,*(undefined4 *)(param_1 + 0xa4));
    *(undefined1 *)(param_1 + 0x5c) = uVar2;
    if (*(char *)(param_1 + 0x5c) == '\0') {
      cVar3 = FUN_005cd560();
      if (cVar3 == '\0') goto LAB_0063ce0c;
    }
    FUN_005cd4e0();
    *(undefined1 *)(param_1 + 0x5b) = 1;
  }
LAB_0063ce0c:
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x6c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x6c)) {
    FUN_005cdea0(*(undefined4 *)(param_1 + 0xa4),0);
    cVar3 = FUN_005cdf00(*(undefined4 *)(param_1 + 0xa4));
    if (cVar3 != '\0') {
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x70) = (float)fVar6 + 1.0;
      *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x70)) {
    fVar6 = (float10)FUN_004b1670();
    if ((float)fVar6 + 45.0 < *(float *)(param_1 + 0x74) ||
        (float)fVar6 + 45.0 == *(float *)(param_1 + 0x74)) {
      uVar4 = *(undefined4 *)(param_1 + 0xa4);
      uVar7 = 2;
      iVar5 = rand();
      uVar4 = FUN_005cdcd0((&PTR_s_cvltnk_008ecae8)[iVar5 % 10],uVar7,uVar4);
      iVar5 = rand();
      if (iVar5 % 100 < 0x32) {
        FUN_005cb960(uVar4,"attack_path1",1);
      }
      else {
        FUN_005cb960(uVar4,"attack_path2",1);
      }
      *(int *)(param_1 + 0xcc) = *(int *)(param_1 + 0xcc) + 1;
      if (*(int *)(param_1 + 0xcc) < 2) {
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x70) = (float)fVar6 + 4.0;
      }
      else {
        *(undefined4 *)(param_1 + 0xcc) = 0;
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x74)) {
    *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    uVar4 = FUN_005cdcd0("cvapc",2,*(undefined4 *)(param_1 + 0xa4));
    *(undefined4 *)(param_1 + 0x94) = uVar4;
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x94),0);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x94),"portal_out",1);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar6 + 20.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar6 + 1.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x84) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x84)) {
    *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
    FUN_00437d30("bd08003.wav");
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x78) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x78)) {
    *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
    FUN_005cbd40(*(undefined4 *)(param_1 + 0x94),1);
    iVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0x94));
    *(undefined4 *)(iVar5 + 0xec) = 0;
    uVar4 = FUN_005c8080("cspilo",2,*(undefined4 *)(param_1 + 0x94),0);
    *(undefined4 *)(param_1 + 0xb0) = uVar4;
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x94),0);
    FUN_005cc140(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0xa4),1);
    *(undefined1 *)(param_1 + 0x5d) = 1;
    FUN_004f6aa0();
    FUN_004f6ab0("bd08001.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("bd08002.otf",DAT_0091755c,0x41000000,0);
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x94));
  }
  if (*(char *)(param_1 + 0x5d) != '\0') {
    cVar3 = FUN_005cdfb0(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0xa4),0x3fa66666)
    ;
    if (cVar3 == '\0') {
      fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xb0));
      if ((double)fVar6 <= 0.0) {
        *(undefined1 *)(param_1 + 99) = 1;
        *(undefined1 *)(param_1 + 0x5d) = 0;
      }
    }
    else {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xb0));
      *(undefined1 *)(param_1 + 0x5d) = 0;
      FUN_004f6a10(0xb4,0x80000000,0x80000000);
      FUN_0049a020();
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x7c) = (float)fVar6 + 180.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x7c)) {
    FUN_0049a080();
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    uVar4 = FUN_005c8250("cspilo",2,"spawn_pilot",0,0);
    *(undefined4 *)(param_1 + 0xb0) = uVar4;
    iVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0x94));
    if (iVar5 != 0) {
      uVar4 = FUN_004ff060("cspilo");
      *(undefined4 *)(iVar5 + 0xec) = uVar4;
    }
    FUN_005ce150(*(undefined4 *)(param_1 + 0x94));
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x94),0);
    FUN_005cc140(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0x94),1);
    *(undefined1 *)(param_1 + 0x5e) = 1;
    *(undefined1 *)(param_1 + 0x5f) = 1;
    FUN_00437d30("bd08004.wav");
    FUN_005cded0(*(undefined4 *)(param_1 + 0xa4));
    FUN_004f6aa0();
    FUN_004f6ab0("bd08002.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("bd08003.otf",DAT_0091755c,0x41000000,0);
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
  }
  if (*(char *)(param_1 + 0x5e) != '\0') {
    FUN_005c8490(param_1 + 0xb0);
  }
  if (*(char *)(param_1 + 0x5e) != '\0') {
    iVar5 = FUN_005c8800(*(undefined4 *)(param_1 + 0x94));
    if (iVar5 == 1) {
      *(undefined1 *)(param_1 + 0x5e) = 0;
      FUN_005cb820(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0x94),1);
    }
  }
  if (*(char *)(param_1 + 0x5e) != '\0') {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xb0));
    if ((float)fVar6 <= 0.0) {
      *(undefined4 *)(param_1 + 0xb0) = 0;
      *(undefined1 *)(param_1 + 0x5e) = 0;
    }
  }
  if (*(char *)(param_1 + 0x5e) != '\0') {
    cVar3 = FUN_005cdfb0(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0x94),0x3fa66666)
    ;
    if (cVar3 != '\0') {
      *(undefined1 *)(param_1 + 0x5e) = 0;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x80) = (float)fVar6 + 60.0;
      iVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0x94));
      if (*(int *)(iVar5 + 0xec) == 0) {
        uVar4 = FUN_004ff060("cspilo");
        *(undefined4 *)(iVar5 + 0xec) = uVar4;
        FUN_00461440(param_1,iVar5);
        FUN_005c83e0(*(undefined4 *)(param_1 + 0xb0));
        *(undefined4 *)(param_1 + 0xb0) = 0;
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x94),0);
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0x8c),1);
      }
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x80)) {
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    cVar3 = FUN_005c8560(param_1 + 0x94);
    if (cVar3 != '\0') {
      *(undefined1 *)(param_1 + 0x60) = 1;
      FUN_005cdea0(*(undefined4 *)(param_1 + 0xa4),1);
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0xa4),1);
    }
  }
  if (*(char *)(param_1 + 0x60) != '\0') {
    iVar5 = FUN_005c8800(*(undefined4 *)(param_1 + 0x94));
    if (iVar5 == 1) {
      *(undefined1 *)(param_1 + 0x60) = 0;
    }
  }
  if (((*(char *)(param_1 + 0x60) != '\0') && (*(char *)(param_1 + 0x65) == '\0')) &&
     (*(char *)(param_1 + 0x66) == '\0')) {
    cVar3 = FUN_005cdfb0(*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0xa4),0x3fa66666)
    ;
    if (cVar3 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x94));
      *(undefined4 *)(param_1 + 0x94) = 0;
      *(undefined1 *)(param_1 + 0x60) = 0;
      *(undefined1 *)(param_1 + 99) = 1;
    }
  }
  fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x90));
  if ((float)fVar6 <= 0.0) {
LAB_0063d711:
    if ((*(char *)(param_1 + 0x65) == '\0') && (*(char *)(param_1 + 0x66) == '\0')) {
      *(undefined1 *)(param_1 + 99) = 1;
      goto LAB_0063d789;
    }
  }
  else {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x9c));
    if ((float)fVar6 <= 0.0) goto LAB_0063d711;
  }
  if (*(int *)(param_1 + 0x94) != 0) {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x94));
    if ((((float)fVar6 <= 0.0) && (*(char *)(param_1 + 0x65) == '\0')) &&
       (*(char *)(param_1 + 0x66) == '\0')) {
      *(undefined4 *)(param_1 + 0x94) = 0;
      *(undefined1 *)(param_1 + 100) = 1;
    }
  }
LAB_0063d789:
  if (*(char *)(param_1 + 99) != '\0') {
    *(undefined1 *)(param_1 + 99) = 0;
    uVar4 = FUN_00437d30("bd08006.wav");
    *(undefined4 *)(param_1 + 0xb8) = uVar4;
    *(undefined1 *)(param_1 + 0x65) = 1;
  }
  if (*(int *)(param_1 + 0xb8) != 0) {
    cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0xb8));
    if (cVar3 != '\0') {
      *(undefined4 *)(param_1 + 0xb8) = 0;
      fVar6 = (float10)FUN_004b1670("bd08lsea.des");
      FUN_0045c0f0((float)fVar6 + 1.0);
    }
  }
  if (*(char *)(param_1 + 100) != '\0') {
    *(undefined1 *)(param_1 + 100) = 0;
    uVar4 = FUN_00437d30("bd08006.wav");
    *(undefined4 *)(param_1 + 0xbc) = uVar4;
    *(undefined1 *)(param_1 + 0x65) = 1;
  }
  if (*(int *)(param_1 + 0xbc) != 0) {
    cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0xbc));
    if (cVar3 != '\0') {
      *(undefined4 *)(param_1 + 0xbc) = 0;
      fVar6 = (float10)FUN_004b1670("bd08lseb.des");
      FUN_0045c0f0((float)fVar6 + 1.0);
    }
  }
  if ((*(int *)(param_1 + 0x94) != 0) && (*(char *)(param_1 + 0x61) == '\0')) {
    iVar5 = FUN_005c8800(*(undefined4 *)(param_1 + 0x94));
    if (iVar5 == 1) {
      *(undefined1 *)(param_1 + 0x61) = 1;
    }
  }
  if ((((*(char *)(param_1 + 0x61) != '\0') && (*(char *)(param_1 + 0x5f) != '\0')) &&
      (*(int *)(param_1 + 0xc0) == 0)) &&
     ((*(char *)(param_1 + 0x66) == '\0' && (*(char *)(param_1 + 0x65) == '\0')))) {
    *(undefined1 *)(param_1 + 0x66) = 1;
    uVar4 = FUN_00437d30("bd08007.wav");
    *(undefined4 *)(param_1 + 0xc0) = uVar4;
  }
  if (*(int *)(param_1 + 0xc0) != 0) {
    cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0xc0));
    if (cVar3 != '\0') {
      fVar6 = (float10)FUN_004b1670("bd08win.des");
      FUN_0045c110((float)fVar6 + 1.0);
      *(undefined4 *)(param_1 + 0xc0) = 0;
    }
  }
  fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa4));
  if ((((double)fVar6 <= 0.0) && (*(char *)(param_1 + 0x66) == '\0')) &&
     (*(char *)(param_1 + 0x65) == '\0')) {
    *(undefined1 *)(param_1 + 0x65) = 1;
    fVar6 = (float10)FUN_004b1670("bd08lsec.des");
    FUN_0045c0f0((float)fVar6 + 1.0);
  }
  FUN_0083e885();
  return;
}

