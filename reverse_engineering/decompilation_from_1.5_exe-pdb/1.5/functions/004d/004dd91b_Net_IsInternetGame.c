/*
 * Entry: 004dd91b
 * Name: Net_IsInternetGame
 * Namespace: Global
 * Signature: int Net_IsInternetGame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Net_IsInternetGame(void)

{
  if (!Net::runNetworking) {
    return 0;
  }
  return (uint)Net::bInternetGame;
}
