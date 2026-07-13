/*
 * Entry: 0059a60a
 * Name: _SetMapMode@8
 * Namespace: Global
 * Signature: int _SetMapMode@8(HDC hdc, int iMode)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _SetMapMode_8(HDC hdc,int iMode)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a60a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = SetMapMode(hdc,iMode);
  return iVar1;
}
