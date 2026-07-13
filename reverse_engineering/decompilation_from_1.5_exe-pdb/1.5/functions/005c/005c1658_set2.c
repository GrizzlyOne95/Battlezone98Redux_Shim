/*
 * Entry: 005c1658
 * Name: set2
 * Namespace: Global
 * Signature: void set2(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set2(lua_State *param_1,int param_2,int param_3)

{
  lua_rawseti(param_1,1,param_2);
  lua_rawseti(param_1,1,param_3);
  return;
}
