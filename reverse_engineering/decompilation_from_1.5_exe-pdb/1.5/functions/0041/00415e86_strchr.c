/*
 * Entry: 00415e86
 * Name: strchr
 * Namespace: Global
 * Signature: char * strchr(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* char * __cdecl strchr(char *,int) */

char * __cdecl strchr(char *param_1,int param_2)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00415e86. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = strchr(param_1,param_2);
  return pcVar1;
}
