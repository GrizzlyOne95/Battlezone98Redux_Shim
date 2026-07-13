/*
 * Entry: 005bcf72
 * Name: luaF_findupval
 * Namespace: Global
 * Signature: UpVal * luaF_findupval(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UpVal * __cdecl luaF_findupval(lua_State *param_1,lua_TValue *param_2)

{
  UpVal **ppUVar1;
  byte bVar2;
  global_State *pgVar3;
  GCObject *pGVar4;
  UpVal *pUVar5;
  GCObject *pGVar6;
  GCObject *pGVar7;
  
  pgVar3 = param_1->l_G;
  pGVar7 = param_1->openupval;
  pGVar6 = (GCObject *)&param_1->openupval;
  while (pGVar7 != (GCObject *)0x0) {
    pGVar4 = ((UpVal *)pGVar6)->next;
    if ((lua_TValue *)(pGVar4->h).metatable < param_2) break;
    if ((lua_TValue *)(pGVar4->h).metatable == param_2) {
      if ((~pgVar3->currentwhite & (pGVar4->gch).marked & 3) != 0) {
        (pGVar4->gch).marked = (pGVar4->gch).marked ^ 3;
        return (UpVal *)pGVar4;
      }
      return (UpVal *)pGVar4;
    }
    pGVar6 = pGVar4;
    pGVar7 = (pGVar4->gch).next;
  }
  pGVar7 = luaM_realloc_(param_1,(void *)0x0,0,0x20);
  (pGVar7->gch).tt = '\n';
  bVar2 = pgVar3->currentwhite;
  (pGVar7->p).k = param_2;
  (pGVar7->gch).marked = bVar2 & 3;
  (pGVar7->gch).next = ((UpVal *)pGVar6)->next;
  ((UpVal *)pGVar6)->next = pGVar7;
  (((<unnamed_tag_00001197> *)&(pGVar7->h).node)->l).prev = &pgVar3->uvhead;
  ppUVar1 = &(pgVar3->uvhead).u.l.next;
  pUVar5 = *ppUVar1;
  (pGVar7->h).lastfree = (Node *)pUVar5;
  *(GCObject **)&pUVar5->u = pGVar7;
  *ppUVar1 = (UpVal *)pGVar7;
  return (UpVal *)pGVar7;
}
