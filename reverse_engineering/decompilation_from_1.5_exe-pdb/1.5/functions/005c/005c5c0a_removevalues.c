/*
 * Entry: 005c5c0a
 * Name: removevalues
 * Namespace: Global
 * Signature: void removevalues(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl removevalues(FuncState *param_1,int param_2)

{
  int in_EAX;
  FuncState *unaff_ESI;
  int unaff_retaddr;
  
  while (in_EAX != -1) {
    patchtestreg(unaff_ESI,unaff_retaddr,(int)param_1);
    in_EAX = getjump(unaff_ESI,unaff_retaddr);
  }
  return;
}
