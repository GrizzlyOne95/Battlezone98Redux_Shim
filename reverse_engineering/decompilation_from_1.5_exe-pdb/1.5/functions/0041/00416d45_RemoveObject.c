/*
 * Entry: 00416d45
 * Name: RemoveObject
 * Namespace: Global
 * Signature: int RemoveObject(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl RemoveObject(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  RemoveObject(iVar1);
  return 0;
}
