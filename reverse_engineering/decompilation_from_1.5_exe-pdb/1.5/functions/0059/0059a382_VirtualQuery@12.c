/*
 * Entry: 0059a382
 * Name: _VirtualQuery@12
 * Namespace: Global
 * Signature: SIZE_T _VirtualQuery@12(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SIZE_T _VirtualQuery_12(LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength)

{
  SIZE_T SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a382. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = VirtualQuery(lpAddress,lpBuffer,dwLength);
  return SVar1;
}
