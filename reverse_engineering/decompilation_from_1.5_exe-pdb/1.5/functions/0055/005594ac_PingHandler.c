/*
 * Entry: 005594ac
 * Name: PingHandler
 * Namespace: Global
 * Signature: void PingHandler(short param_1, long param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PingHandler(short param_1,long param_2,int param_3)

{
  PlayerList::Ping(&playersInRoom,param_1,param_2,param_3);
  return;
}
