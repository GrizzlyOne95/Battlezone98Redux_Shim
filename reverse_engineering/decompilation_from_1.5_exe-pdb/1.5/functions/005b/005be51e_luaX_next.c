/*
 * Entry: 005be51e
 * Name: luaX_next
 * Namespace: Global
 * Signature: void luaX_next(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaX_next(LexState *param_1)

{
  Token *pTVar1;
  int iVar2;
  SemInfo *unaff_ESI;
  
  param_1->lastline = param_1->linenumber;
  pTVar1 = &param_1->lookahead;
  if (pTVar1->token != 0x11f) {
    (param_1->t).token = pTVar1->token;
    *(undefined4 *)&(param_1->t).field_0x4 = *(undefined4 *)&(param_1->lookahead).field_0x4;
    (param_1->t).seminfo.ts = (param_1->lookahead).seminfo.ts;
    *(undefined4 *)((int)&(param_1->t).seminfo + 4) =
         *(undefined4 *)((int)&(param_1->lookahead).seminfo + 4);
    pTVar1->token = 0x11f;
    return;
  }
  iVar2 = llex((LexState *)&(param_1->t).seminfo,unaff_ESI);
  (param_1->t).token = iVar2;
  return;
}
