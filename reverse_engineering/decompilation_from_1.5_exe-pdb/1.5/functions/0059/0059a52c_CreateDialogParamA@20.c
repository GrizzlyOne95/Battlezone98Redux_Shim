/*
 * Entry: 0059a52c
 * Name: _CreateDialogParamA@20
 * Namespace: Global
 * Signature: HWND _CreateDialogParamA@20(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _CreateDialogParamA_20
               (HINSTANCE hInstance,LPCSTR lpTemplateName,HWND hWndParent,DLGPROC lpDialogFunc,
               LPARAM dwInitParam)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a52c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateDialogParamA(hInstance,lpTemplateName,hWndParent,lpDialogFunc,dwInitParam);
  return pHVar1;
}
