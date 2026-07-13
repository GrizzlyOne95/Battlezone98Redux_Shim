/*
 * Entry: 004c8fa9
 * Name: Clamp<long>
 * Namespace: Global
 * Signature: long Clamp<long>(long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Clamp<long>(long param_1,long param_2,long param_3)

{
  if (param_1 < param_2) {
    return param_2;
  }
  if (param_3 < param_1) {
    param_1 = param_3;
  }
  return param_1;
}
