/*
 * Entry: 005c3977
 * Name: adjust_assign
 * Namespace: Global
 * Signature: void adjust_assign(LexState * param_1, int param_2, int param_3, expdesc * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl adjust_assign(LexState *param_1,int param_2,int param_3,expdesc *param_4)

{
  FuncState *pFVar1;
  expkind eVar2;
  int iVar3;
  int in_EAX;
  int iVar4;
  expdesc *in_ECX;
  int in_EDX;
  
  iVar4 = in_EAX - (int)param_1;
  pFVar1 = *(FuncState **)(in_EDX + 0x30);
  eVar2 = in_ECX->k;
  if ((eVar2 == VCALL) || (eVar2 == VVARARG)) {
    iVar4 = iVar4 + 1;
    if (iVar4 < 0) {
      iVar4 = 0;
    }
    luaK_setreturns(pFVar1,in_ECX,iVar4);
    if (1 < iVar4) {
      luaK_reserveregs(pFVar1,iVar4 + -1);
    }
  }
  else {
    if (eVar2 != VVOID) {
      luaK_exp2nextreg(pFVar1,in_ECX);
    }
    if (0 < iVar4) {
      iVar3 = pFVar1->freereg;
      luaK_reserveregs(pFVar1,iVar4);
      luaK_nil(pFVar1,iVar3,iVar4);
    }
  }
  return;
}
