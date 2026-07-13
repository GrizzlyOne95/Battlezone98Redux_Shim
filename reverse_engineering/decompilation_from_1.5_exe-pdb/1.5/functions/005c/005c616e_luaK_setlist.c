/*
 * Entry: 005c616e
 * Name: luaK_setlist
 * Namespace: Global
 * Signature: void luaK_setlist(FuncState * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_setlist(FuncState *param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  FuncState *pFVar2;
  FuncState *pFVar3;
  
  pFVar2 = (FuncState *)((param_3 + -1) / 0x32 + 1);
  uVar1 = -(uint)(param_4 != -1) & param_4;
  if ((int)pFVar2 < 0x200) {
    luaK_codeABC(param_1,OP_SETLIST,param_2,uVar1,(int)pFVar2);
  }
  else {
    pFVar3 = param_1;
    luaK_codeABC(param_1,OP_SETLIST,param_2,uVar1,0);
    luaK_code(pFVar2,param_1->ls->lastline,(int)pFVar3);
  }
  param_1->freereg = param_2 + 1;
  return;
}
