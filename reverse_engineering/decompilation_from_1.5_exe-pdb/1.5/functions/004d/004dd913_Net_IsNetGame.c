/*
 * Entry: 004dd913
 * Name: Net_IsNetGame
 * Namespace: Global
 * Signature: int Net_IsNetGame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Net_IsNetGame(void)

{
  return (uint)Net::runNetworking;
}
