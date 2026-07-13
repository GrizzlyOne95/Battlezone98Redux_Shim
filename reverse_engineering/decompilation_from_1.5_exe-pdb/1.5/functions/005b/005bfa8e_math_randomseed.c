/*
 * Entry: 005bfa8e
 * Name: math_randomseed
 * Namespace: Global
 * Signature: int math_randomseed(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_randomseed(lua_State *param_1)

{
  uint _Seed;
  
  _Seed = luaL_checkinteger(param_1,1);
  srand(_Seed);
  return 0;
}
