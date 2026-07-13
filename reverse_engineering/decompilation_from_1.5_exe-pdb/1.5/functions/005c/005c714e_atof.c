/*
 * Entry: 005c714e
 * Name: atof
 * Namespace: Global
 * Signature: undefined atof()
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* atof */

float10 __cdecl atof(char *param_1)

{
  double dVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c714e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  dVar1 = atof(param_1);
  return (float10)dVar1;
}
