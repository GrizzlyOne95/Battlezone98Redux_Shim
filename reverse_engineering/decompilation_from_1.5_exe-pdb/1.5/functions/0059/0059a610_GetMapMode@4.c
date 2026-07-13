/*
 * Entry: 0059a610
 * Name: _GetMapMode@4
 * Namespace: Global
 * Signature: int _GetMapMode@4(HDC hdc)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _GetMapMode_4(HDC hdc)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a610. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetMapMode(hdc);
  return iVar1;
}
