/*
 * Entry: 005c7e10
 * Name: ogg_stream_clear
 * Namespace: Global
 * Signature: undefined ogg_stream_clear()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_clear */

undefined4 __cdecl ogg_stream_clear(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if ((void *)*param_1 != (void *)0x0) {
      free((void *)*param_1);
    }
    if ((void *)param_1[4] != (void *)0x0) {
      free((void *)param_1[4]);
    }
    if ((void *)param_1[5] != (void *)0x0) {
      free((void *)param_1[5]);
    }
    memset(param_1,0,0x168);
  }
  return 0;
}
