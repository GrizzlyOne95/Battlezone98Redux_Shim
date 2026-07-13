/*
 * Entry: 004186bf
 * Name: SetPathRoundTrip
 * Namespace: Global
 * Signature: int SetPathRoundTrip(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetPathRoundTrip(lua_State *param_1)

{
  char *pcVar1;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  SetPathType(pcVar1,ROUND_TRIP_PATH);
  return 0;
}
