/*
 * Entry: 00552e01
 * Name: PreInternetDpCreate
 * Namespace: Global
 * Signature: void PreInternetDpCreate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PreInternetDpCreate(void)

{
  int iVar1;
  
  iVar1 = adialup_willdial();
  if (iVar1 != 0) {
    dpCreateMinimized = true;
    ShowWindow((HWND)shell_hwnd,6);
  }
  return;
}
