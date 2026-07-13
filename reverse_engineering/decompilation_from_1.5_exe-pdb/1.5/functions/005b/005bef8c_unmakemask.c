/*
 * Entry: 005bef8c
 * Name: unmakemask
 * Namespace: Global
 * Signature: char * unmakemask(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl unmakemask(int param_1,char *param_2)

{
  char *in_EAX;
  uint uVar1;
  bool bVar2;
  
  bVar2 = (param_1 & 1U) != 0;
  if (bVar2) {
    *in_EAX = 'c';
  }
  uVar1 = (uint)bVar2;
  if ((param_1 & 2U) != 0) {
    in_EAX[uVar1] = 'r';
    uVar1 = uVar1 + 1;
  }
  if ((param_1 & 4U) != 0) {
    in_EAX[uVar1] = 'l';
    uVar1 = uVar1 + 1;
  }
  in_EAX[uVar1] = '\0';
  return in_EAX;
}
