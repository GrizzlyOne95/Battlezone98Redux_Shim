/*
 * Entry: 0041873f
 * Name: IsBusy
 * Namespace: Global
 * Signature: int IsBusy(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsBusy(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetHandle(param_1,1);
  bVar1 = IsBusy(iVar2);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
