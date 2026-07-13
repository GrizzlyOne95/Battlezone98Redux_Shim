/*
 * Entry: 0054f38b
 * Name: HandlePauseKeyInput
 * Namespace: Global
 * Signature: void HandlePauseKeyInput(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HandlePauseKeyInput(void)

{
  short sVar1;
  
  if (user_controls.key != 0) {
    sVar1 = MapKeyInput(user_controls.key);
    if (sVar1 == 0x16) {
      PauseKeyToggle();
      user_controls.key = 0;
    }
  }
  return;
}
