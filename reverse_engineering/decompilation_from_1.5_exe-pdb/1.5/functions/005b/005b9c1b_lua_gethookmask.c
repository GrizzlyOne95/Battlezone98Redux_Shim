/*
 * Entry: 005b9c1b
 * Name: lua_gethookmask
 * Namespace: Global
 * Signature: int lua_gethookmask(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_gethookmask(lua_State *param_1)

{
  return (uint)param_1->hookmask;
}
