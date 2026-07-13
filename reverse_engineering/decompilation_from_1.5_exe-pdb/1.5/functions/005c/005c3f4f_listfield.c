/*
 * Entry: 005c3f4f
 * Name: listfield
 * Namespace: Global
 * Signature: void listfield(LexState * param_1, ConsControl * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl listfield(LexState *param_1,ConsControl *param_2)

{
  int *piVar1;
  LexState *in_EAX;
  char *unaff_ESI;
  expdesc *unaff_EDI;
  
  subexpr(in_EAX,unaff_EDI,0);
  if (0x7ffffffd < unaff_EDI[1].u.s.info) {
    errorlimit((FuncState *)0x7ffffffd,0x622394,unaff_ESI);
  }
  unaff_EDI[1].u.s.info = unaff_EDI[1].u.s.info + 1;
  piVar1 = &unaff_EDI[1].u.s.aux;
  *piVar1 = *piVar1 + 1;
  return;
}
