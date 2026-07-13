/*
 * Entry: 00546d17
 * Name: crc32game
 * Namespace: Global
 * Signature: ulong crc32game(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl crc32game(long param_1)

{
  ulong uVar1;
  
  uVar1 = crc32check("check.odf",param_1);
  return uVar1;
}
