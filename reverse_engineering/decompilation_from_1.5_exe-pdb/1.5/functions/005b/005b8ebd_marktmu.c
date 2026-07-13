/*
 * Entry: 005b8ebd
 * Name: marktmu
 * Namespace: Global
 * Signature: void marktmu(global_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl marktmu(global_State *param_1)

{
  GCObject *pGVar1;
  GCObject *extraout_EDX;
  global_State *unaff_ESI;
  
  pGVar1 = unaff_ESI->tmudata;
  if (pGVar1 != (GCObject *)0x0) {
    do {
      pGVar1 = (pGVar1->gch).next;
      (pGVar1->gch).marked = (pGVar1->gch).marked & 0xf8 | unaff_ESI->currentwhite & 3;
      reallymarkobject(unaff_ESI,pGVar1);
      pGVar1 = extraout_EDX;
    } while (extraout_EDX != unaff_ESI->tmudata);
  }
  return;
}
