/*
 * Entry: 005c3470
 * Name: anchor_token
 * Namespace: Global
 * Signature: void anchor_token(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl anchor_token(LexState *param_1)

{
  int iVar1;
  TString *pTVar2;
  LexState *in_ECX;
  
  iVar1 = (in_ECX->t).token;
  if ((iVar1 == 0x11d) || (iVar1 == 0x11e)) {
    pTVar2 = (in_ECX->t).seminfo.ts;
    luaX_newstring(in_ECX,(char *)(pTVar2 + 1),(pTVar2->tsv).len);
  }
  return;
}
