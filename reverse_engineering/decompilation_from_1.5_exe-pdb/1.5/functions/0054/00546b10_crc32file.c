/*
 * Entry: 00546b10
 * Name: crc32file
 * Namespace: Global
 * Signature: ulong crc32file(char * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl crc32file(char *param_1,ulong param_2)

{
  HANDLE hFile;
  DWORD DVar1;
  HANDLE hFileMappingObject;
  uchar *lpBaseAddress;
  
  hFile = CreateFileA(param_1,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
  if (hFile != (HANDLE)0xffffffff) {
    DVar1 = GetFileSize(hFile,(LPDWORD)0x0);
    if ((DVar1 != 0xffffffff) &&
       (hFileMappingObject = CreateFileMappingA(hFile,(LPSECURITY_ATTRIBUTES)0x0,2,0,0,(LPCSTR)0x0),
       hFileMappingObject != (HANDLE)0x0)) {
      lpBaseAddress = MapViewOfFile(hFileMappingObject,4,0,0,0);
      if (lpBaseAddress != (uchar *)0x0) {
        param_2 = crc32seed(lpBaseAddress,DVar1,param_2);
        UnmapViewOfFile(lpBaseAddress);
      }
      CloseHandle(hFileMappingObject);
    }
    CloseHandle(hFile);
  }
  return param_2;
}
