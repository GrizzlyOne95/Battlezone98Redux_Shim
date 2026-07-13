/*
 * Entry: 00558a5f
 * Name: PlayerList::PlayerList
 * Namespace: PlayerList
 * Signature: PlayerList * PlayerList(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PlayerList * __thiscall PlayerList::PlayerList(PlayerList *this)

{
  this->_padding_ = (int)&_vftable_;
  std::vector<Player_*,std::allocator<Player_*>_>::vector<Player_*,std::allocator<Player_*>_>
            (&this->playerV);
  this->dp = (dp_s *)0x0;
  this->hOutput = (HWND__ *)0x0;
  this->hList = (HWND__ *)0x0;
  this->l = 0;
  this->chat = (Chat *)0x0;
  this->bInEnum = false;
  this->PingHandler = (_func___cdecl_void_short_long_int *)0x0;
  this->dp_karma_unique = 0;
  return this;
}
