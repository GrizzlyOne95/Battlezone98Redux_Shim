/*
 * Entry: 0054ccc2
 * Name: movie_shutdown
 * Namespace: Global
 * Signature: void movie_shutdown(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl movie_shutdown(void)

{
  mciSendStringA("close AVIVideo",(LPSTR)0x0,0,(HWND)0x0);
  return;
}
