/*
 * Entry: 00526dfb
 * Name: Star
 * Namespace: Global
 * Signature: int Star(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Star(char *param_1,char *param_2)

{
  char *in_EAX;
  int iVar1;
  
  do {
    iVar1 = DoMatch(in_EAX,param_1);
    if (iVar1 != 0) {
      return 1;
    }
    in_EAX = in_EAX + 1;
  } while (*in_EAX != '\0');
  return -1;
}
