/*
 * Entry: 005c50f1
 * Name: funcname
 * Namespace: Global
 * Signature: int funcname(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl funcname(LexState *param_1,expdesc *param_2)

{
  expdesc *unaff_EBX;
  int unaff_ESI;
  LexState *unaff_EDI;
  bool bVar1;
  
  singlevar(unaff_EDI,unaff_EBX);
  while (*(int *)(unaff_ESI + 0x10) == 0x2e) {
    field(param_1,(expdesc *)unaff_EDI);
  }
  bVar1 = *(int *)(unaff_ESI + 0x10) == 0x3a;
  if (bVar1) {
    field(param_1,(expdesc *)unaff_EDI);
  }
  return (uint)bVar1;
}
