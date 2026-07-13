/*
 * Entry: 005bd656
 * Name: luaM_toobig
 * Namespace: Global
 * Signature: void * luaM_toobig(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl luaM_toobig(lua_State *param_1)

{
  luaG_runerror(param_1,"memory allocation error: block too big");
  return (void *)0x0;
}
