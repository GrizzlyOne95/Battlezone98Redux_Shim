/*
 * Entry: 004ddf61
 * Name: Net_SetIPX
 * Namespace: Global
 * Signature: void Net_SetIPX(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_SetIPX(void)

{
  Net::fWeaponTriggerHoldTime = 0.5;
  Net::dwBandwidth = 10000;
  Net::dwMaxBandwidth = 10000;
  Net::dwMinBandwidth = 10000;
  return;
}
