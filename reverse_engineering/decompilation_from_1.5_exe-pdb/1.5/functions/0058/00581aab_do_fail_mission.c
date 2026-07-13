/*
 * Entry: 00581aab
 * Name: do_fail_mission
 * Namespace: Global
 * Signature: void do_fail_mission(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_fail_mission(void)

{
  long lVar1;
  HDC hDC;
  int iVar2;
  
  hDC = GetDC((HWND)shell_hwnd);
  lVar1 = ResolutionMode;
  EnsurePalette();
  clear_events();
  iVar2 = (*Device.VideoMode.ChangeMode)(&Device,0);
  if (iVar2 == 0) {
    DEBUG_systemError("BattleZone Init_Graphic_System");
  }
  Pause();
  PauseGAS();
  init_bitmap_dialog((HDC__ *)hDC);
  UnlockMouse();
  nShellMode = 0x13;
  lastShellMode = 0x13;
  do {
    DispatchDialog(nShellMode,(HWND__ *)0x0);
  } while (nShellMode != 0);
  clean_bitmap_dialog((HDC__ *)hDC);
  ReleaseDC((HWND)shell_hwnd,hDC);
  SetGASMasterVolumes(-1,-1,-1);
  iVar2 = GetRunning();
  if (iVar2 == 5) {
    UnPauseGAS();
  }
  Resume();
  iVar2 = (*Device.VideoMode.ChangeMode)(&Device,lVar1);
  if (iVar2 == 0) {
    DEBUG_systemError("BattleZone Init_Graphic_System");
  }
  OverlayDefaultPalette(0,0x100,0);
  clear_events();
  LockMouse();
  return;
}
