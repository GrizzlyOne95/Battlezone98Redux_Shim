/*
 * Entry: 0059a59e
 * Name: _GetDeviceCaps@8
 * Namespace: Global
 * Signature: int _GetDeviceCaps@8(HDC hdc, int index)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _GetDeviceCaps_8(HDC hdc,int index)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a59e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetDeviceCaps(hdc,index);
  return iVar1;
}
