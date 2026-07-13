
void __fastcall FUN_006358b0(int param_1)

{
  float *pfVar1;
  char cVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  int local_10;
  int local_c;
  
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x9c);
  uVar4 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x9c) = uVar4;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,8);
    FUN_005cacb0(1,10);
    FUN_004f6aa0();
    *(undefined1 *)(param_1 + 0x54) = 1;
    FUN_005cb790(*(undefined4 *)(param_1 + 0xf0),0x13,1,0,0,0,0,0);
    FUN_005cb790(*(undefined4 *)(param_1 + 0xf4),0x13,1,0,0,0,0,0);
  }
  if (*(char *)(param_1 + 0x58) == '\0') {
    if (*(char *)(param_1 + 0x55) == '\0') {
      FUN_005cd2a0();
      uVar4 = FUN_005c8250("aspilo",1,"pilot",0,0);
      *(undefined4 *)(param_1 + 0xa4) = uVar4;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xa4),"pilot_path",1);
      FUN_005cdf30(*(undefined4 *)(param_1 + 0x9c));
      uVar4 = FUN_00437d30("bd04001.wav");
      *(undefined4 *)(param_1 + 0x104) = uVar4;
      *(undefined1 *)(param_1 + 0x55) = 1;
    }
    cVar2 = FUN_005cd300("camera_start_up",0x2ee,400,*(undefined4 *)(param_1 + 0xa4));
    if ((*(int *)(param_1 + 0xa8) == 0) &&
       (fVar7 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa4),"nav_1",0),
       (double)fVar7 < 20.0)) {
      uVar4 = FUN_005c8250(&DAT_00878c18,0,"nav_1",0,0);
      *(undefined4 *)(param_1 + 0xa8) = uVar4;
    }
    if ((*(int *)(param_1 + 0xac) == 0) &&
       (fVar7 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa4),"nav_2",0),
       (double)fVar7 < 20.0)) {
      uVar4 = FUN_005c8250(&DAT_00878c18,0,"nav_2",0,0);
      *(undefined4 *)(param_1 + 0xac) = uVar4;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x70) = (float)fVar7 + 2.0;
    }
    cVar3 = FUN_005cd560();
    if (cVar3 != '\0') {
      cVar2 = '\x01';
      FUN_00437d80(*(undefined4 *)(param_1 + 0x104));
    }
    if ((cVar2 != '\0') ||
       (fVar7 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 0x70) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x70))) {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x58) = 1;
      *(undefined1 *)(param_1 + 0x55) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xa4));
      *(undefined4 *)(param_1 + 0xa4) = 0;
      FUN_005cdf70(*(undefined4 *)(param_1 + 0x9c));
      if (*(int *)(param_1 + 0xa8) == 0) {
        uVar4 = FUN_005c8250(&DAT_00878c18,0,"nav_1",0,0);
        *(undefined4 *)(param_1 + 0xa8) = uVar4;
      }
      if (*(int *)(param_1 + 0xac) == 0) {
        uVar4 = FUN_005c8250(&DAT_00878c18,0,"nav_2",0,0);
        *(undefined4 *)(param_1 + 0xac) = uVar4;
      }
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x9c),2);
    }
  }
  if ((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 0x59) == '\0')) {
    if (*(char *)(param_1 + 0x56) == '\0') {
      *(undefined1 *)(param_1 + 0x56) = 1;
      *(undefined1 *)(param_1 + 0x59) = 0;
      FUN_005cd2a0();
      FUN_005cdea0(*(undefined4 *)(param_1 + 0xd8),0);
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x78) = (float)fVar7 + 6.0;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x88) = (float)fVar7 + 4.0;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x80) = (float)fVar7 + 1.5;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x84) = (float)fVar7 + 4.0;
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x7c) = (float)fVar7 + 7.0;
    }
    FUN_005cd300("camera_portal",3000,0,*(undefined4 *)(param_1 + 0xd8));
    cVar2 = FUN_005cd560();
    if (cVar2 != '\0') {
      *(undefined4 *)(param_1 + 0x78) = 0xbf800000;
      FUN_00437d80(*(undefined4 *)(param_1 + 0x114));
    }
    fVar7 = (float10)FUN_004b1670();
    if ((float)fVar7 < *(float *)(param_1 + 0x78) || (float)fVar7 == *(float *)(param_1 + 0x78)) {
      fVar7 = (float10)FUN_004b1670();
      if (*(float *)(param_1 + 0x88) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x88))
      {
        *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
        uVar4 = FUN_00437d30("bd04002.wav");
        *(undefined4 *)(param_1 + 0x114) = uVar4;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
      *(undefined1 *)(param_1 + 0x56) = 0;
      *(undefined1 *)(param_1 + 0x59) = 1;
      FUN_005cd4e0();
    }
  }
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    fVar7 = (float10)FUN_004b1670();
    pfVar1 = (float *)(param_1 + 0x80 + local_c * 4);
    if (*pfVar1 <= (float)fVar7 && (float)fVar7 != *pfVar1) {
      *(undefined4 *)(param_1 + 0x80 + local_c * 4) = 0x497423fe;
      uVar4 = FUN_005cdcd0("cvfigh",2,*(undefined4 *)(param_1 + 0xd8));
      *(undefined4 *)(param_1 + 0xdc + local_c * 4) = uVar4;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xdc + local_c * 4),"unit_path",1);
    }
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x7c)) {
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    FUN_005cded0(*(undefined4 *)(param_1 + 0xd8));
  }
  if ((*(char *)(param_1 + 0x59) != '\0') && (*(char *)(param_1 + 0x5b) == '\0')) {
    uVar4 = FUN_00437d30("bd04003.wav");
    *(undefined4 *)(param_1 + 0x100) = uVar4;
    FUN_004f6aa0();
    FUN_004f6ab0("bd04001.otf",DAT_0091755c,0x41000000,0);
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xf8));
    FUN_005c9640(*(undefined4 *)(param_1 + 0xf8),"Scavenger");
    *(undefined1 *)(param_1 + 0x5b) = 1;
    FUN_005c88e0(*(undefined4 *)(param_1 + 0xf8));
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar7 + 120.0;
  }
  if ((*(char *)(param_1 + 0x5c) == '\0') &&
     (fVar7 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x74) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x74))) {
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar7 + 120.0;
    uVar4 = FUN_00437d30("bd04003.wav");
    *(undefined4 *)(param_1 + 0x100) = uVar4;
  }
  if (((*(int *)(param_1 + 0x9c) == *(int *)(param_1 + 0xf8)) && (*(char *)(param_1 + 0x5c) == '\0')
      ) && (*(char *)(param_1 + 0x5d) == '\0')) {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x100));
    if (cVar2 == '\0') {
      FUN_00437d80(*(undefined4 *)(param_1 + 0x100));
    }
    FUN_004f6aa0();
    FUN_004f6ab0("bd04001.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("bd04002.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x5c) = 1;
    FUN_005c9610(*(undefined4 *)(param_1 + 0xf8));
    *(undefined4 *)(param_1 + 0x74) = 0x497423f0;
    FUN_005cb960(*(undefined4 *)(param_1 + 0xf0),"scav_path",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xf4),"scav_path",1);
    FUN_00437d30("bd04010.wav");
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xd8));
  }
  if (((*(char *)(param_1 + 100) == '\0') && (*(int *)(param_1 + 0xf8) == *(int *)(param_1 + 0x9c)))
     && (fVar7 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf8),"trigger_1",0),
        (float)fVar7 < 400.0)) {
    *(undefined1 *)(param_1 + 100) = 1;
  }
  cVar2 = FUN_005ce0e0(*(undefined4 *)(param_1 + 0x9c),"base_limit");
  if (((cVar2 != '\0') && (*(char *)(param_1 + 0x5f) == '\0')) &&
     (*(undefined1 *)(param_1 + 0x5f) = 1, *(char *)(param_1 + 100) == '\0')) {
    if (*(int *)(param_1 + 0x9c) == *(int *)(param_1 + 0xf8)) {
      uVar4 = FUN_00437d30("bd04005.wav");
      *(undefined4 *)(param_1 + 0x11c) = uVar4;
    }
    else {
      *(undefined1 *)(param_1 + 0x60) = 1;
    }
  }
  if ((*(int *)(param_1 + 0x11c) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x11c)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x11c) = 0;
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar7 + 1.0;
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x8c) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x8c)) {
    *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
    uVar4 = FUN_00437d30("bd04006.wav");
    *(undefined4 *)(param_1 + 0x120) = uVar4;
  }
  if ((*(int *)(param_1 + 0x120) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x120)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x120) = 0;
    *(undefined1 *)(param_1 + 0x60) = 1;
  }
  if ((*(char *)(param_1 + 0x60) != '\0') &&
     ((*(char *)(param_1 + 0x61) == '\0' || (*(int *)(param_1 + 0xa0) != *(int *)(param_1 + 0x9c))))
     ) {
    *(undefined1 *)(param_1 + 0x61) = 1;
    for (local_c = 0; local_c < 9; local_c = local_c + 1) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0xb4 + local_c * 4),*(undefined4 *)(param_1 + 0x9c),1);
    }
  }
  if ((*(char *)(param_1 + 0x5d) == '\0') && (cVar2 = FUN_005cd610("cbport"), cVar2 != '\0')) {
    FUN_004f6aa0();
    FUN_004f6ab0("bd04004.otf",DAT_0091755c,0x41000000,0);
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x90) = (float)fVar7 + 2.0;
    *(undefined1 *)(param_1 + 0x5d) = 1;
    FUN_005c9610(*(undefined4 *)(param_1 + 0xd8));
    FUN_004f6ae0(0x3c,0xf,5);
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x90) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x90)) {
    *(undefined4 *)(param_1 + 0x90) = 0x497423fe;
    uVar4 = FUN_00437d30("bd04004.wav");
    *(undefined4 *)(param_1 + 0x108) = uVar4;
  }
  if ((*(int *)(param_1 + 0x108) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x108)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x108) = 0;
  }
  if ((((*(int *)(param_1 + 0x110) == 0) && (*(int *)(param_1 + 0x10c) == 0)) &&
      (*(char *)(param_1 + 0x60) == '\0')) &&
     (((*(char *)(param_1 + 0x5d) != '\0' && (*(char *)(param_1 + 0x65) == '\0')) &&
      (iVar5 = FUN_004f6b10(), (double)iVar5 <= 0.0)))) {
    FUN_004ff160();
    uVar4 = FUN_00437d30("bd04005.wav");
    *(undefined4 *)(param_1 + 0x10c) = uVar4;
  }
  if ((*(int *)(param_1 + 0x10c) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x10c)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x10c) = 0;
    uVar4 = FUN_00437d30("bd04006.wav");
    *(undefined4 *)(param_1 + 0x110) = uVar4;
  }
  if ((*(int *)(param_1 + 0x110) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x110)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x110) = 0;
    *(undefined1 *)(param_1 + 0x60) = 1;
  }
  if (((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x65) == '\0')) &&
     (cVar2 = FUN_005cd610("obdataa"), cVar2 != '\0')) {
    FUN_004ff150();
    FUN_004ff160();
    *(undefined1 *)(param_1 + 0x65) = 1;
    FUN_00437d30("bd04007.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("bd04003.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0x5e) = 1;
  }
  if (((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 0x62) == '\0')) &&
     (*(int *)(param_1 + 0x9c) != *(int *)(param_1 + 0xf8))) {
    *(undefined1 *)(param_1 + 0x62) = 1;
    *(undefined1 *)(param_1 + 0x60) = 1;
  }
  if ((*(char *)(param_1 + 0x66) == '\0') &&
     (iVar5 = FUN_005cd240(*(undefined4 *)(param_1 + 0xe4)), iVar5 == *(int *)(param_1 + 0x9c))) {
    *(undefined1 *)(param_1 + 0x66) = 1;
    uVar4 = FUN_005c8250(&DAT_00878c18,1,"rv_scout",0,0);
    *(undefined4 *)(param_1 + 0xe8) = uVar4;
    FUN_005c8250("bvfigh",1,"escort_units",0,0);
    FUN_005c8250("bvfigh",1,"escort_units",0,0);
    FUN_005c8250("bvfigh",1,"escort_units",0,0);
    FUN_005c8250("bvtank",1,"escort_units",0,0);
    FUN_005c8250("bvtank",1,"escort_units",0,0);
    FUN_005c8250("bvtank",1,"escort_units",0,0);
    fVar7 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x94) = (float)fVar7 + 30.0;
  }
  fVar7 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x94) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x94)) {
    *(undefined4 *)(param_1 + 0x94) = 0x497423fe;
    uVar4 = FUN_005c8250("bvhraza",1,"bomber_wing_x5_spawn_point",0,0);
    FUN_005ccfa0(uVar4,0x45dac000);
    FUN_005ccf70(uVar4,0x45dac000);
    FUN_005cb960(uVar4,"trigger_1",1);
    uVar6 = FUN_005c8250("bvhraza",1,"bomber_wing_x5_spawn_point",0,0);
    FUN_005cbce0(uVar6,uVar4,1);
    uVar6 = FUN_005c8250("bvhraza",1,"bomber_wing_x5_spawn_point",0,0);
    FUN_005cbce0(uVar6,uVar4,1);
    uVar6 = FUN_005c8250("bvhraza",1,"bomber_wing_x5_spawn_point",0,0);
    FUN_005cbce0(uVar6,uVar4,1);
    uVar6 = FUN_005c8250("bvhraza",1,"bomber_wing_x5_spawn_point",0,0);
    FUN_005cbce0(uVar6,uVar4,1);
    uVar4 = FUN_005c8250(&DAT_00878c18,1,"proposed_end_area",0,0);
    *(undefined4 *)(param_1 + 0xe8) = uVar4;
    FUN_005cd7f0(*(undefined4 *)(param_1 + 0xe8),"Drop Zone");
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xe8));
    for (local_10 = 0; local_10 < 5; local_10 = local_10 + 1) {
      uVar4 = FUN_005c8250("cvfighg",2,"chinese_scout_x6_spawn_point",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xec),1);
    }
    for (local_10 = 0; local_10 < 2; local_10 = local_10 + 1) {
      uVar4 = FUN_005c8250("cvfighg",2,"attack_1",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xec),1);
    }
    for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
      uVar4 = FUN_005c8250("cvfighg",2,"attack_2",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xec),1);
    }
    for (local_10 = 0; local_10 < 1; local_10 = local_10 + 1) {
      uVar4 = FUN_005c8250("cvtnk",2,"attack_3",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xec),1);
    }
  }
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    if ((*(char *)(param_1 + local_c + 0x67) == '\0') &&
       (fVar7 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xec),
                                      (&PTR_s_return_1_008fe6d4)[local_c],0), (float)fVar7 < 300.0))
    {
      *(undefined1 *)(param_1 + local_c + 0x67) = 1;
      uVar4 = FUN_005c8250("cvfigh",2,(&PTR_s_return_1_008fe6d4)[local_c],0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xec),1);
      uVar4 = FUN_005c8250("cvfigh",2,(&PTR_s_return_1_008fe6d4)[local_c],0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xec),1);
    }
  }
  fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xec));
  if ((((double)fVar7 <= 0.0) && (*(char *)(param_1 + 0x6b) == '\0')) &&
     (*(char *)(param_1 + 0x6c) == '\0')) {
    fVar7 = (float10)FUN_004b1670("bd04lose.des");
    FUN_0045c0f0((float)fVar7 + 1.0);
    *(undefined1 *)(param_1 + 0x6b) = 1;
  }
  if (((*(char *)(param_1 + 0x5e) != '\0') &&
      (fVar7 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xe4),*(undefined4 *)(param_1 + 0xe8)
                                    ), (double)fVar7 < 50.0)) &&
     ((*(char *)(param_1 + 0x6c) == '\0' && (*(char *)(param_1 + 0x6b) == '\0')))) {
    FUN_004f6aa0();
    FUN_004f6ab0("bd04003.otf",DAT_009175b0,0x41000000,0);
    *(undefined1 *)(param_1 + 0x6c) = 1;
    uVar4 = FUN_00437d30("bd04008.wav");
    *(undefined4 *)(param_1 + 0x118) = uVar4;
  }
  if ((*(int *)(param_1 + 0x118) != 0) &&
     (cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x118)), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0x118) = 0;
    FUN_0045c110(0x3dcccccd,"bd04win.des");
  }
  fVar7 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xd8));
  if ((((float)fVar7 <= 0.0) && (*(char *)(param_1 + 0x6c) == '\0')) &&
     (*(char *)(param_1 + 0x6b) == '\0')) {
    *(undefined1 *)(param_1 + 0x6b) = 1;
    fVar7 = (float10)FUN_004b1670("bd04lose.des");
    FUN_0045c0f0((float)fVar7 + 1.0);
  }
  return;
}

