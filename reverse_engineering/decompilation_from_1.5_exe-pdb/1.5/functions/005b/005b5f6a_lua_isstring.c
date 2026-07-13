/*
 * Entry: 005b5f6a
 * Name: lua_isstring
 * Namespace: Global
 * Signature: int lua_isstring(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_isstring(lua_State *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = lua_type(param_1,param_2);
  if ((iVar1 != 4) && (iVar1 != 3)) {
    return 0;
  }
  return 1;
}
