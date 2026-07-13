/*
 * Entry: 005c67f5
 * Name: luaK_goiftrue
 * Namespace: Global
 * Signature: void luaK_goiftrue(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_goiftrue(FuncState *param_1,expdesc *param_2)

{
  expkind eVar1;
  int iVar2;
  int unaff_ESI;
  expdesc *unaff_EDI;
  
  luaK_dischargevars(param_1,param_2);
  eVar1 = param_2->k;
  if (eVar1 == VTRUE) {
LAB_005c6836:
    iVar2 = -1;
  }
  else {
    if (3 < (int)eVar1) {
      if ((int)eVar1 < 6) goto LAB_005c6836;
      if (eVar1 == VJMP) {
        invertjump(param_1,unaff_EDI);
        iVar2 = (param_2->u).s.info;
        goto LAB_005c6839;
      }
    }
    iVar2 = jumponcond((FuncState *)0x0,unaff_EDI,unaff_ESI);
  }
LAB_005c6839:
  luaK_concat(param_1,&param_2->f,iVar2);
  luaK_patchtohere(param_1,param_2->t);
  param_2->t = -1;
  return;
}
