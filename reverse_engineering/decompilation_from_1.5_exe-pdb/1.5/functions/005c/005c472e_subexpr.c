/*
 * Entry: 005c472e
 * Name: subexpr
 * Namespace: Global
 * Signature: BinOpr subexpr(LexState * param_1, expdesc * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BinOpr __cdecl subexpr(LexState *param_1,expdesc *param_2,uint param_3)

{
  ushort *puVar1;
  int iVar2;
  BinOpr BVar3;
  BinOpr BVar4;
  expdesc *unaff_ESI;
  LexState *unaff_EDI;
  UnOpr UVar5;
  expdesc local_1c;
  
  enterlevel(unaff_EDI);
  iVar2 = (param_1->t).token;
  if (iVar2 == 0x23) {
    UVar5 = OPR_LEN;
  }
  else if (iVar2 == 0x2d) {
    UVar5 = OPR_MINUS;
  }
  else {
    if (iVar2 != 0x10e) {
      simpleexp(unaff_EDI,unaff_ESI);
      goto LAB_005c478c;
    }
    UVar5 = OPR_NOT;
  }
  luaX_next(param_1);
  subexpr(param_1,param_2,8);
  luaK_prefix(param_1->fs,UVar5,param_2);
LAB_005c478c:
  BVar3 = getbinopr((int)unaff_EDI);
  while ((BVar3 != OPR_NOBINOPR && (param_3 < priority[BVar3].left))) {
    luaX_next(param_1);
    luaK_infix(param_1->fs,BVar3,param_2);
    BVar4 = subexpr(param_1,&local_1c,(uint)priority[BVar3].right);
    luaK_posfix(param_1->fs,BVar3,param_2,&local_1c);
    BVar3 = BVar4;
  }
  puVar1 = &param_1->L->nCcalls;
  *puVar1 = *puVar1 - 1;
  return BVar3;
}
