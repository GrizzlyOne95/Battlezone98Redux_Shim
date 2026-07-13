/*
 * Entry: 0055ccd6
 * Name: Net_IsPlayerMuted
 * Namespace: Global
 * Signature: int Net_IsPlayerMuted(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Net_IsPlayerMuted(ushort param_1)

{
  bool bVar1;
  
  dp_result = dpEnumPlayersEx(Net::dp,&dp_session_game,dpEnumGamePlayersCallback,0,0);
  bVar1 = PlayerList::IsMuted((PlayerList *)&playersInSyncGame,param_1);
  return (uint)bVar1;
}
