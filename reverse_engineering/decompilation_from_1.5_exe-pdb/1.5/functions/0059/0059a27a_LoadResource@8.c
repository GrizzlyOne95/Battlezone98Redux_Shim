/*
 * Entry: 0059a27a
 * Name: _LoadResource@8
 * Namespace: Global
 * Signature: HGLOBAL _LoadResource@8(HMODULE hModule, HRSRC hResInfo)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HGLOBAL _LoadResource_8(HMODULE hModule,HRSRC hResInfo)

{
  HGLOBAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a27a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LoadResource(hModule,hResInfo);
  return pvVar1;
}
