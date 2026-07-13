/*
 * Entry: 0055c1fa
 * Name: GamePlayerList::~GamePlayerList
 * Namespace: GamePlayerList
 * Signature: void ~GamePlayerList(GamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GamePlayerList::~GamePlayerList(GamePlayerList *this)

{
  *(undefined ***)this = &PlayerList::_vftable_;
  PlayerList::Clear((PlayerList *)this);
  std::vector<Player_*,std::allocator<Player_*>_>::_Tidy
            ((vector<Player_*,std::allocator<Player_*>_> *)&this->field_0x14);
  operator_delete(*(void **)&this->field_0x14);
  return;
}
