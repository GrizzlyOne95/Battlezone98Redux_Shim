/*
 * Entry: 00418764
 * Name: GetCurrentCommand
 * Namespace: Global
 * Signature: int GetCurrentCommand(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetCurrentCommand(lua_State *param_1)

{
  int iVar1;
  AiCommand AVar2;
  
  iVar1 = GetHandle(param_1,1);
  AVar2 = GetCurrentCommand(iVar1);
  lua_pushinteger(param_1,AVar2);
  return 1;
}
