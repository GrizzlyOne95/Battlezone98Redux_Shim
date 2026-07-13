/*
 * Entry: 0059a63a
 * Name: _GetTextExtentExPointA@28
 * Namespace: Global
 * Signature: BOOL _GetTextExtentExPointA@28(HDC hdc, LPCSTR lpszString, int cchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetTextExtentExPointA_28
               (HDC hdc,LPCSTR lpszString,int cchString,int nMaxExtent,LPINT lpnFit,LPINT lpnDx,
               LPSIZE lpSize)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a63a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetTextExtentExPointA(hdc,lpszString,cchString,nMaxExtent,lpnFit,lpnDx,lpSize);
  return BVar1;
}
