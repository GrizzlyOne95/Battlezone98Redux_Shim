/*
 * Entry: 004191b9
 * Name: PackDouble
 * Namespace: Global
 * Signature: bool PackDouble(char * * param_1, char * param_2, double param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackDouble(char **param_1,char *param_2,double param_3)

{
  char *pcVar1;
  undefined4 *puVar2;
  int *in_EAX;
  
  if (param_1 <= (char **)(*in_EAX + 8U)) {
    return false;
  }
  pcVar1 = (char *)(*in_EAX + -1);
  *pcVar1 = *pcVar1 + '\b';
  puVar2 = (undefined4 *)*in_EAX;
  *puVar2 = param_2;
  puVar2[1] = param_3._0_4_;
  *in_EAX = *in_EAX + 8;
  return true;
}
