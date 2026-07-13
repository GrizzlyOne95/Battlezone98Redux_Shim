/*
 * Entry: 0059a634
 * Name: _EnumFontsA@16
 * Namespace: Global
 * Signature: int _EnumFontsA@16(HDC hdc, LPCSTR lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _EnumFontsA_16(HDC hdc,LPCSTR lpLogfont,FONTENUMPROCA lpProc,LPARAM lParam)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a634. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = EnumFontsA(hdc,lpLogfont,lpProc,lParam);
  return iVar1;
}
