/*
 * Entry: 005b765c
 * Name: luaL_checktype
 * Namespace: Global
 * Signature: void luaL_checktype(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_checktype(lua_State *param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = lua_type(param_1,param_2);
  if (iVar1 != param_3) {
    tag_error(param_1,param_2,param_3);
    return;
  }
  return;
}
