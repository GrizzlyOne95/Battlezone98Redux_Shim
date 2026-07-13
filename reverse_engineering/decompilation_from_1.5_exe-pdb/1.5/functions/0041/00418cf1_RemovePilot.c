/*
 * Entry: 00418cf1
 * Name: RemovePilot
 * Namespace: Global
 * Signature: int RemovePilot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl RemovePilot(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  RemovePilotAI(iVar1);
  return 0;
}
