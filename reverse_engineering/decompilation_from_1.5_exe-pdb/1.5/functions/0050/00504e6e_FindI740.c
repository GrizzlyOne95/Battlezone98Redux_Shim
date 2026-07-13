/*
 * Entry: 00504e6e
 * Name: FindI740
 * Namespace: Global
 * Signature: int FindI740(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FindI740(void)

{
  HANDLE hObject;
  
  hObject = CreateFileA("\\\\.\\GFX",0,0,(LPSECURITY_ATTRIBUTES)0x0,0,0x4000000,(HANDLE)0x0);
  CloseHandle(hObject);
  return (uint)(hObject != (HANDLE)0xffffffff);
}
