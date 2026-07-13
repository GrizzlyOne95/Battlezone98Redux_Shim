/*
 * Entry: 004186da
 * Name: SetPathLoop
 * Namespace: Global
 * Signature: int SetPathLoop(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetPathLoop(lua_State *param_1)

{
  char *pcVar1;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  SetPathType(pcVar1,LOOP_PATH);
  return 0;
}
