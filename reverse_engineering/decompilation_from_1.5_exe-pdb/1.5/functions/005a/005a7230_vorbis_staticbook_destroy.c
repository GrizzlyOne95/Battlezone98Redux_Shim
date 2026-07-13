/*
 * Entry: 005a7230
 * Name: vorbis_staticbook_destroy
 * Namespace: Global
 * Signature: void vorbis_staticbook_destroy(static_codebook * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_staticbook_destroy(static_codebook *param_1)

{
  if (param_1->allocedp != 0) {
    if (param_1->quantlist != (long *)0x0) {
      free(param_1->quantlist);
    }
    if (param_1->lengthlist != (long *)0x0) {
      free(param_1->lengthlist);
    }
    param_1->dim = 0;
    param_1->entries = 0;
    param_1->lengthlist = (long *)0x0;
    param_1->maptype = 0;
    param_1->q_min = 0;
    param_1->q_delta = 0;
    param_1->q_quant = 0;
    param_1->q_sequencep = 0;
    param_1->quantlist = (long *)0x0;
    param_1->allocedp = 0;
    free(param_1);
  }
  return;
}
