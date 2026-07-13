/*
 * Entry: 005be650
 * Name: bit_bor
 * Namespace: Global
 * Signature: int bit_bor(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl bit_bor(lua_State *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 unaff_EDI;
  undefined4 local_8;
  
  local_8 = barg(param_1,1);
  for (iVar1 = lua_gettop(param_1); 1 < iVar1; iVar1 = iVar1 + -1) {
    uVar2 = barg(param_1,iVar1);
    local_8 = local_8 | uVar2;
  }
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)(int)local_8 >> 0x20)))
  ;
  return 1;
}
