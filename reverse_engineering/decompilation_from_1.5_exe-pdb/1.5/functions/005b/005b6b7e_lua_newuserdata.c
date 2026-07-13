/*
 * Entry: 005b6b7e
 * Name: lua_newuserdata
 * Namespace: Global
 * Signature: void * lua_newuserdata(lua_State * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl lua_newuserdata(lua_State *param_1,uint param_2)

{
  lua_TValue *plVar1;
  Table *pTVar2;
  GCObject *pGVar3;
  lua_State *unaff_ESI;
  
  if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
    luaC_step(param_1);
  }
  pTVar2 = getcurrenv(unaff_ESI);
  pGVar3 = (GCObject *)luaS_newudata(param_1,param_2,pTVar2);
  plVar1 = param_1->top;
  (plVar1->value).gc = pGVar3;
  plVar1->tt = 7;
  param_1->top = param_1->top + 1;
  return &pGVar3->u + 1;
}
