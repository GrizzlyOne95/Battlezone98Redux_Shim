/*
 * Entry: 005a2c60
 * Name: _vi_gpsy_free
 * Namespace: Global
 * Signature: void _vi_gpsy_free(vorbis_info_psy_global * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _vi_gpsy_free(vorbis_info_psy_global *param_1)

{
  if (param_1 != (vorbis_info_psy_global *)0x0) {
    memset(param_1,0,0x1ec);
    free(param_1);
  }
  return;
}
