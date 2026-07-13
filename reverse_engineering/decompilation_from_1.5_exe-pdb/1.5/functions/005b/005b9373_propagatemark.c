/*
 * Entry: 005b9373
 * Name: propagatemark
 * Namespace: Global
 * Signature: int propagatemark(global_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl propagatemark(global_State *param_1)

{
  uchar uVar1;
  GCObject *pGVar2;
  global_State *in_EAX;
  int iVar3;
  Closure *unaff_ESI;
  
  pGVar2 = in_EAX->gray;
  uVar1 = (pGVar2->gch).tt;
  (pGVar2->gch).marked = (pGVar2->gch).marked | 4;
  if (uVar1 == '\x05') {
    in_EAX->gray = (pGVar2->h).gclist;
    iVar3 = traversetable(in_EAX,(Table *)&unaff_ESI->c);
    if (iVar3 != 0) {
      (pGVar2->gch).marked = (pGVar2->gch).marked & 0xfb;
    }
    return ((int)&((pGVar2->th).stack_last)->value + (1 << ((pGVar2->h).lsizenode & 0x1f)) * 2 + 2)
           * 0x10;
  }
  if (uVar1 == '\x06') {
    in_EAX->gray = (GCObject *)(pGVar2->h).metatable;
    traverseclosure(in_EAX,unaff_ESI);
    if ((pGVar2->h).flags != '\0') {
      return (uint)(pGVar2->h).lsizenode * 0x10 + 0x18;
    }
    return (uint)(pGVar2->h).lsizenode * 4 + 0x14;
  }
  if (uVar1 == '\b') {
    in_EAX->gray = (pGVar2->th).gclist;
    (pGVar2->th).gclist = in_EAX->grayagain;
    in_EAX->grayagain = pGVar2;
    (pGVar2->gch).marked = (pGVar2->gch).marked & 0xfb;
    traversestack(in_EAX,(lua_State *)&unaff_ESI->c);
    return ((pGVar2->p).sizelineinfo + 5) * 0x18 + (pGVar2->p).sizecode * 0x10;
  }
  if (uVar1 != '\t') {
    return 0;
  }
  in_EAX->gray = (pGVar2->p).gclist;
  traverseproto(in_EAX,(Proto *)&unaff_ESI->c);
  return ((int)&((pGVar2->th).end_ci)->base +
         (pGVar2->p).sizelocvars * 3 + (pGVar2->p).sizek * 4 + (pGVar2->p).sizep +
         (pGVar2->p).sizelineinfo + (pGVar2->p).sizecode) * 4 + 0x4c;
}
