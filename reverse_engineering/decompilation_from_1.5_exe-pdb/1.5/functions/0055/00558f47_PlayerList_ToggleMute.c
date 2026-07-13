/*
 * Entry: 00558f47
 * Name: PlayerList::ToggleMute
 * Namespace: PlayerList
 * Signature: bool ToggleMute(PlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PlayerList::ToggleMute(PlayerList *this,ushort param_1)

{
  Player *pPVar1;
  
  pPVar1 = FindPlayer(this,param_1);
  if (pPVar1 != (Player *)0x0) {
    pPVar1->mute = pPVar1->mute == false;
    ModifyListItem(this,pPVar1);
  }
  return pPVar1 != (Player *)0x0;
}
