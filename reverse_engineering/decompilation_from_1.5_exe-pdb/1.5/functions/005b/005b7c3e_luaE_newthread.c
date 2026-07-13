/*
 * Entry: 005b7c3e
 * Name: luaE_newthread
 * Namespace: Global
 * Signature: lua_State * luaE_newthread(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_State * __cdecl luaE_newthread(lua_State *param_1)

{
  GCObject *pGVar1;
  lua_State *plVar2;
  GCObject *pGVar3;
  
  pGVar1 = luaM_realloc_(param_1,(void *)0x0,0,0x78);
  plVar2 = param_1;
  pGVar3 = pGVar1;
  luaC_link(param_1,pGVar1,'\b');
  preinit_state(plVar2,(global_State *)&pGVar3->gch);
  stack_init(param_1,plVar2);
  *(GCObject **)&(pGVar1->p).nups = (param_1->l_gt).value.gc;
  *(undefined4 *)((int)&(pGVar1->th).l_gt.value + 4) =
       *(undefined4 *)((int)&(param_1->l_gt).value + 4);
  (pGVar1->th).l_gt.tt = (param_1->l_gt).tt;
  (pGVar1->th).hookmask = param_1->hookmask;
  (pGVar1->p).linedefined = param_1->basehookcount;
  (pGVar1->p).gclist = (GCObject *)param_1->hook;
  (pGVar1->p).lastlinedefined = (pGVar1->p).linedefined;
  return (lua_State *)pGVar1;
}
