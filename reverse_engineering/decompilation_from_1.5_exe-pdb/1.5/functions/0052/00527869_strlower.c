/*
 * Entry: 00527869
 * Name: strlower
 * Namespace: Global
 * Signature: char * strlower(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl strlower(char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  cVar1 = *param_1;
  pcVar3 = param_1;
  while (cVar1 != '\0') {
    iVar2 = tolower((int)*pcVar3);
    *pcVar3 = (char)iVar2;
    pcVar3 = pcVar3 + 1;
    cVar1 = *pcVar3;
  }
  return param_1;
}
