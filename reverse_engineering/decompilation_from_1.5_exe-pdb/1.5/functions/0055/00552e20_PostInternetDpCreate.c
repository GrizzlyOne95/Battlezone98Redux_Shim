/*
 * Entry: 00552e20
 * Name: PostInternetDpCreate
 * Namespace: Global
 * Signature: void PostInternetDpCreate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PostInternetDpCreate(void)

{
  if (dpCreateMinimized) {
    ShowWindow((HWND)shell_hwnd,9);
  }
  return;
}
