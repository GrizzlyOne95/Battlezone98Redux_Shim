/*
 * Entry: 00581c8f
 * Name: sgets
 * Namespace: Global
 * Signature: int sgets(char * * param_1, char * param_2, long * param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl sgets(char **param_1,char *param_2,long *param_3,long param_4)

{
  char cVar1;
  int iVar2;
  
  if (*param_3 < 1) {
    iVar2 = 0;
  }
  else {
    cVar1 = **param_1;
    if ((cVar1 == '\n') || (cVar1 == '\r')) {
      *param_1 = *param_1 + 1;
      iVar2 = *param_3;
      *param_3 = iVar2 + -1;
      if (iVar2 < 1) {
        return 0;
      }
    }
    while ((((*param_3 != 0 && (param_4 != 0)) && (cVar1 = **param_1, cVar1 != '\n')) &&
           (cVar1 != '\r'))) {
      iVar2 = (*(code *)0x22591e)((int)cVar1);
      if (iVar2 != 0) {
        *param_2 = **param_1;
        param_2 = param_2 + 1;
        *param_1 = *param_1 + 1;
        *param_3 = *param_3 + -1;
        param_4 = param_4 + -1;
        if ((*param_3 == 0) || (param_4 == 0)) break;
      }
      *param_2 = **param_1;
      param_2 = param_2 + 1;
      *param_1 = *param_1 + 1;
      *param_3 = *param_3 + -1;
      param_4 = param_4 + -1;
    }
    *param_2 = '\0';
    while (((*param_3 != 0 && (param_4 != 0)) && (iVar2 = isspace((int)**param_1), iVar2 != 0))) {
      iVar2 = (*(code *)0x22591e)((int)**param_1);
      if (iVar2 != 0) {
        *param_1 = *param_1 + 1;
        *param_3 = *param_3 + -1;
        param_4 = param_4 + -1;
        if ((*param_3 == 0) || (param_4 == 0)) break;
      }
      *param_1 = *param_1 + 1;
      *param_3 = *param_3 + -1;
      param_4 = param_4 + -1;
    }
    iVar2 = 1;
  }
  return iVar2;
}
