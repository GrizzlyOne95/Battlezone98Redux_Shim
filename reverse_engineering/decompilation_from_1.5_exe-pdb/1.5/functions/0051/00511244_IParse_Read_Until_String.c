/*
 * Entry: 00511244
 * Name: IParse_Read_Until_String
 * Namespace: Global
 * Signature: int IParse_Read_Until_String(char * param_1, int * param_2, int param_3, char * param_4, char * * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Read_Until_String(char *param_1,int *param_2,int param_3,char *param_4,char **param_5)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  size_t _NewSize;
  char *local_10;
  
  bVar3 = false;
  bVar4 = false;
  _NewSize = 1;
  local_10 = param_4 + 1;
  do {
    cVar1 = param_1[*param_2];
    iVar5 = *param_2 + 1;
    *param_2 = iVar5;
    if (param_3 < iVar5) goto LAB_005112ef;
    (*param_5)[_NewSize - 1] = cVar1;
    _NewSize = _NewSize + 1;
    pcVar6 = realloc(*param_5,_NewSize);
    *param_5 = pcVar6;
    if (bVar3) {
      if (*local_10 == cVar1) {
        local_10 = local_10 + 1;
        if (*local_10 == '\0') {
          bVar4 = true;
          pcVar7 = param_4;
          do {
            cVar2 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar2 != '\0');
          _NewSize = _NewSize + (-1 - ((int)pcVar7 - (int)(param_4 + 1)));
        }
      }
      else {
        bVar3 = false;
      }
    }
    if ((cVar1 == *param_4) && (bVar3 = true, param_4[1] == '\0')) {
      bVar4 = true;
      _NewSize = _NewSize - 2;
    }
  } while (!bVar4);
  if (cVar1 == -1) {
LAB_005112ef:
    iVar5 = -1;
  }
  else {
    pcVar6[_NewSize] = '\0';
    iVar5 = 0;
  }
  return iVar5;
}
