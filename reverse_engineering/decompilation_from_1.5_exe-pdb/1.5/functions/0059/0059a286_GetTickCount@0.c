/*
 * Entry: 0059a286
 * Name: _GetTickCount@0
 * Namespace: Global
 * Signature: DWORD _GetTickCount@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _GetTickCount_0(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a286. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetTickCount();
  return DVar1;
}
