/*
 * Entry: 005b984e
 * Name: atomic
 * Namespace: Global
 * Signature: void atomic(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl atomic(lua_State *param_1)

{
  global_State *pgVar1;
  GCObject *in_EAX;
  uint uVar2;
  uint uVar3;
  UpVal *extraout_EDX;
  UpVal *pUVar4;
  GCObject *extraout_EDX_00;
  GCObject *pGVar5;
  GCObject *unaff_EDI;
  bool bVar6;
  
  pgVar1 = (in_EAX->th).l_G;
  for (pUVar4 = (pgVar1->uvhead).u.l.next; pUVar4 != &pgVar1->uvhead; pUVar4 = (pUVar4->u).l.next) {
    if ((((pUVar4->marked & 7) == 0) && (3 < pUVar4->v->tt)) &&
       (pGVar5 = (pUVar4->v->value).gc, ((pGVar5->gch).marked & 3) != 0)) {
      reallymarkobject(pgVar1,pGVar5);
      pUVar4 = extraout_EDX;
    }
  }
  propagateall((global_State *)&unaff_EDI->gch);
  pgVar1->gray = pgVar1->weak;
  pgVar1->weak = (GCObject *)0x0;
  if (((in_EAX->gch).marked & 3) != 0) {
    reallymarkobject(pgVar1,in_EAX);
  }
  markmt((global_State *)&unaff_EDI->gch);
  propagateall((global_State *)&unaff_EDI->gch);
  pgVar1->gray = pgVar1->grayagain;
  pgVar1->grayagain = (GCObject *)0x0;
  propagateall((global_State *)&unaff_EDI->gch);
  uVar2 = luaC_separateudata(&in_EAX->th,0);
  pGVar5 = pgVar1->tmudata;
  bVar6 = pGVar5 == (GCObject *)0x0;
  while (!bVar6) {
    pGVar5 = (pGVar5->gch).next;
    (pGVar5->gch).marked = (pGVar5->gch).marked & 0xf8 | pgVar1->currentwhite & 3;
    reallymarkobject(pgVar1,pGVar5);
    pGVar5 = extraout_EDX_00;
    bVar6 = extraout_EDX_00 == pgVar1->tmudata;
  }
  uVar3 = propagateall((global_State *)&unaff_EDI->gch);
  cleartable(unaff_EDI);
  pgVar1->currentwhite = pgVar1->currentwhite ^ 3;
  pgVar1->sweepgc = &pgVar1->rootgc;
  pgVar1->sweepstrgc = 0;
  pgVar1->gcstate = '\x02';
  pgVar1->estimate = pgVar1->totalbytes - (uVar2 + uVar3);
  return;
}
