/*
 * Entry: 0055cd09
 * Name: Net_MutePlayer
 * Namespace: Global
 * Signature: void Net_MutePlayer(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_MutePlayer(ushort param_1)

{
  Player *pPVar1;
  
  dp_result = dpEnumPlayersEx(Net::dp,&dp_session_game,dpEnumGamePlayersCallback,0,0);
  pPVar1 = PlayerList::FindPlayer((PlayerList *)&playersInSyncGame,param_1);
  if (pPVar1 != (Player *)0x0) {
    pPVar1->mute = true;
  }
  return;
}
