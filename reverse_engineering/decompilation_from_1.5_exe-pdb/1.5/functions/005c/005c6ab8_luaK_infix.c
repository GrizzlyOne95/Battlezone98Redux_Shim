/*
 * Entry: 005c6ab8
 * Name: luaK_infix
 * Namespace: Global
 * Signature: void luaK_infix(FuncState * param_1, BinOpr param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_infix(FuncState *param_1,BinOpr param_2,expdesc *param_3)

{
  int iVar1;
  expdesc *unaff_EBP;
  
  if (-1 < (int)param_2) {
    if ((int)param_2 < 6) {
      iVar1 = isnumeral(unaff_EBP);
      if (iVar1 != 0) {
        return;
      }
    }
    else {
      if (param_2 == OPR_CONCAT) {
        luaK_exp2nextreg(param_1,param_3);
        return;
      }
      if (param_2 == OPR_AND) {
        luaK_goiftrue(param_1,param_3);
        return;
      }
      if (param_2 == OPR_OR) {
        luaK_goiffalse(param_1,(expdesc *)0xe);
        return;
      }
    }
  }
  luaK_exp2RK(param_1,param_3);
  return;
}
