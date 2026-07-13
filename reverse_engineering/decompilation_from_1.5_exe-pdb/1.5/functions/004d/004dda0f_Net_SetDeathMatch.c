/*
 * Entry: 004dda0f
 * Name: Net_SetDeathMatch
 * Namespace: Global
 * Signature: void Net_SetDeathMatch(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_SetDeathMatch(int param_1)

{
  Net::deathmatch = param_1 != 0;
  return;
}
