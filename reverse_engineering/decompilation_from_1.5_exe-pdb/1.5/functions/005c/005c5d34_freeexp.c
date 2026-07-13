/*
 * Entry: 005c5d34
 * Name: freeexp
 * Namespace: Global
 * Signature: void freeexp(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl freeexp(FuncState *param_1,expdesc *param_2)

{
  int *in_EAX;
  int unaff_retaddr;
  
  if (*in_EAX == 0xc) {
    freereg((FuncState *)in_EAX[2],unaff_retaddr);
  }
  return;
}
