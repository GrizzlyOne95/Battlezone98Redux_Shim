/*
 * Entry: 005b6422
 * Name: lua_gettable
 * Namespace: Global
 * Signature: void lua_gettable(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_gettable(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar1 = index2adr(unaff_ESI,unaff_retaddr);
  luaV_gettable(param_1,plVar1,param_1->top + -1,param_1->top + -1);
  return;
}
