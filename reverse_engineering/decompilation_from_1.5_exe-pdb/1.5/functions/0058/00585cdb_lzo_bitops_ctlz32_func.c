/*
 * Entry: 00585cdb
 * Name: lzo_bitops_ctlz32_func
 * Namespace: Global
 * Signature: uint lzo_bitops_ctlz32_func(ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl lzo_bitops_ctlz32_func(ulong param_1)

{
  uint uVar1;
  
  uVar1 = 0x1f;
  if (param_1 != 0) {
    for (; param_1 >> uVar1 == 0; uVar1 = uVar1 - 1) {
    }
  }
  return uVar1 ^ 0x1f;
}
