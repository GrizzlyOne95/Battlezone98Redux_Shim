/*
 * Entry: 005c70fa
 * Name: vsnprintf
 * Namespace: Global
 * Signature: undefined vsnprintf()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* vsnprintf */

void __cdecl vsnprintf(char *param_1,size_t param_2,char *param_3,va_list param_4)

{
                    /* WARNING: Could not recover jumptable at 0x005c70fa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _vsnprintf(param_1,param_2,param_3,param_4);
  return;
}
