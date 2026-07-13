/*
 * Entry: 004186a4
 * Name: SetPathOneWay
 * Namespace: Global
 * Signature: int SetPathOneWay(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetPathOneWay(lua_State *param_1)

{
  char *pcVar1;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  SetPathType(pcVar1,ONE_WAY_PATH);
  return 0;
}
