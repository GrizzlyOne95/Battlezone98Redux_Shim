/*
 * Entry: 005b9819
 * Name: remarkupvals
 * Namespace: Global
 * Signature: void remarkupvals(global_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl remarkupvals(global_State *param_1)

{
  GCObject *pGVar1;
  UpVal *extraout_EDX;
  UpVal *pUVar2;
  global_State *unaff_ESI;
  
  for (pUVar2 = (unaff_ESI->uvhead).u.l.next; pUVar2 != &unaff_ESI->uvhead;
      pUVar2 = (pUVar2->u).l.next) {
    if ((((pUVar2->marked & 7) == 0) && (3 < pUVar2->v->tt)) &&
       (pGVar1 = (pUVar2->v->value).gc, ((pGVar1->gch).marked & 3) != 0)) {
      reallymarkobject(unaff_ESI,pGVar1);
      pUVar2 = extraout_EDX;
    }
  }
  return;
}
