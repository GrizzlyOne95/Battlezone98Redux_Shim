/*
 * Entry: 0055c191
 * Name: PlayerList::~PlayerList
 * Namespace: PlayerList
 * Signature: void ~PlayerList(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::~PlayerList(PlayerList *this)

{
  this->_padding_ = (int)&_vftable_;
  Clear(this);
  std::vector<Player_*,std::allocator<Player_*>_>::_Tidy(&this->playerV);
  operator_delete((void *)(this->playerV)._padding_);
  return;
}
