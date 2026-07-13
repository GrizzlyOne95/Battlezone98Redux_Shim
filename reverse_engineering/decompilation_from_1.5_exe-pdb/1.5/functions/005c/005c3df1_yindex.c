/*
 * Entry: 005c3df1
 * Name: yindex
 * Namespace: Global
 * Signature: void yindex(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl yindex(LexState *param_1,expdesc *param_2)

{
  LexState *unaff_ESI;
  
  luaX_next(unaff_ESI);
  subexpr(unaff_ESI,(expdesc *)param_1,0);
  luaK_exp2val(unaff_ESI->fs,(expdesc *)param_1);
  checknext(param_1,(int)param_2);
  return;
}
