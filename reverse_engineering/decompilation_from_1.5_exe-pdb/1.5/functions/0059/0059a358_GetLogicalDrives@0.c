/*
 * Entry: 0059a358
 * Name: _GetLogicalDrives@0
 * Namespace: Global
 * Signature: DWORD _GetLogicalDrives@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _GetLogicalDrives_0(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a358. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetLogicalDrives();
  return DVar1;
}
