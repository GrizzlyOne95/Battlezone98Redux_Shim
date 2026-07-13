/*
 * Entry: 005b70ec
 * Name: luaL_buffinit
 * Namespace: Global
 * Signature: void luaL_buffinit(lua_State * param_1, luaL_Buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_buffinit(lua_State *param_1,luaL_Buffer *param_2)

{
  param_2->lvl = 0;
  param_2->L = param_1;
  param_2->p = param_2->buffer;
  return;
}
