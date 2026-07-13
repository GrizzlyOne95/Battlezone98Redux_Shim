/*
 * Entry: 005c5ea8
 * Name: luaK_setreturns
 * Namespace: Global
 * Signature: void luaK_setreturns(FuncState * param_1, expdesc * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_setreturns(FuncState *param_1,expdesc *param_2,int param_3)

{
  uint *puVar1;
  
  if (param_2->k == VCALL) {
    puVar1 = param_1->f->code + (param_2->u).s.info;
    *puVar1 = *puVar1 ^ ((param_3 + 1) * 0x4000 ^ *puVar1) & 0x7fc000;
    return;
  }
  if (param_2->k == VVARARG) {
    puVar1 = param_1->f->code + (param_2->u).s.info;
    *puVar1 = (param_3 + 1) * 0x800000 ^ *puVar1 & 0x7fffff;
    puVar1 = param_1->f->code + (param_2->u).s.info;
    *puVar1 = *puVar1 ^ (param_1->freereg << 6 ^ *puVar1) & 0x3fc0;
    luaK_reserveregs(param_1,1);
  }
  return;
}
