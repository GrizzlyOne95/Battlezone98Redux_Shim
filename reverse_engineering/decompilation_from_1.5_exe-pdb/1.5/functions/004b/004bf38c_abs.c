/*
 * Entry: 004bf38c
 * Name: abs
 * Namespace: Global
 * Signature: long abs(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl abs(long param_1)

{
  return (param_1 ^ param_1 >> 0x1f) - (param_1 >> 0x1f);
}
