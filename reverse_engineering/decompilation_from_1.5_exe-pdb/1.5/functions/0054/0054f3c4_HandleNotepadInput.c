/*
 * Entry: 0054f3c4
 * Name: HandleNotepadInput
 * Namespace: Global
 * Signature: void HandleNotepadInput(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HandleNotepadInput(void)

{
  if (user_controls.key != 0) {
    ProcessInput();
    return;
  }
  return;
}
