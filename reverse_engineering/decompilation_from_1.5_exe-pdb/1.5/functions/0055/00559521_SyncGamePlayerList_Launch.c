/*
 * Entry: 00559521
 * Name: SyncGamePlayerList::Launch
 * Namespace: SyncGamePlayerList
 * Signature: void Launch(SyncGamePlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SyncGamePlayerList::Launch(SyncGamePlayerList *this,ushort param_1)

{
  Player *pPVar1;
  char *pcVar2;
  
  pPVar1 = PlayerList::FindPlayer((PlayerList *)this,param_1);
  if (pPVar1 == (Player *)0x0) {
    return;
  }
  if (pPVar1->launched == false) {
    if ((validVehicles == (char *)0x0) ||
       ((pPVar1->blob[1] != '\0' &&
        (pcVar2 = strstr(validVehicles,pPVar1->blob + 1), pcVar2 != (char *)0x0)))) {
      pPVar1->launched = true;
    }
    else {
      Net_KickPlayer(param_1);
    }
    PlayerList::ModifyListItem((PlayerList *)this,pPVar1);
    return;
  }
  return;
}
