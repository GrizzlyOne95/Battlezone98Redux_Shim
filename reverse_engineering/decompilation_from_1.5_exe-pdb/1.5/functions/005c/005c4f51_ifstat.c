/*
 * Entry: 005c4f51
 * Name: ifstat
 * Namespace: Global
 * Signature: void ifstat(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ifstat(LexState *param_1,int param_2)

{
  int iVar1;
  LexState *unaff_ESI;
  LexState *unaff_EDI;
  FuncState *pFVar2;
  int local_c;
  int local_8;
  
  local_c = -1;
  pFVar2 = unaff_ESI->fs;
  local_8 = test_then_block(unaff_EDI);
  while ((unaff_ESI->t).token == 0x105) {
    iVar1 = luaK_jump(pFVar2);
    luaK_concat(pFVar2,&local_c,iVar1);
    luaK_patchtohere(pFVar2,local_8);
    local_8 = test_then_block(unaff_EDI);
  }
  if ((unaff_ESI->t).token == 0x104) {
    iVar1 = luaK_jump(pFVar2);
    luaK_concat(pFVar2,&local_c,iVar1);
    luaK_patchtohere(pFVar2,local_8);
    luaX_next(unaff_ESI);
    block(unaff_EDI);
  }
  else {
    luaK_concat(pFVar2,&local_c,local_8);
  }
  iVar1 = local_c;
  luaK_patchtohere(pFVar2,local_c);
  check_match((LexState *)0x106,0x10a,(int)pFVar2,iVar1);
  return;
}
