/*
 * Entry: 0059a2fe
 * Name: _MapViewOfFile@20
 * Namespace: Global
 * Signature: LPVOID _MapViewOfFile@20(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LPVOID _MapViewOfFile_20(HANDLE hFileMappingObject,DWORD dwDesiredAccess,DWORD dwFileOffsetHigh,
                        DWORD dwFileOffsetLow,SIZE_T dwNumberOfBytesToMap)

{
  LPVOID pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = MapViewOfFile(hFileMappingObject,dwDesiredAccess,dwFileOffsetHigh,dwFileOffsetLow,
                         dwNumberOfBytesToMap);
  return pvVar1;
}
