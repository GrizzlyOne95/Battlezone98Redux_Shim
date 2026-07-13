/*
 * Entry: 005b959a
 * Name: sweeplist
 * Namespace: Global
 * Signature: GCObject * * sweeplist(lua_State * param_1, GCObject * * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GCObject ** __cdecl sweeplist(lua_State *param_1,GCObject **param_2,uint param_3)

{
  byte bVar1;
  global_State *pgVar2;
  GCObject *pGVar3;
  GCObject *unaff_ESI;
  lua_State *unaff_EDI;
  
  pgVar2 = param_1->l_G;
  bVar1 = pgVar2->currentwhite;
  while ((pGVar3 = *param_2, pGVar3 != (GCObject *)0x0 && (param_3 != 0))) {
    if ((pGVar3->gch).tt == '\b') {
      sweeplist(param_1,&(pGVar3->th).openupval,0xfffffffd);
    }
    if ((byte)((bVar1 ^ 3) & ((pGVar3->gch).marked ^ 3)) == 0) {
      *param_2 = (pGVar3->gch).next;
      if (pGVar3 == pgVar2->rootgc) {
        pgVar2->rootgc = (pGVar3->gch).next;
      }
      freeobj(unaff_EDI,unaff_ESI);
      param_3 = param_3 - 1;
    }
    else {
      (pGVar3->gch).marked = pgVar2->currentwhite & 3 | (pGVar3->gch).marked & 0xf8;
      param_2 = (GCObject **)pGVar3;
      param_3 = param_3 - 1;
    }
  }
  return param_2;
}
