/*
 * Entry: 0059a262
 * Name: _VirtualAlloc@16
 * Namespace: Global
 * Signature: LPVOID _VirtualAlloc@16(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LPVOID _VirtualAlloc_16(LPVOID lpAddress,SIZE_T dwSize,DWORD flAllocationType,DWORD flProtect)

{
  LPVOID pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a262. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = VirtualAlloc(lpAddress,dwSize,flAllocationType,flProtect);
  return pvVar1;
}
