/*
 * Entry: 005c8be0
 * Name: ogg_sync_reset
 * Namespace: Global
 * Signature: undefined ogg_sync_reset()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_sync_reset */

undefined4 __cdecl ogg_sync_reset(int param_1)

{
  if (*(int *)(param_1 + 4) < 0) {
    return 0xffffffff;
  }
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  return 0;
}
