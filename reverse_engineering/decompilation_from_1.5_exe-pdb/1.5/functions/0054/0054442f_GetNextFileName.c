/*
 * Entry: 0054442f
 * Name: GetNextFileName
 * Namespace: Global
 * Signature: char * GetNextFileName(char * param_1, char * param_2, char * param_3, int param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl GetNextFileName(char *param_1,char *param_2,char *param_3,int param_4,char *param_5)

{
  char cVar1;
  char *in_EAX;
  char *pcVar2;
  uint uVar3;
  char *in_ECX;
  uint uVar4;
  char *pcVar5;
  
  pcVar5 = in_ECX;
  if (in_EAX < param_1) {
    do {
      if ('\x1f' < *in_EAX) break;
      in_EAX = in_EAX + 1;
    } while (in_EAX < param_1);
    if (in_EAX < param_1) {
      do {
        if ((*in_EAX != ';') && ((*in_EAX != '/' || (in_EAX[1] != '/')))) break;
        if (param_1 <= in_EAX) goto LAB_005444a8;
        do {
          if (*in_EAX < '!') break;
          in_EAX = in_EAX + 1;
        } while (in_EAX < param_1);
        if (param_1 <= in_EAX) goto LAB_005444a8;
        do {
          if ('\x1f' < *in_EAX) break;
          in_EAX = in_EAX + 1;
        } while (in_EAX < param_1);
      } while (in_EAX < param_1);
      if (in_EAX < param_1) {
        do {
          if ((*in_EAX < '!') || ((int)param_2 < 1)) break;
          *pcVar5 = *in_EAX;
          pcVar5 = pcVar5 + 1;
          in_EAX = in_EAX + 1;
          param_2 = param_2 + -1;
        } while (in_EAX < param_1);
        for (; (in_EAX < param_1 && (' ' < *in_EAX)); in_EAX = in_EAX + 1) {
        }
      }
    }
  }
LAB_005444a8:
  *pcVar5 = '\0';
  if (in_ECX != pcVar5) {
    pcVar2 = strrchr(in_ECX,0x2e);
    pcVar5 = param_3;
    if (pcVar2 != (char *)0x0) {
      *pcVar2 = '\0';
    }
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    uVar3 = (int)pcVar5 - (int)param_3;
    pcVar5 = in_ECX + -1;
    do {
      pcVar2 = pcVar5 + 1;
      pcVar5 = pcVar5 + 1;
    } while (*pcVar2 != '\0');
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)param_3;
      param_3 = param_3 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar5 = *param_3;
      param_3 = param_3 + 1;
      pcVar5 = pcVar5 + 1;
    }
    _strlwr(in_ECX);
  }
  return (char *)(-(uint)(in_EAX < param_1) & (uint)in_EAX);
}
