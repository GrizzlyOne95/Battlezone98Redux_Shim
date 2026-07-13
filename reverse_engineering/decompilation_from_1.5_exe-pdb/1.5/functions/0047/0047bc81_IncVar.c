/*
 * Entry: 0047bc81
 * Name: IncVar
 * Namespace: Global
 * Signature: void IncVar(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IncVar(void)

{
  if (AdjustVar::adjuster != (AdjustVar *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0047bc8d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)((int)*AdjustVar::adjuster + 4))();
    return;
  }
  return;
}
