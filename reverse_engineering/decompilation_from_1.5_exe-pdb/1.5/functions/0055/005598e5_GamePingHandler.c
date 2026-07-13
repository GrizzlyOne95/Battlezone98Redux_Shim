/*
 * Entry: 005598e5
 * Name: GamePingHandler
 * Namespace: Global
 * Signature: void GamePingHandler(short param_1, long param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GamePingHandler(short param_1,long param_2,int param_3)

{
  PlayerList::Ping((PlayerList *)&playersInSyncGame,param_1,param_2,param_3);
  return;
}
