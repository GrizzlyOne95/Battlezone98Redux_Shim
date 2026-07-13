/*
 * Entry: 0055959d
 * Name: SyncGamePlayerList::InGame
 * Namespace: SyncGamePlayerList
 * Signature: void InGame(SyncGamePlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SyncGamePlayerList::InGame(SyncGamePlayerList *this,ushort param_1)

{
  Player *pPVar1;
  
  pPVar1 = PlayerList::FindPlayer((PlayerList *)this,param_1);
  if ((pPVar1 != (Player *)0x0) && (pPVar1->InGame == false)) {
    pPVar1->InGame = true;
    PlayerList::ModifyListItem((PlayerList *)this,pPVar1);
  }
  return;
}
