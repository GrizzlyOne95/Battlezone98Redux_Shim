/*
 * Entry: 004186f5
 * Name: CanCommand
 * Namespace: Global
 * Signature: int CanCommand(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CanCommand(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetHandle(param_1,1);
  bVar1 = CanCommand(iVar2);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
