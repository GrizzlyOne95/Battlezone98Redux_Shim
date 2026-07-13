/*
 * Entry: 0058164d
 * Name: do_smain
 * Namespace: Global
 * Signature: void do_smain(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_smain(void)

{
  int iVar1;
  HDC hDC;
  int iVar2;
  
  if (nNetMode == 0) {
    Net_DoNetworking(0);
  }
  if (first != 0) {
    InitCommonControls();
    GetLangIni();
  }
  hDC = GetDC((HWND)shell_hwnd);
  first = 0;
  EnsurePalette();
  init_bitmap_dialog((HDC__ *)hDC);
  UnlockMouse();
  clear_events();
  iVar1 = nMissionStatus;
  if (nNetMode == 1) {
    nNetMode = 0;
    nShellMode = 0xe;
    goto LAB_00581738;
  }
  if (nMissionStatus != 0) {
    if (nOldMissionMode != 0) {
      nOldMissionMode = 0;
      nShellMode = 0xc;
      goto LAB_00581738;
    }
    iVar2 = CheckPlayerSide();
    nPlayerSide = iVar2;
    nMissionCurrentIndex = CheckMissionIndex();
    if (nMissionCurrentIndex < 0) {
      nMissionCurrentIndex = 0;
    }
    else if (iVar1 == 2) {
      nMissionCurrentIndex = nMissionCurrentIndex + 1;
    }
    if (iVar2 == 1) {
      if (nMissionCurrentIndex == (-(uint)(nDemoFlag != 0) & 0xfffffff1) + 0x11) {
        nShellMode = 1;
        nMissionCurrentIndex = 0;
        if (nDemoFlag != 0) {
          nReplayIntro = 0;
          nPlayCredits = 0;
          nShellMode = 0;
          SetRunning(10);
        }
        nUsaMissionIndex = nUsaMissionIndex + 1;
      }
      else {
        nUsaMissionIndex = nMissionCurrentIndex;
        if (nMainMenuCalled == 0) {
          nShellMode = 7;
        }
        else {
          nMainMenuCalled = 0;
          nShellMode = 1;
        }
      }
      goto LAB_00581738;
    }
    if (iVar2 == 2) {
      if (nMissionCurrentIndex != 8) {
        nUssrMissionIndex = nMissionCurrentIndex;
        if (nMainMenuCalled == 0) {
          nShellMode = 8;
        }
        else {
          nMainMenuCalled = 0;
          nShellMode = 1;
        }
        goto LAB_00581738;
      }
      nUssrMissionIndex = nUssrMissionIndex + 1;
      nMissionCurrentIndex = 0;
    }
    else if (iVar2 == 3) {
      if (nMissionCurrentIndex != 4) {
        nTrnMissionIndex = nMissionCurrentIndex;
        if (nMainMenuCalled == 0) {
          nShellMode = 9;
        }
        else {
          nMainMenuCalled = 0;
          nShellMode = 1;
        }
        goto LAB_00581738;
      }
      nTrnMissionIndex = nTrnMissionIndex + 1;
      nMissionCurrentIndex = 0;
    }
  }
  nShellMode = 1;
LAB_00581738:
  lastShellMode = nShellMode;
  while (nShellMode != 0) {
    DispatchDialog(nShellMode,(HWND__ *)0x0);
  }
  if ((nReplayIntro == 0) && (nPlayCredits == 0)) {
    set_video_mode((uint)(UserProfilePtr->graphicDetail).resolution);
    set_sky_detail((uint)(UserProfilePtr->graphicDetail).clouds);
    set_object_detail((uint)(UserProfilePtr->graphicDetail).objDetail);
    set_terrain_detail((uint)(UserProfilePtr->graphicDetail).terrain);
    set_cockpit_detail((uint)(UserProfilePtr->graphicDetail).cockpit);
    set_lineskip_mode((uint)(UserProfilePtr->graphicDetail).lineskip);
    set_hardware_mode((uint)(UserProfilePtr->graphicDetail).hardware);
    set_shadow_mode((uint)(UserProfilePtr->graphicDetail).shadow);
  }
  clear_events();
  LockMouse();
  clean_bitmap_dialog((HDC__ *)hDC);
  ReleaseDC((HWND)shell_hwnd,hDC);
  return;
}
