/*
 * Entry: 005c65e2
 * Name: luaK_exp2val
 * Namespace: Global
 * Signature: void luaK_exp2val(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_exp2val(FuncState *param_1,expdesc *param_2)

{
  if (param_2->t == param_2->f) {
    luaK_dischargevars(param_1,param_2);
  }
  else {
    luaK_exp2anyreg(param_1,param_2);
  }
  return;
}
