/*
 * Entry: 00558768
 * Name: SessionList::SessionList
 * Namespace: SessionList
 * Signature: SessionList * SessionList(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SessionList * __thiscall SessionList::SessionList(SessionList *this)

{
  this->_padding_ = (int)&_vftable_;
  std::vector<Session_*,std::allocator<Session_*>_>::vector<Session_*,std::allocator<Session_*>_>
            (&this->sessionV);
  this->dp = (dp_s *)0x0;
  this->hOutput = (HWND__ *)0x0;
  this->hParentHwnd = (HWND__ *)0x0;
  this->hList = (HWND__ *)0x0;
  this->l = 0;
  this->dp_karma_found = 0;
  this->dp_karma_selected = 0;
  this->optFoundNumber = 0x7fff;
  return this;
}
