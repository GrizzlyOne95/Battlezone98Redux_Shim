/*
 * Entry: 0047637b
 * Name: DisableForceFeedback
 * Namespace: Global
 * Signature: void DisableForceFeedback(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisableForceFeedback(void)

{
  if (ForceFeedbackPresent != 0) {
                    /* WARNING: Could not recover jumptable at 0x00476384. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*pDisableForces)();
    return;
  }
  return;
}
