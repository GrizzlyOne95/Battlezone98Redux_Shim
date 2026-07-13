/*
 * Entry: 005c5f27
 * Name: luaK_setoneret
 * Namespace: Global
 * Signature: void luaK_setoneret(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_setoneret(FuncState *param_1,expdesc *param_2)

{
  uint *puVar1;
  
  if (param_2->k == VCALL) {
    param_2->k = VNONRELOC;
    (param_2->u).s.info = param_1->f->code[(param_2->u).s.info] >> 6 & 0xff;
    return;
  }
  if (param_2->k == VVARARG) {
    puVar1 = param_1->f->code + (param_2->u).s.info;
    *puVar1 = *puVar1 & 0x7fffff | 0x1000000;
    param_2->k = VRELOCABLE;
  }
  return;
}
