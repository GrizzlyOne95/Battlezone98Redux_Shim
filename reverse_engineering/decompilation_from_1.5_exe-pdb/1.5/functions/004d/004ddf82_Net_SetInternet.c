/*
 * Entry: 004ddf82
 * Name: Net_SetInternet
 * Namespace: Global
 * Signature: void Net_SetInternet(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_SetInternet(void)

{
  Net::dwBandwidth = 0x834;
  Net::fWeaponTriggerHoldTime = 1.0;
  Net::dwMaxBandwidth = 5000;
  Net::dwMinBandwidth = 0x514;
  return;
}
