/*
 * Entry: 004ddf47
 * Name: Net_SetHeat
 * Namespace: Global
 * Signature: void Net_SetHeat(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_SetHeat(void)

{
  Net::dwBandwidth = 1000;
  Net::dwMaxBandwidth = 2000;
  Net::dwMinBandwidth = 1000;
  return;
}
