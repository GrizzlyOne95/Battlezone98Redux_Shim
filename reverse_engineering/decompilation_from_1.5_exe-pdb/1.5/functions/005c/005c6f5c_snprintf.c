/*
 * Entry: 005c6f5c
 * Name: snprintf
 * Namespace: Global
 * Signature: undefined snprintf()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* snprintf */

void __cdecl snprintf(char *param_1,size_t param_2,char *param_3)

{
                    /* WARNING: Could not recover jumptable at 0x005c6f5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _snprintf(param_1,param_2,param_3);
  return;
}
