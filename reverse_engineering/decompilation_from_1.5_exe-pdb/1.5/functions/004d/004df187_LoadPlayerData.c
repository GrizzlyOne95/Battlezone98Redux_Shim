/*
 * Entry: 004df187
 * Name: LoadPlayerData
 * Namespace: Global
 * Signature: void LoadPlayerData(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LoadPlayerData(void)

{
  dpEnumPlayers(Net::dp,0,dpEnumPlayersCallbackLoad,0,0);
  return;
}
