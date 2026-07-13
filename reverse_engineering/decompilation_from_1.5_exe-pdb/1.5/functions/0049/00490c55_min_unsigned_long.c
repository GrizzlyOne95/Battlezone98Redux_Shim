/*
 * Entry: 00490c55
 * Name: min<unsigned_long>
 * Namespace: Global
 * Signature: ulong min<unsigned_long>(ulong param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl min<unsigned_long>(ulong param_1,ulong param_2)

{
  if (param_2 <= param_1) {
    param_1 = param_2;
  }
  return param_1;
}
