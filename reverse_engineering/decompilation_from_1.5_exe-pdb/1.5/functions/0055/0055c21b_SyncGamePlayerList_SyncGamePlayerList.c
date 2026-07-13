/*
 * Entry: 0055c21b
 * Name: SyncGamePlayerList::SyncGamePlayerList
 * Namespace: SyncGamePlayerList
 * Signature: SyncGamePlayerList * SyncGamePlayerList(SyncGamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SyncGamePlayerList * __thiscall SyncGamePlayerList::SyncGamePlayerList(SyncGamePlayerList *this)

{
  PlayerList::PlayerList((PlayerList *)this);
  this->_padding_ = (int)&_vftable_;
  return this;
}
