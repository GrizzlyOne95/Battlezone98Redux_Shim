
void __fastcall FUN_006337f0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  char *pcVar7;
  int local_18;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x94) = uVar2;
  if (*(int *)(param_1 + 0x9c) != 0) {
    FUN_005ccf70(*(undefined4 *)(param_1 + 0x9c),0x461c4000);
    FUN_005ccfa0(*(undefined4 *)(param_1 + 0x9c),0x461c4000);
  }
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,8);
    FUN_005cacb0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
    FUN_004f6aa0();
    FUN_004f6ab0("bd03001.otf",DAT_0091755c,0x41000000,0);
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar6 + 420.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar6 + 660.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar6 + 540.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar6 + 420.0;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar6 + 600.0;
    for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
      FUN_005cd6f0(*(undefined4 *)(param_1 + 0xb0 + local_18 * 4));
    }
    uVar2 = FUN_005c7e90("evil_scout4");
    FUN_005cd6f0(uVar2);
    uVar2 = FUN_005c7e90("evil_scout5");
    FUN_005cd6f0(uVar2);
  }
  if (*(char *)(param_1 + 0x58) == '\0') {
    if (*(int *)(param_1 + 0xc4) == 0) {
      uVar2 = FUN_00437d30("bd03001.wav");
      *(undefined4 *)(param_1 + 0xc4) = uVar2;
      FUN_005cd2a0();
    }
    FUN_005cd300("camera_intro",1000,0,*(undefined4 *)(param_1 + 0x94));
    cVar1 = FUN_005cd560();
    if (cVar1 != '\0') {
      FUN_00437d80(*(undefined4 *)(param_1 + 0xc4));
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xc4));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xc4) = 0;
      *(undefined1 *)(param_1 + 0x58) = 1;
      FUN_005cd4e0();
    }
  }
  if ((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 0x59) == '\0')) {
    if (*(int *)(param_1 + 200) == 0) {
      uVar2 = FUN_00437d30("bd03002.wav");
      *(undefined4 *)(param_1 + 200) = uVar2;
      FUN_005cd2a0();
      FUN_005cb960(*(undefined4 *)(param_1 + 0x98),"path_recycler_travel",1);
      *(undefined1 *)(param_1 + 0x65) = 1;
      FUN_005cbc20(*(undefined4 *)(param_1 + 0xa4),*(undefined4 *)(param_1 + 0x98),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x98),1);
    }
    FUN_005cd300("camera_recycler",400,200,*(undefined4 *)(param_1 + 0x98));
    cVar1 = FUN_005cd560();
    if (cVar1 != '\0') {
      FUN_00437d80(*(undefined4 *)(param_1 + 200));
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 200));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 200) = 0;
      *(undefined1 *)(param_1 + 0x59) = 1;
      FUN_005cd4e0();
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xa4));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xa8));
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x6c) = (float)fVar6 + 60.0;
    }
  }
  if (*(char *)(param_1 + 0x65) != '\0') {
    cVar1 = FUN_005cda90(*(undefined4 *)(param_1 + 0x98),"path_recycler_travel");
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x65) = 0;
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x98),*(undefined4 *)(param_1 + 0xac),1);
      uVar2 = FUN_005c8250("cvturr",2,"spawn_turret_1",0,0);
      uVar3 = FUN_005c8250("cvturr",2,"spawn_turret_2",0,0);
      uVar4 = FUN_005c8250("cvfigh",2,"spawn_turret_guard1",0,0);
      FUN_005cd6f0(uVar4);
      FUN_005cbce0(uVar4,uVar2,1);
      uVar4 = FUN_005c8250("cvfigh",2,"spawn_turret_guard1",0,0);
      FUN_005cd6f0(uVar4);
      FUN_005cbce0(uVar4,uVar3,1);
      uVar4 = FUN_005c8250("cvfigh",2,"spawn_turret_guard2",0,0);
      FUN_005cd6f0(uVar4);
      FUN_005cbce0(uVar4,uVar2,1);
      uVar2 = FUN_005c8250("cvfigh",2,"spawn_turret_guard2",0,0);
      FUN_005cd6f0(uVar2);
      FUN_005cbce0(uVar2,uVar3,1);
    }
  }
  if (*(char *)(param_1 + 0x66) == '\0') {
    cVar1 = FUN_005cd7c0(*(undefined4 *)(param_1 + 0x98));
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x66) = 1;
      FUN_005c8250("bvscav",1,"spawn_scav",0,0);
      uVar2 = FUN_005c8250("bvturr",1,"spawn_turret",0,0);
      FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0x98),0);
      uVar2 = FUN_005c8080("bvturr",1,uVar2,0);
      FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0x98),0);
      FUN_005cada0(1,0x18);
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x80) = (float)fVar6 + 30.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x80)) {
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_recycler_attack",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0x98),1);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_recycler_attack",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0x98),1);
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x84) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x84)) {
    *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_recycler_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_recycler_attack",0);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_recycler_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_recycler_attack",0);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_recycler_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_recycler_attack",0);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_recycler_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_recycler_attack",0);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_recycler_attack",0,0);
    FUN_005cd6f0(uVar2);
    FUN_005cb960(uVar2,"path_recycler_attack",0);
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x88) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x88)) {
    *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_recycler_attack",0,0);
    FUN_005cb960(uVar2,"path_recycler_attack",1);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_recycler_attack",0,0);
    FUN_005cb960(uVar2,"path_recycler_attack",1);
  }
  if ((*(char *)(param_1 + 0x59) != '\0') && (*(char *)(param_1 + 0x62) == '\0')) {
    *(undefined1 *)(param_1 + 0x62) = 1;
  }
  fVar6 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x6c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x6c)) &&
     (*(char *)(param_1 + 0x5a) == '\0')) {
    if (*(int *)(param_1 + 0xcc) == 0) {
      uVar2 = FUN_00437d30("bd03003.wav");
      *(undefined4 *)(param_1 + 0xcc) = uVar2;
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xcc));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xcc) = 0;
      *(undefined1 *)(param_1 + 0x5a) = 1;
      *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x70) = (float)fVar6 + 30.0;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x70) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x70)) &&
     (*(char *)(param_1 + 0x5b) == '\0')) {
    if (*(int *)(param_1 + 0xd0) == 0) {
      uVar2 = FUN_00437d30("bd03004.wav");
      *(undefined4 *)(param_1 + 0xd0) = uVar2;
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xd0));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xd0) = 0;
      *(undefined1 *)(param_1 + 0x5b) = 1;
      *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x74) = (float)fVar6 + 10.0;
      FUN_004f6aa0();
      FUN_004f6ab0("bd03001.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("bd03002.otf",DAT_0091755c,0x41000000,0);
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x74) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x74)) &&
     (*(char *)(param_1 + 0x5c) == '\0')) {
    if (*(int *)(param_1 + 0xd4) == 0) {
      uVar2 = FUN_00437d30("bd03005.wav");
      *(undefined4 *)(param_1 + 0xd4) = uVar2;
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xd4));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xd4) = 0;
      *(undefined1 *)(param_1 + 0x5c) = 1;
      *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
    }
  }
  fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0x98));
  if (((double)fVar6 < 75.0) &&
     ((*(char *)(param_1 + 0x55) == '\0' || (*(char *)(param_1 + 0x56) == '\0')))) {
    *(undefined1 *)(param_1 + 0x55) = 1;
    *(undefined1 *)(param_1 + 0x56) = 1;
    FUN_00437d30("bd03006.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("bd03001.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("bd03002.otf",DAT_009175b0,0x41000000,0);
  }
  fVar6 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x78) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x78)) &&
     (*(char *)(param_1 + 0x5d) == '\0')) {
    if (*(int *)(param_1 + 0xd8) == 0) {
      uVar2 = FUN_00437d30("bd03007.wav");
      *(undefined4 *)(param_1 + 0xd8) = uVar2;
      FUN_004f6aa0();
      FUN_004f6ab0("bd03003.otf",DAT_0091755c,0x41000000,0);
    }
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xd8));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xd8) = 0;
      *(undefined1 *)(param_1 + 0x5d) = 1;
      *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
      uVar2 = FUN_005c8250("bvapcb",1,"spawn_apc",0,0);
      *(undefined4 *)(param_1 + 0xa0) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xa0),"path_apc_travel",1);
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xa0));
      uVar2 = FUN_005c8250("bvraz",1,"spawn_apc",0,0);
      FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0xa0),0);
      uVar2 = FUN_005c8250("bvraz",1,"spawn_apc",0,0);
      FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0xa0),0);
      *(undefined1 *)(param_1 + 99) = 1;
    }
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x8c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x8c)) {
    *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
    uVar2 = FUN_005c8250("cvfighf",2,"spawn_attack_apc",0,0);
    FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0xa0),1);
  }
  fVar6 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x7c)) {
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar6 + 90.0;
    uVar4 = 0;
    uVar3 = 0;
    pcVar7 = "spawn_random_1";
    uVar2 = 2;
    iVar5 = rand();
    uVar2 = FUN_005c8250((&PTR_s_cvfigh_008ecac0)[iVar5 % 10],uVar2,pcVar7,uVar3,uVar4);
    FUN_005cbc20(uVar2,*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = 0;
    uVar3 = 0;
    pcVar7 = "spawn_random_2";
    uVar2 = 2;
    iVar5 = rand();
    uVar2 = FUN_005c8250((&PTR_s_cvfigh_008ecac0)[iVar5 % 10],uVar2,pcVar7,uVar3,uVar4);
    FUN_005cbc20(uVar2,*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = 0;
    uVar3 = 0;
    pcVar7 = "spawn_random_3";
    uVar2 = 2;
    iVar5 = rand();
    uVar2 = FUN_005c8250((&PTR_s_cvfigh_008ecac0)[iVar5 % 10],uVar2,pcVar7,uVar3,uVar4);
    FUN_005cbc20(uVar2,*(undefined4 *)(param_1 + 0xa0),1);
    uVar4 = 0;
    uVar3 = 0;
    pcVar7 = "spawn_random_4";
    uVar2 = 2;
    iVar5 = rand();
    uVar2 = FUN_005c8250((&PTR_s_cvfigh_008ecac0)[iVar5 % 10],uVar2,pcVar7,uVar3,uVar4);
    FUN_005cbc20(uVar2,*(undefined4 *)(param_1 + 0xa0),1);
  }
  if (*(char *)(param_1 + 99) != '\0') {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa0));
    if (((double)fVar6 < 0.98) && (*(char *)(param_1 + 0x68) == '\0')) {
      FUN_00437d30("bd03008.wav");
      *(undefined1 *)(param_1 + 0x68) = 1;
    }
  }
  fVar6 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xa0),*(undefined4 *)(param_1 + 0x9c));
  if ((((*(char *)(param_1 + 99) != '\0') && ((float)fVar6 < 75.0)) &&
      (*(char *)(param_1 + 0x6a) == '\0')) && (*(char *)(param_1 + 0x69) == '\0')) {
    *(undefined1 *)(param_1 + 0x6a) = 1;
    uVar2 = FUN_00437d30("bd03009.wav");
    *(undefined4 *)(param_1 + 0xe0) = uVar2;
  }
  if (*(char *)(param_1 + 99) != '\0') {
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xa0),"trigger_ambush",0);
    if (((float)fVar6 < 50.0) && (*(char *)(param_1 + 100) == '\0')) {
      *(undefined1 *)(param_1 + 100) = 1;
      uVar4 = 0;
      uVar3 = 0;
      pcVar7 = "spawn_recycler_attack";
      uVar2 = 2;
      iVar5 = rand();
      uVar2 = FUN_005c8250((&PTR_s_cvfigh_008fe6c8)[iVar5 % 3],uVar2,pcVar7,uVar3,uVar4);
      FUN_005cd6f0(uVar2);
      FUN_005cbc20(uVar2,*(undefined4 *)(param_1 + 0xa0),0);
      uVar4 = 0;
      uVar3 = 0;
      pcVar7 = "spawn_recycler_attack";
      uVar2 = 2;
      iVar5 = rand();
      uVar2 = FUN_005c8250((&PTR_s_cvfigh_008fe6c8)[iVar5 % 3],uVar2,pcVar7,uVar3,uVar4);
      FUN_005cd6f0(uVar2);
      FUN_005cbc20(uVar2,*(undefined4 *)(param_1 + 0xa0),0);
    }
  }
  if ((*(char *)(param_1 + 0x5f) == '\0') && (*(int *)(param_1 + 0xe0) != 0)) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xe0));
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x5f) = 1;
      *(undefined4 *)(param_1 + 0xe0) = 0;
      fVar6 = (float10)FUN_004b1670("bd03win.des");
      FUN_0045c110((float)fVar6 + 2.0);
    }
  }
  fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x98));
  if ((((float)fVar6 <= 0.0) && (*(char *)(param_1 + 0x69) == '\0')) &&
     (*(char *)(param_1 + 0x6a) == '\0')) {
    *(undefined1 *)(param_1 + 0x69) = 1;
    uVar2 = FUN_00437d30("bd03012.wav");
    *(undefined4 *)(param_1 + 0xdc) = uVar2;
  }
  if ((*(char *)(param_1 + 0x5e) == '\0') && (*(int *)(param_1 + 0xdc) != 0)) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xdc));
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x5e) = 1;
      *(undefined4 *)(param_1 + 0xdc) = 0;
      fVar6 = (float10)FUN_004b1670("bd03lsea.des");
      FUN_0045c0f0((float)fVar6 + 2.0);
    }
  }
  if (*(char *)(param_1 + 99) != '\0') {
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa0));
    if ((((float)fVar6 <= 0.0) && (*(char *)(param_1 + 0x69) == '\0')) &&
       (*(char *)(param_1 + 0x6a) == '\0')) {
      uVar2 = FUN_00437d30("bd03010.wav");
      *(undefined4 *)(param_1 + 0xe4) = uVar2;
      *(undefined1 *)(param_1 + 0x69) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x60) == '\0') && (*(int *)(param_1 + 0xe4) != 0)) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xe4));
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x60) = 1;
      *(undefined4 *)(param_1 + 0xe4) = 0;
      uVar2 = FUN_00437d30("bd03011.wav");
      *(undefined4 *)(param_1 + 0xe8) = uVar2;
    }
  }
  if ((*(char *)(param_1 + 0x61) == '\0') && (*(int *)(param_1 + 0xe8) != 0)) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xe8));
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x61) = 1;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      fVar6 = (float10)FUN_004b1670("bd03lseb.des");
      FUN_0045c0f0((float)fVar6 + 2.0);
    }
  }
  return;
}

