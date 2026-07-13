/*
 * Entry: 004d0713
 * Name: max<long>
 * Namespace: Global
 * Signature: long max<long>(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl max<long>(long param_1,long param_2)

{
  if (param_1 < param_2) {
    param_1 = param_2;
  }
  return param_1;
}
