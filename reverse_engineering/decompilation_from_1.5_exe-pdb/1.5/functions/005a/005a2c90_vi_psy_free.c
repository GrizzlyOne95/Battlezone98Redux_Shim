/*
 * Entry: 005a2c90
 * Name: _vi_psy_free
 * Namespace: Global
 * Signature: void _vi_psy_free(vorbis_info_psy * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _vi_psy_free(vorbis_info_psy *param_1)

{
  if (param_1 != (vorbis_info_psy *)0x0) {
    memset(param_1,0,0x208);
    free(param_1);
  }
  return;
}
