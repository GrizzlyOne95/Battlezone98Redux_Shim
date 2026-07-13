/*
 * Entry: 005be555
 * Name: luaX_lookahead
 * Namespace: Global
 * Signature: void luaX_lookahead(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaX_lookahead(LexState *param_1)

{
  int iVar1;
  SemInfo *unaff_ESI;
  
  iVar1 = llex((LexState *)&(param_1->lookahead).seminfo,unaff_ESI);
  (param_1->lookahead).token = iVar1;
  return;
}
