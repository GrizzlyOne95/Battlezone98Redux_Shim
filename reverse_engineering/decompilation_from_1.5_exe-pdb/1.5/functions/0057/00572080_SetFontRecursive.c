/*
 * Entry: 00572080
 * Name: SetFontRecursive
 * Namespace: Global
 * Signature: void SetFontRecursive(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetFontRecursive(HWND__ *param_1)

{
  SetNetworkFont(param_1);
  EnumChildWindows((HWND)param_1,SetFontRecursiveHelper,0);
  return;
}
