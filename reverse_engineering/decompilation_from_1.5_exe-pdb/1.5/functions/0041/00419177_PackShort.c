/*
 * Entry: 00419177
 * Name: PackShort
 * Namespace: Global
 * Signature: bool PackShort(char * * param_1, char * param_2, short param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackShort(char **param_1,char *param_2,short param_3)

{
  char *pcVar1;
  int *in_EAX;
  
  if (param_1 <= (char **)(*in_EAX + 2U)) {
    return false;
  }
  pcVar1 = (char *)(*in_EAX + -1);
  *pcVar1 = *pcVar1 + '\x02';
  *(undefined2 *)*in_EAX = param_2._0_2_;
  *in_EAX = *in_EAX + 2;
  return true;
}
