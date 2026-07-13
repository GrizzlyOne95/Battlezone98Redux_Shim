/*
 * Entry: 00554f53
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::operator[]
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: Player * * operator[](vector<Player_*,std::allocator<Player_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::operator[]
          (vector<Player_*,std::allocator<Player_*>_> *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
