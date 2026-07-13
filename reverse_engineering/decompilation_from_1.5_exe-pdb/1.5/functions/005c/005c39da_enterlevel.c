/*
 * Entry: 005c39da
 * Name: enterlevel
 * Namespace: Global
 * Signature: void enterlevel(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl enterlevel(LexState *param_1)

{
  ushort *puVar1;
  LexState *in_ECX;
  
  puVar1 = &in_ECX->L->nCcalls;
  *puVar1 = *puVar1 + 1;
  if (200 < in_ECX->L->nCcalls) {
    luaX_lexerror(in_ECX,"chunk has too many syntax levels",0);
  }
  return;
}
