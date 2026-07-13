/*
 * Entry: 005b61ce
 * Name: lua_touserdata
 * Namespace: Global
 * Signature: void * lua_touserdata(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl lua_touserdata(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_retaddr;
  
  plVar1 = index2adr(unaff_retaddr,(int)param_1);
  if (plVar1->tt == 2) {
    return (plVar1->value).gc;
  }
  if (plVar1->tt != 7) {
    return (void *)0x0;
  }
  return (void *)((plVar1->value).b + 0x18);
}
