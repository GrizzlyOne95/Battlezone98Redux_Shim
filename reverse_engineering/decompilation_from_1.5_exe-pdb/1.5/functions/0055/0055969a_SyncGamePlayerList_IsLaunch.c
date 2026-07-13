/*
 * Entry: 0055969a
 * Name: SyncGamePlayerList::IsLaunch
 * Namespace: SyncGamePlayerList
 * Signature: bool IsLaunch(SyncGamePlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SyncGamePlayerList::IsLaunch(SyncGamePlayerList *this,ushort param_1)

{
  bool bVar1;
  Player *pPVar2;
  
  pPVar2 = PlayerList::FindPlayer((PlayerList *)this,param_1);
  if ((pPVar2 == (Player *)0x0) || (pPVar2->launched == false)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}
