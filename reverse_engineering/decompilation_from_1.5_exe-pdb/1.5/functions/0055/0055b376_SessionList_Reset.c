/*
 * Entry: 0055b376
 * Name: SessionList::Reset
 * Namespace: SessionList
 * Signature: void Reset(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::Reset(SessionList *this)

{
  Session **ppSVar1;
  
  JoinLobby(this);
  SendMessageA((HWND)this->hList,0x184,0,0);
  while (((int)(this->sessionV)._Mylast - (int)(this->sessionV)._Myfirst & 0xfffffffcU) != 0) {
    ppSVar1 = std::vector<Session_*,std::allocator<Session_*>_>::back(&this->sessionV);
    operator_delete(*ppSVar1);
    std::vector<Session_*,std::allocator<Session_*>_>::pop_back(&this->sessionV);
  }
  return;
}
