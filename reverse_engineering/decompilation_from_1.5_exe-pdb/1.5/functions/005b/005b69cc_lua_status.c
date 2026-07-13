/*
 * Entry: 005b69cc
 * Name: lua_status
 * Namespace: Global
 * Signature: int lua_status(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_status(lua_State *param_1)

{
  return (uint)param_1->status;
}
