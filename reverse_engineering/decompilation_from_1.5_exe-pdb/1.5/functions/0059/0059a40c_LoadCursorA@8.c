/*
 * Entry: 0059a40c
 * Name: _LoadCursorA@8
 * Namespace: Global
 * Signature: HCURSOR _LoadCursorA@8(HINSTANCE hInstance, LPCSTR lpCursorName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HCURSOR _LoadCursorA_8(HINSTANCE hInstance,LPCSTR lpCursorName)

{
  HCURSOR pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a40c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadCursorA(hInstance,lpCursorName);
  return pHVar1;
}
