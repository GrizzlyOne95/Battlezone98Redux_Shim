/*
 * Entry: 00418d29
 * Name: GetHealth
 * Namespace: Global
 * Signature: int GetHealth(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetHealth(lua_State *param_1)

{
  int iVar1;
  float fVar2;
  undefined4 unaff_retaddr;
  
  iVar1 = GetHandle(param_1,1);
  fVar2 = GetHealth(iVar1);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar2 >> 0x20)));
  return 1;
}
