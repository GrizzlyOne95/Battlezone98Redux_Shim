/*
 * Entry: 004839c7
 * Name: ItemExists
 * Namespace: Global
 * Signature: int ItemExists(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ItemExists(char *param_1)

{
  int iVar1;
  
  nItemExists = nItemExists + 1;
  iVar1 = zixIsFileInIndex(param_1);
  return iVar1;
}
