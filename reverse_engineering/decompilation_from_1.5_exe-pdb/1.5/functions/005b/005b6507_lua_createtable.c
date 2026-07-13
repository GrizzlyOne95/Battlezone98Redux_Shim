/*
 * Entry: 005b6507
 * Name: lua_createtable
 * Namespace: Global
 * Signature: void lua_createtable(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_createtable(lua_State *param_1,int param_2,int param_3)

{
  lua_TValue *plVar1;
  GCObject *pGVar2;
  
  if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
    luaC_step(param_1);
  }
  plVar1 = param_1->top;
  pGVar2 = (GCObject *)luaH_new(param_1,param_2,param_3);
  (plVar1->value).gc = pGVar2;
  plVar1->tt = 5;
  param_1->top = param_1->top + 1;
  return;
}
