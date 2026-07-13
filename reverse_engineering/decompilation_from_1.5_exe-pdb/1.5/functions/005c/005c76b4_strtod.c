/*
 * Entry: 005c76b4
 * Name: strtod
 * Namespace: Global
 * Signature: undefined strtod()
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* strtod */

float10 __cdecl strtod(char *param_1,char **param_2)

{
  double dVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c76b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  dVar1 = strtod(param_1,param_2);
  return (float10)dVar1;
}
