/*
 * Entry: 00418d4e
 * Name: GetCurHealth
 * Namespace: Global
 * Signature: int GetCurHealth(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetCurHealth(lua_State *param_1)

{
  int iVar1;
  float fVar2;
  undefined4 unaff_retaddr;
  
  iVar1 = GetHandle(param_1,1);
  fVar2 = GetCurHealth(iVar1);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar2 >> 0x20)));
  return 1;
}
