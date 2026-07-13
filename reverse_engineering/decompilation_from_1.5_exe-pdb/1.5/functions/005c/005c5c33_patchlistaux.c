/*
 * Entry: 005c5c33
 * Name: patchlistaux
 * Namespace: Global
 * Signature: void patchlistaux(FuncState * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl patchlistaux(FuncState *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int in_EAX;
  FuncState *unaff_EBX;
  int unaff_ESI;
  int unaff_EDI;
  
  while (in_EAX != -1) {
    in_EAX = getjump(unaff_EBX,unaff_EDI);
    patchtestreg(unaff_EBX,unaff_EDI,unaff_ESI);
    fixjump(unaff_EBX,unaff_EDI,unaff_ESI);
  }
  return;
}
