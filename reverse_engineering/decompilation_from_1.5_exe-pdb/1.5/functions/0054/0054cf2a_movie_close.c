/*
 * Entry: 0054cf2a
 * Name: movie_close
 * Namespace: Global
 * Signature: void movie_close(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl movie_close(void)

{
  MCIERROR MVar1;
  char local_240 [256];
  char local_140 [256];
  CHAR local_40 [56];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (isMCIPlaying != 0) {
    sprintf(local_140,"close %s wait",mci_movie.aliasName);
    MVar1 = mciSendStringA(local_140,local_40,0x37,(HWND)0x0);
    if (MVar1 != 0) {
      sprintf(local_240,"movie_close(): %s  - Error!",local_140);
    }
    isMCIPlaying = 0;
  }
  return;
}
