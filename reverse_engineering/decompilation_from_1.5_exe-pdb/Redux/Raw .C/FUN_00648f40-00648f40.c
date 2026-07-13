
void __fastcall FUN_00648f40(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  int local_20;
  
  *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x88);
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x88) = uVar2;
  uVar2 = FUN_005c7e90("launch");
  FUN_005ccfd0(uVar2,0x461c4000);
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,0x32);
    FUN_005cacb0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
    FUN_004f6aa0();
    FUN_004f6ab0("bd15001.otf",DAT_0091755c,0x41000000,0);
    uVar2 = FUN_00437d30("bd15001.wav");
    *(undefined4 *)(param_1 + 0x230) = uVar2;
  }
  if (*(int *)(param_1 + 0x230) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x230));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x230) = 0;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x60) = (float)fVar4 + 20.0;
    }
  }
  if (*(char *)(param_1 + 0x5b) == '\0') {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x88),"chin_launch",0);
    if ((float)fVar4 < 300.0) {
      *(undefined1 *)(param_1 + 0x5b) = 1;
      FUN_00437d30("bd15010.wav");
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x60) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x60)) {
    *(undefined4 *)(param_1 + 0x60) = 0x497423fe;
    uVar2 = FUN_00437d30("bd15002.wav");
    *(undefined4 *)(param_1 + 0x234) = uVar2;
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_west_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_west_wave",1);
    FUN_005c95e0(uVar2);
  }
  if (*(int *)(param_1 + 0x234) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x234));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x234) = 0;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 40.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
    *(undefined4 *)(param_1 + 100) = 0x497423fe;
    uVar2 = FUN_00437d30("bd15003.wav");
    *(undefined4 *)(param_1 + 0x238) = uVar2;
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_south_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_south_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_south_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_south_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_south_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_south_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_south_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_south_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_south_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_south_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvapc",2,"spawn_south_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_south_wave",1);
    FUN_005c95e0(uVar2);
  }
  if (*(int *)(param_1 + 0x238) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x238));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x238) = 0;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x68) = (float)fVar4 + 120.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x68) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x68)) {
    *(undefined4 *)(param_1 + 0x68) = 0x497423fe;
    uVar2 = FUN_00437d30("bd15004.wav");
    *(undefined4 *)(param_1 + 0x23c) = uVar2;
    uVar2 = FUN_005c8250("cvapc",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvapc",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvapc",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvhtnk",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvtnk",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
  }
  if (*(int *)(param_1 + 0x23c) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x23c));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x23c) = 0;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x6c) = (float)fVar4 + 180.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x6c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x6c)) {
    *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
    FUN_00437d30("bd15005.wav");
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar4 + 60.0;
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x80)) {
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvltnk",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvhraz",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvhraz",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_east_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_east_wave",1);
    FUN_005c95e0(uVar2);
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar4 + 180.0;
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x70) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x70)) {
    *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
    FUN_00437d30("bd15006.wav");
    uVar2 = FUN_005c8250("cvhtnk",2,"spawn_south_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_south_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvfigh",2,"spawn_north_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_north_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvapc",2,"spawn_west_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_west_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvapc",2,"spawn_west_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_west_wave",1);
    FUN_005c95e0(uVar2);
    uVar2 = FUN_005c8250("cvhaul",2,"spawn_west_wave",0,0);
    *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x22c) * 4) = uVar2;
    *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    FUN_005cb960(uVar2,"path_west_wave",1);
    FUN_005c95e0(uVar2);
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
  local_20 = 0;
  while( true ) {
    if ((*(int *)(param_1 + 0x22c) <= local_20) || (*(char *)(param_1 + 0x5d) != '\0'))
    goto LAB_0064a043;
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x98 + local_20 * 4),"chin_launch",0);
    if ((float)fVar4 < 100.0) break;
    local_20 = local_20 + 1;
  }
  uVar2 = FUN_00437d30("bd15011.wav");
  *(undefined4 *)(param_1 + 0x244) = uVar2;
  *(undefined1 *)(param_1 + 0x5d) = 1;
LAB_0064a043:
  if (*(int *)(param_1 + 0x244) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x244));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x244) = 0;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x7c) = (float)fVar4 + 5.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x7c)) {
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    uVar2 = FUN_00437d30("bd15012.wav");
    *(undefined4 *)(param_1 + 0x248) = uVar2;
  }
  if (*(int *)(param_1 + 0x248) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x248));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x248) = 0;
      fVar4 = (float10)FUN_004b1670("bd15lose.des");
      FUN_0045c0f0((float)fVar4);
    }
  }
  if ((*(char *)(param_1 + 0x5c) != '\0') && (*(char *)(param_1 + 0x55) == '\0')) {
    *(undefined1 *)(param_1 + 0x55) = 1;
    for (local_20 = 0; local_20 < *(int *)(param_1 + 0x22c); local_20 = local_20 + 1) {
      cVar1 = FUN_005c84d0(param_1 + 0x98 + local_20 * 4);
      if (cVar1 != '\0') {
        *(undefined1 *)(param_1 + 0x55) = 0;
        break;
      }
    }
    if (*(char *)(param_1 + 0x55) != '\0') {
      uVar2 = FUN_00437d30("bd15007.wav");
      *(undefined4 *)(param_1 + 0x240) = uVar2;
      FUN_004f6aa0();
      FUN_004f6ab0("bd15001.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("bd15002.otf",DAT_0091755c,0x41000000,0);
    }
  }
  if (*(int *)(param_1 + 0x240) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x240));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x240) = 0;
      *(undefined1 *)(param_1 + 0x5a) = 1;
      FUN_004f6ae0(0x1e,10,5);
    }
  }
  if (*(char *)(param_1 + 0x5a) != '\0') {
    iVar3 = FUN_004f6b10();
    if ((iVar3 < 1) && (*(char *)(param_1 + 0x59) == '\0')) {
      FUN_004ff160();
      fVar4 = (float10)FUN_004b1670("bd15win.des");
      FUN_0045c110((float)fVar4 + 5.0);
      *(undefined1 *)(param_1 + 0x59) = 1;
      FUN_0049b760(0x3f800000,0x3f000000,0xff,0xff,0xff);
      FUN_005ce330("spawn_explosion1","xpltrso");
    }
  }
  if (*(char *)(param_1 + 0x5a) != '\0') {
    iVar3 = FUN_004f6b10();
    if ((iVar3 < 3) && (*(char *)(param_1 + 0x58) == '\0')) {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x88),"spawn_explosion1",0);
      FUN_005cd2a0((float)fVar4);
      FUN_005ce450("camera_finale",0x960,0,"spawn_explosion1");
      *(undefined1 *)(param_1 + 0x58) = 1;
    }
  }
  return;
}

