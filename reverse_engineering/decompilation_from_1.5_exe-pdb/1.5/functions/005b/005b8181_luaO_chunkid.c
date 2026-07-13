/*
 * Entry: 005b8181
 * Name: luaO_chunkid
 * Namespace: Global
 * Signature: void luaO_chunkid(char * param_1, char * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaO_chunkid(char *param_1,char *param_2,uint param_3)

{
  char cVar1;
  char *pcVar2;
  size_t _Count;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  
  if (*param_2 == '=') {
    strncpy(param_1,param_2 + 1,param_3);
    param_1[param_3 - 1] = '\0';
  }
  else if (*param_2 == '@') {
    pcVar5 = param_2 + 1;
    pcVar2 = pcVar5;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    *param_1 = '\0';
    pcVar6 = pcVar5;
    if (param_3 - 8 < (uint)((int)pcVar2 - (int)(param_2 + 2))) {
      pcVar5 = pcVar5 + (((int)pcVar2 - (int)(param_2 + 2)) - (param_3 - 8));
      pcVar2 = param_1 + -1;
      do {
        pcVar6 = pcVar2 + 1;
        pcVar2 = pcVar2 + 1;
      } while (*pcVar6 != '\0');
      *(char (*) [4])pcVar2 = (char  [4])0x2e2e2e;
      pcVar6 = pcVar5;
    }
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar2 = param_1 + -1;
    do {
      pcVar7 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
    } while (*pcVar7 != '\0');
    pcVar7 = pcVar6;
    for (uVar3 = (uint)((int)pcVar5 - (int)pcVar6) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar2 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar2 = pcVar2 + 4;
    }
    for (uVar3 = (int)pcVar5 - (int)pcVar6 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar2 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar2 = pcVar2 + 1;
    }
  }
  else {
    _Count = strcspn(param_2,"\n\r");
    if (param_3 - 0x11 < _Count) {
      _Count = param_3 - 0x11;
    }
    builtin_strncpy(param_1,"[string \"",10);
    pcVar2 = param_2;
    if (param_2[_Count] == '\0') {
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      uVar3 = (int)pcVar2 - (int)param_2;
      pcVar2 = param_1 + -1;
      do {
        pcVar5 = pcVar2 + 1;
        pcVar2 = pcVar2 + 1;
      } while (*pcVar5 != '\0');
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar2 = *(undefined4 *)param_2;
        param_2 = param_2 + 4;
        pcVar2 = pcVar2 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar2 = *param_2;
        param_2 = param_2 + 1;
        pcVar2 = pcVar2 + 1;
      }
    }
    else {
      strncat(param_1,param_2,_Count);
      pcVar2 = param_1 + -1;
      do {
        pcVar5 = pcVar2 + 1;
        pcVar2 = pcVar2 + 1;
      } while (*pcVar5 != '\0');
      *(char (*) [4])pcVar2 = (char  [4])0x2e2e2e;
    }
    pcVar2 = param_1 + -1;
    do {
      pcVar5 = pcVar2;
      pcVar2 = pcVar5 + 1;
    } while (pcVar5[1] != '\0');
    pcVar2[0] = '\"';
    pcVar2[1] = ']';
    pcVar5[3] = '\0';
  }
  return;
}
