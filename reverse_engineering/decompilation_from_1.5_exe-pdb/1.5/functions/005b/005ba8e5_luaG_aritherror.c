/*
 * Entry: 005ba8e5
 * Name: luaG_aritherror
 * Namespace: Global
 * Signature: void luaG_aritherror(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaG_aritherror(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3)

{
  lua_TValue *plVar1;
  lua_TValue local_14;
  
  plVar1 = luaV_tonumber(param_2,&local_14);
  if (plVar1 != (lua_TValue *)0x0) {
    param_2 = param_3;
  }
  luaG_typeerror(param_1,param_2,"perform arithmetic on");
  return;
}
