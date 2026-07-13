/*
 * Entry: 005c85b0
 * Name: ogg_sync_init
 * Namespace: Global
 * Signature: undefined ogg_sync_init()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_sync_init */

undefined4 __cdecl ogg_sync_init(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    param_1[1] = 0xffffffff;
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
