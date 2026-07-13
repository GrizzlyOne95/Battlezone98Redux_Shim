/*
 * Entry: 0059a2d4
 * Name: _FindFirstFileA@8
 * Namespace: Global
 * Signature: HANDLE _FindFirstFileA@8(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _FindFirstFileA_8(LPCSTR lpFileName,LPWIN32_FIND_DATAA lpFindFileData)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = FindFirstFileA(lpFileName,lpFindFileData);
  return pvVar1;
}
