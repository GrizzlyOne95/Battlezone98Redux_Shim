/*
 * Entry: 005c5c73
 * Name: dischargejpc
 * Namespace: Global
 * Signature: void dischargejpc(FuncState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dischargejpc(FuncState *param_1)

{
  int unaff_ESI;
  int unaff_retaddr;
  
  patchlistaux(*(FuncState **)(unaff_ESI + 0x18),0xff,(int)*(FuncState **)(unaff_ESI + 0x18),
               unaff_retaddr,(int)param_1);
  *(undefined4 *)(unaff_ESI + 0x20) = 0xffffffff;
  return;
}
