
void FUN_005c9080(float *param_1,float *param_2,float param_3,float param_4)

{
  float *pfVar1;
  float10 fVar2;
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  undefined4 local_80;
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
  float local_50;
  uint local_4c;
  char local_46;
  char local_45;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar2 = (float10)FUN_0044fb20(0x40400000,param_4 * 0.5);
  local_74 = (float)fVar2;
  local_80 = 0x100;
  local_20 = *param_2;
  local_1c = param_2[1];
  local_18 = param_2[2];
  fVar2 = (float10)FUN_007855e0((double)local_20,(double)local_18);
  local_28 = (float)fVar2;
  local_46 = '\0';
  local_4c = 0;
  local_6c = 9999.0;
  local_2c = local_20;
  local_24 = local_18;
  local_1c = local_28;
  FUN_004627d0(&local_64,&local_58,&local_68,&local_5c);
  local_64 = local_64 + 10.0;
  local_58 = local_58 + 10.0;
  local_68 = local_68 - 10.0;
  local_5c = local_5c - 10.0;
  do {
    fVar2 = (float10)FUN_004588c0();
    local_70 = (float)fVar2;
    fVar2 = (float10)FUN_004588c0();
    local_7c = (float)fVar2;
    local_54 = local_7c + param_3;
    local_45 = '\x01';
    for (local_50 = 0.0; local_50 <= 0.9; local_50 = local_50 + 0.05) {
      pfVar1 = (float *)FUN_005c8fc0(local_8c,&local_20,local_54 * local_50,local_70);
      local_44 = *pfVar1;
      local_40 = pfVar1[1];
      local_3c = pfVar1[2];
      local_14 = local_44;
      local_10 = local_40;
      local_c = local_3c;
      fVar2 = (float10)FUN_00453f80();
      local_78 = (float)fVar2;
      if (local_74 * 2.0 < local_78) {
        local_45 = '\0';
        break;
      }
    }
    if (local_45 != '\0') {
      pfVar1 = (float *)FUN_005c8fc0(local_98,&local_20,local_54,local_70);
      local_38 = *pfVar1;
      local_34 = pfVar1[1];
      local_30 = pfVar1[2];
      local_14 = local_38;
      local_10 = local_34;
      local_c = local_30;
      if ((((local_38 < local_64) || (local_68 <= local_38)) || (local_30 < local_58)) ||
         (local_5c <= local_30)) {
        local_45 = '\0';
      }
    }
    if (local_45 != '\0') {
      fVar2 = (float10)FUN_00453f80();
      local_60 = (float)fVar2;
      if (local_60 < local_6c) {
        local_2c = local_14;
        local_28 = local_10;
        local_24 = local_c;
        local_6c = local_60;
      }
      if (local_60 < local_74) {
        local_2c = local_14;
        local_28 = local_10;
        local_24 = local_c;
        local_46 = '\x01';
      }
    }
    local_4c = local_4c + 1;
    if ((local_4c & 0xf) == 0) {
      local_54 = local_54 * 0.9;
    }
    if ((local_46 != '\0') || (0xff < (int)local_4c)) {
      *param_1 = local_2c;
      param_1[1] = local_28;
      param_1[2] = local_24;
      FUN_0083e885();
      return;
    }
  } while( true );
}

