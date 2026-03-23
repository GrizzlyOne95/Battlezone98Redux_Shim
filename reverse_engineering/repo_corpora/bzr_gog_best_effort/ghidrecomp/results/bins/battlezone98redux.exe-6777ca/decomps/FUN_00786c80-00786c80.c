
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_00786c80(char *param_1)

{
  undefined4 *puVar1;
  size_t sVar2;
  size_t local_20c8;
  char *local_20c4;
  void *local_20c0;
  char *local_20bc;
  char *local_20b8;
  undefined4 *local_20b4;
  undefined4 *local_20b0;
  char *local_20ac;
  char *local_20a8;
  char *local_20a4;
  undefined4 *local_20a0;
  char local_209a;
  char local_2099;
  char local_2098;
  char local_2097;
  char local_2096;
  char local_2095;
  FILE *local_2094;
  char *local_2090;
  undefined1 local_208c [4];
  char local_2088 [4];
  undefined1 auStack_2084 [4091];
  undefined4 uStack_1089;
  undefined1 local_1084 [4091];
  undefined4 uStack_89;
  undefined1 auStack_84 [124];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (((DAT_02cc40b8 != 0) && (DAT_02c319d8 != 0)) && (0xb < DAT_02c319dc)) {
    *(int *)(DAT_02c319d8 + 8) = *(int *)(DAT_02c319d8 + 8) + 1;
  }
  DAT_02cc40b8 = 0;
  if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    sprintf((char *)((int)&uStack_1089 + 1),"%s%s%s",&DAT_02cf3000,&DAT_00871328,&DAT_02cc40c0);
  }
  else {
    local_20bc = param_1;
    local_20a4 = (char *)((int)&uStack_1089 + 1);
    do {
      local_2095 = *local_20bc;
      *local_20a4 = local_2095;
      local_20bc = local_20bc + 1;
      local_20a4 = local_20a4 + 1;
    } while (local_2095 != '\0');
    local_208c = (undefined1  [4])strrchr((char *)((int)&uStack_1089 + 1),0x5c);
    if (local_208c == (undefined1  [4])0x0) {
      local_208c = (undefined1  [4])((int)&uStack_1089 + 1);
    }
    local_2090 = strrchr((char *)((int)&uStack_1089 + 1),0x2f);
    if (local_2090 == (char *)0x0) {
      local_2090 = (char *)((int)&uStack_1089 + 1);
    }
    if ((uint)local_208c < local_2090) {
      local_208c = (undefined1  [4])local_2090;
    }
    local_208c = (undefined1  [4])strrchr((char *)local_208c,0x2e);
    if (local_208c != (undefined1  [4])0x0) {
      *(char *)local_208c = '\0';
    }
    puVar1 = &uStack_1089;
    do {
      local_20b4 = puVar1;
      local_209a = *(char *)((int)local_20b4 + 1);
      puVar1 = (undefined4 *)((int)local_20b4 + 1);
    } while (local_209a != '\0');
    *puVar1 = 0x6e72742e;
    *(undefined1 *)((int)local_20b4 + 5) = 0;
    local_20b4 = puVar1;
    local_20c0 = (void *)FUN_00829130(&DAT_02cc40c0,&local_20c8);
    if (local_20c0 != (void *)0x0) {
      local_2094 = fopen((char *)((int)&uStack_1089 + 1),"w");
      if (local_2094 == (FILE *)0x0) {
        FUN_007d6700("Can\'t create file %s",(int)&uStack_1089 + 1);
      }
      else {
        sVar2 = fwrite(local_20c0,1,local_20c8,local_2094);
        if (sVar2 != local_20c8) {
          FUN_007d6700("Can\'t write file %s",(int)&uStack_1089 + 1);
        }
        fclose(local_2094);
      }
      FUN_0062f240(local_20c0);
    }
    local_208c = (undefined1  [4])strrchr((char *)((int)&uStack_1089 + 1),0x5c);
    if (local_208c == (undefined1  [4])0x0) {
      local_208c = (undefined1  [4])((int)&uStack_1089 + 1);
    }
    local_2090 = strrchr((char *)((int)&uStack_1089 + 1),0x2f);
    if (local_2090 == (char *)0x0) {
      local_2090 = (char *)((int)&uStack_1089 + 1);
    }
    if ((uint)local_208c < local_2090) {
      local_208c = (undefined1  [4])local_2090;
    }
    if ((char *)((int)&uStack_1089 + 1U) < (uint)local_208c) {
      FUN_007800c0((char *)((int)local_208c + 1));
    }
    else {
      FUN_007800c0((int)&uStack_1089 + 1);
    }
  }
  local_20b8 = (char *)((int)&uStack_1089 + 1);
  local_20a8 = (char *)((int)&uStack_89 + 1);
  do {
    local_2097 = *local_20b8;
    *local_20a8 = local_2097;
    local_20b8 = local_20b8 + 1;
    local_20a8 = local_20a8 + 1;
  } while (local_2097 != '\0');
  local_208c = (undefined1  [4])strrchr((char *)((int)&uStack_89 + 1),0x5c);
  if (local_208c == (undefined1  [4])0x0) {
    local_208c = (undefined1  [4])((int)&uStack_89 + 1);
  }
  local_2090 = strrchr((char *)((int)&uStack_89 + 1),0x2f);
  if (local_2090 == (char *)0x0) {
    local_2090 = (char *)((int)&uStack_89 + 1);
  }
  if ((uint)local_208c < local_2090) {
    local_208c = (undefined1  [4])local_2090;
  }
  local_208c = (undefined1  [4])strrchr((char *)local_208c,0x2e);
  if (local_208c != (undefined1  [4])0x0) {
    *(char *)local_208c = '\0';
  }
  puVar1 = &uStack_89;
  do {
    local_20a0 = puVar1;
    local_2099 = *(char *)((int)local_20a0 + 1);
    puVar1 = (undefined4 *)((int)local_20a0 + 1);
  } while (local_2099 != '\0');
  *puVar1 = 0x3267682e;
  *(undefined1 *)((int)local_20a0 + 5) = 0;
  local_20c4 = (char *)((int)&uStack_89 + 1);
  local_20ac = local_2088;
  do {
    local_2096 = *local_20c4;
    *local_20ac = local_2096;
    local_20c4 = local_20c4 + 1;
    local_20ac = local_20ac + 1;
  } while (local_2096 != '\0');
  local_20a0 = puVar1;
  local_208c = (undefined1  [4])strrchr(local_2088,0x5c);
  if (local_208c == (undefined1  [4])0x0) {
    local_208c = (undefined1  [4])local_2088;
  }
  local_2090 = strrchr(local_2088,0x2f);
  if (local_2090 == (char *)0x0) {
    local_2090 = local_2088;
  }
  if ((uint)local_208c < local_2090) {
    local_208c = (undefined1  [4])local_2090;
  }
  local_208c = (undefined1  [4])strrchr((char *)local_208c,0x2e);
  if (local_208c != (undefined1  [4])0x0) {
    *(char *)local_208c = '\0';
  }
  puVar1 = (undefined4 *)(local_208c + 3);
  do {
    local_20b0 = puVar1;
    local_2098 = *(char *)((int)local_20b0 + 1);
    puVar1 = (undefined4 *)((int)local_20b0 + 1);
  } while (local_2098 != '\0');
  *puVar1 = 0x74616d2e;
  *(undefined1 *)((int)local_20b0 + 5) = 0;
  local_20b0 = puVar1;
  local_2094 = fopen((char *)((int)&uStack_89 + 1),"wb");
  if (local_2094 == (FILE *)0x0) {
    FUN_007d6700("Can\'t open file %s",(int)&uStack_89 + 1);
  }
  else {
    sVar2 = fwrite((void *)DAT_02c319d8,1,DAT_02c319dc,local_2094);
    if (sVar2 != DAT_02c319dc) {
      FUN_007d6700("Can\'t write file %s",(int)&uStack_89 + 1);
    }
    fclose(local_2094);
  }
  local_2094 = fopen(local_2088,"wb");
  if (local_2094 == (FILE *)0x0) {
    FUN_007d6700("Can\'t open file %s",local_2088);
  }
  else {
    sVar2 = fwrite(DAT_02c319d0,1,DAT_02c319d4,local_2094);
    if (sVar2 != DAT_02c319d4) {
      FUN_007d6700("Can\'t write file %s",local_2088);
    }
    fclose(local_2094);
  }
  FUN_0083e885();
  return;
}

