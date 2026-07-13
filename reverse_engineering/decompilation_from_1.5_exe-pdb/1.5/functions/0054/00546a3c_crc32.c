/*
 * Entry: 00546a3c
 * Name: crc32
 * Namespace: Global
 * Signature: ulong crc32(uchar * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl crc32(uchar *param_1,ulong param_2)

{
  ulong uVar1;
  
  uVar1 = crc32seed(param_1,param_2,0xffffffff);
  return uVar1;
}
