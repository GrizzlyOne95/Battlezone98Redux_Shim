
void FUN_0061e5d0(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  char *local_74;
  char *local_70;
  char *local_6c;
  char *local_68;
  char *local_64;
  char *local_60;
  char *local_5c;
  char *local_58;
  char *local_54;
  char *local_50;
  undefined4 *local_4c;
  char *local_48;
  undefined1 local_34 [4];
  char local_30 [4];
  char local_2c [36];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  for (local_34 = (undefined1  [4])0x0; (int)local_34 < DAT_0091a450;
      local_34 = (undefined1  [4])((int)local_34 + 1)) {
    if (*(int *)(&DAT_00918440 + (int)local_34 * 0x34) == param_1[1]) goto LAB_0061ea7a;
  }
  local_34 = (undefined1  [4])DAT_0091a450;
  DAT_0091a450 = DAT_0091a450 + 1;
  if (DAT_0091a450 < 0x15) {
    pcVar3 = strstr((char *)*param_1,"_delta");
    if (pcVar3 == (char *)0x0) {
      *(undefined **)(&DAT_00918444 + (int)local_34 * 0x34) = &DAT_00918458 + (int)local_34 * 0x34;
    }
    else {
      *(undefined **)(&DAT_00918444 + (int)local_34 * 0x34) = &DAT_0091845c + (int)local_34 * 0x34;
    }
    *(undefined4 *)(&DAT_00918440 + (int)local_34 * 0x34) = param_1[1];
    *(undefined4 *)(&DAT_00918448 + (int)local_34 * 0x34) = param_1[5] - param_1[4];
    *(undefined4 *)(&DAT_0091844c + (int)local_34 * 0x34) = param_1[4] << 0x10;
    (&DAT_00918454)[(int)local_34 * 0x34] = *(undefined1 *)(param_1 + 7);
    *(undefined4 *)(&DAT_00918450 + (int)local_34 * 0x34) = param_1[3] << 0x10;
    *(int *)(&DAT_00918450 + (int)local_34 * 0x34) =
         *(int *)(&DAT_00918450 + (int)local_34 * 0x34) -
         *(int *)(&DAT_0091844c + (int)local_34 * 0x34);
    *(int *)(&DAT_00918450 + (int)local_34 * 0x34) =
         *(int *)(&DAT_00918450 + (int)local_34 * 0x34) << 1;
    *(int *)(&DAT_00918450 + (int)local_34 * 0x34) =
         *(int *)(&DAT_00918450 + (int)local_34 * 0x34) /
         *(int *)(&DAT_00918448 + (int)local_34 * 0x34);
    *(int *)(&DAT_00918450 + (int)local_34 * 0x34) =
         *(int *)(&DAT_00918450 + (int)local_34 * 0x34) + -0x10000;
    *(undefined4 *)(&DAT_00918460 + (int)local_34 * 0x34) = param_1[6];
    *(undefined4 *)(&DAT_0091845c + (int)local_34 * 0x34) =
         *(undefined4 *)(&DAT_00918450 + (int)local_34 * 0x34);
    local_70 = (char *)*param_1;
    local_64 = local_30;
    do {
      cVar1 = *local_70;
      *local_64 = cVar1;
      local_70 = local_70 + 1;
      local_64 = local_64 + 1;
    } while (cVar1 != '\0');
    pcVar3 = strstr(local_30,"_delta");
    if (pcVar3 != (char *)0x0) {
      *pcVar3 = '\0';
    }
    pcVar3 = local_34 + 3;
    do {
      local_50 = pcVar3;
      pcVar3 = local_50 + 1;
    } while (local_50[1] != '\0');
    builtin_strncpy(local_50 + 1,"_plus",6);
    iVar4 = FUN_0061e420(local_30);
    if (iVar4 == 0) {
      *(undefined4 *)(&DAT_00918464 + (int)local_34 * 0x34) = 0;
    }
    else {
      *(undefined4 *)(&DAT_00918464 + (int)local_34 * 0x34) = *(undefined4 *)(iVar4 + 4);
    }
    local_68 = (char *)*param_1;
    local_48 = local_30;
    do {
      cVar1 = *local_68;
      *local_48 = cVar1;
      local_68 = local_68 + 1;
      local_48 = local_48 + 1;
    } while (cVar1 != '\0');
    pcVar3 = strstr(local_30,"_delta");
    if (pcVar3 != (char *)0x0) {
      *pcVar3 = '\0';
    }
    pcVar3 = local_34 + 3;
    do {
      local_60 = pcVar3;
      pcVar3 = local_60 + 1;
    } while (local_60[1] != '\0');
    builtin_strncpy(local_60 + 1,"_minus",7);
    iVar4 = FUN_0061e420(local_30);
    if (iVar4 == 0) {
      *(undefined4 *)(&DAT_00918468 + (int)local_34 * 0x34) = 0;
    }
    else {
      *(undefined4 *)(&DAT_00918468 + (int)local_34 * 0x34) = *(undefined4 *)(iVar4 + 4);
    }
    local_74 = (char *)*param_1;
    local_58 = local_30;
    do {
      cVar1 = *local_74;
      *local_58 = cVar1;
      local_74 = local_74 + 1;
      local_58 = local_58 + 1;
    } while (cVar1 != '\0');
    puVar2 = (undefined4 *)(local_34 + 3);
    do {
      local_4c = puVar2;
      puVar2 = (undefined4 *)((int)local_4c + 1);
    } while (*(char *)((int)local_4c + 1) != '\0');
    *(undefined4 *)((int)local_4c + 1) = 0x7465735f;
    *(undefined1 *)((int)local_4c + 5) = 0;
    iVar4 = FUN_0061e420(local_30);
    if (iVar4 == 0) {
      *(undefined4 *)(&DAT_00918470 + (int)local_34 * 0x34) = 0;
    }
    else {
      *(undefined4 *)(&DAT_00918470 + (int)local_34 * 0x34) = *(undefined4 *)(iVar4 + 4);
    }
    local_6c = (char *)*param_1;
    local_54 = local_30;
    do {
      cVar1 = *local_6c;
      *local_54 = cVar1;
      local_6c = local_6c + 1;
      local_54 = local_54 + 1;
    } while (cVar1 != '\0');
    pcVar3 = local_34 + 3;
    do {
      local_5c = pcVar3;
      pcVar3 = local_5c + 1;
    } while (local_5c[1] != '\0');
    builtin_strncpy(local_5c + 1,"_reset",7);
    iVar4 = FUN_0061e420(local_30);
    if (iVar4 == 0) {
      *(undefined4 *)(&DAT_0091846c + (int)local_34 * 0x34) = 0;
    }
    else {
      *(undefined4 *)(&DAT_0091846c + (int)local_34 * 0x34) = *(undefined4 *)(iVar4 + 4);
    }
  }
  else {
    DAT_0091a450 = 0x14;
    FUN_007d6830("Too many analog sinks: line %d",DAT_0091fef8);
  }
LAB_0061ea7a:
  FUN_0083e885();
  return;
}

