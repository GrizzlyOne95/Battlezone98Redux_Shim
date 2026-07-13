/*
 * Entry: 004a0b66
 * Name: stdext::hash_value<unsigned_int>
 * Namespace: stdext
 * Signature: uint hash_value<unsigned_int>(uint * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl stdext::hash_value<unsigned_int>(uint *param_1)

{
  return *param_1 ^ 0xdeadbeef;
}
