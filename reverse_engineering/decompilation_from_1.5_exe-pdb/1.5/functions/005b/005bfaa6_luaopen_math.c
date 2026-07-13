/*
 * Entry: 005bfaa6
 * Name: luaopen_math
 * Namespace: Global
 * Signature: int luaopen_math(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl luaopen_math(lua_State *param_1)

{
  undefined4 unaff_ESI;
  
  luaL_register(param_1,"math",mathlib);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,0x400921fb));
  lua_setfield(param_1,-2,"pi");
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,(int)((ulonglong)_DAT_0022592c >> 0x20)));
  lua_setfield(param_1,-2,"huge");
  lua_getfield(param_1,-1,"fmod");
  lua_setfield(param_1,-2,"mod");
  return 1;
}
