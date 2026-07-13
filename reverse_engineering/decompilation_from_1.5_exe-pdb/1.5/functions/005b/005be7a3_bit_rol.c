/*
 * Entry: 005be7a3
 * Name: bit_rol
 * Namespace: Global
 * Signature: int bit_rol(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl bit_rol(lua_State *param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  undefined4 unaff_ESI;
  
  uVar1 = barg(param_1,1);
  uVar2 = barg(param_1,2);
  bVar3 = (byte)uVar2 & 0x1f;
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,
                                          (int)((ulonglong)
                                                (double)(int)(uVar1 << bVar3 | uVar1 >> 0x20 - bVar3
                                                             ) >> 0x20)));
  return 1;
}
