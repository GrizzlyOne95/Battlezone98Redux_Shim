/*
 * Entry: 005bd037
 * Name: luaF_close
 * Namespace: Global
 * Signature: void luaF_close(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaF_close(lua_State *param_1,lua_TValue *param_2)

{
  <unnamed_tag_00001197> *p<Var1;
  GCObject *pGVar2;
  global_State *pgVar3;
  Table *pTVar4;
  
  pGVar2 = param_1->openupval;
  pgVar3 = param_1->l_G;
  while ((pGVar2 != (GCObject *)0x0 &&
         (pGVar2 = param_1->openupval, param_2 <= (pGVar2->h).metatable))) {
    param_1->openupval = (pGVar2->gch).next;
    if ((~pgVar3->currentwhite & (pGVar2->gch).marked & 3) == 0) {
      p<Var1 = (<unnamed_tag_00001197> *)&(pGVar2->h).node;
      ((pGVar2->th).ci)->nresults = (int)(p<Var1->l).prev;
      (((p<Var1->l).prev)->u).l.next = (UpVal *)(pGVar2->h).lastfree;
      pTVar4 = (pGVar2->h).metatable;
      (p<Var1->l).prev = (UpVal *)((Value *)&pTVar4->next)->gc;
      (pGVar2->h).lastfree = *(Node **)&pTVar4->tt;
      (pGVar2->h).gclist = (GCObject *)pTVar4->metatable;
      (pGVar2->h).metatable = (Table *)p<Var1;
      luaC_linkupval(param_1,&pGVar2->uv);
    }
    else {
      luaF_freeupval(param_1,&pGVar2->uv);
    }
    pGVar2 = param_1->openupval;
  }
  return;
}
