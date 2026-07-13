/*
 * Entry: 00555e20
 * Name: PlayerList::GetPlayer
 * Namespace: PlayerList
 * Signature: Player * GetPlayer(PlayerList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player * __thiscall PlayerList::GetPlayer(PlayerList *this,int param_1)

{
  Player **ppPVar1;
  
  ppPVar1 = std::vector<Player_*,std::allocator<Player_*>_>::operator[](&this->playerV,param_1);
  return *ppPVar1;
}
