/*
 * Entry: 0059a280
 * Name: _FindResourceA@12
 * Namespace: Global
 * Signature: HRSRC _FindResourceA@12(HMODULE hModule, LPCSTR lpName, LPCSTR lpType)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HRSRC _FindResourceA_12(HMODULE hModule,LPCSTR lpName,LPCSTR lpType)

{
  HRSRC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a280. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = FindResourceA(hModule,lpName,lpType);
  return pHVar1;
}
