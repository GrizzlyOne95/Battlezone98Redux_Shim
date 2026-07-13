/*
 * Entry: 00418e19
 * Name: GetAmmo
 * Namespace: Global
 * Signature: int GetAmmo(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetAmmo(lua_State *param_1)

{
  int iVar1;
  float fVar2;
  undefined4 unaff_retaddr;
  
  iVar1 = GetHandle(param_1,1);
  fVar2 = GetAmmo(iVar1);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar2 >> 0x20)));
  return 1;
}
