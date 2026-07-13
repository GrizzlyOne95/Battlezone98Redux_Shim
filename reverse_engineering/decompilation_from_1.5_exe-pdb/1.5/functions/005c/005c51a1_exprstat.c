/*
 * Entry: 005c51a1
 * Name: exprstat
 * Namespace: Global
 * Signature: void exprstat(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl exprstat(LexState *param_1)

{
  uint *puVar1;
  FuncState *pFVar2;
  LexState *in_EAX;
  expdesc *unaff_ESI;
  LHS_assign local_24;
  
  pFVar2 = in_EAX->fs;
  primaryexp((LexState *)&local_24.v,unaff_ESI);
  if (local_24.v.k == VCALL) {
    puVar1 = pFVar2->f->code + local_24.v.u.s.info;
    *puVar1 = *puVar1 & 0xff807fff | 0x4000;
  }
  else {
    local_24.prev = (LHS_assign *)0x0;
    assignment(in_EAX,&local_24,1);
  }
  return;
}
