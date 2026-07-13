/*
 * Entry: 005c79c4
 * Name: exit
 * Namespace: Global
 * Signature: undefined exit()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* exit */

void __cdecl exit(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x005c79c4. Too many branches */
                    /* WARNING: Subroutine does not return */
                    /* WARNING: Treating indirect jump as call */
  _exit(param_1);
  return;
}
