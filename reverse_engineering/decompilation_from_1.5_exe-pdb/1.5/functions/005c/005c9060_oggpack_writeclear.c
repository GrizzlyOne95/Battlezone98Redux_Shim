/*
 * Entry: 005c9060
 * Name: oggpack_writeclear
 * Namespace: Global
 * Signature: undefined oggpack_writeclear()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_writeclear */

void __cdecl oggpack_writeclear(undefined4 *param_1)

{
  if ((void *)param_1[2] != (void *)0x0) {
    free((void *)param_1[2]);
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  return;
}
