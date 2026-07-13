/*
 * Entry: 0054f3b4
 * Name: HandleMapInput
 * Namespace: Global
 * Signature: void HandleMapInput(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HandleMapInput(void)

{
  if (user_controls.key != 0) {
    ProcessInput();
    return;
  }
  return;
}
