
void __fastcall FUN_00647580(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  float10 fVar6;
  int local_14;
  
  *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_1 + 0x7c);
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x7c) = uVar2;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cb2d0("bdmisn14.aip",2);
    FUN_005cadd0(1,4);
    FUN_005cacb0(1,10);
    FUN_005cadd0(2,0);
    FUN_005cacb0(2,100);
    *(undefined1 *)(param_1 + 0x54) = 1;
    uVar2 = FUN_00437d30("bd14001.wav");
    *(undefined4 *)(param_1 + 0x94) = uVar2;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x60) = (float)fVar6;
    uVar2 = FUN_005c7e90("start1_1");
    FUN_005cd6f0(uVar2);
    uVar2 = FUN_005c7e90("start1_2");
    FUN_005cd6f0(uVar2);
    uVar2 = FUN_005c7e90("start1_3");
    FUN_005cd6f0(uVar2);
    uVar2 = FUN_005c7e90("start2_1");
    FUN_005cd6f0(uVar2);
    uVar2 = FUN_005c7e90("start2_2");
    FUN_005cd6f0(uVar2);
    uVar2 = FUN_005c7e90("start2_3");
    FUN_005cd6f0(uVar2);
  }
  if (*(int *)(param_1 + 0x94) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x94));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x94) = 0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x60) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x60)) {
    *(undefined4 *)(param_1 + 0x60) = 0x497423fe;
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_initial_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_initial_attack",1);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_initial_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_initial_attack",1);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_initial_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_initial_attack",1);
    uVar2 = FUN_005c8250("cvhraz",2,"spawn_initial_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_initial_attack",1);
    uVar2 = FUN_005c8250("cvhraz",2,"spawn_initial_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_initial_attack",1);
    FUN_004f6aa0();
    FUN_004f6ab0("bd14001.otf",DAT_0091755c,0x41000000,0);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 100) = (float)fVar6 + 120.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar6 + 240.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 100) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 100)) {
    *(undefined4 *)(param_1 + 100) = 0x497423fe;
    FUN_00437d30("bd14002.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("bd14001.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("bd14002.otf",DAT_0091755c,0x41000000,0);
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x70)) {
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    uVar2 = FUN_005c8250("cvhtnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvhtnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x68) = (float)fVar6 + 300.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x68) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x68)) {
    *(undefined4 *)(param_1 + 0x68) = 0x497423fe;
    FUN_00437d30("bd14003.wav");
    uVar2 = FUN_005c8250("cvapcc",2,"spawn_apc",0,0);
    *(undefined4 *)(param_1 + 0x8c) = uVar2;
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x8c));
    FUN_005cb960(*(undefined4 *)(param_1 + 0x8c),"path_apc_travel",1);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_apc",0,0);
    FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0x8c),1);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_apc",0,0);
    FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0x8c),1);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_apc",0,0);
    FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0x8c),1);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_apc",0,0);
    FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0x8c),1);
    uVar2 = FUN_005c8250("cvhraz",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvhraz",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvhraz",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvhraz",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_attack_waves",1);
    uVar3 = FUN_005c8250("cvwalk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar3,"path_attack_waves",1);
    uVar4 = FUN_005c8250("cvwalk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar4,"path_attack_waves",1);
    uVar5 = FUN_005c8250("cvwalk",2,"spawn_attack_waves",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar5,"path_attack_waves",1);
    uVar2 = FUN_005c8250("cvtnkc",2,"spawn_attack_waves",0,0);
    FUN_005cbc20(uVar2,uVar3,1);
    uVar2 = FUN_005c8250("cvtnkc",2,"spawn_attack_waves",0,0);
    FUN_005cbc20(uVar2,uVar4,1);
    uVar2 = FUN_005c8250("cvtnkc",2,"spawn_attack_waves",0,0);
    FUN_005cbc20(uVar2,uVar5,1);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x6c) = (float)fVar6 + 50.0;
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x6c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x6c)) {
    *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    cVar1 = FUN_005c84d0(param_1 + 0x8c);
    if (cVar1 != '\0') {
      FUN_00437d30("bd14004.wav");
    }
  }
  if ((*(char *)(param_1 + 0x56) == '\0') && (*(int *)(param_1 + 0x8c) != 0)) {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x8c));
    if ((double)fVar6 <= 0.0) {
      FUN_005c9610(*(undefined4 *)(param_1 + 0x8c));
      *(undefined1 *)(param_1 + 0x56) = 1;
      FUN_00437d30("bd14005.wav");
      FUN_004f6aa0();
      FUN_004f6ab0("bd14002.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("bd14003.otf",DAT_0091755c,0x41000000,0);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar6 + 240.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x74) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x74)) {
    *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    FUN_005c8250("cvscav",2,"spawn_scav",0,0);
    FUN_005c8250("cvscav",2,"spawn_scav",0,0);
  }
  if (*(char *)(param_1 + 0x57) == '\0') {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x88));
    if (((double)fVar6 <= 0.0) && (*(char *)(param_1 + 0x5e) == '\0')) {
      *(undefined1 *)(param_1 + 0x5e) = 1;
      *(undefined1 *)(param_1 + 0x57) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0("bd14002.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("bd14003.otf",DAT_009175b0,0x41000000,0);
      uVar2 = FUN_00437d30("bd14006.wav");
      *(undefined4 *)(param_1 + 0x98) = uVar2;
    }
  }
  if (*(int *)(param_1 + 0x98) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x98));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x98) = 0;
      fVar6 = (float10)FUN_004b1670("bd14win.des");
      FUN_0045c110((float)fVar6);
    }
  }
  if (*(char *)(param_1 + 0x57) == '\0') {
    cVar1 = FUN_005cda90(*(undefined4 *)(param_1 + 0x8c),"path_apc_travel");
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x5e) == '\0')) {
      *(undefined1 *)(param_1 + 0x5e) = 1;
      uVar2 = FUN_00437d30("bd14007.wav");
      *(undefined4 *)(param_1 + 0x9c) = uVar2;
      FUN_004f6aa0();
      FUN_004f6ab0("bd14001.otf",DAT_0091757c,0x41000000,0);
      FUN_004f6ab0("bd14002.otf",DAT_0091757c,0x41000000,0);
    }
  }
  if (*(int *)(param_1 + 0x9c) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x9c));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x9c) = 0;
      fVar6 = (float10)FUN_004b1670("bd14lsea.des");
      FUN_0045c0f0((float)fVar6);
    }
  }
  fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x84));
  if (((double)fVar6 <= 0.0) && (*(char *)(param_1 + 0x5e) == '\0')) {
    *(undefined1 *)(param_1 + 0x5e) = 1;
    uVar2 = FUN_00437d30("bd14008.wav");
    *(undefined4 *)(param_1 + 0xa0) = uVar2;
  }
  if (*(int *)(param_1 + 0xa0) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xa0));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xa0) = 0;
      fVar6 = (float10)FUN_004b1670("bd14lseb.des");
      FUN_0045c0f0((float)fVar6);
    }
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x7c),"trigger_attack_1",0);
    if ((double)fVar6 < 150.0) {
      *(undefined1 *)(param_1 + 0x5c) = 1;
      for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
        uVar2 = FUN_005c8250("cvhraz",2,"spawn_attack_1",0,0);
        FUN_005cb960(uVar2,"path_attack_1",1);
        FUN_005cd6f0(uVar2);
      }
      for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
        uVar2 = FUN_005c8250("cvltnk",2,"spawn_attack_1",0,0);
        FUN_005cb960(uVar2,"path_attack_1",1);
        FUN_005cd6f0(uVar2);
      }
      for (local_14 = 0; local_14 < 2; local_14 = local_14 + 1) {
        uVar2 = FUN_005c8250("cvwalk",2,"spawn_defend",0,0);
        FUN_005cb960(uVar2,"path_defend",1);
      }
      for (local_14 = 0; local_14 < 5; local_14 = local_14 + 1) {
        uVar2 = FUN_005c8250("cvltnk",2,"spawn_defend",0,0);
        FUN_005cb960(uVar2,"path_defend",1);
      }
    }
  }
  if (*(char *)(param_1 + 0x5d) == '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x7c),"trigger_attack_2",0);
    if ((double)fVar6 < 150.0) {
      *(undefined1 *)(param_1 + 0x5d) = 1;
      for (local_14 = 0; local_14 < 6; local_14 = local_14 + 1) {
        uVar2 = FUN_005c8250("cvhraz",2,"spawn_attack_2",0,0);
        FUN_005cb960(uVar2,"path_attack_2",1);
        FUN_005cd6f0(uVar2);
      }
    }
  }
  return;
}

