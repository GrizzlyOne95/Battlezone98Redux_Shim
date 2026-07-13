/*
 * Entry: 0055ad12
 * Name: ServerList::~ServerList
 * Namespace: ServerList
 * Signature: void ~ServerList(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ServerList::~ServerList(ServerList *this)

{
  Server **ppSVar1;
  vector<Server_*,std::allocator<Server_*>_> *this_00;
  
  this->_padding_ = (int)&_vftable_;
  if (this->iTimerID != 0) {
    KillTimer((HWND)this->hParent,this->iTimerID);
  }
  dpEnumServers(this->dp,0,0,0);
  this_00 = &this->serverV;
  while (((int)(this->serverV)._Mylast - (int)(this->serverV)._Myfirst & 0xfffffffcU) != 0) {
    ppSVar1 = std::vector<Server_*,std::allocator<Server_*>_>::back(this_00);
    operator_delete(*ppSVar1);
    std::vector<Server_*,std::allocator<Server_*>_>::pop_back(this_00);
  }
  std::vector<Server_*,std::allocator<Server_*>_>::_Tidy(this_00);
  operator_delete((void *)this_00->_padding_);
  return;
}
