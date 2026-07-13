/*
 * Entry: 0059a514
 * Name: _DrawTextExA@24
 * Namespace: Global
 * Signature: int _DrawTextExA@24(HDC hdc, LPSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _DrawTextExA_24(HDC hdc,LPSTR lpchText,int cchText,LPRECT lprc,UINT format,
                   LPDRAWTEXTPARAMS lpdtp)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a514. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = DrawTextExA(hdc,lpchText,cchText,lprc,format,lpdtp);
  return iVar1;
}
