/*
 * Entry: 0059a2ce
 * Name: _FindNextFileA@8
 * Namespace: Global
 * Signature: BOOL _FindNextFileA@8(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _FindNextFileA_8(HANDLE hFindFile,LPWIN32_FIND_DATAA lpFindFileData)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2ce. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FindNextFileA(hFindFile,lpFindFileData);
  return BVar1;
}
