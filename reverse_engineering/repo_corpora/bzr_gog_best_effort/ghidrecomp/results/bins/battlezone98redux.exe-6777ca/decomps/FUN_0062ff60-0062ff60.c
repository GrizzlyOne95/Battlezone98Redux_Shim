
void __fastcall FUN_0062ff60(int param_1)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar3 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x90) = uVar3;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,0xc);
    FUN_005cacb0(1,10);
    FUN_00630e30();
    FUN_005cb960(*(undefined4 *)(param_1 + 0x94),"start_path_recycler",1);
    local_14 = 0x447d0000;
    local_10 = 0x40a00000;
    local_c = 0x47c61d80;
    FUN_005cb880(*(undefined4 *)(param_1 + 0x94),&local_14,1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x98),"start_path_wingman1",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x9c),"start_path_wingman2",1);
    uVar3 = FUN_00437d30("bd01001.wav");
    *(undefined4 *)(param_1 + 0xec) = uVar3;
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  fVar5 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x94));
  if (((double)fVar5 <= 0.0) && (*(char *)(param_1 + 0x5f) == '\0')) {
    *(undefined1 *)(param_1 + 0x5f) = 1;
    uVar3 = FUN_00437d30("bd01005.wav");
    *(undefined4 *)(param_1 + 0xe8) = uVar3;
  }
  if (((*(char *)(param_1 + 0x5f) != '\0') && (*(char *)(param_1 + 99) == '\0')) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xe8)), cVar1 != '\0')) {
    fVar5 = (float10)FUN_004b1670("bd01lsea.des");
    FUN_0045c0f0((float)fVar5 + 4.0);
    *(undefined1 *)(param_1 + 99) = 1;
  }
  if (*(char *)(param_1 + 0x59) == '\0') {
    if (*(char *)(param_1 + 0x58) == '\0') {
      FUN_005cd2a0();
      *(undefined1 *)(param_1 + 0x58) = 1;
    }
    cVar1 = FUN_005cd300("camera_start_arc",3000,0xdac,*(undefined4 *)(param_1 + 0x94));
    cVar2 = FUN_005cd560();
    if (cVar2 != '\0') {
      cVar1 = '\x01';
      FUN_00437d80(*(undefined4 *)(param_1 + 0xec));
    }
    if (cVar1 != '\0') {
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x59) = 1;
      *(undefined1 *)(param_1 + 0x58) = 0;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x7c) = (float)fVar5 + 90.0;
    }
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x7c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x7c)) {
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    cVar1 = FUN_005cd7c0(*(undefined4 *)(param_1 + 0x94));
    if (cVar1 == '\0') {
      uVar3 = FUN_00437d30("bd01008.wav");
      *(undefined4 *)(param_1 + 0xfc) = uVar3;
    }
  }
  if ((*(int *)(param_1 + 0xfc) != 0) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xfc)), cVar1 != '\0')) {
    *(undefined4 *)(param_1 + 0xfc) = 0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar5 + 30.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0x80) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x80)) {
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    cVar1 = FUN_005cd7c0(*(undefined4 *)(param_1 + 0x94));
    if (cVar1 == '\0') {
      uVar3 = FUN_00437d30("bd01009.wav");
      *(undefined4 *)(param_1 + 0x100) = uVar3;
    }
  }
  if ((*(int *)(param_1 + 0x100) != 0) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x100)), cVar1 != '\0')) {
    *(undefined4 *)(param_1 + 0x100) = 0;
    fVar5 = (float10)FUN_004b1670("bd01lseb.des");
    FUN_0045c0f0((float)fVar5 + 1.0);
  }
  if ((*(char *)(param_1 + 0x5b) == '\0') &&
     (cVar1 = FUN_005cd7c0(*(undefined4 *)(param_1 + 0x94)), cVar1 != '\0')) {
    *(undefined1 *)(param_1 + 0x5b) = 1;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar5 + 20.0;
    *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
    *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
    *(undefined1 *)(param_1 + 0x55) = 1;
    FUN_00630e30();
  }
  if ((*(char *)(param_1 + 0x5b) != '\0') &&
     (fVar5 = (float10)FUN_004b1670(), *(float *)(param_1 + 0x70) <= (float)fVar5)) {
    if (*(char *)(param_1 + 100) == '\0') {
      *(undefined1 *)(param_1 + 100) = 1;
      uVar3 = FUN_005c8250(&DAT_00878c18,1,"spawn_nav_beacon",0,0);
      *(undefined4 *)(param_1 + 0xd4) = uVar3;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0xd4),"Nav Alpha");
      uVar3 = FUN_005c8250("cvfigh",2,"spawn_attack_ambush",0,0);
      *(undefined4 *)(param_1 + 0xa8) = uVar3;
      iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0xa8));
      *(undefined4 *)(iVar4 + 0xec) = 0;
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0xa8),"ambush_patrol_path",1);
      FUN_005cd690(*(undefined4 *)(param_1 + 0xa8));
      uVar3 = FUN_005c8250("cvfigh",2,"spawn_attack_ambush",0,0);
      *(undefined4 *)(param_1 + 0xac) = uVar3;
      iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0xac));
      *(undefined4 *)(iVar4 + 0xec) = 0;
      FUN_005cc0c0(*(undefined4 *)(param_1 + 0xac),"ambush_patrol_path",1);
      FUN_005cd690(*(undefined4 *)(param_1 + 0xac));
    }
    if (*(char *)(param_1 + 0x5c) == '\0') {
      *(undefined1 *)(param_1 + 0x5c) = 1;
      uVar3 = FUN_00437d30("BD01002.WAV");
      *(undefined4 *)(param_1 + 0xdc) = uVar3;
    }
    if (*(char *)(param_1 + 0x60) == '\0') {
      cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xdc));
      if (cVar1 == '\0') goto LAB_00630e13;
      *(undefined1 *)(param_1 + 0x60) = 1;
    }
    if (*(char *)(param_1 + 0x65) == '\0') {
      *(undefined1 *)(param_1 + 0x65) = 1;
      FUN_005c88e0(*(undefined4 *)(param_1 + 0xd4));
      FUN_00630e30();
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x84) = (float)fVar5 + 60.0;
    }
    fVar5 = (float10)FUN_004b1670();
    if ((*(float *)(param_1 + 0x84) <= (float)fVar5 + 60.0 &&
         (float)fVar5 + 60.0 != *(float *)(param_1 + 0x84)) ||
       (fVar5 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 0x88) <= (float)fVar5 + 30.0 &&
       (float)fVar5 + 30.0 != *(float *)(param_1 + 0x88))) {
      uVar3 = FUN_005cd9d0("spawn_nav_beacon",0,1);
      fVar5 = (float10)FUN_005c9800(uVar3,"spawn_nav_beacon",0);
      if (((float)fVar5 < 100.0) ||
         ((cVar1 = FUN_005cd750(*(undefined4 *)(param_1 + 0xa8)), cVar1 == '\0' ||
          (cVar1 = FUN_005cd750(*(undefined4 *)(param_1 + 0xac)), cVar1 == '\0')))) {
        *(undefined1 *)(param_1 + 0x56) = 1;
        *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
        *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
        FUN_00630e30();
      }
    }
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x84) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x84)) {
      *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
      uVar3 = FUN_00437d30("bd01006.wav");
      *(undefined4 *)(param_1 + 0xf4) = uVar3;
    }
    if ((*(int *)(param_1 + 0xf4) != 0) &&
       (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xf4)), cVar1 != '\0')) {
      *(undefined4 *)(param_1 + 0xf4) = 0;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x88) = (float)fVar5 + 30.0;
    }
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x88) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x88)) {
      *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
      uVar3 = FUN_00437d30("bd01007.wav");
      *(undefined4 *)(param_1 + 0xf8) = uVar3;
    }
    if ((*(int *)(param_1 + 0xf8) != 0) &&
       (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xf8)), cVar1 != '\0')) {
      *(undefined4 *)(param_1 + 0xf8) = 0;
      fVar5 = (float10)FUN_004b1670("bd01lsec.des");
      FUN_0045c0f0((float)fVar5 + 1.0);
    }
    if (*(char *)(param_1 + 0x66) == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xa8);
      if (cVar1 == '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0xac),"ambush_retreat_path",1);
        FUN_005cd690(*(undefined4 *)(param_1 + 0xac));
        fVar5 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x74) = (float)fVar5 + 5.0;
        *(undefined1 *)(param_1 + 0x66) = 1;
      }
      else {
        cVar1 = FUN_005c84d0(param_1 + 0xac);
        if (cVar1 == '\0') {
          FUN_005cc100(*(undefined4 *)(param_1 + 0xa8),"ambush_retreat_path",1);
          FUN_005cd690(*(undefined4 *)(param_1 + 0xa8));
          fVar5 = (float10)FUN_004b1670();
          *(float *)(param_1 + 0x74) = (float)fVar5 + 5.0;
          *(undefined1 *)(param_1 + 0x66) = 1;
        }
      }
    }
    if ((*(char *)(param_1 + 0x56) == '\0') &&
       (fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x90),
                                      *(undefined4 *)(param_1 + 0xd4)), (float)fVar5 < 100.0)) {
      *(undefined1 *)(param_1 + 0x56) = 1;
      *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
      *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
      FUN_00630e30();
    }
    if ((*(char *)(param_1 + 0x66) != '\0') &&
       (fVar5 = (float10)FUN_004b1670(), *(float *)(param_1 + 0x74) <= (float)fVar5)) {
      if (*(char *)(param_1 + 0x67) == '\0') {
        *(undefined1 *)(param_1 + 0x67) = 1;
        uVar3 = FUN_005c8250("cvfigh",2,"spawn_attack_wave1",0,0);
        *(undefined4 *)(param_1 + 0xb0) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(param_1 + 0x94),1);
        FUN_005cd6f0(*(undefined4 *)(param_1 + 0xb0));
        FUN_005cd6c0(*(undefined4 *)(param_1 + 0xb0));
        uVar3 = FUN_005c8250("cvfigh",2,"spawn_attack_wave1_1",0,0);
        *(undefined4 *)(param_1 + 0xb4) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0xb4),*(undefined4 *)(param_1 + 0x94),1);
        FUN_005cd6f0(*(undefined4 *)(param_1 + 0xb4));
        FUN_005cd6c0(*(undefined4 *)(param_1 + 0xb4));
        fVar5 = (float10)FUN_004b1670();
        *(float *)(param_1 + 0x6c) = (float)fVar5 + 60.0;
        FUN_00630e30();
      }
      if (*(char *)(param_1 + 0x5a) == '\0') {
        if (*(char *)(param_1 + 0x58) == '\0') {
          FUN_005cd2a0();
          *(undefined1 *)(param_1 + 0x58) = 1;
          cVar1 = FUN_005c84d0(param_1 + 0xa8);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x94),1);
          }
          cVar1 = FUN_005c84d0(param_1 + 0xac);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0xac),*(undefined4 *)(param_1 + 0x94),1);
          }
          uVar3 = FUN_00437d30("bd01003.wav");
          *(undefined4 *)(param_1 + 0xf0) = uVar3;
        }
        cVar1 = FUN_005cd300("camera_attack_view",2000,1000,*(undefined4 *)(param_1 + 0xb0));
        cVar2 = FUN_005cd560();
        if (cVar2 != '\0') {
          cVar1 = '\x01';
          FUN_00437d80(*(undefined4 *)(param_1 + 0xf0));
        }
        if (cVar1 != '\0') {
          FUN_005cd4e0();
          *(undefined1 *)(param_1 + 0x5a) = 1;
          *(undefined1 *)(param_1 + 0x58) = 0;
          uVar3 = FUN_005c8250("cvfigh",2,"spawn_attack_wave1a",0,0);
          *(undefined4 *)(param_1 + 0xb8) = uVar3;
          FUN_005cb820(*(undefined4 *)(param_1 + 0xb8),*(undefined4 *)(param_1 + 0x94),1);
          FUN_005cd6f0(*(undefined4 *)(param_1 + 0xb8));
          FUN_005cd6c0(*(undefined4 *)(param_1 + 0xb8));
          uVar3 = FUN_005c8250("cvfigh",2,"spawn_attack_wave2",0,0);
          *(undefined4 *)(param_1 + 0xbc) = uVar3;
          FUN_005cb820(*(undefined4 *)(param_1 + 0xbc),*(undefined4 *)(param_1 + 0x94),1);
          FUN_005cd6f0(*(undefined4 *)(param_1 + 0xbc));
          FUN_005cd6c0(*(undefined4 *)(param_1 + 0xbc));
        }
      }
      fVar5 = (float10)FUN_004b1670();
      if (*(float *)(param_1 + 0x6c) <= (float)fVar5) {
        cVar1 = FUN_005c84d0(param_1 + 0xb0);
        if (((((cVar1 == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xb4), cVar1 == '\0')) &&
             (cVar1 = FUN_005c84d0(param_1 + 0xb8), cVar1 == '\0')) &&
            ((cVar1 = FUN_005c84d0(param_1 + 0xbc), cVar1 == '\0' &&
             (cVar1 = FUN_005c84d0(param_1 + 0xa8), cVar1 == '\0')))) &&
           ((cVar1 = FUN_005c84d0(param_1 + 0xac), cVar1 == '\0' &&
            (*(char *)(param_1 + 0x5e) == '\0')))) {
          *(undefined1 *)(param_1 + 0x5e) = 1;
          uVar3 = FUN_00437d30("bd01004.wav");
          *(undefined4 *)(param_1 + 0xe4) = uVar3;
          *(undefined1 *)(param_1 + 0x57) = 1;
          FUN_00630e30();
        }
        if (((*(char *)(param_1 + 0x5e) != '\0') && (*(char *)(param_1 + 0x62) == '\0')) &&
           (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0xe4)), cVar1 != '\0')) {
          *(undefined1 *)(param_1 + 0x62) = 1;
          fVar5 = (float10)FUN_004b1670("bd01win.des");
          FUN_0045c110((float)fVar5 + 4.0);
        }
      }
    }
  }
LAB_00630e13:
  FUN_0083e885();
  return;
}

