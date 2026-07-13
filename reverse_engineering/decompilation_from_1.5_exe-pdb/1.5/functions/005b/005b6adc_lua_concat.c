/*
 * Entry: 005b6adc
 * Name: lua_concat
 * Namespace: Global
 * Signature: void lua_concat(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_concat(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  GCObject *pGVar2;
  
  if (param_2 < 2) {
    if (param_2 == 0) {
      plVar1 = param_1->top;
      pGVar2 = (GCObject *)luaS_newlstr(param_1,"",0);
      (plVar1->value).gc = pGVar2;
      plVar1->tt = 4;
      param_1->top = param_1->top + 1;
    }
  }
  else {
    if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
      luaC_step(param_1);
    }
    luaV_concat(param_1,param_2,((int)param_1->top - (int)param_1->base >> 4) + -1);
    param_1->top = param_1->top + (1 - param_2);
  }
  return;
}
