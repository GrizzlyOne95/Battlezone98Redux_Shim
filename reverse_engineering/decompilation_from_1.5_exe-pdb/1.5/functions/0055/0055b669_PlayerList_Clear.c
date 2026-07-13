/*
 * Entry: 0055b669
 * Name: PlayerList::Clear
 * Namespace: PlayerList
 * Signature: void Clear(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::Clear(PlayerList *this)

{
  Player *this_00;
  LRESULT LVar1;
  uint uVar2;
  Player **ppPVar3;
  
  LVar1 = SendMessageA((HWND)this->hList,0x184,0,0);
  this->l = LVar1;
  uVar2 = (int)(this->playerV)._Mylast - (int)(this->playerV)._Myfirst;
  while ((uVar2 & 0xfffffffc) != 0) {
    ppPVar3 = std::vector<Player_*,std::allocator<Player_*>_>::back(&this->playerV);
    this_00 = *ppPVar3;
    if (this_00 != (Player *)0x0) {
      Player::~Player(this_00);
      operator_delete(this_00);
    }
    std::vector<Player_*,std::allocator<Player_*>_>::pop_back(&this->playerV);
    uVar2 = (int)(this->playerV)._Mylast - (int)(this->playerV)._Myfirst;
  }
  Redraw(this);
  return;
}
