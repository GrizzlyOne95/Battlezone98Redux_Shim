/*
 * Entry: 0050e9df
 * Name: Debug_Strdup
 * Namespace: Global
 * Signature: char * Debug_Strdup(char * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl Debug_Strdup(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = Debug_Malloc((uint)(pcVar2 + (1 - (int)(param_1 + 1))),param_2,param_3);
  if (pcVar2 != (char *)0x0) {
    iVar3 = (int)pcVar2 - (int)param_1;
    do {
      cVar1 = *param_1;
      param_1[iVar3] = cVar1;
      param_1 = param_1 + 1;
    } while (cVar1 != '\0');
  }
  return pcVar2;
}
