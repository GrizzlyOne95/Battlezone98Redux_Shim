
void FUN_005390a0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_a8 [4];
  undefined1 local_a4 [4];
  undefined1 local_a0 [4];
  undefined1 local_9c [4];
  undefined1 local_98 [4];
  undefined1 local_94 [4];
  float local_90;
  float local_8c;
  undefined4 local_88;
  float local_84;
  float local_80;
  float local_7c;
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
  undefined4 local_50;
  float local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int local_8;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(local_8 + 0x80) = uVar2;
  if (*(char *)(local_8 + 0x5d) == '\0') {
    uVar2 = FUN_005c7e90("avhaul0_tug");
    *(undefined4 *)(local_8 + 0x98) = uVar2;
    uVar2 = FUN_005c7e90("avhaul1_tug");
    *(undefined4 *)(local_8 + 0x9c) = uVar2;
    uVar2 = FUN_005c7e90("avhaul2_tug");
    *(undefined4 *)(local_8 + 0xac) = uVar2;
    uVar2 = FUN_005c7e90("svturr2_turrettank");
    *(undefined4 *)(local_8 + 0xa0) = uVar2;
    uVar2 = FUN_005c7e90("second_blockade");
    *(undefined4 *)(local_8 + 0xa4) = uVar2;
    uVar2 = FUN_005c7e90("svturr3_turrettank");
    *(undefined4 *)(local_8 + 0xa8) = uVar2;
    uVar2 = FUN_005c7e90("apcamr3_camerapod");
    *(undefined4 *)(local_8 + 0x88) = uVar2;
    uVar2 = FUN_005c7e90("apcamr4_camerapod");
    *(undefined4 *)(local_8 + 0x8c) = uVar2;
    uVar2 = FUN_005c7e90("apcamr5_camerapod");
    *(undefined4 *)(local_8 + 0x90) = uVar2;
    uVar2 = FUN_005c7e90("launch_pad");
    *(undefined4 *)(local_8 + 0xb0) = uVar2;
    uVar2 = FUN_005c7e90("launch_pad2");
    *(undefined4 *)(local_8 + 0xb4) = uVar2;
    FUN_005c9640(*(undefined4 *)(local_8 + 0x88),"Waypoint 1");
    FUN_005c9640(*(undefined4 *)(local_8 + 0x8c),"Waypoint 2");
    FUN_005c9640(*(undefined4 *)(local_8 + 0x90),"Launch Pad");
    FUN_005c95e0(*(undefined4 *)(local_8 + 0x98));
    FUN_005c9640(*(undefined4 *)(local_8 + 0x98),"Transport 1");
    FUN_005cbd40(*(undefined4 *)(local_8 + 0x98),1);
    FUN_005caff0(*(undefined4 *)(local_8 + 0x98),1);
    FUN_005c95e0(*(undefined4 *)(local_8 + 0x9c));
    FUN_005c9640(*(undefined4 *)(local_8 + 0x9c),"Transport 2");
    FUN_005cbd40(*(undefined4 *)(local_8 + 0x9c),1);
    FUN_005caff0(*(undefined4 *)(local_8 + 0x9c),1);
    FUN_005c95e0(*(undefined4 *)(local_8 + 0xac));
    FUN_005c9640(*(undefined4 *)(local_8 + 0xac),"Transport 3");
    FUN_005cbd40(*(undefined4 *)(local_8 + 0xac),1);
    FUN_005caff0(*(undefined4 *)(local_8 + 0xac),1);
    FUN_005c88e0(*(undefined4 *)(local_8 + 0x88));
    FUN_005cadd0(1,0x32);
    FUN_00437d30("misn1101.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("misn1101.otf",DAT_0091755c,0x41000000,0);
    fVar4 = (float10)FUN_00822d80();
    local_5c = (float)fVar4;
    *(float *)(local_8 + 0x78) = local_5c + 15.0;
    *(undefined1 *)(local_8 + 0x5d) = 1;
  }
  cVar1 = FUN_005c84d0(local_8 + 0xac);
  if (cVar1 != '\0') {
    FUN_005ccfd0(*(undefined4 *)(local_8 + 0xac),0x43960000);
  }
  fVar4 = (float10)FUN_00822d80();
  local_80 = (float)fVar4;
  if (*(float *)(local_8 + 0x78) <= local_80 && local_80 != *(float *)(local_8 + 0x78)) {
    FUN_00437d30("misn1102.wav");
    *(undefined4 *)(local_8 + 0x78) = 0x47c34f80;
    FUN_005cb960(*(undefined4 *)(local_8 + 0x98),"base1",1);
    FUN_005cb960(*(undefined4 *)(local_8 + 0x9c),"base1",1);
    FUN_005cb960(*(undefined4 *)(local_8 + 0xac),"base1",1);
  }
  if (*(char *)(local_8 + 0x5e) == '\0') {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x88),*(undefined4 *)(local_8 + 0xac));
    local_3c = (float)fVar4;
    if (local_3c < 50.0) {
      fVar4 = (float10)FUN_004b1670();
      local_74 = (float)fVar4;
      *(float *)(local_8 + 0x74) = local_74 + 15.0;
      FUN_005cb960(*(undefined4 *)(local_8 + 0xac),"openheimer",1);
      *(undefined1 *)(local_8 + 0x5e) = 1;
    }
  }
  fVar4 = (float10)FUN_00822d80();
  local_44 = (float)fVar4;
  if (*(float *)(local_8 + 0x74) <= local_44 && local_44 != *(float *)(local_8 + 0x74)) {
    *(undefined4 *)(local_8 + 0x74) = 0x47c34f80;
    FUN_00437d30("misn1103.wav");
    FUN_00437d30("misn1104.wav");
    FUN_005c8840(*(undefined4 *)(local_8 + 0xac),2);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xa0),0);
    FUN_005cbc80(*(undefined4 *)(local_8 + 0xa8),0);
    FUN_00437d30("misn1105.wav");
    FUN_005c8250("svfigh",2,"strike1",0,0);
    local_18 = DAT_00917a74;
    FID_conflict_begin(local_c);
    while( true ) {
      uVar2 = FID_conflict_end(local_9c);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_00421ec0();
      local_88 = *puVar3;
      local_20 = FUN_00477590(local_88);
      cVar1 = FUN_005c8410(local_20,"svfigh");
      if (cVar1 != '\0') {
        FUN_005cb960(local_20,"strike_path1",0);
      }
      FUN_0046b260(local_94,0);
    }
    *(undefined1 *)(local_8 + 0x60) = 1;
    FUN_004f6aa0();
    FUN_004f6ab0("misn1102.otf",DAT_0091755c,0x41000000,0);
  }
  if ((*(char *)(local_8 + 0x60) != '\0') && (*(char *)(local_8 + 0x5f) == '\0')) {
    cVar1 = FUN_005c84d0(local_8 + 0xa0);
    if (cVar1 != '\0') {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xa0),*(undefined4 *)(local_8 + 0x80))
      ;
      local_4c = (float)fVar4;
      if (local_4c != 0.0) {
        FUN_00437d30("misn1106.wav");
        *(undefined1 *)(local_8 + 0x5f) = 1;
      }
    }
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x88),*(undefined4 *)(local_8 + 0x98));
  local_7c = (float)fVar4;
  if (local_7c < 50.0) {
LAB_005396cf:
    if (*(char *)(local_8 + 0x61) == '\0') {
      *(undefined1 *)(local_8 + 0x61) = 1;
      FUN_005c88e0(*(undefined4 *)(local_8 + 0x8c));
    }
  }
  else {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x88),*(undefined4 *)(local_8 + 0x80));
    local_54 = (float)fVar4;
    if (local_54 < 50.0) goto LAB_005396cf;
  }
  fVar4 = (float10)FUN_005c9800(*(undefined4 *)(local_8 + 0x98),"check2",1);
  local_90 = (float)fVar4;
  if ((local_90 < 50.0) && (*(char *)(local_8 + 0x62) == '\0')) {
    FUN_005c9610(*(undefined4 *)(local_8 + 0xac));
    *(undefined1 *)(local_8 + 0x62) = 1;
    FUN_005c88e0(*(undefined4 *)(local_8 + 0x90));
    FUN_00437d30("misn1107.wav");
    FUN_005c8250("svfigh",2,"strike2",0,0);
    local_28 = DAT_00917a74;
    FID_conflict_begin(local_10);
    while( true ) {
      uVar2 = FID_conflict_end(local_98);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_00421ec0();
      local_30 = *puVar3;
      local_1c = FUN_00477590(local_30);
      cVar1 = FUN_005c8410(local_1c,"svfigh");
      if (cVar1 != '\0') {
        FUN_005cb960(local_1c,"strike_path2",0);
      }
      FUN_0046b260(local_a4,0);
    }
  }
  if ((*(char *)(local_8 + 0x62) != '\0') && (*(char *)(local_8 + 99) == '\0')) {
    cVar1 = FUN_005c84d0(local_8 + 0xa4);
    if (cVar1 == '\0') {
      FUN_00437d30("misn1102.wav");
      FUN_005cb960(*(undefined4 *)(local_8 + 0x98),"base2",1);
      FUN_005cb960(*(undefined4 *)(local_8 + 0x9c),"base2",1);
      *(undefined1 *)(local_8 + 99) = 1;
    }
  }
  if ((*(char *)(local_8 + 99) != '\0') && (*(char *)(local_8 + 100) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb0),*(undefined4 *)(local_8 + 0x80));
    local_84 = (float)fVar4;
    if (450.0 <= local_84) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0xb0),*(undefined4 *)(local_8 + 0x98))
      ;
      local_64 = (float)fVar4;
      if (450.0 <= local_64) goto LAB_005399b8;
    }
    uVar2 = FUN_005c8250("svtank",2,"launch_attack",0,0);
    *(undefined4 *)(local_8 + 0xb8) = uVar2;
    uVar2 = FUN_005c8250("svtank",2,"launch_attack",0,0);
    *(undefined4 *)(local_8 + 0xbc) = uVar2;
    FUN_005ccfd0(*(undefined4 *)(local_8 + 0xb0),0xbf666666);
    FUN_00437d30("misn1108.wav");
    FUN_005cb820(*(undefined4 *)(local_8 + 0xb8),*(undefined4 *)(local_8 + 0xb0),1);
    FUN_005cb820(*(undefined4 *)(local_8 + 0xbc),*(undefined4 *)(local_8 + 0xb0),1);
    *(undefined1 *)(local_8 + 100) = 1;
  }
LAB_005399b8:
  if (*(char *)(local_8 + 100) != '\0') {
    cVar1 = FUN_005c84d0(local_8 + 0xb0);
    if ((cVar1 == '\0') && (*(char *)(local_8 + 0x56) == '\0')) {
      FUN_00437d30("misn1109.wav");
      *(undefined1 *)(local_8 + 0x56) = 1;
      fVar4 = (float10)FUN_004b1670();
      local_8c = (float)fVar4;
      *(float *)(local_8 + 0x68) = local_8c + 40.0;
    }
  }
  if (*(char *)(local_8 + 100) != '\0') {
    cVar1 = FUN_005c84d0(local_8 + 0xb8);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_8 + 0xbc);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(local_8 + 0xb0);
        if (cVar1 != '\0') {
          FUN_005c83e0(*(undefined4 *)(local_8 + 0xb0));
          *(undefined1 *)(local_8 + 0x56) = 1;
          fVar4 = (float10)FUN_004b1670();
          local_6c = (float)fVar4;
          *(float *)(local_8 + 0x68) = local_6c + 10.0;
        }
      }
    }
  }
  if (*(char *)(local_8 + 0x56) != '\0') {
    fVar4 = (float10)FUN_004b1670();
    local_34 = (float)fVar4;
    if (*(float *)(local_8 + 0x68) <= local_34 && local_34 != *(float *)(local_8 + 0x68)) {
      FUN_005cb960(*(undefined4 *)(local_8 + 0x98),"escape",1);
      FUN_005cb960(*(undefined4 *)(local_8 + 0x9c),"escape",1);
      FUN_00437d30("misn1110.wav");
      FUN_005c95e0(*(undefined4 *)(local_8 + 0xb4));
      FUN_004f6aa0();
      FUN_004f6ab0("misn1103.otf",DAT_0091755c,0x41000000,0);
      FUN_005c9640(*(undefined4 *)(local_8 + 0xb4),"Launch Pad 2");
      *(undefined4 *)(local_8 + 0x68) = 0x47c34f80;
      *(undefined1 *)(local_8 + 0x57) = 1;
      fVar4 = (float10)FUN_004b1670();
      local_38 = (float)fVar4;
      *(float *)(local_8 + 0x6c) = local_38 + 15.0;
    }
  }
  if (*(char *)(local_8 + 0x58) == '\0') {
    fVar4 = (float10)FUN_004b1670();
    local_40 = (float)fVar4;
    if (*(float *)(local_8 + 0x6c) <= local_40 && local_40 != *(float *)(local_8 + 0x6c)) {
      FUN_005c8250("svfigh",2,"strike2",0,0);
      FUN_005c8250("svfigh",2,"strike2",0,0);
      local_24 = DAT_00917a74;
      FID_conflict_begin(local_14);
      while( true ) {
        uVar2 = FID_conflict_end(local_a8);
        cVar1 = FID_conflict_operator__(uVar2);
        if (cVar1 == '\0') break;
        puVar3 = (undefined4 *)FUN_00421ec0();
        local_48 = *puVar3;
        local_2c = FUN_00477590(local_48);
        cVar1 = FUN_005c8410(local_2c,"svfigh");
        if (cVar1 != '\0') {
          FUN_005cb820(local_2c,*(undefined4 *)(local_8 + 0x9c),1);
        }
        FUN_0046b260(local_a0,0);
      }
      local_50 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_8 + 0xb4),0);
      FUN_005cb820(local_50,*(undefined4 *)(local_8 + 0x80),1);
      FUN_005c8250(&DAT_00878c18,1,"last_camera",0,0);
      *(undefined1 *)(local_8 + 0x58) = 1;
      *(undefined4 *)(local_8 + 0x6c) = 0x47c34f80;
    }
  }
  if (*(char *)(local_8 + 0x55) != '\0') goto LAB_00539dd3;
  cVar1 = FUN_005c84d0(local_8 + 0x98);
  if (cVar1 != '\0') {
    cVar1 = FUN_005c84d0(local_8 + 0x9c);
    if (cVar1 != '\0') {
      if (*(char *)(local_8 + 0x5e) != '\0') goto LAB_00539dd3;
      cVar1 = FUN_005c84d0(local_8 + 0xac);
      if (cVar1 != '\0') goto LAB_00539dd3;
    }
  }
  if (*(char *)(local_8 + 0x5e) != '\0') {
    FUN_004f6aa0();
    FUN_004f6ab0("misn1102.otf",DAT_0091755c,0x41000000,0);
  }
  FUN_00437d30("misn1111.wav");
  FUN_00437d30("misn1112.wav");
  *(undefined1 *)(local_8 + 0x55) = 1;
  fVar4 = (float10)FUN_004b1670("misn11l1.des");
  local_58 = (float)fVar4;
  FUN_0045c0f0(local_58 + 15.0);
LAB_00539dd3:
  if ((*(char *)(local_8 + 0x58) != '\0') && (*(char *)(local_8 + 0x59) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x80),*(undefined4 *)(local_8 + 0xb4));
    local_60 = (float)fVar4;
    if (local_60 < 200.0) {
      *(undefined1 *)(local_8 + 0x59) = 1;
    }
  }
  if ((*(char *)(local_8 + 0x58) != '\0') && (*(char *)(local_8 + 0x5a) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x98),*(undefined4 *)(local_8 + 0xb4));
    local_68 = (float)fVar4;
    if (local_68 < 200.0) {
      *(undefined1 *)(local_8 + 0x5a) = 1;
    }
  }
  if ((*(char *)(local_8 + 0x58) != '\0') && (*(char *)(local_8 + 0x5b) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(local_8 + 0x9c),*(undefined4 *)(local_8 + 0xb4));
    local_70 = (float)fVar4;
    if (local_70 < 200.0) {
      *(undefined1 *)(local_8 + 0x5b) = 1;
    }
  }
  if ((*(char *)(local_8 + 0x54) == '\0') && (*(char *)(local_8 + 0x58) != '\0')) {
    cVar1 = FUN_005c84d0(local_8 + 0x98);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(local_8 + 0x9c);
      if ((((cVar1 != '\0') && (*(char *)(local_8 + 0x59) != '\0')) &&
          (*(char *)(local_8 + 0x5a) != '\0')) && (*(char *)(local_8 + 0x5b) != '\0')) {
        FUN_00437d30("misn1113.wav");
        *(undefined1 *)(local_8 + 0x54) = 1;
        fVar4 = (float10)FUN_004b1670("misn11w1.des");
        local_78 = (float)fVar4;
        FUN_0045c110(local_78 + 15.0);
      }
    }
  }
  return;
}

