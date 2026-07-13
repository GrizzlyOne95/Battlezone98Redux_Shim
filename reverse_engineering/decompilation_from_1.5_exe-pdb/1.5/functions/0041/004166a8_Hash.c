/*
 * Entry: 004166a8
 * Name: Hash
 * Namespace: Global
 * Signature: uint Hash(uchar param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl Hash(uchar param_1,uint param_2)

{
  return (param_1 ^ param_2) * 0x1000193;
}
