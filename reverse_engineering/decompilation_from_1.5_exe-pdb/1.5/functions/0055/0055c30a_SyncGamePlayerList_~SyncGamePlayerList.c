/*
 * Entry: 0055c30a
 * Name: SyncGamePlayerList::~SyncGamePlayerList
 * Namespace: SyncGamePlayerList
 * Signature: void ~SyncGamePlayerList(SyncGamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SyncGamePlayerList::~SyncGamePlayerList(SyncGamePlayerList *this)

{
  this->_padding_ = (int)&PlayerList::_vftable_;
  PlayerList::Clear((PlayerList *)this);
  std::vector<Player_*,std::allocator<Player_*>_>::_Tidy
            ((vector<Player_*,std::allocator<Player_*>_> *)&this->_padding_);
  operator_delete((void *)this->_padding_);
  return;
}
