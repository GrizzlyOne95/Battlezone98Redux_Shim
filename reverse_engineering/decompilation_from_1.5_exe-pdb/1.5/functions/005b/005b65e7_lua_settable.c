/*
 * Entry: 005b65e7
 * Name: lua_settable
 * Namespace: Global
 * Signature: void lua_settable(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_settable(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar1 = index2adr(unaff_ESI,unaff_retaddr);
  luaV_settable(param_1,plVar1,param_1->top + -2,param_1->top + -1);
  param_1->top = param_1->top + -2;
  return;
}
