/*
 * Entry: 005afaa0
 * Name: _ve_envelope_shift
 * Namespace: Global
 * Signature: void _ve_envelope_shift(envelope_lookup * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _ve_envelope_shift(envelope_lookup *param_1,long param_2)

{
  int iVar1;
  
  iVar1 = param_2 / param_1->searchstep;
  memmove(param_1->mark,param_1->mark + iVar1,
          (param_1->current / param_1->searchstep - iVar1) * 4 + 8);
  param_1->current = param_1->current - param_2;
  if (-1 < param_1->curmark) {
    param_1->curmark = param_1->curmark - param_2;
  }
  param_1->cursor = param_1->cursor - param_2;
  return;
}
