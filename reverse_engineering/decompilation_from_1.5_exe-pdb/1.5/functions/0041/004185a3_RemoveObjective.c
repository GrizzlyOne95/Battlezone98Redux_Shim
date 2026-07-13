/*
 * Entry: 004185a3
 * Name: RemoveObjective
 * Namespace: Global
 * Signature: int RemoveObjective(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl RemoveObjective(lua_State *param_1)

{
  char *pcVar1;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  InfoDisplay::RemoveObjective(&infoDisplay,pcVar1);
  return 0;
}
