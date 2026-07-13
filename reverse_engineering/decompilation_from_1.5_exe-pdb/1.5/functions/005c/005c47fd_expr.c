/*
 * Entry: 005c47fd
 * Name: expr
 * Namespace: Global
 * Signature: void expr(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl expr(LexState *param_1,expdesc *param_2)

{
  subexpr(param_1,param_2,0);
  return;
}
