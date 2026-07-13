/*
 * Entry: 00546a04
 * Name: crc32seed
 * Namespace: Global
 * Signature: ulong crc32seed(uchar * param_1, ulong param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl crc32seed(uchar *param_1,ulong param_2,ulong param_3)

{
  byte *pbVar1;
  
  pbVar1 = param_1 + param_2;
  for (; param_1 < pbVar1; param_1 = param_1 + 1) {
    param_3 = param_3 << 8 ^ crc32_table[param_3 >> 0x18 ^ (uint)*param_1];
  }
  return ~param_3;
}
