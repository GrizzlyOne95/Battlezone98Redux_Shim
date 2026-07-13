/*
 * Entry: 00550cfb
 * Name: dpEnumThePlayersCallback
 * Namespace: Global
 * Signature: void dpEnumThePlayersCallback(ushort param_1, char * param_2, long param_3, void * param_4, dp_playerId_t * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
dpEnumThePlayersCallback
          (ushort param_1,char *param_2,long param_3,void *param_4,dp_playerId_t *param_5)

{
  char cVar1;
  int iVar2;
  
  if ((param_3 & 1U) != 0) {
    Net::myPlayerID = param_1;
    iVar2 = (int)player_name - (int)param_2;
    do {
      cVar1 = *param_2;
      param_2[iVar2] = cVar1;
      param_2 = param_2 + 1;
    } while (cVar1 != '\0');
  }
  return;
}
