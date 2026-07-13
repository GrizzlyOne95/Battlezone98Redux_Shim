/*
 * Entry: 0055cad2
 * Name: dpEnumPlayersCallback
 * Namespace: Global
 * Signature: void dpEnumPlayersCallback(ushort param_1, char * param_2, long param_3, void * param_4, dp_playerId_t * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
dpEnumPlayersCallback
          (ushort param_1,char *param_2,long param_3,void *param_4,dp_playerId_t *param_5)

{
  GamePlayerList *pGVar1;
  
  if (param_2 == (char *)0x0) {
    if (people_state == 1) {
      people_state = 2;
      pGVar1 = (GamePlayerList *)&playersInRoom;
    }
    else {
      if (people_state != 3) {
        return;
      }
      people_state = 4;
      pGVar1 = &playersInGame;
    }
    PlayerList::EndEnum((PlayerList *)pGVar1);
  }
  else {
    if (people_state == 1) {
      pGVar1 = (GamePlayerList *)&playersInRoom;
    }
    else {
      if (people_state != 3) {
        return;
      }
      pGVar1 = &playersInGame;
    }
    PlayerList::Enum((PlayerList *)pGVar1,param_5);
  }
  return;
}
