/*
 * Entry: 005c34fb
 * Name: testnext
 * Namespace: Global
 * Signature: int testnext(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl testnext(LexState *param_1,int param_2)

{
  LexState *in_EAX;
  
  if ((LexState *)(in_EAX->t).token == param_1) {
    luaX_next(in_EAX);
    return 1;
  }
  return 0;
}
