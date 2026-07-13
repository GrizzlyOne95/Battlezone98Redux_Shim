/*
 * Entry: 005c71a8
 * Name: localtime64
 * Namespace: Global
 * Signature: undefined localtime64()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* localtime64 */

void __cdecl localtime64(__time64_t *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x005c71a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _localtime64(param_1);
  return;
}
