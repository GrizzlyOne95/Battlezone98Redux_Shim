/*
 * Entry: 00556381
 * Name: PlayerNameList::Load
 * Namespace: PlayerNameList
 * Signature: void Load(PlayerNameList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PlayerNameList::Load(PlayerNameList *this,char *param_1)

{
  char cVar1;
  FILE *_File;
  char *pcVar2;
  char local_2a8 [256];
  char local_1a8 [104];
  char local_140 [104];
  char local_d8 [96];
  undefined1 local_78 [8];
  char local_70 [104];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_78;
  if (param_1 != (char *)0x0) {
    memset(local_70,0,0x65);
    memset(local_1a8,0,0x65);
    memset(local_140,0,0x65);
    memset(local_2a8,0,0x100);
    memset(local_d8,0,0x65);
    _File = fopen(param_1,"r");
    if (_File != (FILE *)0x0) {
      Init(this);
      while ((((pcVar2 = fgets(local_70,100,_File), pcVar2 != (char *)0x0 &&
               (pcVar2 = fgets(local_1a8,100,_File), pcVar2 != (char *)0x0)) &&
              (pcVar2 = fgets(local_140,100,_File), pcVar2 != (char *)0x0)) &&
             ((pcVar2 = fgets(local_d8,100,_File), pcVar2 != (char *)0x0 &&
              (pcVar2 = fgets(local_2a8,0xff,_File), pcVar2 != (char *)0x0))))) {
        pcVar2 = local_70;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        if (pcVar2[(int)(local_78 + (7 - (int)(local_70 + 1)))] == '\n') {
          pcVar2 = local_70;
          do {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
          } while (cVar1 != '\0');
          pcVar2[(int)(local_78 + (7 - (int)(local_70 + 1)))] = '\0';
        }
        pcVar2 = local_1a8;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        if (pcVar2[(int)(local_2a8 + (0xff - (int)(local_1a8 + 1)))] == '\n') {
          pcVar2 = local_1a8;
          do {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
          } while (cVar1 != '\0');
          pcVar2[(int)(local_2a8 + (0xff - (int)(local_1a8 + 1)))] = '\0';
        }
        pcVar2 = local_140;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        if (pcVar2[(int)(local_1a8 + (0x67 - (int)(local_140 + 1)))] == '\n') {
          pcVar2 = local_140;
          do {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
          } while (cVar1 != '\0');
          pcVar2[(int)(local_1a8 + (0x67 - (int)(local_140 + 1)))] = '\0';
        }
        pcVar2 = local_d8;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        if (pcVar2[(int)(local_140 + (0x67 - (int)(local_d8 + 1)))] == '\n') {
          pcVar2 = local_d8;
          do {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
          } while (cVar1 != '\0');
          pcVar2[(int)(local_140 + (0x67 - (int)(local_d8 + 1)))] = '\0';
        }
        pcVar2 = local_2a8;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        if (pcVar2[(int)(local_2a8 + (-1 - (int)(local_2a8 + 1)))] == '\n') {
          pcVar2 = local_2a8;
          do {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
          } while (cVar1 != '\0');
          pcVar2[(int)(local_2a8 + (-1 - (int)(local_2a8 + 1)))] = '\0';
        }
        pcVar2 = local_2a8;
        cVar1 = local_2a8[0];
        while (cVar1 != '\0') {
          if (*pcVar2 == '_') {
            *pcVar2 = '\n';
          }
          pcVar2 = pcVar2 + 1;
          cVar1 = *pcVar2;
        }
        Add(this,local_70,local_1a8,local_140,local_2a8,local_d8);
      }
      fclose(_File);
      SelectionChanged(this);
    }
  }
  return;
}
