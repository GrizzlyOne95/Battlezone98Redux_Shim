
bool FUN_004fd190(char *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  float10 fVar4;
  float local_90;
  undefined4 local_8c;
  uint local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c [2];
  char *local_74;
  undefined4 local_70;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  char *local_28;
  char *local_24;
  char *local_20;
  char *local_1c;
  char local_17;
  undefined1 local_16;
  char local_15;
  char *local_14;
  char local_d;
  FILE *local_c;
  char local_5;
  
  local_5 = '\x01';
  local_8c = FUN_004d9c80();
  FUN_004fe800(&DAT_02ceefe0);
  if (DAT_009173b7 != '\0') {
    local_74 = (char *)FUN_004fbaf0(param_1,0x2e);
    if ((local_74 == (char *)0x0) || (iVar2 = _stricmp(local_74,".trn"), iVar2 != 0)) {
      local_34 = 0;
    }
    else {
      local_34 = 1;
    }
    local_d = (char)local_34;
    if (((char)local_34 != '\0') || (DAT_02cc40b8 != 0)) {
      local_14 = (char *)FUN_004fbaf0(param_1,0x5c);
      local_88 = FUN_004fbaf0(param_1,0x2f);
      if (local_14 < local_88) {
        local_14 = (char *)local_88;
      }
      if (local_14 == (char *)0x0) {
        local_14 = param_1;
      }
      else {
        local_14 = (char *)((int)local_14 + 1);
      }
      local_24 = local_14;
      local_1c = &DAT_02a13b28;
      do {
        local_17 = *local_24;
        *local_1c = local_17;
        local_24 = local_24 + 1;
        local_1c = local_1c + 1;
      } while (local_17 != '\0');
      if (local_d == '\0') {
        local_28 = local_14;
        local_20 = &DAT_00915540;
        do {
          local_15 = *local_28;
          *local_20 = local_15;
          local_28 = local_28 + 1;
          local_20 = local_20 + 1;
        } while (local_15 != '\0');
      }
      local_14 = (char *)FUN_004fbaf0(&DAT_02a13b28,0x2e);
      if (local_14 != (undefined1 *)0x0) {
        *local_14 = 0;
      }
      if ((local_5 == '\0') || (iVar2 = FUN_00786c80(param_1), iVar2 == 0)) {
        local_3c = 0;
      }
      else {
        local_3c = 1;
      }
      local_5 = (char)local_3c;
      if (local_d != '\0') {
        return (char)local_3c != '\0';
      }
    }
  }
  local_c = fopen(param_1,"wb");
  FUN_004cf4f0();
  if (local_c == (FILE *)0x0) {
    FUN_007d6830("Failed to save game\n");
    bVar3 = false;
  }
  else {
    DAT_00917b20 = 0x7e0;
    local_16 = DAT_009173b6;
    DAT_009173b6 = 0;
    if ((local_5 == '\0') ||
       (cVar1 = FUN_004cd1b0(local_c,&DAT_00917b20,4,"version"), cVar1 == '\0')) {
      local_44 = 0;
    }
    else {
      local_44 = 1;
    }
    local_5 = (char)local_44;
    if (((char)local_44 == '\0') ||
       (cVar1 = FUN_004ccf20(local_c,&local_16,1,"binarySave"), cVar1 == '\0')) {
      local_84 = 0;
    }
    else {
      local_84 = 1;
    }
    local_5 = (char)local_84;
    DAT_009173b6 = local_16;
    if (((char)local_84 == '\0') ||
       (cVar1 = FUN_004cce90(local_c,&DAT_00915540,0x10,"msn_filename"), cVar1 == '\0')) {
      local_4c = 0;
    }
    else {
      local_4c = 1;
    }
    local_5 = (char)local_4c;
    if (((char)local_4c == '\0') ||
       (cVar1 = FUN_004cd1b0(local_c,&local_8c,4,"seq_count"), cVar1 == '\0')) {
      local_2c = 0;
    }
    else {
      local_2c = 1;
    }
    local_5 = (char)local_2c;
    if (((char)local_2c == '\0') ||
       (cVar1 = FUN_004ccf20(local_c,&DAT_009173b7,1,"missionSave"), cVar1 == '\0')) {
      local_54 = 0;
    }
    else {
      local_54 = 1;
    }
    local_5 = (char)local_54;
    if (DAT_009173b7 == '\0') {
      local_7c[0] = param_2;
      if (((char)local_54 == '\0') ||
         (cVar1 = FUN_004cd1b0(local_c,local_7c,4,"runType"), cVar1 == '\0')) {
        local_80 = 0;
      }
      else {
        local_80 = 1;
      }
      local_5 = (char)local_80;
      if (((char)local_80 == '\0') ||
         (cVar1 = FUN_004ccd80(local_c,&DAT_008e86d8,0x100,"saveGameDesc"), cVar1 == '\0')) {
        local_5c = 0;
      }
      else {
        local_5c = 1;
      }
      local_5 = (char)local_5c;
      if (((char)local_5c == '\0') || (iVar2 = FUN_004fd7e0(local_c,local_7c[0]), iVar2 == 0)) {
        local_64 = 0;
      }
      else {
        local_64 = 1;
      }
      local_5 = (char)local_64;
    }
    if ((local_5 == '\0') ||
       (cVar1 = FUN_004cce90(local_c,&DAT_02a13b28,100,"TerrainName"), cVar1 == '\0')) {
      local_30 = 0;
    }
    else {
      local_30 = 1;
    }
    local_5 = (char)local_30;
    if (DAT_009173b7 == '\0') {
      fVar4 = (float10)FUN_00822d80();
      local_90 = (float)fVar4;
      if ((local_5 == '\0') ||
         (cVar1 = FUN_004cd360(local_c,&local_90,4,"start_time"), cVar1 == '\0')) {
        local_38 = 0;
      }
      else {
        local_38 = 1;
      }
      local_5 = (char)local_38;
    }
    if ((local_5 == '\0') || (cVar1 = FUN_004dd1c0(local_c), cVar1 == '\0')) {
      local_40 = 0;
    }
    else {
      local_40 = 1;
    }
    local_5 = (char)local_40;
    if (((char)local_40 == '\0') || (cVar1 = FUN_005e0da0(local_c), cVar1 == '\0')) {
      local_48 = 0;
    }
    else {
      local_48 = 1;
    }
    local_5 = (char)local_48;
    if (((char)local_48 == '\0') || (cVar1 = FUN_0045d550(local_c), cVar1 == '\0')) {
      local_50 = 0;
    }
    else {
      local_50 = 1;
    }
    local_5 = (char)local_50;
    if (((char)local_50 == '\0') || (cVar1 = FUN_0046f720(local_c), cVar1 == '\0')) {
      local_58 = 0;
    }
    else {
      local_58 = 1;
    }
    local_5 = (char)local_58;
    if (((char)local_58 == '\0') || (cVar1 = FUN_00460790(local_c), cVar1 == '\0')) {
      local_60 = 0;
    }
    else {
      local_60 = 1;
    }
    local_5 = (char)local_60;
    if (DAT_009173b7 == '\0') {
      if (((char)local_60 == '\0') || (cVar1 = FUN_00461d90(local_c), cVar1 == '\0')) {
        local_68 = 0;
      }
      else {
        local_68 = 1;
      }
      local_5 = (char)local_68;
    }
    if ((local_5 == '\0') || (cVar1 = FUN_005c7b90(local_c), cVar1 == '\0')) {
      local_70 = 0;
    }
    else {
      local_70 = 1;
    }
    local_5 = (char)local_70;
    fclose(local_c);
    FUN_004cf4f0();
    bVar3 = local_5 != '\0';
  }
  return bVar3;
}

