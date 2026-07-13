/*
 * Entry: 0047634b
 * Name: CloseForceFeedback
 * Namespace: Global
 * Signature: void CloseForceFeedback(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CloseForceFeedback(void)

{
  if (ForceFeedbackPresent != 0) {
    (*pCloseStick)();
    Sleep(200);
    IForceEnd();
    return;
  }
  return;
}
