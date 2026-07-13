/*
 * Entry: 0059a466
 * Name: _DialogBoxParamA@20
 * Namespace: Global
 * Signature: INT_PTR _DialogBoxParamA@20(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
 * Symbol source: IMPORTED
 * Export status: ok
 */

INT_PTR _DialogBoxParamA_20(HINSTANCE hInstance,LPCSTR lpTemplateName,HWND hWndParent,
                           DLGPROC lpDialogFunc,LPARAM dwInitParam)

{
  INT_PTR IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a466. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = DialogBoxParamA(hInstance,lpTemplateName,hWndParent,lpDialogFunc,dwInitParam);
  return IVar1;
}
