/*
 * Entry: 0055acdc
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::_Umove<Player_*_*>
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: Player * * _Umove<Player_*_*>(vector<Player_*,std::allocator<Player_*>_> * this, Player * * param_1, Player * * param_2, Player * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::_Umove<Player_*_*>
          (vector<Player_*,std::allocator<Player_*>_> *this,Player **param_1,Player **param_2,
          Player **param_3)

{
  Player **ppPVar1;
  
  ppPVar1 = stdext::unchecked_uninitialized_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>
                      (param_1,param_2,param_3,(allocator<Player_*> *)&this->_padding_);
  return ppPVar1;
}
