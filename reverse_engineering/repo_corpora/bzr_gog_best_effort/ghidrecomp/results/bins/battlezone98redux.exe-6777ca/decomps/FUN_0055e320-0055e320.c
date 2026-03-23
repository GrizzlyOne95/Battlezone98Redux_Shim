
void __fastcall FUN_0055e320(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  int local_10;
  
  uVar2 = FUN_005c7fb0();
  if (*(char *)(param_1 + 0x57) == '\0') {
    *(undefined4 *)(param_1 + 0xc4) = 0;
    uVar3 = FUN_005c7e90("spcamr0_camerapod");
    FUN_005c9640(uVar3,"Black Dog Base");
    FUN_005c8840(uVar3,2);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar6 + 120.0;
    FUN_005c8250("avmine",2,&DAT_00882c00,0,0);
    FUN_005c8250("avmine",2,&DAT_00882c08,0,0);
    FUN_005c8250("avmine",2,&DAT_00882c10,0,0);
    uVar3 = FUN_005c7e90("abcafe8_i76building");
    *(undefined4 *)(param_1 + 0x84) = uVar3;
    uVar3 = FUN_005c7e90("avartl3_howitzer");
    *(undefined4 *)(param_1 + 0x88) = uVar3;
    uVar3 = FUN_005c7e90("avartl4_howitzer");
    *(undefined4 *)(param_1 + 0x8c) = uVar3;
    uVar3 = FUN_005c7e90("avturr0_turrettank");
    *(undefined4 *)(param_1 + 0x90) = uVar3;
    uVar3 = FUN_005c7e90("avturr1_turrettank");
    *(undefined4 *)(param_1 + 0x94) = uVar3;
    uVar3 = FUN_005c7e90("defender1");
    *(undefined4 *)(param_1 + 0x98) = uVar3;
    uVar3 = FUN_005c7e90("defender2");
    *(undefined4 *)(param_1 + 0x9c) = uVar3;
    uVar3 = FUN_005c7e90("svrecy0_recycler");
    *(undefined4 *)(param_1 + 0xa4) = uVar3;
    uVar3 = FUN_005c7e90("absilo0_scrapsilo");
    *(undefined4 *)(param_1 + 0xa0) = uVar3;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x88),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x8c),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x98),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x9c),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x90),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x94),1);
    FUN_005cadd0(1,0x14);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 100) = (float)fVar6 + 10.0;
    FUN_00437d30("misns601.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("misns601.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("misns602.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x57) = 1;
  }
  if ((*(char *)(param_1 + 0x5a) == '\0') &&
     (((fVar6 = (float10)FUN_005c9800(uVar2,&DAT_00882c00,1), (float)fVar6 < 250.0 ||
       (fVar6 = (float10)FUN_005c9800(uVar2,&DAT_00882c08,1), (float)fVar6 < 250.0)) ||
      (fVar6 = (float10)FUN_005c9800(uVar2,&DAT_00882c10,1), (float)fVar6 < 250.0)))) {
    FUN_00437d30("misns602.wav");
    *(undefined1 *)(param_1 + 0x5a) = 1;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x78) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x78)) {
    FUN_005cb2d0("misns6.aip",2);
    *(undefined4 *)(param_1 + 0x78) = 0x47c34f80;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 100) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 100)) {
    for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
      cVar1 = FUN_005c84d0(param_1 + 0xa8 + local_10 * 4);
      if (cVar1 != '\0') {
        fVar6 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0xa8 + local_10 * 4));
        if ((0.0 < (float)fVar6) && (*(char *)(param_1 + 0x5d) == '\0')) {
          *(undefined1 *)(param_1 + 0x5d) = 1;
          uVar3 = FUN_005c8250("bvraz",2,"counter1",0,0);
          uVar4 = FUN_005c8250("bvraz",2,"counter2",0,0);
          FUN_005cb820(uVar3,uVar2,1);
          FUN_005cb820(uVar4,uVar2,1);
        }
        iVar5 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0xa8 + local_10 * 4));
        if (iVar5 == 0) {
          switch(*(undefined4 *)(param_1 + 0xc4)) {
          case 0:
            FUN_005cbbb0(*(undefined4 *)(param_1 + 0xa8 + local_10 * 4),&DAT_00882bfc,1);
            break;
          case 1:
            FUN_005cbbb0(*(undefined4 *)(param_1 + 0xa8 + local_10 * 4),&DAT_00882c04,1);
            break;
          case 2:
            FUN_005cbbb0(*(undefined4 *)(param_1 + 0xa8 + local_10 * 4),&DAT_00882c0c,1);
            break;
          case 3:
            FUN_005cbbb0(*(undefined4 *)(param_1 + 0xa8 + local_10 * 4),&DAT_00882c00,1);
            break;
          case 4:
            FUN_005cbbb0(*(undefined4 *)(param_1 + 0xa8 + local_10 * 4),&DAT_00882c08,1);
            break;
          case 5:
            FUN_005cbbb0(*(undefined4 *)(param_1 + 0xa8 + local_10 * 4),&DAT_00882c10,1);
          }
          *(int *)(param_1 + 0xc4) = *(int *)(param_1 + 0xc4) + 1;
          if (5 < *(int *)(param_1 + 0xc4)) {
            *(undefined4 *)(param_1 + 0xc4) = 0;
          }
        }
      }
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar6 + 3.0;
    }
  }
  if ((*(char *)(param_1 + 0x5e) == '\0') &&
     (fVar6 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x68) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x68))) {
    fVar6 = (float10)FUN_005c9800(uVar2,"counter2",0);
    if (400.0 <= (float)fVar6) {
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x68) = (float)fVar6 + 3.0;
    }
    else {
      FUN_005c8250("bvtank",2,"counter2",0,0);
      FUN_005c8250("bvtank",2,"counter2",0,0);
      FUN_005c8250("bvturr",2,"counter2",0,0);
      *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + 300.0;
    }
  }
  if ((*(char *)(param_1 + 0x5f) == '\0') &&
     (fVar6 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x6c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x6c))) {
    fVar6 = (float10)FUN_005c9800(uVar2,"counter3",0);
    if (400.0 <= (float)fVar6) {
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x6c) = (float)fVar6 + 3.0;
    }
    else {
      FUN_005c8250("bvtank",2,"counter3",0,0);
      FUN_005c8250("bvtank",2,"counter3",0,0);
      FUN_005c8250("bvturr",2,"counter3",0,0);
      *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 300.0;
    }
  }
  if ((*(char *)(param_1 + 0x60) == '\0') &&
     (fVar6 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x70) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x70))) {
    fVar6 = (float10)FUN_005c9800(uVar2,"counter4",0);
    if (200.0 <= (float)fVar6) {
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x70) = (float)fVar6 + 3.0;
    }
    else {
      FUN_005c8250("bvtank",2,"counter4",0,0);
      FUN_005c8250("bvtank",2,"counter4",0,0);
      FUN_005c8250("bvturr",2,"counter4",0,0);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x70) = (float)fVar6 + 300.0;
    }
  }
  if ((*(char *)(param_1 + 0x61) == '\0') &&
     (fVar6 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x74) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x74))) {
    fVar6 = (float10)FUN_005c9800(uVar2,"counter5",0);
    if (200.0 <= (float)fVar6) {
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar6 + 3.0;
    }
    else {
      FUN_005c8250("bvtank",2,"counter5",0,0);
      FUN_005c8250("bvtank",2,"counter5",0,0);
      FUN_005c8250("bvturr",2,"counter5",0,0);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar6 + 300.0;
    }
  }
  if ((*(char *)(param_1 + 0x5c) == '\0') &&
     ((fVar6 = (float10)FUN_005c9780(uVar2,*(undefined4 *)(param_1 + 0x88)), (float)fVar6 < 200.0 ||
      (fVar6 = (float10)FUN_005c9780(uVar2,*(undefined4 *)(param_1 + 0x8c)), (float)fVar6 < 200.0)))
     ) {
    *(undefined1 *)(param_1 + 0x5c) = 1;
    FUN_00437d30("misns605.wav");
  }
  if ((*(char *)(param_1 + 0x62) == '\0') &&
     (fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa0),uVar2), (float)fVar6 < 400.0)) {
    uVar3 = FUN_005c8250("bvltnk",2,"counter_attack",0,0);
    FUN_005cb960(uVar3,"counter_attack_path",1);
    uVar3 = FUN_005c8250("bvltnk",2,"counter_attack",0,0);
    FUN_005cb960(uVar3,"counter_attack_path",1);
    uVar3 = FUN_005c8250("bvtank",2,"counter_attack",0,0);
    FUN_005cb960(uVar3,"counter_attack_path",1);
    uVar3 = FUN_005c8250("bvtank",2,"counter_attack",0,0);
    FUN_005cb960(uVar3,"counter_attack_path",1);
    uVar3 = FUN_005c8250("bvrckt",2,"counter_attack",0,0);
    FUN_005cb960(uVar3,"counter_attack_path",1);
    FUN_00437d30("misns603.wav");
    *(undefined1 *)(param_1 + 0x62) = 1;
  }
  if ((*(char *)(param_1 + 0x56) == '\0') &&
     (fVar6 = (float10)FUN_005c9780(uVar2,*(undefined4 *)(param_1 + 0x84)), (float)fVar6 < 300.0)) {
    FUN_004f6aa0();
    FUN_004f6ab0("misns601.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("misns602.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x56) = 1;
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x84));
  }
  if ((*(char *)(param_1 + 0x54) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 == '\0'))
  {
    uVar2 = FUN_00437d30("misns609.wav");
    *(undefined4 *)(param_1 + 200) = uVar2;
    *(undefined1 *)(param_1 + 0x58) = 1;
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  if ((*(char *)(param_1 + 0x54) != '\0') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 200)), cVar1 != '\0')) {
    fVar6 = (float10)FUN_004b1670("misns6w1.des");
    FUN_0045c110((float)fVar6 + 0.0);
    *(undefined1 *)(param_1 + 0x54) = 0;
  }
  if (((*(char *)(param_1 + 0x54) == '\0') && (*(char *)(param_1 + 0x55) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0xa4), cVar1 == '\0')) {
    *(undefined1 *)(param_1 + 0x55) = 1;
    fVar6 = (float10)FUN_004b1670("misns6l1.des");
    FUN_0045c0f0((float)fVar6 + 2.0);
  }
  return;
}

