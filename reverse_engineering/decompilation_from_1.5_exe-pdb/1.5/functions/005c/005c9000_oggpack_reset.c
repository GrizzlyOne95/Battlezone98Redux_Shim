/*
 * Entry: 005c9000
 * Name: oggpack_reset
 * Namespace: Global
 * Signature: undefined oggpack_reset()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_reset */

void __cdecl oggpack_reset(undefined4 *param_1)

{
  if (param_1[3] != 0) {
    param_1[3] = (undefined1 *)param_1[2];
    *(undefined1 *)param_1[2] = 0;
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}
