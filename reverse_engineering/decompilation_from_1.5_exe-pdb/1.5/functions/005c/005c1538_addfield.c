/*
 * Entry: 005c1538
 * Name: addfield
 * Namespace: Global
 * Signature: void addfield(lua_State * param_1, luaL_Buffer * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl addfield(lua_State *param_1,luaL_Buffer *param_2,int param_3)

{
  int iVar1;
  lua_State *unaff_ESI;
  
  lua_rawgeti(unaff_ESI,1,(int)param_2);
  iVar1 = lua_isstring(unaff_ESI,-1);
  if (iVar1 == 0) {
    iVar1 = lua_type(unaff_ESI,-1);
    lua_typename(unaff_ESI,iVar1);
    luaL_error(unaff_ESI,"invalid value (%s) at index %d in table for \'concat\'");
  }
  luaL_addvalue((luaL_Buffer *)param_1);
  return;
}
