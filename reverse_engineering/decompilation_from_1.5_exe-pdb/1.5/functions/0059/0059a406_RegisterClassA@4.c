/*
 * Entry: 0059a406
 * Name: _RegisterClassA@4
 * Namespace: Global
 * Signature: ATOM _RegisterClassA@4(WNDCLASSA * lpWndClass)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ATOM _RegisterClassA_4(WNDCLASSA *lpWndClass)

{
  ATOM AVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a406. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  AVar1 = RegisterClassA(lpWndClass);
  return AVar1;
}
