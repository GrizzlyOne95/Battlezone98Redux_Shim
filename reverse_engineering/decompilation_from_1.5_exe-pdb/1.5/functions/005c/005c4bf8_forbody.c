/*
 * Entry: 005c4bf8
 * Name: forbody
 * Namespace: Global
 * Signature: void forbody(LexState * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl forbody(LexState *param_1,int param_2,int param_3,int param_4,int param_5)

{
  FuncState *pFVar1;
  int iVar2;
  int in_EAX;
  int iVar3;
  int unaff_ESI;
  LexState *unaff_EDI;
  FuncState *pFVar4;
  BlockCnt local_14;
  int local_8;
  
  pFVar1 = *(FuncState **)(in_EAX + 0x30);
  adjustlocalvars(unaff_EDI,unaff_ESI);
  checknext(unaff_EDI,unaff_ESI);
  if (param_4 == 0) {
    local_8 = luaK_jump(pFVar1);
  }
  else {
    local_8 = luaK_codeABx(pFVar1,OP_FORPREP,(int)param_1,0x1fffe);
  }
  local_14.breaklist = -1;
  local_14.isbreakable = '\0';
  local_14.nactvar = pFVar1->nactvar;
  local_14.upval = '\0';
  local_14.previous = pFVar1->bl;
  pFVar1->bl = &local_14;
  adjustlocalvars(unaff_EDI,unaff_ESI);
  pFVar4 = pFVar1;
  luaK_reserveregs(pFVar1,param_3);
  block((LexState *)pFVar4);
  leaveblock(pFVar4);
  iVar2 = local_8;
  luaK_patchtohere(pFVar1,local_8);
  if (param_4 == 0) {
    iVar3 = luaK_codeABC(pFVar1,OP_TFORLOOP,(int)param_1,0,param_3);
  }
  else {
    iVar3 = luaK_codeABx(pFVar1,OP_FORLOOP,(int)param_1,0x1fffe);
  }
  luaK_fixline(pFVar1,param_2);
  if (param_4 == 0) {
    iVar3 = luaK_jump(pFVar1);
  }
  luaK_patchlist(pFVar1,iVar3,iVar2 + 1);
  return;
}
