/*
 * Entry: 004171a9
 * Name: SetOwner
 * Namespace: Global
 * Signature: int SetOwner(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetOwner(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = GetHandle(param_1,2);
  SetOwner(iVar1,iVar2);
  return 0;
}
