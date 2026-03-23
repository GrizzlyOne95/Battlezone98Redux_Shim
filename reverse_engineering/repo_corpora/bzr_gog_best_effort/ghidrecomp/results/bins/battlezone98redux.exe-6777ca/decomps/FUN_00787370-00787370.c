
/* WARNING: Removing unreachable block (ram,0x007873be) */
/* WARNING: Removing unreachable block (ram,0x007875d4) */

undefined1 * FUN_00787370(char *param_1)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  undefined1 *puVar5;
  char *local_c;
  char *local_8;
  
  if (((DAT_009454d4 == (undefined1 *)0x0) || (DAT_009454d0 == (char *)0x0)) ||
     (iVar2 = _stricmp(param_1,&DAT_02c419e8), puVar5 = DAT_009454d4, iVar2 != 0)) {
    DAT_02c419e8 = 0;
    DAT_009454d0 = (char *)0x0;
    DAT_009454d4 = (undefined1 *)0x0;
    pcVar3 = (char *)FUN_00829130(param_1,&DAT_009454d0);
    if (pcVar3 == (char *)0x0) {
      puVar5 = (undefined1 *)0x0;
    }
    else {
      pcVar4 = pcVar3 + (int)DAT_009454d0;
      local_c = &DAT_02c319e8;
      local_8 = pcVar3;
      while ((local_8 < pcVar4 && (local_c < &DAT_02c419e7))) {
        if ((*local_8 == ';') || ((*local_8 == '/' && (local_8[1] == '/')))) {
          for (; (*local_8 != '\n' && (local_8 < pcVar4)); local_8 = local_8 + 1) {
          }
        }
        else if ((*local_8 == '/') && (local_8[1] == '*')) {
          for (local_8 = local_8 + 4;
              ((local_8 < pcVar4 && (local_8[-2] != '*')) && (local_8[-1] != '/'));
              local_8 = local_8 + 1) {
          }
        }
        else {
          pcVar1 = local_8;
          if (*local_8 == '\"') {
            while ((local_8 = pcVar1 + 1, *local_8 != '\"' && (local_8 < pcVar4))) {
              *local_c = *local_8;
              local_c = local_c + 1;
              pcVar1 = local_8;
            }
            local_8 = pcVar1 + 2;
          }
          else if ((*local_8 < '!') && (*local_8 != '\n')) {
            local_8 = local_8 + 1;
          }
          else {
            iVar2 = toupper((int)*local_8);
            *local_c = (char)iVar2;
            local_c = local_c + 1;
            local_8 = local_8 + 1;
          }
        }
      }
      *local_c = '\0';
      DAT_02c419e7 = 0;
      DAT_009454d4 = &DAT_02c319e8;
      DAT_009454d0 = local_c + -0x2c319e8;
      strncpy(&DAT_02c419e8,param_1,0x100);
      FUN_0062f240(pcVar3);
      if (((int)DAT_009454d0 < 1) || (puVar5 = DAT_009454d4, DAT_009454d4 == (undefined1 *)0x0)) {
        DAT_009454d0 = (char *)0x0;
        DAT_009454d4 = (undefined1 *)0x0;
        puVar5 = (undefined1 *)0x0;
      }
    }
  }
  return puVar5;
}

