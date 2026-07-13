/*
 * Entry: 005bfb1a
 * Name: str_len
 * Namespace: Global
 * Signature: int str_len(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl str_len(lua_State *param_1)

{
  uint local_8;
  
  luaL_checklstring(param_1,1,&local_8);
  lua_pushinteger(param_1,local_8);
  return 1;
}
