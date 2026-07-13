/*
 * Entry: 0054cfa9
 * Name: movie_check
 * Namespace: Global
 * Signature: void movie_check(uint param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl movie_check(uint param_1,long param_2)

{
  HWND__ *local_10 [3];
  
  if ((isMCIPlaying != 0) && (param_1 == 1)) {
    if (mciCued != 0) {
      mciCued = 0;
      local_10[0] = shell_hwnd;
      mciSendCommandA(mci_movie.movieID,0x806,1,(DWORD_PTR)local_10);
      return;
    }
    if ((param_2 & 0xffffU) == mci_movie.movieID) {
      movie_close();
    }
  }
  return;
}
