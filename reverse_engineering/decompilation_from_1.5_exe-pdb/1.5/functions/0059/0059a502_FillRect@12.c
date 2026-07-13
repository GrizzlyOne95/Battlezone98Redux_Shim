/*
 * Entry: 0059a502
 * Name: _FillRect@12
 * Namespace: Global
 * Signature: int _FillRect@12(HDC hDC, RECT * lprc, HBRUSH hbr)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _FillRect_12(HDC hDC,RECT *lprc,HBRUSH hbr)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a502. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = FillRect(hDC,lprc,hbr);
  return iVar1;
}
