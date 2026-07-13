/*
 * Entry: 005595c3
 * Name: SyncGamePlayerList::HostLaunch
 * Namespace: SyncGamePlayerList
 * Signature: void HostLaunch(SyncGamePlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SyncGamePlayerList::HostLaunch(SyncGamePlayerList *this,ushort param_1)

{
  Player *pPVar1;
  
  pPVar1 = PlayerList::FindPlayer((PlayerList *)this,param_1);
  if (pPVar1 != (Player *)0x0) {
    pPVar1->hostlaunched = true;
    PlayerList::ModifyListItem((PlayerList *)this,pPVar1);
  }
  return;
}
