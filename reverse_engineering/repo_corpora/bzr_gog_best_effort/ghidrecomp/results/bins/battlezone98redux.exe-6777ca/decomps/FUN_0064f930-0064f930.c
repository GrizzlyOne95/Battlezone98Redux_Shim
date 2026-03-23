
void __fastcall FUN_0064f930(int param_1)

{
  float fVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  char *local_20;
  int local_18;
  int local_c;
  
  *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0xc4);
  uVar3 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xc4) = uVar3;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cacb0(1,10);
    FUN_005cadd0(1,0);
    *(undefined1 *)(param_1 + 0x54) = 1;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar6 + 1.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar6;
    FUN_004f6aa0();
    FUN_004f6ab0("ch03001.otf",DAT_0091755c,0x41000000,0);
    for (local_c = 0; local_c < 6; local_c = local_c + 1) {
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xcc + local_c * 4));
      FUN_005c88b0(*(undefined4 *)(param_1 + 0xcc + local_c * 4),2);
    }
    FUN_004f6ae0(0x30c,0x1e,10);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar6 + 480.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x70)) {
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    uVar3 = FUN_00437d30("ch03001.wav");
    *(undefined4 *)(param_1 + 0x110) = uVar3;
  }
  if (*(int *)(param_1 + 0x110) != 0) {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x110));
    if (cVar2 != '\0') {
      *(undefined4 *)(param_1 + 0x110) = 0;
    }
  }
  if (*(char *)(param_1 + 0x55) == '\0') {
    iVar4 = FUN_004f6b10();
    if ((((double)iVar4 <= 0.0) && (*(char *)(param_1 + 0x6d) == '\0')) &&
       (*(char *)(param_1 + 0x6c) == '\0')) {
      *(undefined1 *)(param_1 + 0x6d) = 1;
      fVar6 = (float10)FUN_004b1670("ch03lsea.des");
      FUN_0045c0f0((float)fVar6 + 1.0);
    }
  }
  if (*(char *)(param_1 + 0x55) == '\0') {
    *(undefined1 *)(param_1 + 0x55) = 1;
    for (local_c = 0; local_c < 6; local_c = local_c + 1) {
      if ((*(int *)(param_1 + 0xc4) == *(int *)(param_1 + 0xcc + local_c * 4)) &&
         (*(char *)(param_1 + local_c + 0x5c) == '\0')) {
        *(undefined1 *)(param_1 + local_c + 0x5c) = 1;
        FUN_00437d30("ch03002.wav");
      }
      if (((*(char *)(param_1 + local_c + 0x62) == '\0') &&
          (*(int *)(param_1 + 0xc4) != *(int *)(param_1 + 0xcc + local_c * 4))) &&
         (*(char *)(param_1 + local_c + 0x5c) != '\0')) {
        fVar6 = (float10)FUN_005ccf10(*(undefined4 *)(param_1 + 0xcc + local_c * 4));
        if (400.0 < (float)fVar6) {
          iVar4 = FUN_005cd040(*(undefined4 *)(param_1 + 0xcc + local_c * 4));
          if (400 < iVar4) {
            *(undefined1 *)(param_1 + local_c + 0x62) = 1;
            iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0xcc + local_c * 4));
            iVar5 = FUN_0045bdf0();
            if (iVar5 == 0) {
              *(undefined4 *)(iVar4 + 0xec) = 0;
              FUN_00461440(param_1,iVar4);
            }
            FUN_005c88b0(*(undefined4 *)(param_1 + 0xcc + local_c * 4),2);
            FUN_005c9610(*(undefined4 *)(param_1 + 0xcc + local_c * 4));
          }
        }
      }
      if (*(char *)(param_1 + local_c + 0x62) == '\0') {
        *(undefined1 *)(param_1 + 0x55) = 0;
      }
    }
    if (*(char *)(param_1 + 0x55) != '\0') {
      FUN_004ff150();
      FUN_004ff160();
      FUN_004f6aa0();
      FUN_004f6ab0("ch03001.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("ch03002.otf",DAT_0091755c,0x41000000,0);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar6;
      uVar3 = FUN_005c8250(&DAT_00878c18,1,"nav_base",0,0);
      FUN_005cd7f0(uVar3,"CCA Base");
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x74)) {
    *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    iVar4 = rand();
    *(int *)(param_1 + 0x10c) = iVar4 % 6;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xbc) = (float)fVar6;
    for (local_c = 0; local_c < 6; local_c = local_c + 1) {
      if (*(int *)(param_1 + 0x10c) == local_c) {
        local_20 = "svapcq";
      }
      else {
        local_20 = "svapcr";
      }
      uVar3 = FUN_005c8250(local_20,2,(&PTR_s_apc_east_008ecde8)[local_c],0,0);
      *(undefined4 *)(param_1 + 0xe4 + local_c * 4) = uVar3;
      FUN_005c88b0(*(undefined4 *)(param_1 + 0xe4 + local_c * 4),1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0xe4 + local_c * 4),
                   (&PTR_s_east_path_008ece0c)[local_c],1);
      uVar3 = FUN_005c8250("svtank",2,(&PTR_s_east_defend_008ece24)[local_c],0,0);
      FUN_005cbce0(uVar3,*(undefined4 *)(param_1 + 0xe4 + local_c * 4),1);
      uVar3 = FUN_005c8250("svtank",2,(&PTR_s_east_defend_008ece24)[local_c],0,0);
      FUN_005cbce0(uVar3,*(undefined4 *)(param_1 + 0xe4 + local_c * 4),1);
      uVar3 = FUN_005c8250("svhraz",2,(&PTR_s_east_defend_008ece24)[local_c],0,0);
      FUN_005cbce0(uVar3,*(undefined4 *)(param_1 + 0xe4 + local_c * 4),1);
      uVar3 = FUN_005c8250("svfigh",2,(&PTR_s_east_defend_008ece24)[local_c],0,0);
      FUN_005cbce0(uVar3,*(undefined4 *)(param_1 + 0xe4 + local_c * 4),1);
    }
    *(undefined4 *)(param_1 + 0xfc) =
         *(undefined4 *)(param_1 + 0xe4 + *(int *)(param_1 + 0x10c) * 4);
    FUN_007d6a70("General APC spawned at %s",(&PTR_s_apc_east_008ecde8)[*(int *)(param_1 + 0x10c)]);
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x78) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x78)) {
    *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
    uVar3 = FUN_005c8250("cvmufa",1,"factory",0,0);
    *(undefined4 *)(param_1 + 0x100) = uVar3;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x100),"factory_path",1);
    FUN_005cada0(1,100);
    uVar3 = FUN_005c8250("cvslfa",1,"factory",0,0);
    *(undefined4 *)(param_1 + 0x104) = uVar3;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x104),"factory_path",1);
    FUN_005cada0(1,100);
  }
  if (*(int *)(param_1 + 0x100) != 0) {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x100));
    if ((((float)fVar6 <= 0.0) && (*(char *)(param_1 + 0x6d) == '\0')) &&
       (*(char *)(param_1 + 0x6c) == '\0')) {
      *(undefined1 *)(param_1 + 0x6d) = 1;
      fVar6 = (float10)FUN_004b1670("ch03lsee.des");
      FUN_0045c0f0((float)fVar6 + 1.0);
    }
  }
  if ((*(char *)(param_1 + 0x55) != '\0') && (*(char *)(param_1 + 0x56) == '\0')) {
    for (local_c = 0; local_c < 3; local_c = local_c + 1) {
      if (*(char *)(param_1 + local_c + 0x68) == '\0') {
        fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xe4 + local_c * 8),
                                      (&PTR_s_east_exit_008ecda0)[local_c],0);
        if (40.0 <= (double)fVar6) {
          fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xe8 + local_c * 8),
                                        (&PTR_s_east_exit_008ecda0)[local_c],0);
          if (40.0 <= (double)fVar6) goto LAB_006500cc;
        }
        *(undefined1 *)(param_1 + local_c + 0x68) = 1;
        FUN_00437d30((&PTR_s_ch03003_wav_008ecd94)[local_c]);
        FUN_005cb960(*(undefined4 *)(param_1 + 0xe4 + local_c * 8),
                     (&PTR_s_east_back_008ece00)[local_c],1);
        FUN_005cb960(*(undefined4 *)(param_1 + 0xe8 + local_c * 8),
                     (&PTR_s_east_back_008ece00)[local_c],1);
        FUN_005cb820(*(undefined4 *)(param_1 + 0xcc + local_c * 8),
                     *(undefined4 *)(param_1 + 0xe4 + local_c * 8),1);
        FUN_005cb820(*(undefined4 *)(param_1 + 0xd0 + local_c * 8),
                     *(undefined4 *)(param_1 + 0xe8 + local_c * 8),1);
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x80 + local_c * 0x14) = (float)fVar6;
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x84 + local_c * 0x14) = (float)fVar6 + 5.0;
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x88 + local_c * 0x14) = (float)fVar6 + 10.0;
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x8c + local_c * 0x14) = (float)fVar6 + 15.0;
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x90 + local_c * 0x14) = (float)fVar6 + 20.0;
      }
LAB_006500cc:
    }
  }
  for (local_c = 0; local_c < 0xf; local_c = local_c + 1) {
    fVar6 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x80 + local_c * 4) <= (float)fVar6) {
      *(undefined4 *)(param_1 + 0x80 + local_c * 4) = 0x497423fe;
      FUN_005ce330((&PTR_s_east_exit_008ecdac)[local_c],"xgasxpl");
    }
  }
  if (*(int *)(param_1 + 0xfc) != 0) {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xfc));
    if ((((double)fVar6 <= 0.0) && (*(char *)(param_1 + 0x6d) == '\0')) &&
       (*(char *)(param_1 + 0x6c) == '\0')) {
      *(undefined1 *)(param_1 + 0x6d) = 1;
      uVar3 = FUN_00437d30("ch03008.wav");
      *(undefined4 *)(param_1 + 0x114) = uVar3;
    }
  }
  if (*(int *)(param_1 + 0x114) != 0) {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x114));
    if (cVar2 != '\0') {
      *(undefined4 *)(param_1 + 0x114) = 0;
      fVar6 = (float10)FUN_004b1670("ch03lsec.des");
      FUN_0045c0f0((float)fVar6 + 1.0);
    }
  }
  if (*(int *)(param_1 + 0x118) != 0) {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x118));
    if (cVar2 != '\0') {
      *(undefined4 *)(param_1 + 0x118) = 0;
      fVar6 = (float10)FUN_004b1670("ch03lsed.des");
      FUN_0045c0f0((float)fVar6 + 1.0);
    }
  }
  if (*(int *)(param_1 + 0xfc) != 0) {
    fVar1 = *(float *)(param_1 + 0xbc);
    fVar6 = (float10)FUN_004b1670();
    if (fVar1 + 120.0 < (float)fVar6) {
      fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xfc),"base_fail",0);
      if (((double)fVar6 < 50.0) && (*(char *)(param_1 + 0x6d) == '\0')) {
        *(undefined1 *)(param_1 + 0x6d) = 1;
        uVar3 = FUN_00437d30("ch03009.wav");
        *(undefined4 *)(param_1 + 0x120) = uVar3;
      }
    }
  }
  if (*(int *)(param_1 + 0x120) != 0) {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x120));
    if (cVar2 != '\0') {
      *(undefined4 *)(param_1 + 0x120) = 0;
      fVar6 = (float10)FUN_004b1670("ch03lsed.des");
      FUN_0045c0f0((float)fVar6 + 1.0);
    }
  }
  if ((*(char *)(param_1 + 0x56) == '\0') && (*(int *)(param_1 + 0x10c) != -1)) {
    iVar4 = FUN_005c8800(*(undefined4 *)(param_1 + 0xfc));
    if (iVar4 == 1) {
      *(undefined1 *)(param_1 + 0x56) = 1;
      FUN_00437d30("ch03006.wav");
      FUN_004f6aa0();
      FUN_004f6ab0("ch03001.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("ch03002.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("ch03003.otf",DAT_0091755c,0x41000000,0);
    }
  }
  if ((*(char *)(param_1 + 0x56) != '\0') && (*(char *)(param_1 + 0x6b) == '\0')) {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xfc),"trigger_1",0);
    if ((double)fVar6 < 30.0) {
      *(undefined1 *)(param_1 + 0x6b) = 1;
      for (local_c = 0; local_c < 6; local_c = local_c + 1) {
        uVar3 = FUN_005c8250("svfigh",2,"apc_attack",0,0);
        FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xfc),1);
      }
      for (local_c = 0; local_c < 4; local_c = local_c + 1) {
        uVar3 = FUN_005c8250("svfigh",2,"apc_attack_2",0,0);
        FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0xfc),1);
      }
      uVar3 = FUN_005c8250("svtank",2,"factory_attack",0,0);
      FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0x100),1);
      uVar3 = FUN_005c8250("svtank",2,"factory_attack",0,0);
      FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0x100),1);
      uVar3 = FUN_005c8250("svtank",2,"factory_attack",0,0);
      FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0x100),1);
      uVar3 = FUN_005c8250("svfigh",2,"factory_attack",0,0);
      FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0x100),1);
      uVar3 = FUN_005c8250("svfigh",2,"factory_attack",0,0);
      FUN_005cb820(uVar3,*(undefined4 *)(param_1 + 0x100),1);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x7c)) {
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar6 + 3600.0;
    iVar4 = FUN_005cbda0("mine_path");
    for (local_18 = 0; local_18 < iVar4; local_18 = local_18 + 1) {
      FUN_005c8250("proxmind",2,"mine_path",local_18,0);
    }
  }
  if ((*(char *)(param_1 + 0x56) != '\0') && (*(char *)(param_1 + 0x6c) == '\0')) {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xfc),"won_mission",0);
    if (((float)fVar6 < 60.0) && (*(char *)(param_1 + 0x6d) == '\0')) {
      *(undefined1 *)(param_1 + 0x6c) = 1;
      fVar6 = (float10)FUN_004b1670("ch03win.des");
      FUN_0045c110((float)fVar6 + 1.0);
    }
  }
  return;
}

