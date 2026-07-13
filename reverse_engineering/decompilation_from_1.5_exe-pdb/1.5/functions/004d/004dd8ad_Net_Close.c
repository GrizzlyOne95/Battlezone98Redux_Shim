/*
 * Entry: 004dd8ad
 * Name: Net_Close
 * Namespace: Global
 * Signature: void Net_Close(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_Close(void)

{
  if (Net::dp != (dp_s *)0x0) {
    Net::Close(false);
    dpDestroy(Net::dp,0);
    Net::dp = (dp_s *)0x0;
  }
  return;
}
