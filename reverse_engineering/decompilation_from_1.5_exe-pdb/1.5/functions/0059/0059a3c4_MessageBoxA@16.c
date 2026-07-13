/*
 * Entry: 0059a3c4
 * Name: _MessageBoxA@16
 * Namespace: Global
 * Signature: int _MessageBoxA@16(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _MessageBoxA_16(HWND hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = MessageBoxA(hWnd,lpText,lpCaption,uType);
  return iVar1;
}
