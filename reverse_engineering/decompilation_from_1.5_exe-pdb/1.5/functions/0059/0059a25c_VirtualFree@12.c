/*
 * Entry: 0059a25c
 * Name: _VirtualFree@12
 * Namespace: Global
 * Signature: BOOL _VirtualFree@12(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _VirtualFree_12(LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a25c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = VirtualFree(lpAddress,dwSize,dwFreeType);
  return BVar1;
}
