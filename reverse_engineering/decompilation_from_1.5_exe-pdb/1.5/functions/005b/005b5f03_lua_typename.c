/*
 * Entry: 005b5f03
 * Name: lua_typename
 * Namespace: Global
 * Signature: char * lua_typename(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lua_typename(lua_State *param_1,int param_2)

{
  if (param_2 == -1) {
    return "no value";
  }
  return *(char **)(&luaT_typenames + param_2 * 4);
}
