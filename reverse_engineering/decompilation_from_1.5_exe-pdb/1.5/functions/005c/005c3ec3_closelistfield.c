/*
 * Entry: 005c3ec3
 * Name: closelistfield
 * Namespace: Global
 * Signature: void closelistfield(FuncState * param_1, ConsControl * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl closelistfield(FuncState *param_1,ConsControl *param_2)

{
  expdesc *unaff_ESI;
  
  if (unaff_ESI->k != VVOID) {
    luaK_exp2nextreg(param_1,unaff_ESI);
    unaff_ESI->k = VVOID;
    if (unaff_ESI[1].u.s.aux == 0x32) {
      luaK_setlist(param_1,*(int *)(unaff_ESI[1].k + VGLOBAL),unaff_ESI[1].u.s.info,0x32);
      unaff_ESI[1].u.s.aux = 0;
    }
  }
  return;
}
