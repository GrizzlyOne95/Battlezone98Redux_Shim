
undefined1 * FUN_00824ad0(undefined4 param_1,undefined4 param_2,char *param_3)

{
  byte bVar1;
  char cVar2;
  undefined1 *puVar3;
  bool bVar4;
  uint local_24;
  char *local_20;
  char *local_1c;
  byte *local_18;
  byte *local_14;
  byte *local_10;
  uint local_c;
  
  local_c = 0;
  for (local_10 = (byte *)&param_1; (local_c < 8 && ((*local_10 & 0x7f) != 0));
      local_10 = local_10 + 1) {
    (&DAT_02cc1b48)[local_c] = *local_10 & 0x7f;
    local_c = local_c + 1;
  }
  if (local_c == 0) {
    puVar3 = (undefined1 *)0x0;
  }
  else {
    local_1c = &DAT_02cc1b48 + local_c;
    *local_1c = '\0';
    local_18 = &DAT_008767b4;
    local_14 = &DAT_02cc1b48;
    do {
      bVar1 = *local_14;
      bVar4 = bVar1 < *local_18;
      if (bVar1 != *local_18) {
LAB_00824b8b:
        local_24 = -(uint)bVar4 | 1;
        goto LAB_00824b93;
      }
      if (bVar1 == 0) break;
      bVar1 = local_14[1];
      bVar4 = bVar1 < local_18[1];
      if (bVar1 != local_18[1]) goto LAB_00824b8b;
      local_14 = local_14 + 2;
      local_18 = local_18 + 2;
    } while (bVar1 != 0);
    local_24 = 0;
LAB_00824b93:
    if (local_24 == 0) {
      puVar3 = (undefined1 *)0x0;
    }
    else {
      local_10 = (byte *)local_1c;
      if (param_3 == (char *)0x0) {
        for (; local_c < 8; local_c = local_c + 1) {
          *local_10 = '\0';
          local_10 = local_10 + 1;
        }
      }
      else {
        local_20 = param_3;
        do {
          cVar2 = *local_20;
          *local_1c = cVar2;
          local_20 = local_20 + 1;
          local_1c = local_1c + 1;
        } while (cVar2 != '\0');
      }
      puVar3 = &DAT_02cc1b48;
    }
  }
  return puVar3;
}

