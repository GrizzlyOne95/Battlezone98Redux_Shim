
undefined4 * FUN_00588e00(char *param_1)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 *local_3c;
  char *local_38;
  char *local_34;
  size_t local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  char *local_20;
  char *local_1c;
  char *local_18;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bceb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0058a160(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *local_24 = 1;
  strncpy((char *)(local_24 + 1),param_1,0xe);
  local_30 = FUN_00481a60(local_24 + 1);
  local_38 = (char *)FUN_00481af0(local_24 + 1);
  local_1c = local_38 + local_30;
  local_34 = malloc(local_30);
  local_24[5] = local_34;
  local_18 = local_38;
  local_3c = local_24 + 6;
  local_44 = 0;
  local_20 = local_34;
  local_40 = FUN_0058a1a0(&local_44);
  while (local_18 < local_1c) {
    while (((local_18 < local_1c && (*local_18 < '!')) &&
           (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
      local_18 = local_18 + 1;
    }
    if (((local_18 < local_1c) && (*local_18 == ';')) ||
       ((*local_18 == '/' && (local_18[1] == '/')))) {
      while ((local_18 < local_1c && (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
        local_18 = local_18 + 1;
      }
    }
    else if (((local_18 < local_1c) && (*local_18 == '/')) && (local_18[1] == '*')) {
      for (local_18 = local_18 + 4;
          ((local_18 < local_1c && (local_18[-2] != '*')) && (local_18[-1] != '/'));
          local_18 = local_18 + 1) {
      }
    }
    else if ((local_1c <= local_18) || (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0')) {
      if ((local_18 < local_1c) && (*local_18 == '[')) {
        local_28 = 0x811c9dc5;
        while (((local_18 = local_18 + 1, local_18 < local_1c && (*local_18 != ']')) &&
               (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
          uVar3 = tolower((int)*local_18);
          local_11 = (undefined1)uVar3;
          local_28 = FUN_00446440(uVar3 & 0xff,local_28);
        }
        local_40 = FUN_0058a220(&local_28);
        while ((local_18 < local_1c && (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
          local_18 = local_18 + 1;
        }
      }
      else {
        local_2c = 0x811c9dc5;
        while (((local_18 < local_1c && (' ' < *local_18)) &&
               ((*local_18 != '=' && (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))))) {
          uVar3 = tolower((int)*local_18);
          local_12 = (undefined1)uVar3;
          local_2c = FUN_00446440(uVar3 & 0xff,local_2c);
          local_18 = local_18 + 1;
        }
        while (((local_18 < local_1c && (*local_18 != '=')) &&
               (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
          local_18 = local_18 + 1;
        }
        if (((local_18 < local_1c) && (*local_18 == '=')) &&
           (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0')) {
          local_18 = local_18 + 1;
        }
        while (((local_18 < local_1c && (*local_18 < '!')) &&
               (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
          local_18 = local_18 + 1;
        }
        iVar4 = _strnicmp(local_18,"NULL",4);
        pcVar1 = local_20;
        if (iVar4 != 0) {
          if ((*local_18 == '\"') || (*local_18 == -0x6d)) {
            while ((local_18 = local_18 + 1, local_18 < local_1c &&
                   (((*local_18 != '\"' && (*local_18 != -0x6c)) &&
                    (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))))) {
              *local_20 = *local_18;
              local_20 = local_20 + 1;
            }
          }
          else if ((*local_18 == '\'') || (*local_18 == -0x6f)) {
            while (((local_18 = local_18 + 1, local_18 < local_1c &&
                    ((*local_18 != '\'' && (*local_18 != -0x6e)))) &&
                   (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
              *local_20 = *local_18;
              local_20 = local_20 + 1;
            }
          }
          else {
            while (((local_18 < local_1c && (' ' < *local_18)) &&
                   (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
              *local_20 = *local_18;
              local_20 = local_20 + 1;
              local_18 = local_18 + 1;
            }
          }
          *local_20 = '\0';
          local_20 = local_20 + 1;
          puVar5 = (undefined4 *)FUN_0058a0c0(&local_2c);
          *puVar5 = pcVar1;
        }
        while ((local_18 < local_1c && (cVar2 = FUN_00588dd0((int)*local_18), cVar2 == '\0'))) {
          local_18 = local_18 + 1;
        }
      }
    }
    if (*local_18 == '\r') {
      local_18 = local_18 + 1;
    }
    if (*local_18 == '\n') {
      local_18 = local_18 + 1;
    }
  }
  FUN_00481990(local_24 + 1);
  ExceptionList = local_10;
  return local_24;
}

