/*
 * Entry: 00418cda
 * Name: KillPilot
 * Namespace: Global
 * Signature: int KillPilot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl KillPilot(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  KillPilot(iVar1);
  return 0;
}
