
void __fastcall FUN_00631b40(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  int local_20;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x68) = uVar2;
  if (*(int *)(param_1 + 0xd4) < 0x10) {
    if ((*(char *)(param_1 + 0x54) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x68), cVar1 == '\0')
       ) {
      if (*(float *)(param_1 + 0x60) == 0.0) {
        fVar6 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x60) = (float)fVar6 + 2.0;
      }
      else {
        fVar6 = (float10)FUN_004b1670();
        if (*(float *)(param_1 + 0x60) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x60)
           ) {
          fVar6 = (float10)FUN_004b1670("bd02lose.des");
          FUN_0045c0f0((float)fVar6 + 2.0);
          *(undefined1 *)(param_1 + 0x54) = 1;
          return;
        }
      }
    }
    else {
      if (*(char *)(param_1 + 0x54) != '\0') {
        return;
      }
      *(undefined4 *)(param_1 + 0x60) = 0;
    }
  }
  if ((*(int *)(param_1 + 0xd4) < 0x10) && (cVar1 = FUN_005c84d0(param_1 + 0x6c), cVar1 == '\0')) {
    fVar6 = (float10)FUN_004b1670("bd02lsea.des");
    FUN_0045c0f0((float)fVar6 + 2.0);
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  switch(*(undefined4 *)(param_1 + 0xd4)) {
  case 0:
    FUN_005cadd0(1,0x1e);
    FUN_005cacb0(1,10);
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xac));
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xb0));
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xb4));
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0xb8));
    FUN_00631960();
    *(undefined4 *)(param_1 + 0xd4) = 1;
    fVar6 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x58) = (float)fVar6 + 2.0;
    break;
  case 1:
    fVar6 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x58) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x58)) {
      uVar2 = FUN_00437d30("bd02001.wav");
      *(undefined4 *)(param_1 + 0xd8) = uVar2;
      *(undefined4 *)(param_1 + 0xd4) = 2;
      *(undefined4 *)(param_1 + 0x58) = 0;
    }
    break;
  case 2:
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xd8));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xd4) = 3;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x58) = (float)fVar6 + 20.0;
    }
    break;
  case 3:
    fVar6 = (float10)FUN_004b1670();
    if ((float)fVar6 < *(float *)(param_1 + 0x58) || (float)fVar6 == *(float *)(param_1 + 0x58)) {
      return;
    }
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_wave1_scout1",0,0);
    *(undefined4 *)(param_1 + 0x70) = uVar2;
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_wave1_scout2",0,0);
    *(undefined4 *)(param_1 + 0x74) = uVar2;
    FUN_00437d30("bd02002.wav");
    FUN_005cd2a0();
    *(undefined4 *)(param_1 + 0xd4) = 4;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x70),"wave1_scout1_attackpath",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x74),"wave1_scout2_attackpath",1);
  case 4:
    cVar1 = FUN_005cd300("camera_decloak",2000,1000,*(undefined4 *)(param_1 + 0x70));
    if ((cVar1 != '\0') || (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
      FUN_005cd4e0();
      *(undefined4 *)(param_1 + 0xd4) = 5;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x58) = (float)fVar6 + 5.0;
    }
    break;
  case 5:
    fVar6 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x58) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x58)) {
      *(undefined4 *)(param_1 + 0xd4) = 6;
      FUN_00437d30("bd02003.wav");
      FUN_00631960();
    }
    break;
  case 6:
    cVar1 = FUN_005c84d0(param_1 + 0x70);
    if (((cVar1 == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x74), cVar1 == '\0')) &&
       (cVar1 = FUN_005c84d0(param_1 + 0x78), cVar1 == '\0')) {
      *(undefined4 *)(param_1 + 0xd4) = 7;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x58) = (float)fVar6 + 20.0;
    }
    break;
  case 7:
    fVar6 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x58) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x58)) {
      *(undefined4 *)(param_1 + 0xd4) = 8;
      uVar2 = FUN_005c8250("cvfigh",2,"spawn_wave2_scout1",0,0);
      *(undefined4 *)(param_1 + 0x7c) = uVar2;
      uVar2 = FUN_005c8250("cvfigh",2,"spawn_wave2_scout2",0,0);
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0x7c),"wave2_scout1_attackpath",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x80),"wave2_scout2_attackpath",1);
    }
    break;
  case 8:
    cVar1 = FUN_005c84d0(param_1 + 0x7c);
    if ((((cVar1 == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x80), cVar1 == '\0')) &&
        (cVar1 = FUN_005c84d0(param_1 + 0x84), cVar1 == '\0')) &&
       (cVar1 = FUN_005c84d0(param_1 + 0x88), cVar1 == '\0')) {
      *(undefined4 *)(param_1 + 0xd4) = 9;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x58) = (float)fVar6 + 10.0;
    }
    break;
  case 9:
    fVar6 = (float10)FUN_004b1670();
    if ((float)fVar6 < *(float *)(param_1 + 0x58) || (float)fVar6 == *(float *)(param_1 + 0x58)) {
      return;
    }
    uVar2 = FUN_00437d30("bd02004.wav");
    *(undefined4 *)(param_1 + 0xd8) = uVar2;
    *(undefined4 *)(param_1 + 0xd4) = 10;
    FUN_00631960();
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_enemy_scout1",0,0);
    *(undefined4 *)(param_1 + 0x8c) = uVar2;
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_enemy_scout2",0,0);
    *(undefined4 *)(param_1 + 0x90) = uVar2;
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_enemy_ltnk",0,0);
    *(undefined4 *)(param_1 + 0x9c) = uVar2;
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_enemy_tank",0,0);
    *(undefined4 *)(param_1 + 0xa4) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x8c),"spawn_nav_alpha",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x90),"spawn_nav_alpha",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x9c),"spawn_nav_alpha",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0xa4),"spawn_nav_alpha",1);
    cVar1 = FUN_005c84d0(param_1 + 0xac);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xac),"path_turret1",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xb0);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xb0),"path_turret2",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xb4);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xb4),"path_turret3",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xb8);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xb8),"path_turret4",1);
    }
    FUN_005cd2a0();
  case 10:
    FUN_005cd300("camera_massive_attack",2000,10,*(undefined4 *)(param_1 + 0xa4));
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xd8));
    if (cVar1 != '\0') {
      uVar2 = FUN_00437d30("bd02005.wav");
      *(undefined4 *)(param_1 + 0xd8) = uVar2;
      *(undefined4 *)(param_1 + 0xd4) = 0xb;
    }
    break;
  case 0xb:
    FUN_005cd300("camera_massive_attack",2000,10,*(undefined4 *)(param_1 + 0xa4));
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xd8));
    if (cVar1 != '\0') {
      FUN_005cd4e0();
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x8c));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x90));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x94));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x98));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x9c));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xa0));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xa4));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xa8));
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"spawn_nav_alpha",0,0);
      *(undefined4 *)(param_1 + 0xbc) = uVar2;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0xbc),"Nav Alpha");
      *(undefined4 *)(param_1 + 0xd4) = 0xd;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x58) = (float)fVar6 + 4.0;
      FUN_00631960();
      FUN_005cb960(*(undefined4 *)(param_1 + 0x6c),"path_recycler_retreat",1);
      *(undefined1 *)(param_1 + 0x55) = 0;
      uVar2 = FUN_005c8250("cvfigh",2,"spawn_scout1_harrass",0,0);
      *(undefined4 *)(param_1 + 0xc0) = uVar2;
      uVar2 = FUN_005c8250("cvltnk",2,"spawn_ltnk1_harrass",0,0);
      *(undefined4 *)(param_1 + 0xc4) = uVar2;
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0xc0),*(undefined4 *)(param_1 + 0x68),1);
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0xc4),*(undefined4 *)(param_1 + 0x68),1);
    }
    break;
  case 0xd:
    if ((*(char *)(param_1 + 0x55) == '\0') &&
       (fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x6c),"trigger_1",0),
       (float)fVar6 < 100.0)) {
      for (local_20 = 0; local_20 < 2; local_20 = local_20 + 1) {
        uVar2 = FUN_005c8250("cvfigh",2,"fighter_1",0,0);
        FUN_005cb820(uVar2,*(undefined4 *)(param_1 + 0x68),1);
      }
      *(undefined1 *)(param_1 + 0x55) = 1;
    }
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x6c));
    if ((iVar4 == 0) && (cVar1 = FUN_005c84d0(param_1 + 0x6c), cVar1 != '\0')) {
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x6c),1);
      uVar2 = FUN_00437d30("bd02006.wav");
      *(undefined4 *)(param_1 + 0xd8) = uVar2;
      *(undefined4 *)(param_1 + 0xd4) = 0xe;
    }
    break;
  case 0xe:
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xd8));
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xc0));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xc4));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xac));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xb0));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xb4));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xb8));
      FUN_00437d30("bd02007.wav");
      uVar2 = FUN_005c8250("cvhraz",2,"spawn_bomber_1",0,0);
      *(undefined4 *)(param_1 + 200) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x6c),1);
      uVar2 = FUN_005c8250("cvhraz",2,"spawn_bomber_2",0,0);
      *(undefined4 *)(param_1 + 0xcc) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 0xcc),*(undefined4 *)(param_1 + 0x6c),1);
      fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x6c));
      *(float *)(param_1 + 0x5c) = (float)fVar6;
      *(undefined4 *)(param_1 + 0xd8) = 0;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x58) = (float)fVar6 + 10.0;
      *(undefined4 *)(param_1 + 0xd4) = 0xf;
    }
    break;
  case 0xf:
    if ((*(int *)(param_1 + 200) != 0) &&
       (iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 200)), iVar4 != 0)) {
      fVar6 = (float10)FUN_0046fbd0();
      fVar7 = (float10)FUN_004624f0();
      if ((float)fVar6 != (float)fVar7) {
        fVar6 = (float10)FUN_004624f0();
        fVar7 = (float10)FUN_0046fbd0();
        (**(code **)(*(int *)(iVar4 + 0x18) + 0x28))((float)fVar6 - (float)fVar7);
      }
    }
    if ((*(int *)(param_1 + 0xcc) != 0) &&
       (iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0xcc)), iVar4 != 0)) {
      fVar6 = (float10)FUN_0046fbd0();
      fVar7 = (float10)FUN_004624f0();
      if ((float)fVar6 != (float)fVar7) {
        fVar6 = (float10)FUN_004624f0();
        fVar7 = (float10)FUN_0046fbd0();
        (**(code **)(*(int *)(iVar4 + 0x18) + 0x28))((float)fVar6 - (float)fVar7);
      }
    }
    fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x6c));
    if (((float)fVar6 < *(float *)(param_1 + 0x5c)) &&
       (iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x6c)), iVar4 != 0)) {
      FUN_004a76a0(*(undefined4 *)(param_1 + 0x5c));
    }
    fVar6 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"camera_bomber_chasecam",0);
    fVar7 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),"camera_bomber_chasecam",0);
    if ((((float)fVar6 <= 60.0) || ((float)fVar7 <= 60.0)) ||
       (fVar6 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 0x58) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x58))) {
      FUN_005cd2a0();
      *(undefined4 *)(param_1 + 0x58) = 0;
      *(undefined4 *)(param_1 + 0xd4) = 0x10;
    }
    break;
  case 0x10:
    if (*(int *)(param_1 + 200) != 0) {
      piVar3 = (int *)FUN_00462630(*(undefined4 *)(param_1 + 200));
      if (piVar3 != (int *)0x0) {
        fVar6 = (float10)FUN_0046fbd0();
        fVar7 = (float10)FUN_004624f0();
        if ((float)fVar6 != (float)fVar7) {
          fVar6 = (float10)FUN_004624f0();
          fVar7 = (float10)FUN_0046fbd0();
          (**(code **)(piVar3[6] + 0x28))((float)fVar6 - (float)fVar7);
        }
      }
      if (piVar3 != (int *)0x0) {
        iVar4 = FUN_00417c80();
        iVar5 = FUN_0046d060();
        if (iVar4 != iVar5) {
          iVar4 = FUN_0046d060();
          iVar5 = FUN_00417c80();
          (**(code **)(*piVar3 + 0x18))(iVar4 - iVar5);
        }
      }
    }
    if (*(int *)(param_1 + 0xcc) != 0) {
      piVar3 = (int *)FUN_00462630(*(undefined4 *)(param_1 + 0xcc));
      if (piVar3 != (int *)0x0) {
        fVar6 = (float10)FUN_0046fbd0();
        fVar7 = (float10)FUN_004624f0();
        if ((float)fVar6 != (float)fVar7) {
          fVar6 = (float10)FUN_004624f0();
          fVar7 = (float10)FUN_0046fbd0();
          (**(code **)(piVar3[6] + 0x28))((float)fVar6 - (float)fVar7);
        }
      }
      if (piVar3 != (int *)0x0) {
        iVar4 = FUN_00417c80();
        iVar5 = FUN_0046d060();
        if (iVar4 != iVar5) {
          iVar4 = FUN_0046d060();
          iVar5 = FUN_00417c80();
          (**(code **)(*piVar3 + 0x18))(iVar4 - iVar5);
        }
      }
    }
    FUN_005cd300("camera_bomber_chasecam",1000,0,*(undefined4 *)(param_1 + 0x6c));
    if ((*(float *)(param_1 + 0x5c) != 0.0) &&
       (fVar6 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x6c)),
       *(float *)(param_1 + 0x5c) != (float)fVar6)) {
      *(undefined4 *)(param_1 + 0x5c) = 0;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x58) = (float)fVar6 + 10.0;
      FUN_00437d30("bd02008.wav");
    }
    if ((*(float *)(param_1 + 0x58) != 0.0) &&
       (fVar6 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 0x58) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x58))) {
      iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x6c));
      if (iVar4 != 0) {
        fVar6 = (float10)FUN_004624f0();
        FUN_004a76a0((float)fVar6 * 0.05);
      }
      *(undefined4 *)(param_1 + 0x58) = 0;
    }
    if ((*(int *)(param_1 + 0xd8) == 0) && (cVar1 = FUN_005c84d0(param_1 + 0x6c), cVar1 == '\0')) {
      *(undefined4 *)(param_1 + 0x58) = 0;
      uVar2 = FUN_00437d30("bd02009.wav");
      *(undefined4 *)(param_1 + 0xd8) = uVar2;
    }
    if ((*(int *)(param_1 + 0xd8) != 0) &&
       (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xd8)), cVar1 != '\0')) {
      *(undefined4 *)(param_1 + 0xd4) = 0x11;
      fVar6 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x58) = (float)fVar6 + 3.0;
      FUN_00631960();
    }
    break;
  case 0x11:
    FUN_005cd300("camera_bomber_chasecam",1000,0,*(undefined4 *)(param_1 + 0x6c));
    fVar6 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x58) <= (float)fVar6 && (float)fVar6 != *(float *)(param_1 + 0x58)) {
      *(undefined4 *)(param_1 + 0xd4) = 0x12;
      FUN_005cd4e0();
      fVar6 = (float10)FUN_004b1670("bd02win.des");
      FUN_0045c110((float)fVar6 + 5.0);
    }
  }
  return;
}

