/*
 * Entry: 005be821
 * Name: bit_bswap
 * Namespace: Global
 * Signature: int bit_bswap(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl bit_bswap(lua_State *param_1)

{
  uint uVar1;
  
  uVar1 = barg(param_1,1);
  uVar1 = (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8 | (uVar1 & 0xff00 | uVar1 << 0x10) << 8;
  lua_pushnumber(param_1,(double)CONCAT44(uVar1,(int)((ulonglong)(double)(int)uVar1 >> 0x20)));
  return 1;
}
