/*
 * Entry: 0054ccac
 * Name: movie_initialize
 * Namespace: Global
 * Signature: int movie_initialize(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl movie_initialize(void)

{
  MCIERROR MVar1;
  
  MVar1 = mciSendStringA("open AVIVideo",(LPSTR)0x0,0,(HWND)0x0);
  return (uint)(MVar1 == 0);
}
