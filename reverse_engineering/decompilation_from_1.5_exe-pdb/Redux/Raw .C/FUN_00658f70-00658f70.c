
void __fastcall FUN_00658f70(int param_1)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  undefined *puVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 local_1c;
  char local_13;
  int local_c;
  
  *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(param_1 + 0xa8);
  uVar4 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xa8) = uVar4;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cacb0(1,10);
    FUN_005cadd0(1,8);
    *(undefined1 *)(param_1 + 0x54) = 1;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x90) = (float)fVar6 + 90.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar6 + 780.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa0) = (float)fVar6 + 840.0;
  }
  if ((*(int *)(param_1 + 0xa8) != *(int *)(param_1 + 0xac)) && (*(char *)(param_1 + 0x5e) == '\0'))
  {
    FUN_005c88b0(*(undefined4 *)(param_1 + 0xa8),1);
  }
  if (*(char *)(param_1 + 0x5b) == '\0') {
    if (*(char *)(param_1 + 0x58) == '\0') {
      *(undefined1 *)(param_1 + 0x58) = 1;
      FUN_005cd2a0();
      uVar4 = FUN_00437d30("ch07001.wav");
      *(undefined4 *)(param_1 + 0x134) = uVar4;
    }
    local_13 = FUN_005cd300("cin_start",800,0x960,*(undefined4 *)(param_1 + 0xb0));
    cVar2 = FUN_005cd560();
    if (cVar2 != '\0') {
      local_13 = '\x01';
      FUN_00437d80(*(undefined4 *)(param_1 + 0x134));
    }
    if (local_13 != '\0') {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x5b) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0("ch07001.otf",DAT_0091755c,0x41000000,0);
    }
  }
  for (local_c = 0; local_c < 7; local_c = local_c + 1) {
    cVar2 = FUN_005c84d0(param_1 + 0xd4 + local_c * 4);
    if ((cVar2 != '\0') && (*(char *)(param_1 + local_c + 0x71) == '\0')) {
      fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa8),
                                    *(undefined4 *)(param_1 + 0xd4 + local_c * 4));
      if ((float)fVar6 < 160.0) {
        FUN_005cb820(*(undefined4 *)(param_1 + 0xd4 + local_c * 4),*(undefined4 *)(param_1 + 0xa8),1
                    );
        *(undefined1 *)(param_1 + local_c + 0x71) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x5f) == '\0') {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0xb0));
    if ((float)fVar6 < 30.0) {
      *(undefined1 *)(param_1 + 0x5e) = 1;
      *(undefined1 *)(param_1 + 0x5f) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5e) != '\0') {
    if (*(char *)(param_1 + 0x59) == '\0') {
      FUN_005cd2a0();
      *(undefined1 *)(param_1 + 0x59) = 1;
      FUN_005cdf30(*(undefined4 *)(param_1 + 0xa8));
      FUN_005c88b0(*(undefined4 *)(param_1 + 0xa8),2);
      uVar4 = FUN_005c8250("sspilo",0,"fake_spn",0,0);
      *(undefined4 *)(param_1 + 0xb4) = uVar4;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xb4),"fake_vanish",1);
    }
    FUN_005cd300("cin_burglar",400,0,*(undefined4 *)(param_1 + 0xb0));
    if (*(int *)(param_1 + 0xb4) != 0) {
      fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xb4),"fake_vanish",0);
      if ((float)fVar6 < 10.0) {
        FUN_005c83e0(*(undefined4 *)(param_1 + 0xb4));
        *(undefined4 *)(param_1 + 0xb4) = 0;
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x94) = (float)fVar6 + 3.0;
      }
    }
    fVar6 = (float10)FUN_004b1670();
    if ((float)fVar6 < *(float *)(param_1 + 0x94) || (float)fVar6 == *(float *)(param_1 + 0x94)) {
      cVar2 = FUN_005cd560();
      if (cVar2 == '\0') goto LAB_00659439;
    }
    FUN_005cd4e0();
    if (*(int *)(param_1 + 0xb4) != 0) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xb4));
    }
    FUN_005c88b0(*(undefined4 *)(param_1 + 0xa8),1);
    FUN_005cdf70(*(undefined4 *)(param_1 + 0xa8));
    FUN_005c8cb0(*(undefined4 *)(param_1 + 0xa8),"burglar_exit",0);
    *(undefined1 *)(param_1 + 0x5e) = 0;
    if (*(int *)(param_1 + 0x128) == 0) {
      *(undefined1 *)(param_1 + 0x61) = 1;
    }
    else if (*(int *)(param_1 + 0x128) == 1) {
      *(undefined1 *)(param_1 + 0x62) = 1;
    }
    *(undefined1 *)(param_1 + 0x55) = 1;
  }
LAB_00659439:
  if (*(char *)(param_1 + 0x61) != '\0') {
    if (*(char *)(param_1 + 0x5a) == '\0') {
      *(undefined1 *)(param_1 + 0x5a) = 1;
      FUN_005cd2a0();
      uVar4 = FUN_00437d30("ch07002.wav");
      *(undefined4 *)(param_1 + 0x138) = uVar4;
      uVar4 = FUN_005c8250(&DAT_00878c18,1,"nav_north",0,0);
      *(undefined4 *)(param_1 + 0x120) = uVar4;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0x120),"North Bridge");
    }
    bVar1 = false;
    if (*(char *)(param_1 + 99) == '\0') {
      uVar3 = FUN_005cd300("cin_north",0x640,0x708,*(undefined4 *)(param_1 + 0xf0));
      *(undefined1 *)(param_1 + 99) = uVar3;
    }
    if (*(char *)(param_1 + 99) != '\0') {
      cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x138));
      if (cVar2 != '\0') {
        bVar1 = true;
      }
    }
    cVar2 = FUN_005cd560();
    if (cVar2 != '\0') {
      bVar1 = true;
      FUN_00437d80(*(undefined4 *)(param_1 + 0x138));
    }
    if (bVar1) {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x61) = 0;
      FUN_004f6aa0();
      FUN_004f6ab0("ch07001.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("ch07002n.otf",DAT_0091755c,0x41000000,0);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x98) = (float)fVar6 + 10.0;
    }
  }
  if (*(char *)(param_1 + 0x62) != '\0') {
    if (*(char *)(param_1 + 0x5a) == '\0') {
      FUN_007d6a70("East Sequence now playing");
      *(undefined1 *)(param_1 + 0x5a) = 1;
      FUN_005cd2a0();
      uVar4 = FUN_00437d30("ch07003.wav");
      *(undefined4 *)(param_1 + 0x138) = uVar4;
      uVar4 = FUN_005c8250(&DAT_00878c18,1,"nav_east",0,0);
      *(undefined4 *)(param_1 + 0x120) = uVar4;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0x120),"East Bridge");
    }
    bVar1 = false;
    if (*(char *)(param_1 + 99) == '\0') {
      uVar3 = FUN_005cd300("cin_east",0x640,0x708,*(undefined4 *)(param_1 + 0xf4));
      *(undefined1 *)(param_1 + 99) = uVar3;
    }
    if (*(char *)(param_1 + 99) != '\0') {
      cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x138));
      if (cVar2 != '\0') {
        bVar1 = true;
      }
    }
    cVar2 = FUN_005cd560();
    if (cVar2 != '\0') {
      bVar1 = true;
      FUN_00437d80(*(undefined4 *)(param_1 + 0x138));
    }
    if (bVar1) {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x62) = 0;
      FUN_004f6aa0();
      FUN_004f6ab0("ch07001.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("ch07002e.otf",DAT_0091755c,0x41000000,0);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x98) = (float)fVar6 + 10.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x98) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x98)) {
    *(undefined4 *)(param_1 + 0x98) = 0x497423fe;
    for (local_c = 0; local_c < 6; local_c = local_c + 1) {
      cVar2 = FUN_005c84d0(param_1 + 0xbc + local_c * 4);
      if (cVar2 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0xbc + local_c * 4),*(undefined4 *)(param_1 + 0xa8),1
                    );
      }
    }
    FUN_00437d30("ch07004.wav");
  }
  if (*(char *)(param_1 + 100) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_1_trig",0);
    if ((float)fVar6 < 900.0) {
      *(undefined1 *)(param_1 + 100) = 1;
      uVar4 = FUN_005c8250("ssusera",2,"zn_1_snip_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("svturr",2,"zn_1_turr_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"zn_1_pilo_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  if (*(char *)(param_1 + 0x65) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_2_trig",0);
    if ((float)fVar6 < 900.0) {
      *(undefined1 *)(param_1 + 0x65) = 1;
      uVar4 = FUN_005c8250("ssusera",2,"zn_2_snip_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("svturr",2,"zn_2_turr_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"zn_2_pilo_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  if (*(char *)(param_1 + 0x66) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_3_trig",0);
    if ((float)fVar6 < 900.0) {
      *(undefined1 *)(param_1 + 0x66) = 1;
      uVar4 = FUN_005c8250("ssusera",2,"zn_3_snip_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"zn_3_snip_3_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("svturr",2,"zn_3_turr_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  if (*(char *)(param_1 + 0x67) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_4_trig",0);
    if ((float)fVar6 < 900.0) {
      *(undefined1 *)(param_1 + 0x67) = 1;
      uVar4 = FUN_005c8250("ssusera",2,"zn_4_snip_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"zn_4_snip_2_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("svturr",2,"zn_4_turr_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  if (*(char *)(param_1 + 0x68) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_5_trig",0);
    if ((float)fVar6 < 900.0) {
      *(undefined1 *)(param_1 + 0x68) = 1;
      uVar4 = FUN_005c8250("ssusera",2,"zn_5_snip_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("svturr",2,"zn_5_turr_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"zn_5_pilo_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  if (*(char *)(param_1 + 0x69) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_6_trig",0);
    if ((float)fVar6 < 900.0) {
      *(undefined1 *)(param_1 + 0x69) = 1;
      uVar4 = FUN_005c8250("ssusera",2,"zn_6_snip_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("svturr",2,"zn_6_turr_2_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  if (*(char *)(param_1 + 0x6a) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_7_trig",0);
    if ((float)fVar6 < 900.0) {
      *(undefined1 *)(param_1 + 0x6a) = 1;
      uVar4 = FUN_005c8250("ssusera",2,"zn_7_snip_1_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"zn_7_snip_2_spn",0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x9c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x9c)) &&
     (*(char *)(param_1 + 0x5f) != '\0')) {
    *(undefined4 *)(param_1 + 0x9c) = 0x497423fe;
    FUN_00437d30("ch07005.wav");
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xa0) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0xa0)) {
    if (*(int *)(param_1 + 0x130) == *(int *)(param_1 + 300)) {
      local_1c = FUN_005c8250("svapca",2,(&PTR_s_north_spn_008fe744)[*(int *)(param_1 + 0x128)],0,0)
      ;
      *(undefined4 *)(param_1 + 0xb8) = local_1c;
    }
    else if ((*(int *)(param_1 + 0x130) == 2) ||
            ((*(int *)(param_1 + 0x130) == 1 && (*(int *)(param_1 + 300) == 2)))) {
      uVar9 = 0;
      uVar8 = 0;
      puVar7 = (&PTR_s_north_spn_008fe744)[*(int *)(param_1 + 0x128)];
      uVar4 = 2;
      iVar5 = rand();
      local_1c = FUN_005c8250((&PTR_s_svapcc_008ece3c)[iVar5 % 0xf],uVar4,puVar7,uVar8,uVar9);
    }
    else {
      local_1c = FUN_005c8250("svapcb",2,(&PTR_s_north_spn_008fe744)[*(int *)(param_1 + 0x128)],0,0)
      ;
    }
    FUN_005cb960(local_1c,(&PTR_s_north_path_008fe754)[*(int *)(param_1 + 0x128)],1);
    iVar5 = FUN_00462630(local_1c);
    *(undefined4 *)(iVar5 + 0xec) = 0;
    uVar4 = FUN_005c8250("svfigh",2,(&PTR_s_north_spn_008fe744)[*(int *)(param_1 + 0x128)],0,0);
    iVar5 = FUN_00462630(uVar4);
    *(undefined4 *)(iVar5 + 0xec) = 0;
    FUN_005cbce0(uVar4,local_1c,1);
    *(int *)(param_1 + 0x130) = *(int *)(param_1 + 0x130) + 1;
    if (*(int *)(param_1 + 0x130) == 3) {
      *(undefined4 *)(param_1 + 0xa0) = 0x497423fe;
      *(undefined1 *)(param_1 + 0x6b) = 1;
    }
    else {
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0xa0) = (float)fVar6 + 8.0;
    }
  }
  if (*(char *)(param_1 + 0x78) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),
                                  (&PTR_s_north_trig_008fe74c)[*(int *)(param_1 + 0x128)],0);
    if ((float)fVar6 < 350.0) {
      *(undefined1 *)(param_1 + 0x78) = 1;
      uVar4 = FUN_005c8250("sssold",2,
                           (&PTR_s_sold_north_1_spn_008fe6fc)[*(int *)(param_1 + 0x128) * 2],0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sssold",2,
                           (&PTR_s_sold_north_2_spn_008fe700)[*(int *)(param_1 + 0x128) * 2],0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,
                           (&PTR_s_pilo_north_1_spn_008fe72c)[*(int *)(param_1 + 0x128) * 2],0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,
                           (&PTR_s_pilo_north_2_spn_008fe730)[*(int *)(param_1 + 0x128) * 2],0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      *(undefined1 *)(param_1 + 0x56) = 1;
      FUN_004f6aa0();
      if (*(char *)(param_1 + 0x55) == '\0') {
        FUN_004f6ab0("ch07001.otf",DAT_0091755c,0x41000000,0);
      }
      else {
        FUN_004f6ab0("ch07001.otf",DAT_009175b0,0x41000000,0);
      }
      if (*(char *)(param_1 + 0x5f) != '\0') {
        FUN_004f6ab0((&PTR_s_ch07002n_otf_008ece78)[*(int *)(param_1 + 0x128)],DAT_009175b0,
                     0x41000000,0);
      }
      FUN_004f6ab0("ch07003.otf",DAT_0091755c,0x41000000,0);
    }
  }
  if (*(char *)(param_1 + 0x6c) == '\0') {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xf0 + *(int *)(param_1 + 0x128) * 4));
    if ((double)fVar6 <= 0.0) {
      *(undefined1 *)(param_1 + 0x6c) = 1;
      FUN_005ce330((&PTR_s_expl_north_spn_008fe73c)[*(int *)(param_1 + 0x128)],"xtorxplb");
      uVar4 = FUN_005c8250("sspilo",2,
                           (&PTR_s_north_sold_1_spn_008fe70c)[*(int *)(param_1 + 0x128) * 3],0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,
                           (&PTR_s_north_sold_2_spn_008fe710)[*(int *)(param_1 + 0x128) * 3],0,0);
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  if (*(int *)(param_1 + 0xb8) != 0) {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xb8));
    if (((double)fVar6 <= 0.0) && (*(char *)(param_1 + 0x57) == '\0')) {
      *(undefined1 *)(param_1 + 0x57) = 1;
      FUN_004f6aa0();
      if (*(char *)(param_1 + 0x55) == '\0') {
        FUN_004f6ab0("ch07001.otf",DAT_0091755c,0x41000000,0);
      }
      else {
        FUN_004f6ab0("ch07001.otf",DAT_009175b0,0x41000000,0);
      }
      if (*(char *)(param_1 + 0x5f) != '\0') {
        FUN_004f6ab0((&PTR_s_ch07002n_otf_008ece78)[*(int *)(param_1 + 0x128)],DAT_009175b0,
                     0x41000000,0);
      }
      FUN_004f6ab0("ch07003.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("ch07004.otf",DAT_0091755c,0x41000000,0);
      FUN_00437d30("ch07008.wav");
      uVar4 = FUN_005c8250(&DAT_00878c18,1,"nav_end",0,0);
      FUN_005cd7f0(uVar4,"Drop Zone");
    }
  }
  if (*(char *)(param_1 + 0x57) != '\0') {
    if (*(char *)(param_1 + 0x79) == '\0') {
      fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_8_trig",0);
      if ((float)fVar6 < 800.0) {
        *(undefined1 *)(param_1 + 0x79) = 1;
        uVar4 = FUN_005c8250("sspilo",2,"back_1_1_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
        uVar4 = FUN_005c8250("sspilo",2,"back_1_2_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      }
    }
    if (*(char *)(param_1 + 0x7a) == '\0') {
      fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_9_trig",0);
      if ((float)fVar6 < 800.0) {
        *(undefined1 *)(param_1 + 0x7a) = 1;
        uVar4 = FUN_005c8250("sspilo",2,"back_2_1_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
        uVar4 = FUN_005c8250("sspilo",2,"back_2_2_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      }
    }
    if (*(char *)(param_1 + 0x7b) == '\0') {
      fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"nav_end",0);
      if ((float)fVar6 < 1000.0) {
        *(undefined1 *)(param_1 + 0x7b) = 1;
        uVar4 = FUN_005c8250("sspilo",2,"pilo_end_1_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
        uVar4 = FUN_005c8250("sspilo",2,"pilo_end_2_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
        uVar4 = FUN_005c8250("sspilo",2,"pilo_end_3_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      }
    }
    if (*(char *)(param_1 + 0x7c) == '\0') {
      fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"zn_3_trig",0);
      if ((float)fVar6 < 800.0) {
        *(undefined1 *)(param_1 + 0x7c) = 1;
        uVar4 = FUN_005c8250("sspilo",2,"back_1_5_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
        uVar4 = FUN_005c8250("sspilo",2,"back_1_6_spn",0,0);
        FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      }
    }
  }
  if (((*(int *)(param_1 + 0xb8) != 0) && (*(char *)(param_1 + 0x80) == '\0')) &&
     (*(char *)(param_1 + 0x7f) == '\0')) {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xb8),
                                  (&PTR_s_north_wav_008fe6f4)[*(int *)(param_1 + 0x128)],0);
    if (((float)fVar6 < 50.0) && (*(char *)(param_1 + 0x70) == '\0')) {
      *(undefined1 *)(param_1 + 0x70) = 1;
      FUN_00437d30("ch07006.wav");
    }
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xb8),
                                  (&PTR_s_north_fail_008fe724)[*(int *)(param_1 + 0x128)],0);
    if ((float)fVar6 < 50.0) {
      *(undefined1 *)(param_1 + 0x80) = 1;
      uVar4 = FUN_00437d30("ch07007.wav");
      *(undefined4 *)(param_1 + 0x140) = uVar4;
    }
  }
  if (*(int *)(param_1 + 0x140) != 0) {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x140));
    if (cVar2 != '\0') {
      *(undefined4 *)(param_1 + 0x140) = 0;
      fVar6 = (float10)FUN_004b1670("ch07lose.des");
      FUN_0045c0f0((float)fVar6 + 1.0);
    }
  }
  if (*(char *)(param_1 + 0x57) != '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"nav_end",0);
    if (((float)fVar6 < 170.0) && (*(char *)(param_1 + 0x6f) == '\0')) {
      *(undefined1 *)(param_1 + 0x6f) = 1;
      uVar4 = FUN_005c8250("ssusera",2,"snip_end_1_spn",0,0);
      *(undefined4 *)(param_1 + 0xf8) = uVar4;
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("ssusera",2,"snip_end_2_spn",0,0);
      *(undefined4 *)(param_1 + 0xfc) = uVar4;
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"snip_end_3_spn",0,0);
      *(undefined4 *)(param_1 + 0x100) = uVar4;
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sssold",2,"sold_end_1_spn",0,0);
      *(undefined4 *)(param_1 + 0x104) = uVar4;
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"sold_end_2_spn",0,0);
      *(undefined4 *)(param_1 + 0x108) = uVar4;
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
      uVar4 = FUN_005c8250("sspilo",2,"sold_end_3_spn",0,0);
      *(undefined4 *)(param_1 + 0x10c) = uVar4;
      FUN_005cb820(uVar4,*(undefined4 *)(param_1 + 0xa8),1);
    }
  }
  if (*(char *)(param_1 + 0x57) != '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"nav_end",0);
    if (((float)fVar6 < 140.0) && (*(char *)(param_1 + 0x7d) == '\0')) {
      *(undefined1 *)(param_1 + 0x7d) = 1;
      FUN_005c8250("cspilo",1,"rescue_1_spn",200,0);
      FUN_005c8250("cspilo",1,"rescue_2_spn",200,0);
      FUN_005c8250("cspilo",1,"rescue_3_spn",200,0);
      FUN_005c8250("cspilo",1,"rescue_4_spn",200,0);
      FUN_005c8250("cspilo",1,"rescue_5_spn",200,0);
    }
  }
  if ((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x6f) != '\0')) {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa8),"nav_end",0);
    if (((float)fVar6 < 50.0) &&
       ((*(char *)(param_1 + 0x7f) == '\0' && (*(char *)(param_1 + 0x80) == '\0')))) {
      *(undefined1 *)(param_1 + 0x7f) = 1;
      for (local_c = 0; local_c < 6; local_c = local_c + 1) {
        cVar2 = FUN_005c84d0(param_1 + 0xf8 + local_c * 4);
        if (cVar2 != '\0') {
          *(undefined1 *)(param_1 + 0x7f) = 0;
          break;
        }
      }
      if (*(char *)(param_1 + 0x7f) != '\0') {
        uVar4 = FUN_00437d30("ch07009.wav");
        *(undefined4 *)(param_1 + 0x13c) = uVar4;
        FUN_004f6aa0();
        if (*(char *)(param_1 + 0x55) == '\0') {
          FUN_004f6ab0("ch07001.otf",DAT_0091755c,0x41000000,0);
        }
        else {
          FUN_004f6ab0("ch07001.otf",DAT_009175b0,0x41000000,0);
        }
        if (*(char *)(param_1 + 0x5f) != '\0') {
          FUN_004f6ab0((&PTR_s_ch07002n_otf_008ece78)[*(int *)(param_1 + 0x128)],DAT_009175b0,
                       0x41000000,0);
        }
        FUN_004f6ab0("ch07003.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("ch07004.otf",DAT_009175b0,0x41000000,0);
      }
    }
  }
  if (*(int *)(param_1 + 0x13c) != 0) {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x13c));
    if (cVar2 != '\0') {
      *(undefined4 *)(param_1 + 0x13c) = 0;
      fVar6 = (float10)FUN_004b1670("ch07win.des");
      FUN_0045c110((float)fVar6 + 1.0);
    }
  }
  if (*(int *)(param_1 + 0x110) != 0) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x110));
    if ((float)fVar6 < 5.0) {
      cVar2 = FUN_005ce6e0(*(undefined4 *)(param_1 + 0xa8));
      if (cVar2 != '\0') {
        FUN_0049b760(0x3f800000,0x40a00000,0,0xff,0);
        FUN_004376c0("repair.wav",0,0);
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x110));
        *(undefined4 *)(param_1 + 0x110) = 0;
      }
    }
  }
  if (*(int *)(param_1 + 0x114) != 0) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x114));
    if ((float)fVar6 < 5.0) {
      cVar2 = FUN_005ce6e0(*(undefined4 *)(param_1 + 0xa8));
      if (cVar2 != '\0') {
        FUN_0049b760(0x3f800000,0x40a00000,0,0xff,0);
        FUN_004376c0("repair.wav",0,0);
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x114));
        *(undefined4 *)(param_1 + 0x114) = 0;
      }
    }
  }
  if (*(int *)(param_1 + 0x118) != 0) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x118));
    if ((float)fVar6 < 5.0) {
      cVar2 = FUN_005ce190(*(undefined4 *)(param_1 + 0xa8));
      if (cVar2 != '\0') {
        FUN_0049b760(0x3f800000,0x40a00000,0,0xff,0);
        FUN_004376c0("repair.wav",0,0);
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x118));
        *(undefined4 *)(param_1 + 0x118) = 0;
      }
    }
  }
  if (*(int *)(param_1 + 0x11c) != 0) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x11c));
    if ((float)fVar6 < 5.0) {
      cVar2 = FUN_005ce190(*(undefined4 *)(param_1 + 0xa8));
      if (cVar2 != '\0') {
        FUN_0049b760(0x3f800000,0x40a00000,0,0xff,0);
        FUN_004376c0("repair.wav",0,0);
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x11c));
        *(undefined4 *)(param_1 + 0x11c) = 0;
      }
    }
  }
  return;
}

