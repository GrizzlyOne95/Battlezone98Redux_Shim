/*
 * Entry: 005b9b35
 * Name: luaC_linkupval
 * Namespace: Global
 * Signature: void luaC_linkupval(lua_State * param_1, UpVal * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaC_linkupval(lua_State *param_1,UpVal *param_2)

{
  byte bVar1;
  global_State *pgVar2;
  GCObject *pGVar3;
  
  pgVar2 = param_1->l_G;
  param_2->next = pgVar2->rootgc;
  pgVar2->rootgc = (GCObject *)param_2;
  bVar1 = param_2->marked;
  if ((bVar1 & 7) == 0) {
    if (pgVar2->gcstate == '\x01') {
      param_2->marked = bVar1 | 4;
      if ((3 < param_2->v->tt) && (pGVar3 = (param_2->v->value).gc, ((pGVar3->gch).marked & 3) != 0)
         ) {
        luaC_barrierf(param_1,(GCObject *)param_2,pGVar3);
        return;
      }
    }
    else {
      param_2->marked = pgVar2->currentwhite & 3 | bVar1 & 0xf8;
    }
  }
  return;
}
