/*
 * Entry: 0059a56e
 * Name: _SetBkMode@8
 * Namespace: Global
 * Signature: int _SetBkMode@8(HDC hdc, int mode)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _SetBkMode_8(HDC hdc,int mode)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a56e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = SetBkMode(hdc,mode);
  return iVar1;
}
