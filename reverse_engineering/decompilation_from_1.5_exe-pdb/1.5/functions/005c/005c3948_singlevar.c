/*
 * Entry: 005c3948
 * Name: singlevar
 * Namespace: Global
 * Signature: void singlevar(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl singlevar(LexState *param_1,expdesc *param_2)

{
  FuncState *pFVar1;
  int in_EAX;
  TString *pTVar2;
  int iVar3;
  LexState *unaff_ESI;
  expdesc *unaff_EDI;
  
  pTVar2 = str_checkname(unaff_ESI);
  pFVar1 = *(FuncState **)(in_EAX + 0x30);
  iVar3 = singlevaraux(pFVar1,pTVar2,unaff_EDI,1);
  if (iVar3 == 8) {
    iVar3 = luaK_stringK(pFVar1,pTVar2);
    (unaff_EDI->u).s.info = iVar3;
  }
  return;
}
