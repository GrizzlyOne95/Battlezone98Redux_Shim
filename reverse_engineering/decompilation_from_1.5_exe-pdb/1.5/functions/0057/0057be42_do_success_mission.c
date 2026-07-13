/*
 * Entry: 0057be42
 * Name: do_success_mission
 * Namespace: Global
 * Signature: void do_success_mission(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_success_mission(void)

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
  iVar2 = check_ending(1,0);
  if (iVar2 != 0) {
    do_ending_movie();
  }
  init_bitmap_dialog((HDC__ *)hDC);
  UnlockMouse();
  Shell_DialogBoxParam(shell_hInstance,(char *)0x82,shell_hwnd,SuccessMissionDlgProc,0);
  clean_bitmap_dialog((HDC__ *)hDC);
  ReleaseDC((HWND)shell_hwnd,hDC);
  iVar2 = check_ending(1,1);
  if (iVar2 == 0) {
    iVar2 = check_ending(2,1);
    if (iVar2 == 0) goto LAB_0057bf01;
  }
  do_credits_movie();
LAB_0057bf01:
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
