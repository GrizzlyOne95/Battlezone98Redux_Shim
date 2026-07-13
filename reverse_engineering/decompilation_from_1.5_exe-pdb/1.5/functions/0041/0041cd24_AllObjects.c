/*
 * Entry: 0041cd24
 * Name: AllObjects
 * Namespace: Global
 * Signature: int AllObjects(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AllObjects(lua_State *param_1)

{
  lua_pushinteger(param_1,0);
  lua_pushcclosure(param_1,AllObjectsNext,1);
  return 1;
}
