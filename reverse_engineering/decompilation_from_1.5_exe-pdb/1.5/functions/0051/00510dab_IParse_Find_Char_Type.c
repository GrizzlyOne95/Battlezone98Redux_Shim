/*
 * Entry: 00510dab
 * Name: IParse_Find_Char_Type
 * Namespace: Global
 * Signature: int IParse_Find_Char_Type(char param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IParse_Find_Char_Type(char param_1)

{
  int iVar1;
  int _C;
  
  if (param_1 == -1) {
    return 3;
  }
  _C = (int)param_1;
  iVar1 = isalnum(_C);
  if (((iVar1 == 0) && (param_1 != '.')) && (param_1 != '_')) {
    iVar1 = isspace(_C);
    if (((iVar1 == 0) && (iVar1 = isgraph(_C), iVar1 != 0)) && (param_1 != '\r')) {
      return 2;
    }
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}
