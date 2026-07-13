/*
 * Entry: 004793e0
 * Name: do_ending_movie
 * Namespace: Global
 * Signature: void do_ending_movie(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_ending_movie(void)

{
  int iVar1;
  HANDLE pvVar2;
  
  LastGAS();
  iVar1 = movie_open("outro.avi");
  if (iVar1 != 0) {
    GetClientRect((HWND)shell_hwnd,(LPRECT)&gameWindow);
    SetFocus((HWND)shell_hwnd);
    LockMouse();
    nMCIcheck = movie_play(0,&gameWindow);
    if (nMCIcheck != 0) {
      iVar1 = -2;
      pvVar2 = GetCurrentThread();
      SetThreadPriority(pvVar2,iVar1);
      ScreenMode = SCREENMODE_MOVIE;
      while( true ) {
        iVar1 = movie_is_playing();
        if (iVar1 == 0) break;
        HandleMessageQueue(&Device);
      }
      BlackOutScreen(Black_Color);
      iVar1 = 0;
      pvVar2 = GetCurrentThread();
      SetThreadPriority(pvVar2,iVar1);
    }
    UnlockMouse();
  }
  FirstGAS(Device.hwndApp);
  return;
}
