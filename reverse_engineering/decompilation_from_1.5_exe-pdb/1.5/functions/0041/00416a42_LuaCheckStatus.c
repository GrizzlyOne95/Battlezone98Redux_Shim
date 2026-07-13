/*
 * Entry: 00416a42
 * Name: LuaCheckStatus
 * Namespace: Global
 * Signature: bool LuaCheckStatus(int param_1, lua_State * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl LuaCheckStatus(int param_1,lua_State *param_2,char *param_3)

{
  if (param_1 != 0) {
    lua_tolstring(param_2,-1,(uint *)0x0);
    DEBUG_systemWarning(param_3);
    return false;
  }
  return true;
}
