/*
 * Entry: 0041929f
 * Name: UnpackZero
 * Namespace: Global
 * Signature: void UnpackZero(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackZero(char **param_1,lua_State *param_2)

{
  uint unaff_retaddr;
  
  lua_pushnumber((lua_State *)param_1,(double)((ulonglong)unaff_retaddr << 0x20));
  return;
}
