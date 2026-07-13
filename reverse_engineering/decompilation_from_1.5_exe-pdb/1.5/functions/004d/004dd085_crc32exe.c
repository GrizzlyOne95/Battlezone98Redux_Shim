/*
 * Entry: 004dd085
 * Name: crc32exe
 * Namespace: Global
 * Signature: ulong crc32exe(ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl crc32exe(ulong param_1)

{
  ulong uVar1;
  
  uVar1 = crc32seed((uchar *)AI_Init,0x184ca0,param_1);
  return uVar1;
}
