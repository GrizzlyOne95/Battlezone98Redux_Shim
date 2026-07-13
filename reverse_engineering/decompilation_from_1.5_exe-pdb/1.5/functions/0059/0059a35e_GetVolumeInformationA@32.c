/*
 * Entry: 0059a35e
 * Name: _GetVolumeInformationA@32
 * Namespace: Global
 * Signature: BOOL _GetVolumeInformationA@32(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetVolumeInformationA_32
               (LPCSTR lpRootPathName,LPSTR lpVolumeNameBuffer,DWORD nVolumeNameSize,
               LPDWORD lpVolumeSerialNumber,LPDWORD lpMaximumComponentLength,
               LPDWORD lpFileSystemFlags,LPSTR lpFileSystemNameBuffer,DWORD nFileSystemNameSize)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a35e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetVolumeInformationA
                    (lpRootPathName,lpVolumeNameBuffer,nVolumeNameSize,lpVolumeSerialNumber,
                     lpMaximumComponentLength,lpFileSystemFlags,lpFileSystemNameBuffer,
                     nFileSystemNameSize);
  return BVar1;
}
