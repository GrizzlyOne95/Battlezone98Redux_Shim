/*
 * Entry: 005818e4
 * Name: do_escape
 * Namespace: Global
 * Signature: void do_escape(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_escape(void)

{
  HDC hDC;
  long lVar1;
  int iVar2;
  
  (*giddiKeyboard.flush_key)();
  hDC = GetDC((HWND)shell_hwnd);
  user_controls.key = 0;
  UnlockMouse();
  EnsurePalette();
  clear_events();
  lVar1 = Get_Closest_RGB_Entry(0.0,0.0,0.0);
  BlackOutScreen(lVar1);
  iVar2 = (*Device.VideoMode.ChangeMode)(&Device,0);
  if (iVar2 == 0) {
    DEBUG_systemError("BattleZone Init_Graphic_System");
  }
  clear_events();
  iVar2 = Net_IsNetGame();
  if (iVar2 == 0) {
    Pause();
  }
  PauseAudio();
  init_bitmap_dialog((HDC__ *)hDC);
  nShellMode = 0xb;
  lastShellMode = 0xb;
  do {
    DispatchDialog(nShellMode,(HWND__ *)0x0);
  } while (nShellMode != 0);
  clean_bitmap_dialog((HDC__ *)hDC);
  ReleaseDC((HWND)shell_hwnd,hDC);
  iVar2 = GetRunning();
  if (iVar2 == 5) {
    SetGASMasterVolumes(-1,-1,-1);
    UnPauseAudio();
    StartMusic(-1,0);
    iVar2 = Net_IsNetGame();
    if (iVar2 == 0) {
      Resume();
    }
    set_video_mode((uint)(UserProfilePtr->graphicDetail).resolution);
    set_sky_detail((uint)(UserProfilePtr->graphicDetail).clouds);
    set_object_detail((uint)(UserProfilePtr->graphicDetail).objDetail);
    set_terrain_detail((uint)(UserProfilePtr->graphicDetail).terrain);
    set_cockpit_detail((uint)(UserProfilePtr->graphicDetail).cockpit);
    set_lineskip_mode((uint)(UserProfilePtr->graphicDetail).lineskip);
    set_hardware_mode((uint)(UserProfilePtr->graphicDetail).hardware);
    set_shadow_mode((uint)(UserProfilePtr->graphicDetail).shadow);
    clear_events();
    iVar2 = (*Device.VideoMode.ChangeMode)(&Device,(uint)(UserProfilePtr->graphicDetail).resolution)
    ;
    if (iVar2 == 0) {
      DEBUG_systemError("BattleZone Init_Graphic_System");
    }
    clear_events();
    clear_events();
    SetFocus((HWND)shell_hwnd);
    OverlayDefaultPalette(0,0x100,0);
    LockMouse();
    return;
  }
  return;
}
