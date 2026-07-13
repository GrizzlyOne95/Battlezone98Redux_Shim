/*
 * Entry: 0059a322
 * Name: _DeleteFileA@4
 * Namespace: Global
 * Signature: BOOL _DeleteFileA@4(LPCSTR lpFileName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _DeleteFileA_4(LPCSTR lpFileName)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a322. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteFileA(lpFileName);
  return BVar1;
}
