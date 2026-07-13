/*
 * Entry: 005b68da
 * Name: f_Ccall
 * Namespace: Global
 * Signature: void f_Ccall(lua_State * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl f_Ccall(lua_State *param_1,void *param_2)

{
  lua_TValue *plVar1;
  Table *pTVar2;
  GCObject *pGVar3;
  lua_State *unaff_ESI;
  
  pTVar2 = getcurrenv(unaff_ESI);
  pGVar3 = (GCObject *)luaF_newCclosure(param_1,0,pTVar2);
  (pGVar3->h).node = *(Node **)param_2;
  plVar1 = param_1->top;
  (plVar1->value).gc = pGVar3;
  plVar1->tt = 6;
  param_1->top = param_1->top + 1;
  plVar1 = param_1->top;
  (plVar1->value).gc = *(GCObject **)((int)param_2 + 4);
  plVar1->tt = 2;
  param_1->top = param_1->top + 1;
  luaD_call(param_1,param_1->top + -2,0);
  return;
}
