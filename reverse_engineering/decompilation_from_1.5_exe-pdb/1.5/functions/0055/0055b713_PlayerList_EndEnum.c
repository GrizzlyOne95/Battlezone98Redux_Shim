/*
 * Entry: 0055b713
 * Name: PlayerList::EndEnum
 * Namespace: PlayerList
 * Signature: void EndEnum(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::EndEnum(PlayerList *this)

{
  vector<Player_*,std::allocator<Player_*>_> *this_00;
  Player *this_01;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> _Var1;
  bool bVar2;
  Player **ppPVar3;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
  this_00 = &this->playerV;
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_14,(this->playerV)._Myfirst,(_Container_base_aux *)this_00);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_14,(this->playerV)._Mylast,(_Container_base_aux *)this_00);
  bVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                    (&local_c,&local_14);
  do {
    if (bVar2) {
LAB_0055b7b7:
      this->bInEnum = false;
      return;
    }
    ppPVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_c);
    this_01 = *ppPVar3;
    if (this_01->mark == 0) {
      DeleteListItem(this,this_01->id);
      Player::~Player(this_01);
      operator_delete(this_01);
      _Var1._Myptr = (Player **)local_c._padding_;
      _Var1._padding_ = (int)&local_14;
      std::vector<Player_*,std::allocator<Player_*>_>::erase(this_00,_Var1);
      goto LAB_0055b7b7;
    }
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_14,(this->playerV)._Mylast,(_Container_base_aux *)this_00);
    bVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_c,&local_14);
  } while( true );
}
