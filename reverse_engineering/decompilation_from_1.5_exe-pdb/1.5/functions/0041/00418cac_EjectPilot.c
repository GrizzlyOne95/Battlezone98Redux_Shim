/*
 * Entry: 00418cac
 * Name: EjectPilot
 * Namespace: Global
 * Signature: int EjectPilot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl EjectPilot(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  EjectPilot(iVar1);
  return 0;
}
