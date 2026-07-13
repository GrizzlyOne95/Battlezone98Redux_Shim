/*
 * Entry: 005c51f2
 * Name: retstat
 * Namespace: Global
 * Signature: void retstat(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl retstat(LexState *param_1)

{
  uint *puVar1;
  FuncState *pFVar2;
  LexState *in_EAX;
  int iVar3;
  uint uVar4;
  int extraout_ECX;
  expdesc *unaff_EDI;
  expdesc local_1c;
  
  pFVar2 = in_EAX->fs;
  luaX_next(in_EAX);
  iVar3 = block_follow((int)unaff_EDI);
  if ((iVar3 == 0) && (extraout_ECX != 0x3b)) {
    iVar3 = explist1((LexState *)&local_1c,unaff_EDI);
    if ((local_1c.k == VCALL) || (local_1c.k == VVARARG)) {
      luaK_setreturns(pFVar2,&local_1c,-1);
      if ((local_1c.k == VCALL) && (iVar3 == 1)) {
        puVar1 = pFVar2->f->code + local_1c.u.s.info;
        *puVar1 = *puVar1 & 0xffffffdd | 0x1d;
      }
      uVar4 = (uint)pFVar2->nactvar;
      iVar3 = -1;
    }
    else if (iVar3 == 1) {
      uVar4 = luaK_exp2anyreg(pFVar2,&local_1c);
    }
    else {
      luaK_exp2nextreg(pFVar2,&local_1c);
      uVar4 = (uint)pFVar2->nactvar;
    }
  }
  else {
    iVar3 = 0;
    uVar4 = 0;
  }
  luaK_ret(pFVar2,uVar4,iVar3);
  return;
}
