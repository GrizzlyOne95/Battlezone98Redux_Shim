
undefined4 FUN_0069a480(undefined4 param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  byte bVar1;
  char cVar2;
  void *pvVar3;
  bool bVar4;
  uint local_3c;
  uint local_38;
  uint local_34;
  byte *local_30;
  byte *local_2c;
  byte *local_28;
  byte *local_24;
  byte *local_20;
  byte *local_1c;
  char *local_18;
  char *local_14;
  int local_10;
  
  local_20 = &DAT_00871540;
  local_1c = (byte *)(param_5 + 0x50);
  do {
    bVar1 = *local_1c;
    bVar4 = bVar1 < *local_20;
    if (bVar1 != *local_20) {
LAB_0069a4df:
      local_34 = -(uint)bVar4 | 1;
      goto LAB_0069a4e7;
    }
    if (bVar1 == 0) break;
    bVar1 = local_1c[1];
    bVar4 = bVar1 < local_20[1];
    if (bVar1 != local_20[1]) goto LAB_0069a4df;
    local_1c = local_1c + 2;
    local_20 = local_20 + 2;
  } while (bVar1 != 0);
  local_34 = 0;
LAB_0069a4e7:
  if (local_34 == 0) {
    local_10 = FUN_006994c0(4,param_5);
    *(int *)(local_10 + 0xc) = (int)*(char *)(param_5 + 0xf0);
  }
  else if (param_2 == 1) {
    local_10 = FUN_006994c0(4,param_5);
  }
  else {
    local_28 = (byte *)&DAT_00871534;
    local_24 = (byte *)(param_5 + 0x50);
    do {
      bVar1 = *local_24;
      bVar4 = bVar1 < *local_28;
      if (bVar1 != *local_28) {
LAB_0069a5a4:
        local_38 = -(uint)bVar4 | 1;
        goto LAB_0069a5ac;
      }
      if (bVar1 == 0) break;
      bVar1 = local_24[1];
      bVar4 = bVar1 < local_28[1];
      if (bVar1 != local_28[1]) goto LAB_0069a5a4;
      local_24 = local_24 + 2;
      local_28 = local_28 + 2;
    } while (bVar1 != 0);
    local_38 = 0;
LAB_0069a5ac:
    if ((local_38 == 0) && (param_2 == 4)) {
      local_10 = FUN_006994c0(10,param_5);
      pvVar3 = malloc(*(size_t *)(param_3 + 8));
      *(void **)(local_10 + 8) = pvVar3;
      *(undefined4 *)(local_10 + 0xc) = *(undefined4 *)(param_3 + 8);
    }
    else {
      local_30 = (byte *)&DAT_00871534;
      local_2c = (byte *)(param_5 + 0x50);
      do {
        bVar1 = *local_2c;
        bVar4 = bVar1 < *local_30;
        if (bVar1 != *local_30) {
LAB_0069a65e:
          local_3c = -(uint)bVar4 | 1;
          goto LAB_0069a666;
        }
        if (bVar1 == 0) break;
        bVar1 = local_2c[1];
        bVar4 = bVar1 < local_30[1];
        if (bVar1 != local_30[1]) goto LAB_0069a65e;
        local_2c = local_2c + 2;
        local_30 = local_30 + 2;
      } while (bVar1 != 0);
      local_3c = 0;
LAB_0069a666:
      if ((local_3c != 0) || (param_2 != 6)) {
        return 0xffffffff;
      }
      local_10 = FUN_006994c0(10,param_5);
      pvVar3 = malloc(*(size_t *)(param_3 + 8));
      *(void **)(local_10 + 8) = pvVar3;
      *(undefined4 *)(local_10 + 0xc) = *(undefined4 *)(param_3 + 8);
      local_14 = (char *)(param_5 + 400);
      do {
        cVar2 = *local_14;
        local_14 = local_14 + 1;
      } while (cVar2 != '\0');
      strncpy(*(char **)(local_10 + 8),(char *)(param_5 + 0x191),
              (size_t)(local_14 + (-2 - (param_5 + 0x191))));
      local_18 = (char *)(param_5 + 400);
      do {
        cVar2 = *local_18;
        local_18 = local_18 + 1;
      } while (cVar2 != '\0');
      local_18[(*(int *)(local_10 + 8) + -2) - (param_5 + 0x191)] = '\0';
    }
  }
  FUN_00699650(param_1,local_10);
  return 0;
}

