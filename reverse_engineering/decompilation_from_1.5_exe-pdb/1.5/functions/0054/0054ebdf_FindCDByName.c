/*
 * Entry: 0054ebdf
 * Name: FindCDByName
 * Namespace: Global
 * Signature: int FindCDByName(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FindCDByName(char *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *_Str1;
  int iVar3;
  char *pcVar4;
  char cVar5;
  uint uVar6;
  
  iVar2 = param_2;
  uVar6 = 0;
  CDIndex = 0;
  if (param_2 != 0) {
    WhichCD = '\0';
  }
  param_2 = 0;
  do {
    if (uVar6 != 0) {
      return uVar6;
    }
    if (IsCD[param_2] != '\0') {
      CDIndex = CDIndex + 1;
      cVar5 = (char)param_2 + 'A';
      _Str1 = GetVolumeName(cVar5);
      if (_Str1 != (char *)0x0) {
        pcVar4 = param_1;
        do {
          cVar1 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        iVar3 = _strnicmp(_Str1,param_1,(int)pcVar4 - (int)(param_1 + 1));
        if (iVar3 == 0) {
          if (iVar2 != 0) {
            WhichCD = cVar5;
          }
          uVar6 = 1;
        }
      }
    }
    param_2 = param_2 + 1;
  } while (param_2 < 0x1a);
  if ((uVar6 == 0) && (iVar2 != 0)) {
    uVar6 = (uint)(WhichCD != '\0');
  }
  return uVar6;
}
