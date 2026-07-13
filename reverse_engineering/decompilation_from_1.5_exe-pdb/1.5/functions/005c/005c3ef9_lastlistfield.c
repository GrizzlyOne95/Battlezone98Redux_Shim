/*
 * Entry: 005c3ef9
 * Name: lastlistfield
 * Namespace: Global
 * Signature: void lastlistfield(FuncState * param_1, ConsControl * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lastlistfield(FuncState *param_1,ConsControl *param_2)

{
  expkind eVar1;
  expdesc *unaff_ESI;
  FuncState *unaff_EDI;
  
  if (unaff_ESI[1].u.s.aux != 0) {
    eVar1 = unaff_ESI->k;
    if ((eVar1 != VCALL) && (eVar1 != VVARARG)) {
      if (eVar1 != VVOID) {
        luaK_exp2nextreg(unaff_EDI,unaff_ESI);
      }
      luaK_setlist(unaff_EDI,*(int *)(unaff_ESI[1].k + VGLOBAL),unaff_ESI[1].u.s.info,
                   unaff_ESI[1].u.s.aux);
      return;
    }
    luaK_setreturns(unaff_EDI,unaff_ESI,-1);
    luaK_setlist(unaff_EDI,*(int *)(unaff_ESI[1].k + VGLOBAL),unaff_ESI[1].u.s.info,-1);
    unaff_ESI[1].u.s.info = unaff_ESI[1].u.s.info + -1;
  }
  return;
}
