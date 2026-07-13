/*
 * Entry: 005c659c
 * Name: luaK_exp2anyreg
 * Namespace: Global
 * Signature: int luaK_exp2anyreg(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaK_exp2anyreg(FuncState *param_1,expdesc *param_2)

{
  FuncState *pFVar1;
  int unaff_ESI;
  expdesc *unaff_EDI;
  
  luaK_dischargevars(param_1,param_2);
  if (param_2->k == VNONRELOC) {
    pFVar1 = (FuncState *)(param_2->u).s.info;
    if (param_2->t == param_2->f) {
      return (int)pFVar1;
    }
    if ((int)(uint)param_1->nactvar <= (int)pFVar1) {
      exp2reg(pFVar1,unaff_EDI,unaff_ESI);
      goto LAB_005c65db;
    }
  }
  luaK_exp2nextreg(param_1,param_2);
LAB_005c65db:
  return (param_2->u).s.info;
}
