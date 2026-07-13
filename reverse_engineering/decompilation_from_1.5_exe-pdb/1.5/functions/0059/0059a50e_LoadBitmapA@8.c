/*
 * Entry: 0059a50e
 * Name: _LoadBitmapA@8
 * Namespace: Global
 * Signature: HBITMAP _LoadBitmapA@8(HINSTANCE hInstance, LPCSTR lpBitmapName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HBITMAP _LoadBitmapA_8(HINSTANCE hInstance,LPCSTR lpBitmapName)

{
  HBITMAP pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a50e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadBitmapA(hInstance,lpBitmapName);
  return pHVar1;
}
