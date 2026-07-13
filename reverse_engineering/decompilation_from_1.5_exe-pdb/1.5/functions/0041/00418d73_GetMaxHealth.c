/*
 * Entry: 00418d73
 * Name: GetMaxHealth
 * Namespace: Global
 * Signature: int GetMaxHealth(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetMaxHealth(lua_State *param_1)

{
  int iVar1;
  float fVar2;
  undefined4 unaff_retaddr;
  
  iVar1 = GetHandle(param_1,1);
  fVar2 = GetMaxHealth(iVar1);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar2 >> 0x20)));
  return 1;
}
