/*
 * Entry: 0047636b
 * Name: EnableForceFeedback
 * Namespace: Global
 * Signature: void EnableForceFeedback(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl EnableForceFeedback(void)

{
  if (ForceFeedbackPresent != 0) {
                    /* WARNING: Could not recover jumptable at 0x00476374. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*pEnableForces)();
    return;
  }
  return;
}
