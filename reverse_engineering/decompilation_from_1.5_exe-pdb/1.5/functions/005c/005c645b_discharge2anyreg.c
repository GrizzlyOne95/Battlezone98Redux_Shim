/*
 * Entry: 005c645b
 * Name: discharge2anyreg
 * Namespace: Global
 * Signature: void discharge2anyreg(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl discharge2anyreg(FuncState *param_1,expdesc *param_2)

{
  int *in_EAX;
  FuncState *in_ECX;
  FuncState *unaff_EBX;
  int unaff_ESI;
  expdesc *unaff_EDI;
  
  if (*in_EAX != 0xc) {
    luaK_reserveregs(in_ECX,1);
    discharge2reg(unaff_EBX,unaff_EDI,unaff_ESI);
  }
  return;
}
