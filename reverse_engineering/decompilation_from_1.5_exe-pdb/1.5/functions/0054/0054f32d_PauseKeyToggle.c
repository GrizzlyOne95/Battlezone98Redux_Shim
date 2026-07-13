/*
 * Entry: 0054f32d
 * Name: PauseKeyToggle
 * Namespace: Global
 * Signature: void PauseKeyToggle(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PauseKeyToggle(void)

{
  if (ScreenMode == SCREENMODE_PAUSE) {
    if (LastMode == SCREENMODE_SIM) {
      LockMouse();
      UnPauseAudio();
      Resume();
      EnableForceFeedback();
    }
    SetScreenMode(LastMode);
    return;
  }
  if (LastMode == SCREENMODE_SIM) {
    UnlockMouse();
    PauseAudio();
    Pause();
    DisableForceFeedback();
  }
  LastMode = SetScreenMode(SCREENMODE_PAUSE);
  return;
}
