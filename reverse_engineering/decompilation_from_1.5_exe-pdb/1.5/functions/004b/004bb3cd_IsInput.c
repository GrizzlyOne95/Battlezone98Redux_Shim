/*
 * Entry: 004bb3cd
 * Name: IsInput
 * Namespace: Global
 * Signature: int IsInput(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsInput(void)

{
  inputCalled = 1;
  if (((undefined1)ScreenMode &
      (SCREENMODE_MOVIE|SCREENMODE_MENU|SCREENMODE_NOTEPAD|SCREENMODE_MAP|SCREENMODE_PAUSE)) == 0) {
    if (user_controls.key != 0) {
      if (gamekey_map[user_controls.key] == '\v') {
        inputFound = 1;
      }
      else if (gamekey_map[user_controls.key] == '\x16') {
        PauseKeyToggle();
      }
      ClearKeyboardState();
      user_controls.key = 0;
    }
  }
  else {
    inputFound = 0;
  }
  return inputFound;
}
