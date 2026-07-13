/*
 * Entry: 0047a355
 * Name: HandleGamePauses
 * Namespace: Global
 * Signature: void HandleGamePauses(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HandleGamePauses(int param_1)

{
  int iVar1;
  DWORD dwMilliseconds;
  
  iVar1 = Net_IsNetGame();
  if (iVar1 == 0) {
    if (param_1 != 0) {
      HandlePauseInput();
      NextGAS(1);
      Render_Pause_Message(&View_Record.MainCam);
      goto LAB_0047a391;
    }
    dwMilliseconds = 0x10;
  }
  else {
    DoNetEscapeFrame();
    dwMilliseconds = 0x14;
  }
  Sleep(dwMilliseconds);
LAB_0047a391:
  HandleMessageQueue(&Device);
  return;
}
