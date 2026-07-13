/*
 * Entry: 005c8ec0
 * Name: oggpack_writeinit
 * Namespace: Global
 * Signature: undefined oggpack_writeinit()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_writeinit */

void __cdecl oggpack_writeinit(undefined4 *param_1)

{
  undefined1 *puVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  puVar1 = malloc(0x100);
  param_1[2] = puVar1;
  param_1[3] = puVar1;
  *puVar1 = 0;
  param_1[4] = 0x100;
  return;
}
