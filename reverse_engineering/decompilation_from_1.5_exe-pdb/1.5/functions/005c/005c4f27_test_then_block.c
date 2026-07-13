/*
 * Entry: 005c4f27
 * Name: test_then_block
 * Namespace: Global
 * Signature: int test_then_block(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl test_then_block(LexState *param_1)

{
  LexState *in_EAX;
  int iVar1;
  int unaff_ESI;
  LexState *unaff_EDI;
  
  luaX_next(in_EAX);
  iVar1 = cond(unaff_EDI);
  checknext(unaff_EDI,unaff_ESI);
  block(unaff_EDI);
  return iVar1;
}
