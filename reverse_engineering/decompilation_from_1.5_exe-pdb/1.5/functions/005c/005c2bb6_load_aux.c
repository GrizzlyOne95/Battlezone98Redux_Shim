/*
 * Entry: 005c2bb6
 * Name: load_aux
 * Namespace: Global
 * Signature: int load_aux(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl load_aux(lua_State *param_1,int param_2)

{
  if (param_2 == 0) {
    return 1;
  }
  lua_pushnil(param_1);
  lua_insert(param_1,-2);
  return 2;
}
