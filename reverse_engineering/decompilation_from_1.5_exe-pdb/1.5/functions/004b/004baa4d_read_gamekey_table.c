/*
 * Entry: 004baa4d
 * Name: read_gamekey_table
 * Namespace: Global
 * Signature: int read_gamekey_table(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_gamekey_table(void)

{
  char cVar1;
  FILE *_File;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  char *pcVar5;
  int local_15c;
  char local_158 [120];
  undefined1 local_e0 [136];
  char local_58 [40];
  char local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_e0;
  inmap_lineno = 0;
  gamekey_map[0x1b] = '\v';
  inmap_filename = "gamekey.map";
  _File = fopen("gamekey.map","r");
  if (_File == (FILE *)0x0) {
    DEBUG_systemWarning("gamekey.map error: can\'t open file.");
    iVar2 = 0;
  }
  else {
    iVar2 = getNonBlankLine(local_158,0xff,(_iobuf *)_File);
    while (iVar2 != 0) {
      iVar2 = sscanf(local_158,"%s %s",local_30,local_58);
      if (iVar2 == 2) {
        pcVar5 = strtok(local_58,"+");
        if (pcVar5 == (char *)0x0) {
          pcVar5 = "gamekey.map error: line %d, bad sequence.";
          goto LAB_004baaf9;
        }
        local_15c = 0;
        do {
          uVar4 = 0;
          do {
            iVar2 = _stricmp(key_name[uVar4].name,pcVar5);
            if (iVar2 == 0) {
              iVar2 = (int)key_name[uVar4].code;
              if (iVar2 != 0) goto LAB_004bab88;
              break;
            }
            uVar4 = uVar4 + 1;
          } while (uVar4 < 0x59);
          pcVar3 = pcVar5;
          do {
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          if ((uint)((int)pcVar3 - (int)(pcVar5 + 1)) < 2) {
            iVar2 = tolower((int)*pcVar5);
LAB_004bab88:
            local_15c = local_15c + iVar2;
          }
          else {
            DEBUG_systemWarning("gamekey.map error: line %d, not a valid key name.");
          }
          pcVar5 = strtok((char *)0x0,"+");
        } while (pcVar5 != (char *)0x0);
        uVar4 = 0;
        do {
          iVar2 = _stricmp(gamekey_name[uVar4].name,local_30);
          if (iVar2 == 0) break;
          uVar4 = uVar4 + 1;
        } while (uVar4 < 0x2a);
        if (uVar4 < 0x2a) {
          if ((gamekey_map[(short)local_15c] != '\0') &&
             (gamekey_map[(short)local_15c] != gamekey_name[uVar4].code)) {
            pcVar5 = "gamekey.map error: line %d, multiple defines \"%s\".";
            goto LAB_004babfd;
          }
          if ((short)local_15c < 0x1001) {
            gamekey_map[(short)local_15c] = gamekey_name[uVar4].code;
          }
        }
        else {
          pcVar5 = "gamekey.map error: line %d, no gamekey %s.";
LAB_004babfd:
          DEBUG_systemWarning(pcVar5);
        }
      }
      else {
        pcVar5 = "gamekey.map error: line %d, read error.";
LAB_004baaf9:
        DEBUG_systemWarning(pcVar5);
      }
      iVar2 = getNonBlankLine(local_158,0xff,(_iobuf *)_File);
    }
    fclose(_File);
    iVar2 = 1;
  }
  return iVar2;
}
