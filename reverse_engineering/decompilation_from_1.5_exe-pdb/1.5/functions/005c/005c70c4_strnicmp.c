/*
 * Entry: 005c70c4
 * Name: strnicmp
 * Namespace: Global
 * Signature: undefined strnicmp()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* strnicmp */

void __cdecl strnicmp(char *param_1,char *param_2,size_t param_3)

{
                    /* WARNING: Could not recover jumptable at 0x005c70c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _strnicmp(param_1,param_2,param_3);
  return;
}
