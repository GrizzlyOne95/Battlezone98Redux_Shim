/*
 * Entry: 005b9c24
 * Name: lua_gethookcount
 * Namespace: Global
 * Signature: int lua_gethookcount(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_gethookcount(lua_State *param_1)

{
  return param_1->basehookcount;
}
