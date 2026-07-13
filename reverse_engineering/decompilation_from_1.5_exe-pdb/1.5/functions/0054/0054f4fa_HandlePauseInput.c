/*
 * Entry: 0054f4fa
 * Name: HandlePauseInput
 * Namespace: Global
 * Signature: void HandlePauseInput(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HandlePauseInput(void)

{
  if (ScreenMode == SCREENMODE_PAUSE) {
    HandlePauseKeyInput();
    return;
  }
  if (ScreenMode == SCREENMODE_MAP) {
    HandleMapInput();
    return;
  }
  if (ScreenMode == SCREENMODE_NOTEPAD) {
    HandleNotepadInput();
    return;
  }
  if (ScreenMode == SCREENMODE_MENU) {
    HandleMenuInput();
    return;
  }
  return;
}
