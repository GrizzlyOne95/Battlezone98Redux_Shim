/*
 * Entry: 005bce57
 * Name: luaS_newudata
 * Namespace: Global
 * Signature: Udata * luaS_newudata(lua_State * param_1, uint param_2, Table * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Udata * __cdecl luaS_newudata(lua_State *param_1,uint param_2,Table *param_3)

{
  byte bVar1;
  GCObject *pGVar2;
  
  if (0xffffffe5 < param_2) {
    luaM_toobig(param_1);
  }
  pGVar2 = luaM_realloc_(param_1,(void *)0x0,0,param_2 + 0x18);
  bVar1 = param_1->l_G->currentwhite;
  (pGVar2->h).metatable = (Table *)0x0;
  (pGVar2->gch).marked = bVar1 & 3;
  (pGVar2->h).node = (Node *)param_2;
  (pGVar2->gch).tt = '\a';
  (pGVar2->h).array = (lua_TValue *)param_3;
  (pGVar2->gch).next = param_1->l_G->mainthread->next;
  param_1->l_G->mainthread->next = pGVar2;
  return (Udata *)pGVar2;
}
