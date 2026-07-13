/*
 * Entry: 00558a3e
 * Name: GameSessionList::~GameSessionList
 * Namespace: GameSessionList
 * Signature: void ~GameSessionList(GameSessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameSessionList::~GameSessionList(GameSessionList *this)

{
  *(undefined ***)this = &SessionList::_vftable_;
  std::vector<Session_*,std::allocator<Session_*>_>::_Tidy
            ((vector<Session_*,std::allocator<Session_*>_> *)&this->field_0x14);
  operator_delete(*(void **)&this->field_0x14);
  return;
}
