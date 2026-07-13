/*
 * Entry: 0059a304
 * Name: _CreateFileMappingA@24
 * Namespace: Global
 * Signature: HANDLE _CreateFileMappingA@24(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _CreateFileMappingA_24
                 (HANDLE hFile,LPSECURITY_ATTRIBUTES lpFileMappingAttributes,DWORD flProtect,
                 DWORD dwMaximumSizeHigh,DWORD dwMaximumSizeLow,LPCSTR lpName)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a304. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = CreateFileMappingA(hFile,lpFileMappingAttributes,flProtect,dwMaximumSizeHigh,
                              dwMaximumSizeLow,lpName);
  return pvVar1;
}
