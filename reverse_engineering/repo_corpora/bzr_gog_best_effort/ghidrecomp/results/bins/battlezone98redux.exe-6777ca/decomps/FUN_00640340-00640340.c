
void __fastcall FUN_00640340(int param_1)

{
  float fVar1;
  bool bVar3;
  undefined1 uVar4;
  char cVar5;
  undefined4 uVar6;
  float10 fVar7;
  int local_14;
  int local_10;
  float fVar2;
  
  uVar6 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x80) = uVar6;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,100);
    FUN_005cadd0(2,0);
    FUN_005cacb0(1,10);
    FUN_004f6aa0();
    FUN_004f6ab0("bd10001.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0(PTR_s_bd10002_otf_008ecb10,DAT_0091755c,0x41000000,0);
    FUN_004f6ab0(PTR_s_bd10003_otf_008ecb14,DAT_0091755c,0x41000000,0);
    FUN_004f6ab0(PTR_s_bd10004_otf_008ecb18,DAT_0091755c,0x41000000,0);
    FUN_004f6ab0(PTR_s_bd10005_otf_008ecb1c,DAT_0091755c,0x41000000,0);
    FUN_004f6ab0(PTR_s_bd10006_otf_008ecb20,DAT_0091755c,0x41000000,0);
    FUN_004f6ab0(PTR_s_bd10007_otf_008ecb24,DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
    FUN_006402a0(0x43c80000,(&PTR_s_defend_a_008ecb38)[local_10],param_1 + 0x5f + local_10,
                 &PTR_s_cvtnk_008ecba8 + local_10 * 9);
  }
  for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
    FUN_006402a0(0x43c80000,(&PTR_s_patrol_a_008ecb28)[local_10],param_1 + 99 + local_10,
                 &PTR_s_cvfigh_008ecb48 + local_10 * 6);
  }
  if (*(char *)(param_1 + 0x59) == '\0') {
    if (*(char *)(param_1 + 0x56) == '\0') {
      FUN_005cd2a0();
      uVar6 = FUN_00437d30("bd10001.wav");
      *(undefined4 *)(param_1 + 0xa8) = uVar6;
      *(undefined1 *)(param_1 + 0x56) = 1;
    }
    if (*(char *)(param_1 + 0x5c) == '\0') {
      uVar4 = FUN_005cd300("camera_start",3000,2000,*(undefined4 *)(param_1 + 0x90));
      *(undefined1 *)(param_1 + 0x5c) = uVar4;
    }
    if (((*(char *)(param_1 + 0x5c) != '\0') &&
        (cVar5 = FUN_00437d60(*(undefined4 *)(param_1 + 0xa8)), cVar5 != '\0')) &&
       (*(float *)(param_1 + 0x78) == 999999.9)) {
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x78) = (float)fVar7 + 2.0;
    }
    fVar7 = (float10)FUN_004b1670();
    fVar1 = *(float *)(param_1 + 0x78);
    fVar2 = *(float *)(param_1 + 0x78);
    cVar5 = FUN_005cd560();
    if (cVar5 != '\0') {
      FUN_00437d80(*(undefined4 *)(param_1 + 0xa8));
    }
    if (cVar5 != '\0' || fVar2 <= (float)fVar7 && (float)fVar7 != fVar1) {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x59) = 1;
    }
  }
  if (*(char *)(param_1 + 0x55) == '\0') {
    *(undefined1 *)(param_1 + 0x55) = 1;
    for (local_14 = 0; local_14 < 6; local_14 = local_14 + 1) {
      fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x84 + local_14 * 4));
      if ((float)fVar7 <= 0.0) {
        if ((&DAT_00920c94)[local_14] == '\0') {
          FUN_004ff0d0((&PTR_s_bd10002_otf_008ecb10)[local_14],DAT_009175b0,0x41000000,0);
          (&DAT_00920c94)[local_14] = 1;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x55) = 0;
      }
    }
    if (*(char *)(param_1 + 0x55) != '\0') {
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x6c) = (float)fVar7 + 10.0;
    }
  }
  if ((*(char *)(param_1 + 0x55) != '\0') &&
     (fVar7 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x6c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x6c))) {
    *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    FUN_005c8250(&DAT_00878c18,1,"navcam_end",0,0);
    uVar6 = FUN_00437d30("bd10002.wav");
    *(undefined4 *)(param_1 + 0xac) = uVar6;
  }
  if (((*(char *)(param_1 + 0x55) != '\0') && (*(int *)(param_1 + 0xac) != 0)) &&
     (cVar5 = FUN_00437d60(*(undefined4 *)(param_1 + 0xac)), cVar5 != '\0')) {
    *(undefined4 *)(param_1 + 0xac) = 0;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar7 + 5.0;
  }
  if ((*(char *)(param_1 + 0x55) != '\0') &&
     (fVar7 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x70) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x70))) {
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    *(undefined1 *)(param_1 + 0x5d) = 1;
    uVar6 = FUN_005c8250("bvapc",1,&DAT_00875928,0,0);
    *(undefined4 *)(param_1 + 0x9c) = uVar6;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x9c),"apc_path",1);
    FUN_005c8250("cbport",0,"portal",0,0);
  }
  if ((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x5a) == '\0')) {
    if (*(char *)(param_1 + 0x57) == '\0') {
      FUN_005cd2a0();
      *(undefined1 *)(param_1 + 0x57) = 1;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar7 + 7.0;
    }
    FUN_005cd300("camera_apc",0x1e,200,*(undefined4 *)(param_1 + 0x9c));
    fVar7 = (float10)FUN_004b1670();
    if ((*(float *)(param_1 + 0x74) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x74))
       || (cVar5 = FUN_005cd560(), cVar5 != '\0')) {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x5a) = 1;
      *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    }
  }
  if ((*(char *)(param_1 + 0x5a) != '\0') && (*(char *)(param_1 + 0x5e) == '\0')) {
    *(undefined1 *)(param_1 + 0x5e) = 1;
    uVar6 = FUN_005c8250("bvrecy",1,"recycler",0,0);
    *(undefined4 *)(param_1 + 0xa0) = uVar6;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xa0),"recycler_path",1);
    for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
      uVar6 = FUN_005c8250("cvtnka",1,"capture",0,0);
      FUN_005cb620(uVar6,0);
      FUN_005cbc20(uVar6,*(undefined4 *)(param_1 + 0xa0),1);
    }
  }
  if ((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 0x5b) == '\0')) {
    if (*(char *)(param_1 + 0x58) == '\0') {
      FUN_005cd2a0();
      uVar6 = FUN_00437d30("bd10003.wav");
      *(undefined4 *)(param_1 + 0xb0) = uVar6;
      *(undefined1 *)(param_1 + 0x58) = 1;
      *(undefined1 *)(param_1 + 0x5c) = 0;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x78) = (float)fVar7 + 10.0;
    }
    bVar3 = false;
    if (*(char *)(param_1 + 0x5c) == '\0') {
      uVar4 = FUN_005cd300("camera_end",0x1e,200,*(undefined4 *)(param_1 + 0xa0));
      *(undefined1 *)(param_1 + 0x5c) = uVar4;
    }
    cVar5 = FUN_00437d60(*(undefined4 *)(param_1 + 0xb0));
    if ((cVar5 != '\0') &&
       (fVar7 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 0x78) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x78))) {
      bVar3 = true;
    }
    cVar5 = FUN_005cd560();
    if (cVar5 != '\0') {
      bVar3 = true;
      FUN_00437d80(*(undefined4 *)(param_1 + 0xb0));
    }
    if (bVar3) {
      *(undefined1 *)(param_1 + 0x5b) = 1;
      fVar7 = (float10)FUN_004b1670("bd10win.des");
      FUN_0045c110((float)fVar7 + 1.0);
    }
  }
  return;
}

