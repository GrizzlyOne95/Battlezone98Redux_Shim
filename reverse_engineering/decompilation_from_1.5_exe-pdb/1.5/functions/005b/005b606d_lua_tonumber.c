/*
 * Entry: 005b606d
 * Name: lua_tonumber
 * Namespace: Global
 * Signature: double lua_tonumber(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl lua_tonumber(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  undefined4 in_stack_ffffffec;
  undefined4 in_stack_fffffff0;
  
  plVar1 = index2adr((lua_State *)in_stack_ffffffec,in_stack_fffffff0);
  if (plVar1->tt != 3) {
    plVar1 = luaV_tonumber(plVar1,(lua_TValue *)&stack0xffffffec);
    if (plVar1 == (lua_TValue *)0x0) {
      return 0.0;
    }
  }
  return (plVar1->value).n;
}
