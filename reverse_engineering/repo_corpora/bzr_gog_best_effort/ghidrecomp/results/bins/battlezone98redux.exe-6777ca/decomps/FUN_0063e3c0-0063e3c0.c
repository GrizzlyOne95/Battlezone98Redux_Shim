
void __fastcall FUN_0063e3c0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_d0 [4];
  undefined1 local_cc [4];
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  undefined4 local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  undefined1 local_18 [4];
  int local_14;
  float local_10;
  undefined4 local_c;
  int local_8;
  
  local_14 = 0;
  *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0x8c);
  local_8 = param_1;
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(local_8 + 0x8c) = uVar2;
  if (*(char *)(local_8 + 0x54) == '\0') {
    FUN_005cadd0(1,0);
    FUN_005cacb0(1,0);
    *(undefined1 *)(local_8 + 0x54) = 1;
    fVar4 = (float10)FUN_004b1670();
    local_70 = (float)fVar4;
    *(float *)(local_8 + 0x6c) = local_70 + 1.0;
    FUN_004f6aa0();
    FUN_004f6ab0("bd09001.otf",DAT_0091755c,0x41000000,0);
    FUN_005c95e0(*(undefined4 *)(local_8 + 0x9c));
  }
  fVar4 = (float10)FUN_004b1670();
  local_c0 = (float)fVar4;
  if (*(float *)(local_8 + 0x6c) <= local_c0 && local_c0 != *(float *)(local_8 + 0x6c)) {
    *(undefined4 *)(local_8 + 0x6c) = 0x497423fe;
    uVar2 = FUN_00437d30("bd09001.wav");
    *(undefined4 *)(local_8 + 0xc4) = uVar2;
  }
  if (*(int *)(local_8 + 0xc4) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 0xc4));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_8 + 0xc4) = 0;
      fVar4 = (float10)FUN_004b1670();
      local_38 = (float)fVar4;
      *(float *)(local_8 + 0x70) = local_38 + 15.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  local_88 = (float)fVar4;
  if (*(float *)(local_8 + 0x70) <= local_88 && local_88 != *(float *)(local_8 + 0x70)) {
    *(undefined4 *)(local_8 + 0x70) = 0x497423fe;
    cVar1 = FUN_005c8410(*(undefined4 *)(local_8 + 0x8c),"cvapc");
    if ((cVar1 != '\0') && (*(char *)(local_8 + 0x66) == '\0')) {
      *(undefined1 *)(local_8 + 0x62) = 1;
      *(undefined1 *)(local_8 + 0x5d) = 1;
      uVar2 = FUN_00437d30("bd09002.wav");
      *(undefined4 *)(local_8 + 200) = uVar2;
      FUN_004f6ab0("bd09004.otf",DAT_0091755c,0x41000000,0);
    }
  }
  if (*(char *)(local_8 + 0x62) == '\0') {
    cVar1 = FUN_005c8410(*(undefined4 *)(local_8 + 0x8c),"cvapc");
    if ((cVar1 == '\0') && (*(char *)(local_8 + 0x66) == '\0')) {
      *(undefined1 *)(local_8 + 0x66) = 1;
      *(undefined1 *)(local_8 + 0x5d) = 0;
      FUN_005c88b0(*(undefined4 *)(local_8 + 0x8c),1);
      FUN_005cb820(*(undefined4 *)(local_8 + 0xa0),*(undefined4 *)(local_8 + 0x8c),1);
      FUN_005cb820(*(undefined4 *)(local_8 + 0xa4),*(undefined4 *)(local_8 + 0x8c),1);
      FUN_005cb820(*(undefined4 *)(local_8 + 0xa8),*(undefined4 *)(local_8 + 0x8c),1);
      FUN_005cb820(*(undefined4 *)(local_8 + 0xac),*(undefined4 *)(local_8 + 0x8c),1);
      fVar4 = (float10)FUN_004b1670();
      local_40 = (float)fVar4;
      *(float *)(local_8 + 0x80) = local_40 + 1.0;
      FUN_004f6aa0();
      FUN_004f6ab0("bd09003.otf",DAT_0091755c,0x41000000,0);
    }
  }
  if (*(int *)(local_8 + 200) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 200));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_8 + 200) = 0;
    }
  }
  if (*(char *)(local_8 + 0x5d) == '\0') {
    if (*(char *)(local_8 + 0x66) != '\0') {
      FUN_005c88b0(*(undefined4 *)(local_8 + 0x8c),1);
    }
  }
  else {
    FUN_005c88b0(*(undefined4 *)(local_8 + 0x8c),2);
  }
  if ((*(char *)(local_8 + 0x55) != '\0') && (*(char *)(local_8 + 0x66) == '\0')) {
    if (*(char *)(local_8 + 0x60) == '\0') {
      local_24 = 0.0;
    }
    else {
      local_24 = 75.0;
    }
    if (*(char *)(local_8 + 0x56) == '\0') {
      local_1c = 0.0;
    }
    else {
      local_1c = 75.0;
    }
    local_10 = local_24 + 75.0 + local_1c;
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x8c),*(undefined4 *)(local_8 + 0xa0));
    local_b0 = (float)fVar4;
    if (((local_10 < local_b0) || (*(int *)(local_8 + 0xa0) == 0)) ||
       (*(int *)(local_8 + 0xa0) == *(int *)(local_8 + 0x8c))) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x8c),*(undefined4 *)(local_8 + 0xa4))
      ;
      local_48 = (float)fVar4;
      if (((local_10 < local_48) || (*(int *)(local_8 + 0xa4) == 0)) ||
         (*(int *)(local_8 + 0xa4) == *(int *)(local_8 + 0x8c))) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x8c),
                                      *(undefined4 *)(local_8 + 0xa8));
        local_90 = (float)fVar4;
        if (((local_10 < local_90) || (*(int *)(local_8 + 0xa8) == 0)) ||
           (*(int *)(local_8 + 0xa8) == *(int *)(local_8 + 0x8c))) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x8c),
                                        *(undefined4 *)(local_8 + 0xac));
          local_50 = (float)fVar4;
          if (((local_10 < local_50) || (*(int *)(local_8 + 0xac) == 0)) ||
             (*(int *)(local_8 + 0xac) == *(int *)(local_8 + 0x8c))) {
            *(undefined1 *)(local_8 + 0x5d) = 0;
            *(undefined1 *)(local_8 + 0x66) = 1;
            fVar4 = (float10)FUN_004b1670();
            local_c8 = (float)fVar4;
            *(float *)(local_8 + 0x80) = local_c8 + 2.0;
          }
        }
      }
    }
  }
  if (((*(char *)(local_8 + 0x66) == '\0') && (*(char *)(local_8 + 0x55) == '\0')) &&
     (((((*(int *)(local_8 + 0x8c) == *(int *)(local_8 + 0x9c) ||
         ((*(int *)(local_8 + 0x8c) == *(int *)(local_8 + 0xa0) ||
          (*(int *)(local_8 + 0x8c) == *(int *)(local_8 + 0xa4))))) ||
        (*(int *)(local_8 + 0x8c) == *(int *)(local_8 + 0xa8))) ||
       (*(int *)(local_8 + 0x8c) == *(int *)(local_8 + 0xac))) &&
      (*(char *)(local_8 + 0x62) != '\0')))) {
    *(undefined1 *)(local_8 + 0x5d) = 0;
    *(undefined1 *)(local_8 + 0x55) = 1;
    FUN_005c9610(*(undefined4 *)(local_8 + 0x9c));
    fVar4 = (float10)FUN_004b1670();
    local_58 = (float)fVar4;
    *(float *)(local_8 + 0x74) = local_58 + 5.0;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"spawn_beacon1",0,0);
    *(undefined4 *)(local_8 + 0xb0) = uVar2;
  }
  if (*(char *)(local_8 + 0x55) == '\0') {
    cVar1 = FUN_005c8490(local_8 + 0x9c);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c8490(local_8 + 0xa0);
      if (cVar1 != '\0') {
        cVar1 = FUN_005c8490(local_8 + 0xa4);
        if (cVar1 != '\0') {
          cVar1 = FUN_005c8490(local_8 + 0xa4);
          if (cVar1 != '\0') {
            cVar1 = FUN_005c8490(local_8 + 0xa8);
            if (cVar1 != '\0') {
              cVar1 = FUN_005c8490(local_8 + 0xac);
              if (cVar1 != '\0') goto LAB_0063eb04;
            }
          }
        }
      }
    }
    FUN_005c88b0(*(undefined4 *)(local_8 + 0x8c),1);
    *(undefined1 *)(local_8 + 0x5d) = 0;
    *(undefined1 *)(local_8 + 0x66) = 1;
    fVar4 = (float10)FUN_004b1670();
    local_98 = (float)fVar4;
    *(float *)(local_8 + 0x80) = local_98 + 2.0;
  }
LAB_0063eb04:
  fVar4 = (float10)FUN_004b1670();
  local_60 = (float)fVar4;
  if ((*(float *)(local_8 + 0x74) <= local_60 && local_60 != *(float *)(local_8 + 0x74)) &&
     (*(char *)(local_8 + 0x5e) == '\0')) {
    *(undefined4 *)(local_8 + 0x74) = 0x497423fe;
    uVar2 = FUN_00437d30("bd09003.wav");
    *(undefined4 *)(local_8 + 0xcc) = uVar2;
  }
  if (*(int *)(local_8 + 0xcc) != 0) {
    cVar1 = FUN_00437d60(*(undefined4 *)(local_8 + 0xcc));
    if (cVar1 != '\0') {
      *(undefined4 *)(local_8 + 0xcc) = 0;
      FUN_004f6aa0();
      FUN_004f6ab0("bd09001.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("bd09002.otf",DAT_0091755c,0x41000000,0);
      fVar4 = (float10)FUN_004b1670();
      local_b8 = (float)fVar4;
      *(float *)(local_8 + 0x7c) = local_b8 + 1.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  local_68 = (float)fVar4;
  if (*(float *)(local_8 + 0x7c) <= local_68 && local_68 != *(float *)(local_8 + 0x7c)) {
    *(undefined4 *)(local_8 + 0x7c) = 0x497423fe;
    cVar1 = FUN_005c84d0(local_8 + 0xa0);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(local_8 + 0xa0),"tank_path",1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xa4);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(local_8 + 0xa4),"tank_path",1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xa8);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(local_8 + 0xa8),"tank_path",1);
    }
    cVar1 = FUN_005c84d0(local_8 + 0xac);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(local_8 + 0xac),"tank_path",1);
    }
  }
  if (*(char *)(local_8 + 99) == '\0') {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb0),*(undefined4 *)(local_8 + 0x9c));
    local_a0 = (float)fVar4;
    if (100.0 <= local_a0) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb0),*(undefined4 *)(local_8 + 0xa0))
      ;
      local_2c = (float)fVar4;
      if (100.0 <= local_2c) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb0),
                                      *(undefined4 *)(local_8 + 0xa4));
        local_c4 = (float)fVar4;
        if (100.0 <= local_c4) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb0),
                                        *(undefined4 *)(local_8 + 0xa8));
          local_78 = (float)fVar4;
          if (100.0 <= local_78) {
            fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb0),
                                          *(undefined4 *)(local_8 + 0xac));
            local_a8 = (float)fVar4;
            if (100.0 <= local_a8) goto LAB_0063ee13;
          }
        }
      }
    }
    *(undefined1 *)(local_8 + 99) = 1;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"spawn_beacon2",0,0);
    *(undefined4 *)(local_8 + 0xb4) = uVar2;
  }
LAB_0063ee13:
  if (((*(char *)(local_8 + 0x55) != '\0') && (*(char *)(local_8 + 0x5f) == '\0')) &&
     (*(char *)(local_8 + 0x5e) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x8c),*(undefined4 *)(local_8 + 0xb0));
    local_80 = (float)fVar4;
    if (local_80 < 100.0) {
      *(undefined1 *)(local_8 + 0x5f) = 1;
      FUN_00437d30("bd09004.wav");
    }
  }
  if (*(char *)(local_8 + 100) == '\0') {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb4),*(undefined4 *)(local_8 + 0x9c));
    local_30 = (float)fVar4;
    if (100.0 <= local_30) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb4),*(undefined4 *)(local_8 + 0xa0))
      ;
      local_34 = (float)fVar4;
      if (100.0 <= local_34) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb4),
                                      *(undefined4 *)(local_8 + 0xa4));
        local_3c = (float)fVar4;
        if (100.0 <= local_3c) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb4),
                                        *(undefined4 *)(local_8 + 0xa8));
          local_44 = (float)fVar4;
          if (100.0 <= local_44) {
            fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb4),
                                          *(undefined4 *)(local_8 + 0xac));
            local_4c = (float)fVar4;
            if (100.0 <= local_4c) goto LAB_0063ef95;
          }
        }
      }
    }
    *(undefined1 *)(local_8 + 100) = 1;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"spawn_beacon3",0,0);
    *(undefined4 *)(local_8 + 0xb8) = uVar2;
  }
LAB_0063ef95:
  if (((*(char *)(local_8 + 0x55) != '\0') && (*(char *)(local_8 + 0x60) == '\0')) &&
     (*(char *)(local_8 + 0x5e) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x8c),*(undefined4 *)(local_8 + 0xb4));
    local_54 = (float)fVar4;
    if (local_54 < 100.0) {
      *(undefined1 *)(local_8 + 0x60) = 1;
      FUN_00437d30("bd09005.wav");
      fVar4 = (float10)FUN_004b1670();
      local_5c = (float)fVar4;
      *(float *)(local_8 + 0x78) = local_5c + 5.0;
    }
  }
  fVar4 = (float10)FUN_004b1670();
  local_64 = (float)fVar4;
  if (*(float *)(local_8 + 0x78) <= local_64 && local_64 != *(float *)(local_8 + 0x78)) {
    *(undefined4 *)(local_8 + 0x78) = 0x497423fe;
    FUN_00437d30("bd09006.wav");
    FUN_005c95e0(*(undefined4 *)(local_8 + 0x98));
  }
  if (((*(char *)(local_8 + 0x55) != '\0') && (*(char *)(local_8 + 0x56) == '\0')) &&
     ((*(char *)(local_8 + 0x5f) != '\0' && (*(char *)(local_8 + 0x60) != '\0')))) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x8c),*(undefined4 *)(local_8 + 0xb8));
    local_6c = (float)fVar4;
    if (local_6c < 100.0) {
      *(undefined1 *)(local_8 + 0x56) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0("bd09001.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("bd09002.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("bd09003.otf",DAT_0091755c,0x41000000,0);
    }
  }
  fVar4 = (float10)FUN_004b1670();
  local_74 = (float)fVar4;
  if ((*(float *)(local_8 + 0x80) <= local_74 && local_74 != *(float *)(local_8 + 0x80)) &&
     (*(char *)(local_8 + 0x5e) == '\0')) {
    FUN_005c88b0(*(undefined4 *)(local_8 + 0x8c),1);
    FUN_004f6aa0();
    if (*(char *)(local_8 + 0x55) != '\0') {
      FUN_004f6ab0("bd09001.otf",DAT_009175b0,0x41000000,0);
    }
    if (*(char *)(local_8 + 0x56) != '\0') {
      FUN_004f6ab0("bd09002.otf",DAT_009175b0,0x41000000,0);
    }
    FUN_004f6ab0("bd09003.otf",DAT_0091755c,0x41000000,0);
    *(undefined4 *)(local_8 + 0x80) = 0x497423fe;
    *(undefined1 *)(local_8 + 0x5e) = 1;
    local_c = FUN_005c8250("cvfigh",2,"spawn_deviate1",0,0);
    FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    if ((*(char *)(local_8 + 0x55) == '\0') || (*(char *)(local_8 + 0x60) == '\0')) {
      local_c = FUN_005c8250("cvfigh",2,"spawn_deviate1",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    if (*(char *)(local_8 + 0x56) == '\0') {
      local_c = FUN_005c8250("cvltnk",2,"spawn_deviate2",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    if ((*(char *)(local_8 + 0x55) == '\0') || (*(char *)(local_8 + 0x60) == '\0')) {
      local_c = FUN_005c8250("cvltnk",2,"spawn_deviate2",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    if (*(char *)(local_8 + 0x56) == '\0') {
      local_c = FUN_005c8250("cvhtnk",2,"spawn_deviate3",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
      local_c = FUN_005c8250("cvrckt",2,"spawn_deviate4",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    else {
      local_c = FUN_005c8250("cvfigh",2,"spawn_deviate4",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    if ((*(char *)(local_8 + 0x55) == '\0') || (*(char *)(local_8 + 0x60) == '\0')) {
      local_c = FUN_005c8250("cvrckt",2,"spawn_deviate4",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    local_c = FUN_005c8250("cvfigh",2,"spawn_deviate5",0,0);
    FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    if ((*(char *)(local_8 + 0x55) == '\0') || (*(char *)(local_8 + 0x60) == '\0')) {
      local_c = FUN_005c8250("cvfigh",2,"spawn_deviate5",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    if (*(char *)(local_8 + 0x56) == '\0') {
      local_c = FUN_005c8250("cvtnk",2,"spawn_deviate6",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    if ((*(char *)(local_8 + 0x55) == '\0') || (*(char *)(local_8 + 0x60) == '\0')) {
      local_c = FUN_005c8250("cvtnk",2,"spawn_deviate6",0,0);
      FUN_005cb820(local_c,*(undefined4 *)(local_8 + 0x8c),1);
    }
    FUN_00437d30("bd09007.wav");
    local_20 = DAT_00917a74;
    FID_conflict_begin(local_18);
    while( true ) {
      uVar2 = FID_conflict_end(local_d0);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_00421ec0();
      local_7c = *puVar3;
      local_28 = FUN_00477590(local_7c);
      cVar1 = FUN_005c8410(local_28,"cvturrc");
      if (cVar1 != '\0') {
        FUN_005cb820(local_28,*(undefined4 *)(local_8 + 0x8c),1);
      }
      FUN_0046b260(local_cc,0);
    }
  }
  if (*(char *)(local_8 + 0x55) != '\0') {
    cVar1 = FUN_005c8410(*(undefined4 *)(local_8 + 0x8c),"cvtnkb");
    if ((cVar1 == '\0') && (*(float *)(local_8 + 0x84) <= 0.0 && *(float *)(local_8 + 0x84) != 0.0))
    {
      fVar4 = (float10)FUN_004b1670();
      local_84 = (float)fVar4;
      *(float *)(local_8 + 0x84) = local_84 + 600.0;
    }
  }
  if (0.0 < *(float *)(local_8 + 0x84)) {
    cVar1 = FUN_005c8410(*(undefined4 *)(local_8 + 0x8c),"cvtnkb");
    if (cVar1 != '\0') {
      *(undefined4 *)(local_8 + 0x84) = 0xbf800000;
    }
  }
  if (0.0 < *(float *)(local_8 + 0x84)) {
    fVar4 = (float10)FUN_004b1670();
    local_8c = (float)fVar4;
    if (((*(float *)(local_8 + 0x84) <= local_8c && local_8c != *(float *)(local_8 + 0x84)) &&
        (*(char *)(local_8 + 0x69) == '\0')) && (*(char *)(local_8 + 0x68) == '\0')) {
      *(undefined1 *)(local_8 + 0x68) = 1;
      *(undefined4 *)(local_8 + 0x84) = 0xbf800000;
      fVar4 = (float10)FUN_004b1670("bd09lose.des");
      local_94 = (float)fVar4;
      FUN_0045c0f0(local_94 + 1.0);
    }
  }
  fVar4 = (float10)FUN_005c9800(*(undefined4 *)(local_8 + 0x8c),"trigger_1",0);
  local_9c = (float)fVar4;
  if ((local_9c < 200.0) && (*(char *)(local_8 + 0x5c) == '\0')) {
    *(undefined1 *)(local_8 + 0x5c) = 1;
    for (local_14 = 0; local_14 < 2; local_14 = local_14 + 1) {
      local_a4 = FUN_005c8250("cvtnkb",2,"last_one",0,0);
      FUN_005cb820(local_a4,*(undefined4 *)(local_8 + 0x8c),1);
    }
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x8c),*(undefined4 *)(local_8 + 0x98));
  local_ac = (float)fVar4;
  if ((local_ac < 250.0) && (*(char *)(local_8 + 0x67) == '\0')) {
    *(undefined1 *)(local_8 + 0x67) = 1;
    FUN_005cdea0(*(undefined4 *)(local_8 + 0x98),1);
    uVar2 = FUN_00437d30("bd09008.wav");
    *(undefined4 *)(local_8 + 0xc0) = uVar2;
  }
  cVar1 = FUN_005cdfb0(*(undefined4 *)(local_8 + 0x8c),*(undefined4 *)(local_8 + 0x98),0x3fa66666);
  if (((cVar1 != '\0') && (*(char *)(local_8 + 0x69) == '\0')) &&
     (*(char *)(local_8 + 0x68) == '\0')) {
    cVar1 = FUN_005c8410(*(undefined4 *)(local_8 + 0x8c),"cvtnkb");
    if (cVar1 == '\0') {
      *(undefined1 *)(local_8 + 0x68) = 1;
      *(undefined4 *)(local_8 + 0x84) = 0xbf800000;
      fVar4 = (float10)FUN_004b1670("bd09lose.des");
      local_b4 = (float)fVar4;
      FUN_0045c0f0(local_b4 + 1.0);
    }
    else {
      *(undefined1 *)(local_8 + 0x69) = 1;
      fVar4 = (float10)FUN_004b1670("bd09win.des");
      FUN_0045c110((float)fVar4);
    }
  }
  fVar4 = (float10)FUN_005cced0(*(undefined4 *)(local_8 + 0x98));
  if ((((double)fVar4 <= 0.0) && (*(char *)(local_8 + 0x68) == '\0')) &&
     (*(char *)(local_8 + 0x69) == '\0')) {
    *(undefined1 *)(local_8 + 0x68) = 1;
    fVar4 = (float10)FUN_004b1670("bd09lseb.des");
    local_bc = (float)fVar4;
    FUN_0045c0f0(local_bc + 1.0);
  }
  return;
}

