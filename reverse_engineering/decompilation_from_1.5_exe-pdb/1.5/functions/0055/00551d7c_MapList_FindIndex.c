/*
 * Entry: 00551d7c
 * Name: MapList::FindIndex
 * Namespace: MapList
 * Signature: int FindIndex(MapList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall MapList::FindIndex(MapList *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar4 = 0;
  if (0 < (int)this->s) {
    do {
      pcVar2 = param_1;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      iVar3 = strncmp(param_1,*(char **)((int)&(this[1].hPlayerList)->unused + iVar5),
                      (int)pcVar2 - (int)(param_1 + 1));
      if (iVar3 == 0) {
        pcVar2 = param_1;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        if (pcVar2[*(int *)((int)&(this[1].hPlayerList)->unused + iVar5) - (int)(param_1 + 1)] ==
            '.') {
          return iVar4;
        }
      }
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 0x14;
    } while (iVar4 < (int)this->s);
  }
  return -1;
}
