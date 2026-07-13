/*
 * Entry: 0059a508
 * Name: _DrawFocusRect@8
 * Namespace: Global
 * Signature: BOOL _DrawFocusRect@8(HDC hDC, RECT * lprc)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _DrawFocusRect_8(HDC hDC,RECT *lprc)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a508. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DrawFocusRect(hDC,lprc);
  return BVar1;
}
