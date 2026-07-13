/*
 * Entry: 004c186f
 * Name: min<long>
 * Namespace: Global
 * Signature: long min<long>(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl min<long>(long param_1,long param_2)

{
  if (param_2 <= param_1) {
    param_1 = param_2;
  }
  return param_1;
}
