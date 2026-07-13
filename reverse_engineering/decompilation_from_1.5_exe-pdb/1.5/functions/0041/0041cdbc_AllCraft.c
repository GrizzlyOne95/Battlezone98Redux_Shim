/*
 * Entry: 0041cdbc
 * Name: AllCraft
 * Namespace: Global
 * Signature: int AllCraft(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AllCraft(lua_State *param_1)

{
  lua_pushinteger(param_1,0);
  lua_pushcclosure(param_1,AllCraftNext,1);
  return 1;
}
