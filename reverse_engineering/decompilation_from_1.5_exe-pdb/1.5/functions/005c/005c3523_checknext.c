/*
 * Entry: 005c3523
 * Name: checknext
 * Namespace: Global
 * Signature: void checknext(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl checknext(LexState *param_1,int param_2)

{
  LexState *in_EAX;
  LexState *in_ECX;
  int unaff_ESI;
  
  if ((LexState *)(in_ECX->t).token != in_EAX) {
    error_expected(in_EAX,unaff_ESI);
  }
  luaX_next(in_ECX);
  return;
}
