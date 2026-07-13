/*
 * Entry: 00582000
 * Name: Get_TimeNow
 * Namespace: Global
 * Signature: DWORD Get_TimeNow(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD Get_TimeNow(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00582000. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = timeGetTime();
  return DVar1;
}
