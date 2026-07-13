/*
 * Entry: 005c790a
 * Name: vsnprintf_s
 * Namespace: Global
 * Signature: undefined vsnprintf_s()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* vsnprintf_s */

void __cdecl vsnprintf_s(char *param_1,size_t param_2,size_t param_3,char *param_4,va_list param_5)

{
                    /* WARNING: Could not recover jumptable at 0x005c790a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _vsnprintf_s(param_1,param_2,param_3,param_4,param_5);
  return;
}
