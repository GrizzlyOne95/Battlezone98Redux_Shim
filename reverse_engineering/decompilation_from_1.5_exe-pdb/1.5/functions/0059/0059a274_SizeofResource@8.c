/*
 * Entry: 0059a274
 * Name: _SizeofResource@8
 * Namespace: Global
 * Signature: DWORD _SizeofResource@8(HMODULE hModule, HRSRC hResInfo)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _SizeofResource_8(HMODULE hModule,HRSRC hResInfo)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a274. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = SizeofResource(hModule,hResInfo);
  return DVar1;
}
