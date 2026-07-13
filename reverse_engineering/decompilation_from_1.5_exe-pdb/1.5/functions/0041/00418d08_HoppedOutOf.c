/*
 * Entry: 00418d08
 * Name: HoppedOutOf
 * Namespace: Global
 * Signature: int HoppedOutOf(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl HoppedOutOf(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  iVar1 = HoppedOutOf(iVar1);
  PushHandle(param_1,iVar1);
  return 0;
}
