/*
 * Entry: 005c9610
 * Name: oggpack_bytes
 * Namespace: Global
 * Signature: undefined oggpack_bytes()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_bytes */

int __cdecl oggpack_bytes(int *param_1)

{
  return ((int)(param_1[1] + 7 + (param_1[1] + 7 >> 0x1f & 7U)) >> 3) + *param_1;
}
