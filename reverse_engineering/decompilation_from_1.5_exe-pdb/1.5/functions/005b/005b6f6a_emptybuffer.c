/*
 * Entry: 005b6f6a
 * Name: emptybuffer
 * Namespace: Global
 * Signature: int emptybuffer(luaL_Buffer * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl emptybuffer(luaL_Buffer *param_1)

{
  uint uVar1;
  int *unaff_ESI;
  
  uVar1 = (*unaff_ESI - (int)unaff_ESI) - 0xc;
  if (uVar1 == 0) {
    return 0;
  }
  lua_pushlstring((lua_State *)unaff_ESI[2],(char *)(unaff_ESI + 3),uVar1);
  unaff_ESI[1] = unaff_ESI[1] + 1;
  *unaff_ESI = (int)(unaff_ESI + 3);
  return 1;
}
