/*
 * Entry: 00558f1b
 * Name: PlayerList::Mute
 * Namespace: PlayerList
 * Signature: bool Mute(PlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PlayerList::Mute(PlayerList *this,ushort param_1)

{
  bool bVar1;
  Player *pPVar2;
  
  pPVar2 = FindPlayer(this,param_1);
  if ((pPVar2 == (Player *)0x0) || (pPVar2->mute != false)) {
    bVar1 = false;
  }
  else {
    pPVar2->mute = true;
    ModifyListItem(this,pPVar2);
    bVar1 = true;
  }
  return bVar1;
}
