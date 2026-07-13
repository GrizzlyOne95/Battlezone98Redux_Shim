/*
 * Entry: 00526efe
 * Name: wildmat
 * Namespace: Global
 * Signature: int wildmat(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl wildmat(char *param_1,char *param_2)

{
  int iVar1;
  
  if (((*param_2 == '?') || (*param_2 == '*')) && (*param_1 == '.')) {
    return 0;
  }
  iVar1 = DoMatch(param_1,param_2);
  return (uint)(iVar1 == 1);
}
