/*
 * Entry: 005be5dc
 * Name: bit_bnot
 * Namespace: Global
 * Signature: int bit_bnot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl bit_bnot(lua_State *param_1)

{
  uint uVar1;
  
  uVar1 = barg(param_1,1);
  lua_pushnumber(param_1,(double)CONCAT44(~uVar1,(int)((ulonglong)(double)(int)~uVar1 >> 0x20)));
  return 1;
}
