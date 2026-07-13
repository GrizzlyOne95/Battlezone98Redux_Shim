/*
 * Entry: 005c6fbc
 * Name: chdir
 * Namespace: Global
 * Signature: undefined chdir()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* chdir */

void __cdecl chdir(char *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x005c6fbc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _chdir(param_1);
  return;
}
