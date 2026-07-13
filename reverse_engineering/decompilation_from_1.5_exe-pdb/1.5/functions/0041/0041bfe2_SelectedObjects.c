/*
 * Entry: 0041bfe2
 * Name: SelectedObjects
 * Namespace: Global
 * Signature: int SelectedObjects(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SelectedObjects(lua_State *param_1)

{
  lua_pushinteger(param_1,0);
  lua_pushcclosure(param_1,SelectedObjectsNext,1);
  return 1;
}
