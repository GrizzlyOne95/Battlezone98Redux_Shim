/*
 * Entry: 004171f2
 * Name: SetPilotClass
 * Namespace: Global
 * Signature: int SetPilotClass(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetPilotClass(lua_State *param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = GetHandle(param_1,1);
  pcVar2 = luaL_checklstring(param_1,2,(uint *)0x0);
  SetPilotClass(iVar1,pcVar2);
  return 0;
}
