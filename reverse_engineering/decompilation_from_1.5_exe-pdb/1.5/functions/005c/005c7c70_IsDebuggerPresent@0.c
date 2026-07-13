/*
 * Entry: 005c7c70
 * Name: _IsDebuggerPresent@0
 * Namespace: Global
 * Signature: BOOL _IsDebuggerPresent@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _IsDebuggerPresent_0(void)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsDebuggerPresent();
  return BVar1;
}
