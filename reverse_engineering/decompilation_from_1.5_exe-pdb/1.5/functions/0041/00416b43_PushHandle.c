/*
 * Entry: 00416b43
 * Name: PushHandle
 * Namespace: Global
 * Signature: void PushHandle(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PushHandle(lua_State *param_1,int param_2)

{
  if (param_2 != 0) {
    lua_pushlightuserdata(param_1,(void *)param_2);
    return;
  }
  lua_pushnil(param_1);
  return;
}
