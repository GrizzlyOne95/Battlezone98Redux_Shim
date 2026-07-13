/*
 * Entry: 00419199
 * Name: PackInt
 * Namespace: Global
 * Signature: bool PackInt(char * * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackInt(char **param_1,char *param_2,int param_3)

{
  char *pcVar1;
  int *in_EAX;
  
  if (param_1 <= (char **)(*in_EAX + 4U)) {
    return false;
  }
  pcVar1 = (char *)(*in_EAX + -1);
  *pcVar1 = *pcVar1 + '\x04';
  *(char **)*in_EAX = param_2;
  *in_EAX = *in_EAX + 4;
  return true;
}
