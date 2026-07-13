/*
 * Entry: 005be8fc
 * Name: luaopen_bit
 * Namespace: Global
 * Signature: int luaopen_bit(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaopen_bit(lua_State *param_1)

{
  uint uVar1;
  undefined4 unaff_ESI;
  
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,0x41d56a8c));
  uVar1 = barg(param_1,-1);
  if (uVar1 != 0x55aa3377) {
    luaL_error(param_1,"bit library self-test failed (%s)");
  }
  luaL_register(param_1,"bit",bit_funcs);
  return 1;
}
