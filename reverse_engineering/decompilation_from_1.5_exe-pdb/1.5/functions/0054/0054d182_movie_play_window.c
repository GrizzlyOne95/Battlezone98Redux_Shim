/*
 * Entry: 0054d182
 * Name: movie_play_window
 * Namespace: Global
 * Signature: int movie_play_window(HWND__ * param_1, int param_2, tagRECT * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl movie_play_window(HWND__ *param_1,int param_2,tagRECT *param_3)

{
  MCIERROR MVar1;
  char *_Format;
  char local_240 [256];
  char local_140 [256];
  CHAR local_40 [56];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  mci_movie.mode = param_2;
  if (param_3 == (tagRECT *)0x0) {
    sprintf(local_140,"put %s destination",mci_movie.aliasName);
    mci_movie.rect.left = 0;
    mci_movie.rect.top = 0;
    mci_movie.rect.right = 0x27f;
    mci_movie.rect.bottom = 0x1df;
  }
  else {
    mci_movie.rect.left = param_3->left;
    mci_movie.rect.top = param_3->top;
    mci_movie.rect.right = param_3->right;
    mci_movie.rect.bottom = param_3->bottom;
    sprintf(local_140,"put %s destination at %d %d %d %d",mci_movie.aliasName,mci_movie.rect.left,
            mci_movie.rect.top,mci_movie.rect.right - mci_movie.rect.left,
            mci_movie.rect.bottom - mci_movie.rect.top);
  }
  MVar1 = mciSendStringA(local_140,local_40,0x37,(HWND)0x0);
  if (MVar1 == 0) {
    sprintf(local_140,"window %s handle %d",mci_movie.aliasName,param_1);
    MVar1 = mciSendStringA(local_140,local_40,0x37,(HWND)0x0);
    if (MVar1 == 0) {
      if ((param_2 == 0) || (param_2 == 1)) {
        sprintf(local_140,"play %s notify",mci_movie.aliasName);
      }
      MVar1 = mciSendStringA(local_140,local_40,0x37,(HWND)param_1);
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
