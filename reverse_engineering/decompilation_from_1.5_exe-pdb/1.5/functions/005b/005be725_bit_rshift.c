/*
 * Entry: 005be725
 * Name: bit_rshift
 * Namespace: Global
 * Signature: int bit_rshift(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl bit_rshift(lua_State *param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 unaff_ESI;
  
  uVar1 = barg(param_1,1);
  uVar2 = barg(param_1,2);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,
                                          (int)((ulonglong)
                                                (double)(int)(uVar1 >> ((byte)uVar2 & 0x1f)) >> 0x20
                                               )));
  return 1;
}
