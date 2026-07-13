/*
 * Entry: 005b5d0f
 * Name: lua_newthread
 * Namespace: Global
 * Signature: lua_State * lua_newthread(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_State * __cdecl lua_newthread(lua_State *param_1)

{
  lua_TValue *plVar1;
  GCObject *pGVar2;
  
  if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
    luaC_step(param_1);
  }
  pGVar2 = (GCObject *)luaE_newthread(param_1);
  plVar1 = param_1->top;
  (plVar1->value).gc = pGVar2;
  plVar1->tt = 8;
  param_1->top = param_1->top + 1;
  return (lua_State *)pGVar2;
}
