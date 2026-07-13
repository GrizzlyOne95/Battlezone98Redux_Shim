/*
 * Entry: 00558860
 * Name: SessionList::~SessionList
 * Namespace: SessionList
 * Signature: void ~SessionList(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::~SessionList(SessionList *this)

{
  this->_padding_ = (int)&_vftable_;
  std::vector<Session_*,std::allocator<Session_*>_>::_Tidy(&this->sessionV);
  operator_delete((void *)(this->sessionV)._padding_);
  return;
}
