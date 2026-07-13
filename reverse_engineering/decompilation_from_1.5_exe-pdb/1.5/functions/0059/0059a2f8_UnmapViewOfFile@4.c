/*
 * Entry: 0059a2f8
 * Name: _UnmapViewOfFile@4
 * Namespace: Global
 * Signature: BOOL _UnmapViewOfFile@4(LPCVOID lpBaseAddress)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _UnmapViewOfFile_4(LPCVOID lpBaseAddress)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = UnmapViewOfFile(lpBaseAddress);
  return BVar1;
}
