/*
 * Entry: 005c9a8e
 * Name: getcwd
 * Namespace: Global
 * Signature: undefined getcwd()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* getcwd */

void __cdecl getcwd(char *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x005c9a8e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _getcwd(param_1,param_2);
  return;
}
