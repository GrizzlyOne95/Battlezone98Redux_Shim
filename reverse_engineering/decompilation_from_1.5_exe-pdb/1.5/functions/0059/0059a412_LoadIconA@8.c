/*
 * Entry: 0059a412
 * Name: _LoadIconA@8
 * Namespace: Global
 * Signature: HICON _LoadIconA@8(HINSTANCE hInstance, LPCSTR lpIconName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HICON _LoadIconA_8(HINSTANCE hInstance,LPCSTR lpIconName)

{
  HICON pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a412. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadIconA(hInstance,lpIconName);
  return pHVar1;
}
