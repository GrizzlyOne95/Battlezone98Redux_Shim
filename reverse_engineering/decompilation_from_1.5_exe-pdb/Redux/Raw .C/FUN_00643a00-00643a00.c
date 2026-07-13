
void __fastcall FUN_00643a00(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float10 fVar7;
  int local_28;
  char local_1d;
  int local_1c;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xac) = uVar2;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,0x32);
    FUN_005cadd0(2,10);
    FUN_005cacb0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  if (*(char *)(param_1 + 0x5a) == '\0') {
    if (*(char *)(param_1 + 0x58) == '\0') {
      *(undefined1 *)(param_1 + 0x58) = 1;
      FUN_005cd2a0();
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x98) = (float)fVar7 + 3.0;
    }
    local_1d = FUN_005cd300("camera_start",300,2000,*(undefined4 *)(param_1 + 0xb4));
    fVar7 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x98) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x98)) {
      *(undefined4 *)(param_1 + 0x98) = 0x497423fe;
      *(undefined1 *)(param_1 + 0x5c) = 1;
      uVar2 = FUN_00437d30("bd12001.wav");
      *(undefined4 *)(param_1 + 0xf0) = uVar2;
    }
    cVar1 = FUN_005cd560();
    if ((cVar1 != '\0') && (local_1d = '\x01', *(int *)(param_1 + 0xf0) != 0)) {
      FUN_00437d80(*(undefined4 *)(param_1 + 0xf0));
    }
    if (local_1d != '\0') {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x5a) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0("bd12001.otf",DAT_0091755c,0x41000000,0);
    }
  }
  if (*(char *)(param_1 + 0x5e) == '\0') {
    *(undefined1 *)(param_1 + 0x5e) = 1;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar7 + 120.0;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar7 + 240.0;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar7 + 360.0;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar7 + 480.0;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar7 + 780.0;
    *(float *)(param_1 + 0xa0) = *(float *)(param_1 + 0x80) - 2.0;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar7 + 546.0;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar7 + 552.0;
    *(float *)(param_1 + 0xa4) = *(float *)(param_1 + 0x88) + 2.0;
    *(float *)(param_1 + 0x8c) = *(float *)(param_1 + 0x80) + 5.0;
    *(undefined4 *)(param_1 + 0x9c) = 0x42700000;
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x70)) {
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    uVar2 = FUN_005c8250("cvfigh",2,"attack_1",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 200),1);
    uVar3 = FUN_005c8250("cvfigh",2,"attack_1",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 200),1);
    uVar4 = FUN_005c8250("cvfigh",2,"attack_1",0,0);
    FUN_005cd6f0(uVar4);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 200),1);
    uVar4 = FUN_005c8250("cvtnk",2,"defend_1",0,0);
    FUN_005cd6f0(uVar4);
    FUN_005cbce0(uVar4,uVar2,1);
    uVar2 = FUN_005c8250("cvtnk",2,"defend_1",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cbce0(uVar2,uVar3,1);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x74)) {
    *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    uVar2 = FUN_005c8250("cvfigh",2,"attack_2",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xcc),1);
    uVar3 = FUN_005c8250("cvfigh",2,"attack_2",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xcc),1);
    uVar4 = FUN_005c8250("cvfigh",2,"attack_2",0,0);
    FUN_005cd6f0(uVar4);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xcc),1);
    uVar5 = FUN_005c8250("cvhtnk",2,"attack_2",0,0);
    FUN_005cd6f0(uVar5);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xcc),1);
    uVar6 = FUN_005c8250("cvfigh",2,"defend_2",0,0);
    FUN_005cd6f0(uVar6);
    FUN_005cbce0(uVar6,uVar2,1);
    uVar2 = FUN_005c8250("cvfigh",2,"defend_2",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cbce0(uVar2,uVar3,1);
    uVar2 = FUN_005c8250("cvfigh",2,"defend_2",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cbce0(uVar2,uVar4,1);
    uVar2 = FUN_005c8250("cvhtnk",2,"defend_2",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cbce0(uVar2,uVar5,1);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x78) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x78)) {
    *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
    uVar2 = FUN_005c8250("cvhraz",2,"attack_3",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xd0),1);
    uVar3 = FUN_005c8250("cvhraz",2,"attack_3",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xd0),1);
    uVar4 = FUN_005c8250("cvfigh",2,"attack_3",0,0);
    FUN_005cd6f0(uVar4);
    FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xd0),1);
    uVar5 = FUN_005c8250("cvfigh",2,"attack_3",0,0);
    FUN_005cd6f0(uVar5);
    FUN_005cb820(uVar5,*(undefined4 *)(param_1 + 0xd0),1);
    uVar6 = FUN_005c8250("cvtnk",2,"defend_3",0,0);
    FUN_005cd6f0(uVar6);
    FUN_005cbce0(uVar6,uVar2,1);
    uVar2 = FUN_005c8250("cvtnk",2,"defend_3",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cbce0(uVar2,uVar3,1);
    uVar2 = FUN_005c8250("cvfigh",2,"defend_3",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cbce0(uVar2,uVar4,1);
    uVar2 = FUN_005c8250("cvfigh",2,"defend_3",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cbce0(uVar2,uVar5,1);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x7c)) {
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    uVar2 = FUN_005c8250("cvwalk",2,"attack_4",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xb8),1);
    uVar3 = FUN_005c8250("cvltnk",2,"defend_4",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar3 = FUN_005c8250("cvltnk",2,"defend_4",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar2 = FUN_005c8250("cvwalk",2,"attack_5",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xbc),1);
    uVar3 = FUN_005c8250("cvltnk",2,"defend_5",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar3 = FUN_005c8250("cvltnk",2,"defend_5",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar2 = FUN_005c8250("cvwalk",2,"attack_6",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xc0),1);
    uVar3 = FUN_005c8250("cvtnk",2,"defend_6",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar3 = FUN_005c8250("cvtnk",2,"defend_6",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar2 = FUN_005c8250("cvwalk",2,"attack_7",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xc4),1);
    uVar3 = FUN_005c8250("cvtnk",2,"defend_7",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar3 = FUN_005c8250("cvtnk",2,"defend_7",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar2 = FUN_005c8250("cvwalk",2,"attack_8",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xb4),1);
    uVar3 = FUN_005c8250("cvhtnk",2,"defend_8",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
    uVar3 = FUN_005c8250("cvhtnk",2,"defend_8",0,0);
    FUN_005cd6f0(uVar3);
    FUN_005cbce0(uVar3,uVar2,1);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xa0) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0xa0)) {
    *(undefined4 *)(param_1 + 0xa0) = 0x497423fe;
    FUN_005cdea0(*(undefined4 *)(param_1 + 0xb4),0);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xa4) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0xa4)) {
    *(undefined4 *)(param_1 + 0xa4) = 0x497423fe;
    FUN_005cded0(*(undefined4 *)(param_1 + 0xb4));
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x80)) {
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    uVar2 = FUN_005cdcd0("bvrecyd",1,*(undefined4 *)(param_1 + 0xb4));
    *(undefined4 *)(param_1 + 0xb0) = uVar2;
    local_14 = 0x44e62000;
    local_10 = 0x42d0999a;
    local_c = 0x47c55300;
    FUN_005cb880(*(undefined4 *)(param_1 + 0xb0),&local_14,1);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x84) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x84)) {
    *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
    uVar2 = FUN_005cdcd0("bvtank",1,*(undefined4 *)(param_1 + 0xb4));
    FUN_005cb960(uVar2,"follow",1);
    uVar2 = FUN_005cdcd0("bvtank",1,*(undefined4 *)(param_1 + 0xb4));
    FUN_005cb960(uVar2,"follow",1);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x88) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x88)) {
    *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
    uVar2 = FUN_005cdcd0("bvfigh",1,*(undefined4 *)(param_1 + 0xb4));
    FUN_005cb960(uVar2,"follow",1);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x8c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x8c)) {
    *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
    FUN_004f6aa0();
    FUN_004f6ab0("bd12001.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("bd12002.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x55) = 1;
  }
  if ((*(char *)(param_1 + 0x55) != '\0') && (*(char *)(param_1 + 0x56) == '\0')) {
    *(undefined1 *)(param_1 + 0x56) = 1;
    for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1) {
      fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xd8 + local_28 * 4));
      if (0.0 < (double)fVar7) {
        *(undefined1 *)(param_1 + 0x56) = 0;
        break;
      }
    }
    if (*(char *)(param_1 + 0x56) != '\0') {
      uVar2 = FUN_00437d30("bd12003.wav");
      *(undefined4 *)(param_1 + 0xec) = uVar2;
    }
  }
  if (((*(char *)(param_1 + 0x56) != '\0') && (*(char *)(param_1 + 0x6c) == '\0')) &&
     (*(char *)(param_1 + 0x6b) == '\0')) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xec));
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x6c) = 1;
      fVar7 = (float10)FUN_004b1670("bd12win.des");
      FUN_0045c110((float)fVar7 + 1.0);
    }
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x9c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x9c)) {
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar7 + 60.0;
    FUN_005c8250("npscr1",0,"scrap_1",0,0);
    FUN_005c8250("npscr1",0,"scrap_1",0,0);
    FUN_005c8250("npscr1",0,"scrap_1",0,0);
    FUN_005c8250("npscr1",0,"scrap_2",0,0);
    FUN_005c8250("npscr1",0,"scrap_2",0,0);
    FUN_005c8250("npscr1",0,"scrap_2",0,0);
  }
  for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1) {
    if (*(char *)(param_1 + local_1c + 0x5f) == '\0') {
      fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 200 + local_1c * 4));
      if ((double)fVar7 < 0.25) {
        *(undefined1 *)(param_1 + local_1c + 0x5f) = 1;
        FUN_00437d30((&PTR_s_bd12005_wav_008ecd74)[local_1c]);
      }
    }
    if (*(char *)(param_1 + local_1c + 99) == '\0') {
      fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xb8 + local_1c * 4));
      if ((double)fVar7 < 0.25) {
        *(undefined1 *)(param_1 + local_1c + 99) = 1;
        FUN_00437d30((&PTR_s_bd12005_wav_008ecd74)[local_1c]);
      }
    }
  }
  local_1c = 0;
  do {
    if (3 < local_1c) {
      if (((*(char *)(param_1 + 0x67) == '\0') && (*(char *)(param_1 + 0x68) == '\0')) &&
         ((*(char *)(param_1 + 0x69) == '\0' && (*(char *)(param_1 + 0x6a) == '\0')))) {
        FUN_005ce190(*(undefined4 *)(param_1 + 0xb4));
      }
      fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xb4));
      if (((float)fVar7 <= 0.0) && (*(char *)(param_1 + 0x5d) == '\0')) {
        *(undefined1 *)(param_1 + 0x5d) = 1;
        uVar2 = FUN_00437d30("bd12004.wav");
        *(undefined4 *)(param_1 + 0xf4) = uVar2;
      }
      if (((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x6b) == '\0')) &&
         (*(char *)(param_1 + 0x6c) == '\0')) {
        cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xf4));
        if (cVar1 != '\0') {
          *(undefined1 *)(param_1 + 0x6b) = 1;
          fVar7 = (float10)FUN_004b1670("bd12lsea.des");
          FUN_0045c0f0((float)fVar7 + 2.0);
        }
      }
      FUN_0083e885();
      return;
    }
    if (*(char *)(param_1 + local_1c + 0x67) == '\0') {
      fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 200 + local_1c * 4));
      if (0.0 < (double)fVar7) {
        fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xb8 + local_1c * 4));
        if (0.0 < (double)fVar7) goto LAB_00644d2c;
      }
      *(undefined1 *)(param_1 + local_1c + 0x67) = 1;
      uVar2 = FUN_005c8250("cvltnk",2,(&PTR_s_despor_1_008ecd84)[local_1c],0,0);
      FUN_005cd6f0(uVar2);
      FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xb4),1);
      uVar2 = FUN_005c8250("cvltnk",2,(&PTR_s_despor_1_008ecd84)[local_1c],0,0);
      FUN_005cd6f0(uVar2);
      FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xb4),1);
    }
LAB_00644d2c:
    local_1c = local_1c + 1;
  } while( true );
}

