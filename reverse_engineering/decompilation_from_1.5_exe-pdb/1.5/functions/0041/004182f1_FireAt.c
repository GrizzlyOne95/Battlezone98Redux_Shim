/*
 * Entry: 004182f1
 * Name: FireAt
 * Namespace: Global
 * Signature: int FireAt(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FireAt(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = GetHandle(param_1,2);
  FireAt(iVar1,iVar2);
  return 0;
}
