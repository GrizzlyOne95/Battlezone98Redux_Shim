/*
 * Entry: 005b5d3f
 * Name: lua_gettop
 * Namespace: Global
 * Signature: int lua_gettop(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_gettop(lua_State *param_1)

{
  return (int)param_1->top - (int)param_1->base >> 4;
}
