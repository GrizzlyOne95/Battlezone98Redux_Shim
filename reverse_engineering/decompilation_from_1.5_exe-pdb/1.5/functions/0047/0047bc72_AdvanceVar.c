/*
 * Entry: 0047bc72
 * Name: AdvanceVar
 * Namespace: Global
 * Signature: void AdvanceVar(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AdvanceVar(void)

{
  if (AdjustVar::adjuster != (AdjustVar *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0047bc7e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*AdjustVar::adjuster)();
    return;
  }
  return;
}
