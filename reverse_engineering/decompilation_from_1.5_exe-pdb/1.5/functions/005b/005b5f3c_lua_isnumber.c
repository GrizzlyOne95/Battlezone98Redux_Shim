/*
 * Entry: 005b5f3c
 * Name: lua_isnumber
 * Namespace: Global
 * Signature: int lua_isnumber(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_isnumber(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  undefined4 in_stack_ffffffec;
  undefined4 in_stack_fffffff0;
  
  plVar1 = index2adr((lua_State *)in_stack_ffffffec,in_stack_fffffff0);
  if (plVar1->tt != 3) {
    plVar1 = luaV_tonumber(plVar1,(lua_TValue *)&stack0xffffffec);
    if (plVar1 == (lua_TValue *)0x0) {
      return 0;
    }
  }
  return 1;
}
