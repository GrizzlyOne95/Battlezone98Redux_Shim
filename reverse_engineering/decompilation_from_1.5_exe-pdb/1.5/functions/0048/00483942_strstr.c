/*
 * Entry: 00483942
 * Name: strstr
 * Namespace: Global
 * Signature: char * strstr(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* char * __cdecl strstr(char *,char const *) */

char * __cdecl strstr(char *param_1,char *param_2)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00483942. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = strstr(param_1,param_2);
  return pcVar1;
}
