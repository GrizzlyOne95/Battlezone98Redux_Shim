/*
 * Entry: 00511c63
 * Name: IParse_Find_Matched_Bracket
 * Namespace: Global
 * Signature: int IParse_Find_Matched_Bracket(char * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IParse_Find_Matched_Bracket(char *param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 1;
  while( true ) {
    if (param_2 == param_3) {
      return param_2;
    }
    if (param_1[param_2] == '{') {
      iVar1 = iVar1 + 1;
    }
    if ((param_1[param_2] == '}') && (iVar1 = iVar1 + -1, iVar1 == 0)) break;
    param_2 = param_2 + 1;
  }
  return param_2;
}
