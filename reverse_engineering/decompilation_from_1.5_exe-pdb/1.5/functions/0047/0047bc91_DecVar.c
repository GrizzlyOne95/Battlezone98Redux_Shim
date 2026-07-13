/*
 * Entry: 0047bc91
 * Name: DecVar
 * Namespace: Global
 * Signature: void DecVar(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DecVar(void)

{
  if (AdjustVar::adjuster != (AdjustVar *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0047bc9d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)((int)*AdjustVar::adjuster + 8))();
    return;
  }
  return;
}
