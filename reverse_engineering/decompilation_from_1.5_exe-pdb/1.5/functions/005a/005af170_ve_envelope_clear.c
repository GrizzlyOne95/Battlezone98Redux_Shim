/*
 * Entry: 005af170
 * Name: _ve_envelope_clear
 * Namespace: Global
 * Signature: void _ve_envelope_clear(envelope_lookup * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _ve_envelope_clear(envelope_lookup *param_1)

{
  int iVar1;
  float **ppfVar2;
  
  mdct_clear(&param_1->mdct);
  ppfVar2 = &param_1->band[0].window;
  iVar1 = 7;
  do {
    free(*ppfVar2);
    ppfVar2 = ppfVar2 + 4;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  free(param_1->mdct_win);
  free(param_1->filter);
  free(param_1->mark);
  memset(param_1,0,0xb4);
  return;
}
