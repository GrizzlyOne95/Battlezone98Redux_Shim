/*
 * Entry: 005b61f3
 * Name: lua_tothread
 * Namespace: Global
 * Signature: lua_State * lua_tothread(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_State * __cdecl lua_tothread(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_retaddr;
  
  plVar1 = index2adr(unaff_retaddr,(int)param_1);
  if (plVar1->tt != 8) {
    return (lua_State *)0x0;
  }
  return (lua_State *)(plVar1->value).gc;
}
