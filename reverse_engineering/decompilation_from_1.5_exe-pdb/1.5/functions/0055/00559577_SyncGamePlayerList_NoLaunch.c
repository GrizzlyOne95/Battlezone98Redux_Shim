/*
 * Entry: 00559577
 * Name: SyncGamePlayerList::NoLaunch
 * Namespace: SyncGamePlayerList
 * Signature: void NoLaunch(SyncGamePlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SyncGamePlayerList::NoLaunch(SyncGamePlayerList *this,ushort param_1)

{
  Player *pPVar1;
  
  pPVar1 = PlayerList::FindPlayer((PlayerList *)this,param_1);
  if ((pPVar1 != (Player *)0x0) && (pPVar1->launched != false)) {
    pPVar1->launched = false;
    PlayerList::ModifyListItem((PlayerList *)this,pPVar1);
  }
  return;
}
