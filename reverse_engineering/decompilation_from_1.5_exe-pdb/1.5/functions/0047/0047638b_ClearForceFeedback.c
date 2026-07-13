/*
 * Entry: 0047638b
 * Name: ClearForceFeedback
 * Namespace: Global
 * Signature: void ClearForceFeedback(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearForceFeedback(void)

{
  if (ForceFeedbackPresent != 0) {
                    /* WARNING: Could not recover jumptable at 0x00476394. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*pClearForces)();
    return;
  }
  return;
}
