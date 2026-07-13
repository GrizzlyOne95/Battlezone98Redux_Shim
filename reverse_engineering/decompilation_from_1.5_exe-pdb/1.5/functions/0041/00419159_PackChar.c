/*
 * Entry: 00419159
 * Name: PackChar
 * Namespace: Global
 * Signature: bool PackChar(char * * param_1, char * param_2, char param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackChar(char **param_1,char *param_2,char param_3)

{
  char *pcVar1;
  int *in_ECX;
  
  if (param_1 <= (char **)(*in_ECX + 1U)) {
    return false;
  }
  pcVar1 = (char *)(*in_ECX + -1);
  *pcVar1 = *pcVar1 + '\x01';
  *(undefined1 *)*in_ECX = param_2._0_1_;
  *in_ECX = *in_ECX + 1;
  return true;
}
