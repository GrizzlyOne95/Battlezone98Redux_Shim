/*
 * Entry: 005be56b
 * Name: barg
 * Namespace: Global
 * Signature: uint barg(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl barg(lua_State *param_1,int param_2)

{
  int iVar1;
  double dVar2;
  uint local_c;
  
  dVar2 = lua_tonumber(param_1,param_2);
  local_c = SUB84(dVar2 + 6755399441055744.0,0);
  if (local_c == 0) {
    iVar1 = lua_isnumber(param_1,param_2);
    if (iVar1 == 0) {
      luaL_typerror(param_1,param_2,"number");
    }
  }
  return local_c;
}
