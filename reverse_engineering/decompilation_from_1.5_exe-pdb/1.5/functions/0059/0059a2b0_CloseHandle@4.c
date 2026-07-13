/*
 * Entry: 0059a2b0
 * Name: _CloseHandle@4
 * Namespace: Global
 * Signature: BOOL _CloseHandle@4(HANDLE hObject)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _CloseHandle_4(HANDLE hObject)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CloseHandle(hObject);
  return BVar1;
}
