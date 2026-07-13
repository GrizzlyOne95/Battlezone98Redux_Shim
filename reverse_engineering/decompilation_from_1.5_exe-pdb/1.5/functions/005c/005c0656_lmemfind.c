/*
 * Entry: 005c0656
 * Name: lmemfind
 * Namespace: Global
 * Signature: char * lmemfind(char * param_1, uint param_2, char * param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lmemfind(char *param_1,uint param_2,char *param_3,uint param_4)

{
  char *_MaxCount;
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *unaff_EBX;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  
  if (param_3 == (char *)0x0) {
    return param_1;
  }
  if (param_2 < param_3) {
    return (char *)0x0;
  }
  _MaxCount = (char *)(param_2 - (int)(param_3 + -1));
  do {
    if ((_MaxCount == (char *)0x0) ||
       (pcVar1 = memchr(param_1,(int)*unaff_EBX,(size_t)_MaxCount), pcVar1 == (char *)0x0)) {
      return (char *)0x0;
    }
    pcVar2 = pcVar1 + 1;
    bVar6 = true;
    pcVar3 = param_3 + -1;
    pcVar4 = pcVar2;
    pcVar5 = unaff_EBX;
    do {
      pcVar5 = pcVar5 + 1;
      if (pcVar3 == (char *)0x0) break;
      pcVar3 = pcVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
    } while (bVar6);
    if (bVar6) {
      return pcVar1;
    }
    _MaxCount = param_1 + ((int)_MaxCount - (int)pcVar2);
    param_1 = pcVar2;
  } while( true );
}
