/*
 * Entry: 005c4bd0
 * Name: exp1
 * Namespace: Global
 * Signature: int exp1(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl exp1(LexState *param_1)

{
  LexState *unaff_ESI;
  expdesc local_1c;
  
  expr(unaff_ESI,&local_1c);
  luaK_exp2nextreg(unaff_ESI->fs,&local_1c);
  return local_1c.k;
}
