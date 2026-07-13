/*
 * Entry: 005ae860
 * Name: mdct_clear
 * Namespace: Global
 * Signature: void mdct_clear(mdct_lookup * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_clear(mdct_lookup *param_1)

{
  if (param_1 != (mdct_lookup *)0x0) {
    if (param_1->trig != (float *)0x0) {
      free(param_1->trig);
    }
    if (param_1->bitrev != (int *)0x0) {
      free(param_1->bitrev);
    }
    param_1->n = 0;
    param_1->log2n = 0;
    param_1->trig = (float *)0x0;
    param_1->bitrev = (int *)0x0;
    param_1->scale = 0.0;
  }
  return;
}
