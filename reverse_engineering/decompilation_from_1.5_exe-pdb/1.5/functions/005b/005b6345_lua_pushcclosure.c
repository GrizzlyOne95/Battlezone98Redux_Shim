/*
 * Entry: 005b6345
 * Name: lua_pushcclosure
 * Namespace: Global
 * Signature: void lua_pushcclosure(lua_State * param_1, _func___cdecl_int_lua_State_ptr * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
lua_pushcclosure(lua_State *param_1,_func___cdecl_int_lua_State_ptr *param_2,int param_3)

{
  lua_TValue *plVar1;
  Table *pTVar2;
  GCObject *pGVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  lua_State *unaff_ESI;
  
  if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
    luaC_step(param_1);
  }
  pTVar2 = getcurrenv(unaff_ESI);
  pGVar3 = (GCObject *)luaF_newCclosure(param_1,param_3,pTVar2);
  (pGVar3->h).node = (Node *)param_2;
  param_1->top = param_1->top + -param_3;
  if (param_3 != 0) {
    puVar5 = (undefined4 *)(param_3 * 0x10 + 0x18 + (int)pGVar3);
    do {
      param_3 = param_3 + -1;
      puVar6 = puVar5 + -4;
      puVar4 = (undefined4 *)((-0x18 - (int)pGVar3) + (int)puVar6 + (int)param_1->top);
      *puVar6 = *puVar4;
      puVar5[-3] = puVar4[1];
      puVar5[-2] = puVar4[2];
      puVar5 = puVar6;
    } while (param_3 != 0);
  }
  plVar1 = param_1->top;
  (plVar1->value).gc = pGVar3;
  plVar1->tt = 6;
  param_1->top = param_1->top + 1;
  return;
}
