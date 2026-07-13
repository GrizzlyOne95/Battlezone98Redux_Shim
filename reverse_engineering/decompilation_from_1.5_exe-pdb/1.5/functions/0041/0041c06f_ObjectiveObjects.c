/*
 * Entry: 0041c06f
 * Name: ObjectiveObjects
 * Namespace: Global
 * Signature: int ObjectiveObjects(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ObjectiveObjects(lua_State *param_1)

{
  lua_pushinteger(param_1,0);
  lua_pushcclosure(param_1,ObjectiveObjectsNext,1);
  return 1;
}
