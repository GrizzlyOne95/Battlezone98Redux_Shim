/*
 * Entry: 0048ab44
 * Name: stdext::hash_value<unsigned_long>
 * Namespace: stdext
 * Signature: uint hash_value<unsigned_long>(ulong * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl stdext::hash_value<unsigned_long>(ulong *param_1)

{
  return *param_1 ^ 0xdeadbeef;
}
