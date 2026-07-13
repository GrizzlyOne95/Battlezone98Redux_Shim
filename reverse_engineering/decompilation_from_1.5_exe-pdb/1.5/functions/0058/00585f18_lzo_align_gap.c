/*
 * Entry: 00585f18
 * Name: __lzo_align_gap
 * Namespace: Global
 * Signature: uint __lzo_align_gap(void * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl __lzo_align_gap(void *param_1,ulong param_2)

{
  return (((int)param_1 + (param_2 - 1)) / param_2) * param_2 - (int)param_1;
}
