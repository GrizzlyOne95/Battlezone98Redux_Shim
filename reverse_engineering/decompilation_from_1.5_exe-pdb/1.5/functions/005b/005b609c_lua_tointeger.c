/*
 * Entry: 005b609c
 * Name: lua_tointeger
 * Namespace: Global
 * Signature: int lua_tointeger(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_tointeger(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  
  plVar1 = index2adr((lua_State *)in_stack_ffffffe0,in_stack_ffffffe4);
  if (plVar1->tt != 3) {
    plVar1 = luaV_tonumber(plVar1,(lua_TValue *)&stack0xffffffe0);
    if (plVar1 == (lua_TValue *)0x0) {
      return 0;
    }
  }
  return (int)ROUND((plVar1->value).n);
}
