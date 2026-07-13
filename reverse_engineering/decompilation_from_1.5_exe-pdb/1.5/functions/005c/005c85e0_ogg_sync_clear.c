/*
 * Entry: 005c85e0
 * Name: ogg_sync_clear
 * Namespace: Global
 * Signature: undefined ogg_sync_clear()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_sync_clear */

undefined4 __cdecl ogg_sync_clear(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if ((void *)*param_1 != (void *)0x0) {
      free((void *)*param_1);
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
  }
  return 0;
}
