/*
 * Entry: 004ec039
 * Name: VerifyObjective
 * Namespace: Global
 * Signature: int VerifyObjective(long param_1, long param_2, char * * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VerifyObjective(long param_1,long param_2,char **param_3,char *param_4)

{
  int in_EAX;
  int in_ECX;
  
  if (((*(int *)(in_ECX + in_EAX * 4) != 0) && (-1 < in_EAX)) && (in_EAX < param_1)) {
    return 1;
  }
  if (param_2 != 0) {
    DEBUG_systemWarning("Objective %d does not exist... cannot %s");
  }
  return 0;
}
