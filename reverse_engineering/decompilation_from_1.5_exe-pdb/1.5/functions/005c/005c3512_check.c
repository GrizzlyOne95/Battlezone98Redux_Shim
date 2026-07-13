/*
 * Entry: 005c3512
 * Name: check
 * Namespace: Global
 * Signature: void check(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl check(LexState *param_1,int param_2)

{
  LexState *in_EAX;
  int in_ECX;
  int unaff_ESI;
  
  if (*(LexState **)(in_ECX + 0x10) != in_EAX) {
    error_expected(in_EAX,unaff_ESI);
  }
  return;
}
