/*
 * Entry: 0047a39d
 * Name: DoFrame
 * Namespace: Global
 * Signature: void DoFrame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DoFrame(void)

{
  ulong uVar1;
  int iVar2;
  HANDLE pvVar3;
  float fVar4;
  DWORD DVar5;
  
  uVar1 = Get_Frame_Count();
  if (uVar1 == 0x14) {
    SetLastSessionFlag();
  }
  iVar2 = Net_IsNetGame();
  if (((iVar2 != 0) && (respawn == 1)) && (fVar4 = Get_TimeLocal(), respawn_timer < fVar4)) {
    respawn = 0;
    Net_CreatePlayer(0);
    if (runningSS != 5) {
      return;
    }
  }
  if (Device.ShutDownReq != 0) {
    DEBUG_systemError("ERROR, Device_Set_ShutDown has been called");
  }
  SetLoopTimes();
  NextInputs();
  if ((WeAreActive != 0) &&
     ((ScreenMode &
      (SCREENMODE_MOVIE|SCREENMODE_MENU|SCREENMODE_NOTEPAD|SCREENMODE_MAP|SCREENMODE_PAUSE)) == 0))
  {
    iVar2 = 2;
    pvVar3 = GetCurrentThread();
    SetThreadPriority(pvVar3,iVar2);
    iVar2 = UserPref_arcadeMode();
    if (iVar2 == 0) {
      CheckEntityCollisions();
    }
    ProcessInput();
    GameFeature_ControlAll();
    iVar2 = Net_IsNetGame();
    if ((iVar2 != 0) && (iVar2 = Net_Execute(), iVar2 == 0)) {
      runningSS = 2;
    }
    iVar2 = UserPref_arcadeMode();
    if (iVar2 == 0) {
      Manage_AI(&Device);
    }
    Simulate();
    ControlWeapons();
    iVar2 = Net_IsNetGame();
    if (iVar2 != 0) {
      GameObject_BroadCast();
    }
    TexAnim_Animate();
    iVar2 = 0;
    pvVar3 = GetCurrentThread();
    SetThreadPriority(pvVar3,iVar2);
    NextGAS(1);
    if (ScreenMode == SCREENMODE_SIM) {
      DVar5 = 0x100;
      pvVar3 = GetCurrentProcess();
      SetPriorityClass(pvVar3,DVar5);
      Render_Next_Frame(&View_Record.MainCam);
      DVar5 = 0x20;
      pvVar3 = GetCurrentProcess();
      SetPriorityClass(pvVar3,DVar5);
      iVar2 = 0;
      pvVar3 = GetCurrentThread();
      SetThreadPriority(pvVar3,iVar2);
    }
    Show_TargetPosition();
    Cache_Display();
    Init_Object_Database();
    HandleMessageQueue(&Device);
    return;
  }
  HandleGamePauses(WeAreActive);
  return;
}
