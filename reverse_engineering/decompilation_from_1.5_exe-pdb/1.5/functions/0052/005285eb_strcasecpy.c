/*
 * Entry: 005285eb
 * Name: strcasecpy
 * Namespace: Global
 * Signature: char * strcasecpy(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl strcasecpy(char *param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  for (; *param_2 != '\0'; param_2 = param_2 + 1) {
    iVar1 = tolower((int)*param_2);
    *pcVar2 = (char)iVar1;
    pcVar2 = pcVar2 + 1;
  }
  *pcVar2 = '\0';
  return param_1;
}
