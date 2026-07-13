/*
 * Entry: 0055237c
 * Name: DupString
 * Namespace: Global
 * Signature: char * DupString(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl DupString(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = malloc((size_t)(pcVar2 + (1 - (int)(param_1 + 1))));
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
