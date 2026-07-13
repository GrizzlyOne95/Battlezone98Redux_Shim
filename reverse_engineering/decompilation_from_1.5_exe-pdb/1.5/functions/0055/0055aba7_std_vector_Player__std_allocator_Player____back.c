/*
 * Entry: 0055aba7
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::back
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: Player * * back(vector<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::back
          (vector<Player_*,std::allocator<Player_*>_> *this)

{
  Player **ppPVar1;
  _Vector_iterator<Player_*,std::allocator<Player_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<Player_*,std::allocator<Player_*>_>::operator-
                    ((_Vector_iterator<Player_*,std::allocator<Player_*>_> *)&local_c,(int)local_14)
  ;
  ppPVar1 = _Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(_Var2._0_4_);
  return ppPVar1;
}
