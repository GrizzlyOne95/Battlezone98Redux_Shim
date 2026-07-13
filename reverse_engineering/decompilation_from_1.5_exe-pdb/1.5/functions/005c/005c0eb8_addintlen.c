/*
 * Entry: 005c0eb8
 * Name: addintlen
 * Namespace: Global
 * Signature: void addintlen(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl addintlen(char *param_1)

{
  char *pcVar1;
  char *in_ECX;
  
  do {
    pcVar1 = in_ECX;
    in_ECX = pcVar1 + 1;
  } while (*pcVar1 != '\0');
  pcVar1[-0xffffffff00000001] = 'l';
  pcVar1[0] = '\0';
  *pcVar1 = pcVar1[-1];
  pcVar1[1] = '\0';
  return;
}
