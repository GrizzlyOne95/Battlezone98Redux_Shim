/*
 * Entry: 0054d001
 * Name: movie_play
 * Namespace: Global
 * Signature: int movie_play(int param_1, tagRECT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl movie_play(int param_1,tagRECT *param_2)

{
  MCIERROR MVar1;
  char *_Format;
  char local_240 [256];
  char local_140 [256];
  CHAR local_40 [56];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  mci_movie.mode = param_1;
  if (param_2 == (tagRECT *)0x0) {
    sprintf(local_140,"put %s destination",mci_movie.aliasName);
    mci_movie.rect.left = 0;
    mci_movie.rect.top = 0;
    mci_movie.rect.right = 0x27f;
    mci_movie.rect.bottom = 0x1df;
  }
  else {
    mci_movie.rect.left = param_2->left;
    mci_movie.rect.top = param_2->top;
    mci_movie.rect.right = param_2->right;
    mci_movie.rect.bottom = param_2->bottom;
    sprintf(local_140,"put %s destination at %d %d %d %d",mci_movie.aliasName,mci_movie.rect.left,
            mci_movie.rect.top,mci_movie.rect.right - mci_movie.rect.left,
            mci_movie.rect.bottom - mci_movie.rect.top);
  }
  MVar1 = mciSendStringA(local_140,local_40,0x37,(HWND)0x0);
  if (MVar1 == 0) {
    sprintf(local_140,"window %s handle %d",mci_movie.aliasName,shell_hwnd);
    MVar1 = mciSendStringA(local_140,local_40,0x37,(HWND)0x0);
    if (MVar1 == 0) {
      if ((param_1 == 0) || (param_1 == 1)) {
        sprintf(local_140,"play %s notify",mci_movie.aliasName);
      }
      MVar1 = mciSendStringA(local_140,local_40,0x37,(HWND)shell_hwnd);
      if (MVar1 == 0) {
        isMCIPlaying = 1;
        return 1;
      }
      _Format = "sfxPlayMCI(): %s  - Error!";
    }
    else {
      _Format = "movie_play (): %s  - Error!";
    }
  }
  else {
    _Format = "movie_play(): %s  - Error!";
  }
  sprintf(local_240,_Format,local_140);
  return 0;
}
