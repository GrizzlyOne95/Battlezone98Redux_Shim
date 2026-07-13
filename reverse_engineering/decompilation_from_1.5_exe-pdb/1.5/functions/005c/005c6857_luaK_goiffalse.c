/*
 * Entry: 005c6857
 * Name: luaK_goiffalse
 * Namespace: Global
 * Signature: void luaK_goiffalse(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_goiffalse(FuncState *param_1,expdesc *param_2)

{
  expkind eVar1;
  expdesc *in_EAX;
  int iVar2;
  FuncState *in_ECX;
  int unaff_ESI;
  expdesc *unaff_EDI;
  
  luaK_dischargevars(in_ECX,in_EAX);
  eVar1 = in_EAX->k;
  if ((eVar1 == VNIL) || (eVar1 == VFALSE)) {
    iVar2 = -1;
  }
  else if (eVar1 == VJMP) {
    iVar2 = (in_EAX->u).s.info;
  }
  else {
    iVar2 = jumponcond((FuncState *)0x1,unaff_EDI,unaff_ESI);
  }
  luaK_concat(in_ECX,&in_EAX->t,iVar2);
  luaK_patchtohere(in_ECX,in_EAX->f);
  in_EAX->f = -1;
  return;
}
