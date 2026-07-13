/*
 * Entry: 0059a3a6
 * Name: _FindWindowA@8
 * Namespace: Global
 * Signature: HWND _FindWindowA@8(LPCSTR lpClassName, LPCSTR lpWindowName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _FindWindowA_8(LPCSTR lpClassName,LPCSTR lpWindowName)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3a6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = FindWindowA(lpClassName,lpWindowName);
  return pHVar1;
}
