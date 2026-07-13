/*
 * Entry: 004ddfa9
 * Name: Network_ToggleDisplay
 * Namespace: Global
 * Signature: void Network_ToggleDisplay(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Network_ToggleDisplay(void)

{
  net_display = (uint)(net_display == 0);
  return;
}
