/*
 * Entry: 0055caae
 * Name: dpEnumGamePlayersCallback
 * Namespace: Global
 * Signature: void dpEnumGamePlayersCallback(ushort param_1, char * param_2, long param_3, void * param_4, dp_playerId_t * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
dpEnumGamePlayersCallback
          (ushort param_1,char *param_2,long param_3,void *param_4,dp_playerId_t *param_5)

{
  if (param_1 == 0xfa01) {
    PlayerList::EndEnum((PlayerList *)&playersInSyncGame);
  }
  else {
    PlayerList::Enum((PlayerList *)&playersInSyncGame,param_5);
  }
  return;
}
