/*
 * Entry: 005c8700
 * Name: ogg_sync_wrote
 * Namespace: Global
 * Signature: undefined ogg_sync_wrote()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_sync_wrote */

undefined4 __cdecl ogg_sync_wrote(int param_1,int param_2)

{
  if (-1 < *(int *)(param_1 + 4)) {
    param_2 = *(int *)(param_1 + 8) + param_2;
    if (param_2 <= *(int *)(param_1 + 4)) {
      *(int *)(param_1 + 8) = param_2;
      return 0;
    }
  }
  return 0xffffffff;
}
