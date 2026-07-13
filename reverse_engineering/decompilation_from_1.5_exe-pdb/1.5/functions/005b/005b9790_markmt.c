/*
 * Entry: 005b9790
 * Name: markmt
 * Namespace: Global
 * Signature: void markmt(global_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl markmt(global_State *param_1)

{
  GCObject *pGVar1;
  Table **extraout_EDX;
  Table **ppTVar2;
  global_State *unaff_ESI;
  int iVar3;
  
  ppTVar2 = unaff_ESI->mt;
  iVar3 = 9;
  do {
    pGVar1 = (GCObject *)*ppTVar2;
    if ((pGVar1 != (GCObject *)0x0) && (((pGVar1->gch).marked & 3) != 0)) {
      reallymarkobject(unaff_ESI,pGVar1);
      ppTVar2 = extraout_EDX;
    }
    ppTVar2 = ppTVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}
