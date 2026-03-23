
void __fastcall FUN_00651560(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  float10 fVar7;
  float10 fVar8;
  uint local_cc;
  int local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  char local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar4 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x6c) = uVar4;
  iVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0x98));
  fVar7 = (float10)FUN_0046fbd0();
  fVar8 = (float10)FUN_004624f0();
  if ((float)fVar7 != (float)fVar8) {
    fVar7 = (float10)FUN_004624f0();
    fVar8 = (float10)FUN_0046fbd0();
    (**(code **)(*(int *)(iVar5 + 0x18) + 0x28))((float)fVar7 - (float)fVar8);
  }
  iVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0x90));
  fVar7 = (float10)FUN_0046fbd0();
  fVar8 = (float10)FUN_004624f0();
  if ((float)fVar7 != (float)fVar8) {
    fVar7 = (float10)FUN_004624f0();
    fVar8 = (float10)FUN_0046fbd0();
    (**(code **)(*(int *)(iVar5 + 0x18) + 0x28))((float)fVar7 - (float)fVar8);
  }
  if (*(int *)(param_1 + 0x1d4) == 0x10) {
    iVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0x6c));
    fVar7 = (float10)FUN_0046fbd0();
    fVar8 = (float10)FUN_004624f0();
    if ((float)fVar7 != (float)fVar8) {
      fVar7 = (float10)FUN_004624f0();
      fVar8 = (float10)FUN_0046fbd0();
      (**(code **)(*(int *)(iVar5 + 0x18) + 0x28))((float)fVar7 - (float)fVar8);
    }
  }
  if ((*(int *)(param_1 + 0x1dc) != 0) && (*(int *)(param_1 + 0x1d4) < 0x10)) {
    FUN_00651220();
  }
  if ((*(int *)(param_1 + 0x1d4) != 1) && (*(int *)(param_1 + 0x6c) != *(int *)(param_1 + 0x70))) {
    if (*(char *)(param_1 + 0x58) != '\0') {
      FUN_005cd6c0(*(undefined4 *)(param_1 + 0x70));
      FUN_005cd790(*(undefined4 *)(param_1 + 0x70),0);
    }
    *(undefined1 *)(param_1 + 0x58) = 0;
  }
  cVar3 = *(char *)(param_1 + 0x54);
  cVar1 = FUN_005cd750(*(undefined4 *)(param_1 + 0x6c));
  if (cVar3 != cVar1) {
    FUN_006510b0();
    *(bool *)(param_1 + 0x54) = *(char *)(param_1 + 0x54) == '\0';
  }
  switch(*(undefined4 *)(param_1 + 0x1d4)) {
  case 1:
    FUN_005cadd0(1,0);
    FUN_005cacb0(1,10);
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x6c);
    *(undefined4 *)(param_1 + 0x1d4) = 2;
    uVar4 = FUN_00437d30("ch04001.wav");
    *(undefined4 *)(param_1 + 0x1e0) = uVar4;
    FUN_005cd2a0();
  case 2:
    cVar3 = FUN_005cd300("camera_start",1000,0x4b0,*(undefined4 *)(param_1 + 0x74));
    if ((cVar3 != '\0') || (cVar3 = FUN_005cd560(), cVar3 != '\0')) {
      FUN_00437d80(*(undefined4 *)(param_1 + 0x1e0));
      FUN_005cd4e0();
      *(undefined4 *)(param_1 + 0x1d4) = 3;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x5c) = (float)fVar7 + 5.0;
    }
    break;
  case 3:
    fVar7 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x5c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x5c)) {
      FUN_00437d30("ch04007.wav");
      FUN_004f6ae0(DAT_025cfa1c * -5 + 0x9b,0x80000000,0x80000000);
      *(undefined4 *)(param_1 + 0x1d4) = 4;
      *(undefined4 *)(param_1 + 0x1d8) = 0;
      FUN_006510b0();
      FUN_005c88e0(*(undefined4 *)(param_1 + 0x78));
    }
    break;
  case 4:
    iVar5 = FUN_004f6b10();
    if (iVar5 < 1) {
      FUN_00437d30("ch04006.wav");
      fVar7 = (float10)FUN_004b1670("ch04lsea.des");
      FUN_0045c0f0((float)fVar7 + 2.0);
      *(undefined4 *)(param_1 + 0x1d4) = 100;
    }
    else {
      fVar7 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x6c),
                                    *(undefined4 *)(param_1 + 0x78 + *(int *)(param_1 + 0x1d8) * 4))
      ;
      if ((float)fVar7 < 50.0) {
        if (*(int *)(param_1 + 0x1d8) < 5) {
          *(int *)(param_1 + 0x1d8) = *(int *)(param_1 + 0x1d8) + 1;
          sprintf(local_14,"nav_%d",*(int *)(param_1 + 0x1d8) + 1);
          uVar4 = FUN_005c8250(&DAT_00878c18,1,local_14,0,0);
          *(undefined4 *)(param_1 + 0x78 + *(int *)(param_1 + 0x1d8) * 4) = uVar4;
          if (*(int *)(param_1 + 0x1d8) == 5) {
            FUN_005cd7f0(*(undefined4 *)(param_1 + 0x78 + *(int *)(param_1 + 0x1d8) * 4),
                         "Pit Entrance");
          }
          FUN_005c88e0(*(undefined4 *)(param_1 + 0x78 + *(int *)(param_1 + 0x1d8) * 4));
        }
        else {
          for (local_28 = 0; local_28 <= *(int *)(param_1 + 0x1d8); local_28 = local_28 + 1) {
            FUN_005c83e0(*(undefined4 *)(param_1 + 0x78 + local_28 * 4));
          }
          FUN_004ff160();
          *(undefined4 *)(param_1 + 0x1d4) = 6;
          FUN_006510b0();
          FUN_005c88b0(*(undefined4 *)(param_1 + 0x6c),2);
          FUN_005c95e0(*(undefined4 *)(param_1 + 0x74));
        }
      }
    }
    break;
  case 6:
    uVar2 = FUN_005ce630(*(undefined4 *)(param_1 + 0x74));
    *(undefined1 *)(param_1 + 0x56) = uVar2;
    fVar7 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x6c),"trigger_1",0);
    if (((float)fVar7 <= 70.0) || (*(char *)(param_1 + 0x56) != '\0')) {
      *(undefined4 *)(param_1 + 0x1e0) = 0;
      *(undefined4 *)(param_1 + 0x1d4) = 7;
    }
    break;
  case 7:
    if ((*(int *)(param_1 + 0x1e0) == 0) ||
       (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1e0)), cVar3 != '\0')) {
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x5c) = (float)fVar7 + 1.0;
      *(undefined4 *)(param_1 + 0x1d4) = 8;
    }
    break;
  case 8:
    fVar7 = (float10)FUN_004b1670();
    if ((float)fVar7 < *(float *)(param_1 + 0x5c) || (float)fVar7 == *(float *)(param_1 + 0x5c))
    break;
    uVar4 = FUN_005c8250("sspilo",2,"pilot_1",0,0,*(undefined4 *)(param_1 + 0x15c),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_2",0,0,*(undefined4 *)(param_1 + 0x160),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_3",0,0,*(undefined4 *)(param_1 + 0x164),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_4",0,0,*(undefined4 *)(param_1 + 0x168),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_5",0,0,*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_6",0,0,*(undefined4 *)(param_1 + 0x170),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_11",0,0,*(undefined4 *)(param_1 + 0x184),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_14",0,0,*(undefined4 *)(param_1 + 400),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_17",0,0,*(undefined4 *)(param_1 + 0x19c),1);
    FUN_005cc180(uVar4);
    uVar4 = FUN_005c8250("sspilo",2,"pilot_25",0,0,*(undefined4 *)(param_1 + 0x1bc),1);
    FUN_005cc180(uVar4);
    *(undefined4 *)(param_1 + 0x1d4) = 9;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x5c) = (float)fVar7 + 5.0;
    FUN_005cd2a0();
  case 9:
    FUN_005cd300("camera_alarm",2000,0,*(undefined4 *)(param_1 + 0x94));
    cVar3 = FUN_005cd560();
    if ((cVar3 != '\0') ||
       (fVar7 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 0x5c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x5c))) {
      FUN_005cd4e0();
      uVar4 = FUN_005c8250("sspilo",2,"pilot_7",0,0,*(undefined4 *)(param_1 + 0x174),1);
      FUN_005cc140(uVar4);
      uVar4 = FUN_005c8250("sspilo",2,"pilot_8",0,0,*(undefined4 *)(param_1 + 0x178),1);
      FUN_005cc140(uVar4);
      uVar4 = FUN_005c8250("sspilo",2,"pilot_9",0,0,*(undefined4 *)(param_1 + 0x17c),1);
      FUN_005cc140(uVar4);
      uVar4 = FUN_005c8250("sspilo",2,"pilot_10",0,0,*(undefined4 *)(param_1 + 0x180),1);
      FUN_005cc140(uVar4);
      uVar4 = FUN_005c8250("sspilo",2,"pilot_12",0,0,*(undefined4 *)(param_1 + 0x188),1);
      FUN_005cc140(uVar4);
      uVar4 = FUN_005c8250("sspilo",2,"pilot_13",0,0,*(undefined4 *)(param_1 + 0x18c),1);
      FUN_005cc140(uVar4);
      uVar4 = FUN_005c7e90("empty_15");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      uVar4 = FUN_005c7e90("empty_16");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      uVar4 = FUN_005c7e90("empty_18");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      uVar4 = FUN_005c7e90("empty_19");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      uVar4 = FUN_005c7e90("empty_20");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      uVar4 = FUN_005c7e90("empty_21");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      uVar4 = FUN_005c7e90("empty_22");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      uVar4 = FUN_005c7e90("empty_23");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      uVar4 = FUN_005c7e90("empty_24");
      uVar4 = FUN_005c8080("sspilo",2,uVar4,0,uVar4,1);
      FUN_005cc180(uVar4);
      cVar3 = FUN_005cd750(*(undefined4 *)(param_1 + 0x6c));
      if (cVar3 == '\0') {
        *(undefined4 *)(param_1 + 0x1dc) = 1;
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x6c),1);
        for (local_28 = 0; local_28 < 0x19; local_28 = local_28 + 1) {
          *(undefined4 *)(param_1 + 0x9c + local_28 * 4) =
               *(undefined4 *)(param_1 + 0x15c + local_28 * 4);
          FUN_005cb820(*(undefined4 *)(param_1 + 0x9c + local_28 * 4),
                       *(undefined4 *)(param_1 + 0x6c),1);
        }
        for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1) {
          *(undefined4 *)(param_1 + 0x100 + local_28 * 4) =
               *(undefined4 *)(param_1 + 0x1c0 + local_28 * 4);
          FUN_005cb820(*(undefined4 *)(param_1 + 0x100 + local_28 * 4),
                       *(undefined4 *)(param_1 + 0x6c),1);
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x1dc) = 0;
      }
      *(undefined4 *)(param_1 + 0x1d4) = 10;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x1dc) != 0) {
      if (*(int *)(param_1 + 0x1e4) == 0) {
        cVar3 = FUN_005cd750(*(undefined4 *)(param_1 + 0x6c));
        if (cVar3 != '\0') {
          uVar4 = FUN_00437d30("ch04002.wav");
          *(undefined4 *)(param_1 + 0x1e4) = uVar4;
          FUN_005cd6c0(*(undefined4 *)(param_1 + 0x6c));
          FUN_005cd790(*(undefined4 *)(param_1 + 0x6c),0);
        }
      }
      else {
        cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1e4));
        if (cVar3 != '\0') {
          *(undefined4 *)(param_1 + 0x1e4) = 0;
        }
      }
    }
    fVar7 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x6c),*(undefined4 *)(param_1 + 0x74));
    if ((float)fVar7 <= 200.0) {
      uVar4 = FUN_005c8250("svfigh",2,"fighter_1",0,0,"figh1_path",1);
      FUN_005cb960(uVar4);
      uVar4 = FUN_005c8250("svfigh",2,"fighter_2",0,0,"figh2_path",1);
      FUN_005cb960(uVar4);
      *(undefined4 *)(param_1 + 0x1d4) = 0xb;
    }
    break;
  case 0xb:
    if (*(int *)(param_1 + 0x1dc) != 0) {
      if (*(int *)(param_1 + 0x1e4) == 0) {
        cVar3 = FUN_005cd750(*(undefined4 *)(param_1 + 0x6c));
        if (cVar3 != '\0') {
          uVar4 = FUN_00437d30("ch04002.wav");
          *(undefined4 *)(param_1 + 0x1e4) = uVar4;
          FUN_005cd6c0(*(undefined4 *)(param_1 + 0x6c));
          FUN_005cd790(*(undefined4 *)(param_1 + 0x6c),0);
        }
      }
      else {
        cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1e4));
        if (cVar3 != '\0') {
          *(undefined4 *)(param_1 + 0x1e4) = 0;
        }
      }
    }
    if (*(char *)(param_1 + 0x56) == '\0') {
      uVar2 = FUN_005ce630(*(undefined4 *)(param_1 + 0x74));
      *(undefined1 *)(param_1 + 0x56) = uVar2;
    }
    if (*(char *)(param_1 + 0x56) != '\0') {
      *(undefined4 *)(param_1 + 0x1e0) = 0;
      FUN_005c9610(*(undefined4 *)(param_1 + 0x74));
      *(undefined4 *)(param_1 + 0x1d4) = 0xc;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x5c) = (float)fVar7 + 45.0;
      FUN_006510b0();
      if (*(int *)(param_1 + 0x1dc) == 0) {
        fVar7 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar7 + 5.0;
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x6c),1);
        *(undefined4 *)(param_1 + 0x1dc) = 1;
      }
    }
    break;
  case 0xc:
    fVar7 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 100)) {
      *(undefined4 *)(param_1 + 100) = 0x47c34f80;
      cVar3 = FUN_005cd750(*(undefined4 *)(param_1 + 0x6c));
      if (cVar3 != '\0') {
        uVar4 = FUN_00437d30("ch04002.wav");
        *(undefined4 *)(param_1 + 0x1e0) = uVar4;
        FUN_005cd6c0(*(undefined4 *)(param_1 + 0x6c));
      }
      FUN_005cd790(*(undefined4 *)(param_1 + 0x6c),0);
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x6c),1);
      for (local_28 = 0; local_28 < 0x19; local_28 = local_28 + 1) {
        *(undefined4 *)(param_1 + 0x9c + local_28 * 4) =
             *(undefined4 *)(param_1 + 0x15c + local_28 * 4);
        FUN_005cb820(*(undefined4 *)(param_1 + 0x9c + local_28 * 4),*(undefined4 *)(param_1 + 0x6c),
                     1);
      }
      for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1) {
        *(undefined4 *)(param_1 + 0x100 + local_28 * 4) =
             *(undefined4 *)(param_1 + 0x1c0 + local_28 * 4);
        FUN_005cb820(*(undefined4 *)(param_1 + 0x100 + local_28 * 4),*(undefined4 *)(param_1 + 0x6c)
                     ,1);
      }
    }
    if ((80000.0 < *(float *)(param_1 + 100)) &&
       ((*(int *)(param_1 + 0x1e0) == 0 ||
        (cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1e0)), cVar3 != '\0')))) {
      uVar4 = FUN_00437d30("ch04003.wav");
      *(undefined4 *)(param_1 + 0x1e0) = uVar4;
      for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1) {
        uVar4 = FUN_005c8250("svfigha",2,"chase_1",0,0);
        *(undefined4 *)(param_1 + 0x110 + local_28 * 4) = uVar4;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x110 + local_28 * 4),*(undefined4 *)(param_1 + 0x6c)
                     ,1);
        uVar4 = FUN_005c8250("svtanka",2,"chase_2",0,0);
        *(undefined4 *)(param_1 + 0x120 + local_28 * 4) = uVar4;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x120 + local_28 * 4),*(undefined4 *)(param_1 + 0x6c)
                     ,1);
        uVar4 = FUN_005c8250("svfigha",2,"chase_3",0,0);
        *(undefined4 *)(param_1 + 0x130 + local_28 * 4) = uVar4;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x130 + local_28 * 4),*(undefined4 *)(param_1 + 0x6c)
                     ,1);
      }
      uVar4 = FUN_005c8250("svfigh",2,"portal_units",0,0);
      *(undefined4 *)(param_1 + 0x140) = uVar4;
      uVar4 = FUN_005c8250("svfigh",2,"portal_units",0,0);
      *(undefined4 *)(param_1 + 0x144) = uVar4;
      uVar4 = FUN_005c8250("svfigh",2,"portal_units",0,0);
      *(undefined4 *)(param_1 + 0x148) = uVar4;
      uVar4 = FUN_005c8250("svfigh",2,"portal_units",0,0);
      *(undefined4 *)(param_1 + 0x14c) = uVar4;
      uVar4 = FUN_005c8250("svfigh",2,"portal_units",0,0);
      *(undefined4 *)(param_1 + 0x150) = uVar4;
      uVar4 = FUN_005c8250("svfigh",2,"portal_units",0,0);
      *(undefined4 *)(param_1 + 0x154) = uVar4;
      FUN_005cdea0(*(undefined4 *)(param_1 + 0x90),1);
      local_20 = 0x44cee000;
      local_1c = 0x43260000;
      local_18 = 0x47c65b00;
      uVar4 = FUN_005c8380("svfigh",1,&local_20,0);
      fVar7 = (float10)FUN_005ccf40(uVar4);
      FUN_005ccf70(uVar4,(float)fVar7 / 2.0);
      iVar5 = FUN_005cd070(uVar4);
      FUN_005cd0a0(uVar4,iVar5 / 2);
      FUN_005ccd70(uVar4);
      *(undefined4 *)(param_1 + 0x1d4) = 0xd;
    }
    break;
  case 0xd:
    cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1e0));
    if (cVar3 != '\0') {
      uVar4 = FUN_00437d30("ch04008.wav");
      *(undefined4 *)(param_1 + 0x1e0) = uVar4;
      *(undefined4 *)(param_1 + 0x1d4) = 0xe;
    }
    break;
  case 0xe:
    cVar3 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1e0));
    if (cVar3 != '\0') {
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x60) = ((float)fVar7 + 120.0 + 15.0 + 25.0) - (float)(DAT_025cfa1c * 5);
      uVar4 = FUN_005c8250(&DAT_00878c18,1,"nav_base",0,0);
      *(undefined4 *)(param_1 + 0x78) = uVar4;
      FUN_005c88e0(*(undefined4 *)(param_1 + 0x78));
      *(undefined4 *)(param_1 + 0x1d4) = 0xf;
    }
    break;
  case 0xf:
    fVar7 = (float10)FUN_004b1670();
    if ((float)fVar7 < *(float *)(param_1 + 0x60) || (float)fVar7 == *(float *)(param_1 + 0x60)) {
      fVar7 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x6c),*(undefined4 *)(param_1 + 0x90))
      ;
      if ((float)fVar7 < 100.0) {
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x78));
        FUN_004ff160();
        FUN_00462630(*(undefined4 *)(param_1 + 0x6c));
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x6c),2);
        iVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0x6c));
        fVar7 = (float10)FUN_0046fbd0();
        fVar8 = (float10)FUN_004624f0();
        if ((float)fVar7 != (float)fVar8) {
          fVar7 = (float10)FUN_004624f0();
          fVar8 = (float10)FUN_0046fbd0();
          (**(code **)(*(int *)(iVar5 + 0x18) + 0x28))((float)fVar7 - (float)fVar8);
        }
        FUN_005cdf30(*(undefined4 *)(param_1 + 0x6c));
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x6c),2);
        *(undefined4 *)(param_1 + 0x1d4) = 0x10;
        FUN_005cd2a0();
        *(undefined1 *)(param_1 + 0x57) = 0;
        *(undefined4 *)(param_1 + 0x5c) = 0;
      }
    }
    else {
      fVar7 = (float10)FUN_004b1670("ch04lseb.des");
      FUN_0045c0f0((float)fVar7 + 2.0);
      *(undefined4 *)(param_1 + 0x1d4) = 100;
    }
    break;
  case 0x10:
    for (local_28 = 0; local_28 < 0x19; local_28 = local_28 + 1) {
      cVar3 = FUN_005c84d0(param_1 + 0x9c + local_28 * 4);
      if (cVar3 != '\0') {
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x9c + local_28 * 4),1);
      }
    }
    for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1) {
      cVar3 = FUN_005c84d0(param_1 + 0x100 + local_28 * 4);
      if (cVar3 != '\0') {
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x100 + local_28 * 4),1);
      }
      cVar3 = FUN_005c84d0(param_1 + 0x110 + local_28 * 4);
      if (cVar3 != '\0') {
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x110 + local_28 * 4),1);
      }
      cVar3 = FUN_005c84d0(param_1 + 0x120 + local_28 * 4);
      if (cVar3 != '\0') {
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x120 + local_28 * 4),1);
      }
      cVar3 = FUN_005c84d0(param_1 + 0x130 + local_28 * 4);
      if (cVar3 != '\0') {
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x130 + local_28 * 4),1);
      }
    }
    for (local_28 = 0; local_28 < 6; local_28 = local_28 + 1) {
      cVar3 = FUN_005c84d0(param_1 + 0x140 + local_28 * 4);
      if (cVar3 != '\0') {
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x140 + local_28 * 4),1);
      }
    }
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x6c),2);
    if (*(char *)(param_1 + 0x57) == '\0') {
      uVar6 = FUN_005cd390("auto_end",500,3000);
      local_cc = uVar6 & 0xff;
    }
    else {
      FUN_005cd390("auto_end",500,0);
    }
    if ((*(char *)(param_1 + 0x57) == '\0') && (local_cc != 0)) {
      *(undefined1 *)(param_1 + 0x57) = 1;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x5c) = (float)fVar7 + 2.0;
    }
    if ((*(char *)(param_1 + 0x57) != '\0') &&
       (fVar7 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 0x5c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x5c))) {
      FUN_005cded0(*(undefined4 *)(param_1 + 0x90));
      *(undefined4 *)(param_1 + 0x1d4) = 100;
      fVar7 = (float10)FUN_004b1670("ch04win.des");
      FUN_0045c110((float)fVar7 + 4.0);
    }
  }
  if (*(int *)(param_1 + 0x6c) != *(int *)(param_1 + 0x70)) {
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x6c);
  }
  FUN_0083e885();
  return;
}

