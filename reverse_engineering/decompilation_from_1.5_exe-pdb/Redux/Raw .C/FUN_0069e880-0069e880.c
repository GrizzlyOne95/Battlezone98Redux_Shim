
void FUN_0069e880(char *param_1,char *param_2,char *param_3,char *param_4,char *param_5,
                 char *param_6)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
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
  char *local_4c;
  char *local_48;
  char *local_44;
  char *local_40;
  char *local_3c;
  char *local_38;
  char *local_34;
  char *local_30;
  char *local_2c;
  char *local_28;
  char *local_24;
  char *local_20;
  
  *param_1 = '\0';
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    local_74 = param_2;
    local_60 = param_1;
    do {
      cVar1 = *local_74;
      *local_60 = cVar1;
      local_74 = local_74 + 1;
      local_60 = local_60 + 1;
    } while (cVar1 != '\0');
  }
  if ((param_3 != (char *)0x0) && (*param_3 != '\0')) {
    if (*param_1 != '\0') {
      local_20 = param_1;
      pcVar3 = local_20;
      do {
        local_20 = pcVar3;
        pcVar3 = local_20 + 1;
      } while (*local_20 != '\0');
      if (local_20[-1] != '\\') {
        local_3c = param_1;
        pcVar3 = local_3c;
        do {
          local_3c = pcVar3;
          pcVar3 = local_3c + 1;
        } while (*local_3c != '\0');
        if (local_3c[-1] != ':') {
          local_2c = param_1;
          pcVar3 = local_2c;
          do {
            local_2c = pcVar3;
            pcVar3 = local_2c + 1;
          } while (*local_2c != '\0');
          if (local_2c[-1] != '/') {
            local_68 = param_1 + -1;
            do {
              pcVar3 = local_68 + 1;
              local_68 = local_68 + 1;
            } while (*pcVar3 != '\0');
            local_68[0] = '\\';
            local_68[1] = '\0';
          }
        }
      }
    }
    local_4c = param_3;
    do {
      cVar1 = *local_4c;
      local_4c = local_4c + 1;
    } while (cVar1 != '\0');
    local_54 = param_1 + -1;
    do {
      pcVar3 = local_54 + 1;
      local_54 = local_54 + 1;
    } while (*pcVar3 != '\0');
    pcVar3 = param_3;
    for (uVar2 = (uint)((int)local_4c - (int)param_3) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)local_54 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      local_54 = local_54 + 4;
    }
    for (uVar2 = (int)local_4c - (int)param_3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *local_54 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      local_54 = local_54 + 1;
    }
  }
  if ((param_4 != (char *)0x0) && (*param_4 != '\0')) {
    if (*param_1 != '\0') {
      local_34 = param_1;
      pcVar3 = local_34;
      do {
        local_34 = pcVar3;
        pcVar3 = local_34 + 1;
      } while (*local_34 != '\0');
      if (local_34[-1] != '\\') {
        local_44 = param_1;
        pcVar3 = local_44;
        do {
          local_44 = pcVar3;
          pcVar3 = local_44 + 1;
        } while (*local_44 != '\0');
        if (local_44[-1] != ':') {
          local_24 = param_1;
          pcVar3 = local_24;
          do {
            local_24 = pcVar3;
            pcVar3 = local_24 + 1;
          } while (*local_24 != '\0');
          if (local_24[-1] != '/') {
            local_70 = param_1 + -1;
            do {
              pcVar3 = local_70 + 1;
              local_70 = local_70 + 1;
            } while (*pcVar3 != '\0');
            local_70[0] = '\\';
            local_70[1] = '\0';
          }
        }
      }
    }
    local_28 = param_4;
    do {
      cVar1 = *local_28;
      local_28 = local_28 + 1;
    } while (cVar1 != '\0');
    local_6c = param_1 + -1;
    do {
      pcVar3 = local_6c + 1;
      local_6c = local_6c + 1;
    } while (*pcVar3 != '\0');
    pcVar3 = param_4;
    for (uVar2 = (uint)((int)local_28 - (int)param_4) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)local_6c = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      local_6c = local_6c + 4;
    }
    for (uVar2 = (int)local_28 - (int)param_4 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *local_6c = *pcVar3;
      pcVar3 = pcVar3 + 1;
      local_6c = local_6c + 1;
    }
  }
  if ((param_5 != (char *)0x0) && (*param_5 != '\0')) {
    if (*param_1 != '\0') {
      local_30 = param_1;
      pcVar3 = local_30;
      do {
        local_30 = pcVar3;
        pcVar3 = local_30 + 1;
      } while (*local_30 != '\0');
      if (local_30[-1] != '\\') {
        local_38 = param_1;
        pcVar3 = local_38;
        do {
          local_38 = pcVar3;
          pcVar3 = local_38 + 1;
        } while (*local_38 != '\0');
        if (local_38[-1] != ':') {
          local_40 = param_1;
          pcVar3 = local_40;
          do {
            local_40 = pcVar3;
            pcVar3 = local_40 + 1;
          } while (*local_40 != '\0');
          if (local_40[-1] != '/') {
            local_64 = param_1 + -1;
            do {
              pcVar3 = local_64 + 1;
              local_64 = local_64 + 1;
            } while (*pcVar3 != '\0');
            local_64[0] = '\\';
            local_64[1] = '\0';
          }
        }
      }
    }
    local_48 = param_5;
    do {
      cVar1 = *local_48;
      local_48 = local_48 + 1;
    } while (cVar1 != '\0');
    local_58 = param_1 + -1;
    do {
      pcVar3 = local_58 + 1;
      local_58 = local_58 + 1;
    } while (*pcVar3 != '\0');
    pcVar3 = param_5;
    for (uVar2 = (uint)((int)local_48 - (int)param_5) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)local_58 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      local_58 = local_58 + 4;
    }
    for (uVar2 = (int)local_48 - (int)param_5 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *local_58 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      local_58 = local_58 + 1;
    }
  }
  if (param_6 != (char *)0x0) {
    local_50 = param_6;
    do {
      cVar1 = *local_50;
      local_50 = local_50 + 1;
    } while (cVar1 != '\0');
    local_5c = param_1 + -1;
    do {
      pcVar3 = local_5c + 1;
      local_5c = local_5c + 1;
    } while (*pcVar3 != '\0');
    pcVar3 = param_6;
    for (uVar2 = (uint)((int)local_50 - (int)param_6) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)local_5c = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      local_5c = local_5c + 4;
    }
    for (uVar2 = (int)local_50 - (int)param_6 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *local_5c = *pcVar3;
      pcVar3 = pcVar3 + 1;
      local_5c = local_5c + 1;
    }
  }
  return;
}

