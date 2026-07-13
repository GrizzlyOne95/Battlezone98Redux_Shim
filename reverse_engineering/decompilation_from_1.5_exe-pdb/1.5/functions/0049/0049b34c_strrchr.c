/*
 * Entry: 0049b34c
 * Name: strrchr
 * Namespace: Global
 * Signature: char * strrchr(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* char * __cdecl strrchr(char *,int) */

char * __cdecl strrchr(char *param_1,int param_2)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0049b34c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = strrchr(param_1,param_2);
  return pcVar1;
}
