/*
 * Entry: 005b97b7
 * Name: markroot
 * Namespace: Global
 * Signature: void markroot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl markroot(lua_State *param_1)

{
  global_State *pgVar1;
  GCObject *pGVar2;
  int in_EDX;
  int extraout_EDX;
  int extraout_EDX_00;
  global_State *unaff_ESI;
  
  pgVar1 = *(global_State **)(in_EDX + 0x10);
  pgVar1->gray = (GCObject *)0x0;
  pgVar1->grayagain = (GCObject *)0x0;
  pgVar1->weak = (GCObject *)0x0;
  if (((((GCObject *)pgVar1->mainthread)->gch).marked & 3) != 0) {
    reallymarkobject(pgVar1,(GCObject *)pgVar1->mainthread);
    in_EDX = extraout_EDX;
  }
  if ((3 < (pgVar1->mainthread->l_gt).tt) &&
     (pGVar2 = (pgVar1->mainthread->l_gt).value.gc, ((pGVar2->gch).marked & 3) != 0)) {
    reallymarkobject(pgVar1,pGVar2);
    in_EDX = extraout_EDX_00;
  }
  if ((3 < *(int *)(*(int *)(in_EDX + 0x10) + 0x68)) &&
     (pGVar2 = *(GCObject **)(*(int *)(in_EDX + 0x10) + 0x60), ((pGVar2->gch).marked & 3) != 0)) {
    reallymarkobject(pgVar1,pGVar2);
  }
  markmt(unaff_ESI);
  pgVar1->gcstate = '\x01';
  return;
}
