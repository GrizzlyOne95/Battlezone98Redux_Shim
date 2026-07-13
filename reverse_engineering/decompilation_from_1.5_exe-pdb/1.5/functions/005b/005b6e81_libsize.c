/*
 * Entry: 005b6e81
 * Name: libsize
 * Namespace: Global
 * Signature: int libsize(luaL_Reg * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl libsize(luaL_Reg *param_1)

{
  int iVar1;
  int iVar2;
  int *in_ECX;
  
  iVar2 = 0;
  iVar1 = *in_ECX;
  while (iVar1 != 0) {
    in_ECX = in_ECX + 2;
    iVar2 = iVar2 + 1;
    iVar1 = *in_ECX;
  }
  return iVar2;
}
